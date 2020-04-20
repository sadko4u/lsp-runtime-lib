/*
 * OutStream.cpp
 *
 *  Created on: 16 апр. 2020 г.
 *      Author: sadko
 */

#include <lsp-plug.in/mm/IOutAudioStream.h>
#include <lsp-plug.in/mm/sample.h>
#include <lsp-plug.in/common/alloc.h>
#include <lsp-plug.in/stdlib/string.h>
#include <stdlib.h>

namespace lsp
{
    namespace mm
    {
        
        IOutAudioStream::IOutAudioStream()
        {
            nOffset             = -1;
            pBuffer             = NULL;
            nBufSize            = 0;
            nErrorCode          = STATUS_CLOSED;
            sFormat.srate       = 0;
            sFormat.channels    = 0;
            sFormat.frames      = -1;
            sFormat.format      = SFMT_NONE;
        }
        
        IOutAudioStream::~IOutAudioStream()
        {
            do_close();
        }

        void IOutAudioStream::do_close()
        {
            if (pBuffer != NULL)
            {
                ::free(pBuffer);
                pBuffer = NULL;
            }
            nOffset = -1;
        }
    
        status_t IOutAudioStream::ensure_capacity(size_t bytes)
        {
            // Not enough space in temporary buffer?
            if (nBufSize >= bytes)
                return STATUS_OK;

            // Perform buffer re-allocation
            bytes           = align_size(bytes, 0x200);
            uint8_t *buf    = static_cast<uint8_t *>(::realloc(pBuffer, bytes));
            if (buf == NULL)
                return set_error(STATUS_NO_MEM);
            pBuffer         = buf;
            nBufSize        = bytes;

            return STATUS_OK;
        }

        ssize_t IOutAudioStream::direct_write(const void *src, size_t nframes, size_t fmt)
        {
            return -STATUS_NOT_IMPLEMENTED;
        }

        ssize_t IOutAudioStream::conv_write(const void *src, size_t nframes, size_t fmt)
        {
            if (nOffset < 0)
                return -set_error(STATUS_CLOSED);

            size_t rsize    = sformat_size_of(fmt) * sFormat.channels;
            if (rsize <= 0)
                return -set_error(STATUS_BAD_FORMAT);

            size_t afmt     = select_format(fmt);
            size_t fsize    = sformat_size_of(afmt) * sFormat.channels;
            if (fsize <= 0)
                return -set_error(STATUS_UNSUPPORTED_FORMAT);

            // Perform conversion loop
            const uint8_t *sptr = static_cast<const uint8_t *>(src);
            size_t nwritten = 0;

            while (nframes > 0)
            {
                size_t to_write = (nframes > IO_BUF_SIZE) ? IO_BUF_SIZE : nframes;

                // Need to perform encoding?
                if (afmt != fmt)
                {
                    // Check that we have enough place
                    size_t atotal = to_write * fsize;
                    size_t rtotal = to_write * rsize;
                    if (!ensure_capacity(to_write * (fsize + rsize)))
                        return -set_error(STATUS_NO_MEM);

                    // Perform conversion
                    ::memcpy(&pBuffer[atotal], src, rtotal);
                    if (!convert_samples(pBuffer, &pBuffer[atotal], to_write * sFormat.channels, afmt, fmt))
                        return -set_error(STATUS_UNSUPPORTED_FORMAT);
                    src = pBuffer;
                }
                else
                    src = sptr;

                // Call direct write
                ssize_t written = direct_write(src, to_write, afmt);
                if (written < 0)
                {
                    if (nwritten > 0)
                        break;
                    set_error(-written);
                    return written;
                }

                // Update pointers
                nwritten   += written;
                nframes    -= written;
                sptr       += fsize * written;
            }

            set_error(STATUS_OK);
            return nwritten;
        }

        size_t IOutAudioStream::select_format(size_t rfmt)
        {
            return 0;
        }

        status_t IOutAudioStream::info(audio_stream_t *dst) const
        {
            if (dst == NULL)
                return STATUS_BAD_ARGUMENTS;
            *dst    = sFormat;
            return STATUS_OK;
        }

        status_t IOutAudioStream::flush()
        {
            return set_error(STATUS_OK);
        }

        status_t IOutAudioStream::close()
        {
            do_close();
            return set_error(STATUS_OK);
        }

        wssize_t IOutAudioStream::position()
        {
            return (nOffset >= 0) ? nOffset : -set_error(STATUS_CLOSED);
        }

        wssize_t IOutAudioStream::seek(wsize_t nframes)
        {
            return -set_error(STATUS_NOT_SUPPORTED);
        }

        ssize_t IOutAudioStream::write(const uint8_t *dst, size_t nframes)
        {
            return conv_write(dst, nframes, SFMT_U8 | SFMT_CPU);
        }

        ssize_t IOutAudioStream::write(const int8_t *dst, size_t nframes)
        {
            return conv_write(dst, nframes, SFMT_S8 | SFMT_CPU);
        }

        ssize_t IOutAudioStream::write(const uint16_t *dst, size_t nframes)
        {
            return conv_write(dst, nframes, SFMT_U16 | SFMT_CPU);
        }

        ssize_t IOutAudioStream::write(const int16_t *dst, size_t nframes)
        {
            return conv_write(dst, nframes, SFMT_S16 | SFMT_CPU);
        }

        ssize_t IOutAudioStream::write(const uint32_t *dst, size_t nframes)
        {
            return conv_write(dst, nframes, SFMT_U32 | SFMT_CPU);
        }

        ssize_t IOutAudioStream::write(const int32_t *dst, size_t nframes)
        {
            return conv_write(dst, nframes, SFMT_S32 | SFMT_CPU);
        }

        ssize_t IOutAudioStream::write(const f32_t *dst, size_t nframes)
        {
            return conv_write(dst, nframes, SFMT_F32 | SFMT_CPU);
        }

        ssize_t IOutAudioStream::write(const f64_t *dst, size_t nframes)
        {
            return conv_write(dst, nframes, SFMT_F64 | SFMT_CPU);
        }
    } /* namespace mm */
} /* namespace lsp */
