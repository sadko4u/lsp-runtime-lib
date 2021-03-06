/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-runtime-lib
 * Created on: 19 апр. 2020 г.
 *
 * lsp-runtime-lib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * lsp-runtime-lib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with lsp-runtime-lib. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef LSP_PLUG_IN_MM_INAUDIOFILESTREAM_H_
#define LSP_PLUG_IN_MM_INAUDIOFILESTREAM_H_

#include <lsp-plug.in/runtime/version.h>
#include <lsp-plug.in/runtime/LSPString.h>
#include <lsp-plug.in/io/Path.h>
#include <lsp-plug.in/mm/IInAudioStream.h>

#ifdef USE_LIBSNDFILE
    #include <sndfile.h>
#else
    #include <mmsystem.h>
    #include <mmreg.h>
    #include <msacm.h>
#endif

namespace lsp
{
    namespace mm
    {
    #ifndef USE_LIBSNDFILE
        class ACMStream;
        class MMIOReader;
    #endif /* USE_LIBSNDFILE */

        class InAudioFileStream: public IInAudioStream
        {
            private:
                InAudioFileStream & operator = (const InAudioFileStream &);

            protected:
                // Platform-specific parameters
            #ifdef USE_LIBSNDFILE
                SNDFILE            *hHandle;
            #else
                MMIOReader         *pMMIO;
                ACMStream          *pACM;
                WAVEFORMATEX       *pFormat;
            #endif

                // Common parameters
                bool                bSeekable;

            protected:
            #ifdef USE_LIBSNDFILE
                static status_t     decode_sf_error(SNDFILE *fd);
            #else
                static ssize_t      decode_sample_format(WAVEFORMATEX *wfe);
                ssize_t             read_acm_convert(void *dst, size_t nframes, size_t fmt);
            #endif

                virtual ssize_t     direct_read(void *dst, size_t nframes, size_t fmt);

                virtual size_t      select_format(size_t fmt);

                status_t            close_handle();

            public:
                explicit InAudioFileStream();
                virtual ~InAudioFileStream();

            public:
                /**
                 * Open audio stream
                 * @param path path to the audio file
                 * @return status of operation
                 */
                virtual status_t    open(const char *path);

                /**
                 * Open audio stream
                 * @param path path to the audio file
                 * @return status of operation
                 */
                virtual status_t    open(const LSPString *path);

                /**
                 * Open audio stream
                 * @param path path to the audio file
                 * @return status of operation
                 */
                virtual status_t    open(const io::Path *path);

                virtual status_t    close();

                virtual wssize_t    skip(wsize_t nframes);

                virtual wssize_t    seek(wsize_t nframes);
        };
    
    } /* namespace mm */
} /* namespace lsp */

#endif /* LSP_PLUG_IN_MM_INAUDIOFILESTREAM_H_ */
