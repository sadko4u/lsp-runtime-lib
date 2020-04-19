/*
 * inaudiofilestream.cpp
 *
 *  Created on: 19 апр. 2020 г.
 *      Author: sadko
 */

#include <lsp-plug.in/test-fw/utest.h>
#include <lsp-plug.in/test-fw/ByteBuffer.h>
#include <lsp-plug.in/test-fw/FloatBuffer.h>
#include <lsp-plug.in/mm/InAudioFileStream.h>
#include <lsp-plug.in/stdlib/math.h>

#define BUF_SAMPLES     127
#define FRAMES          2048

/* Code to generate audio file
#include <stdio.h>
#include <sndfile.h>
#include <math.h>

#define FRAMES 2048

int main()
{
    SF_INFO sf_info;
    SNDFILE *sf_obj;

    sf_info.frames      = FRAMES;
    sf_info.samplerate  = 48000;
    sf_info.channels    = 2;
    sf_info.format      = SF_FORMAT_WAV | SF_FORMAT_PCM_16 | SF_ENDIAN_LITTLE;
    sf_info.sections    = 0;
    sf_info.seekable    = 0;

    // Open sound file
    if ((sf_obj = sf_open("pcm.wav", SFM_WRITE, &sf_info)) == NULL)
        return -1;

    float delta = (8 * M_PI) / FRAMES;
    float buf[2 * FRAMES];
    float *dst = buf;
    for (size_t i=0; i<FRAMES; ++i, dst += 2)
    {
        dst[0] = sinf(i * delta);
        dst[1] = cosf(i * delta);
    }

    sf_writef_float(sf_obj, buf, FRAMES);
    sf_close(sf_obj);
}
 */

UTEST_BEGIN("runtime.mm", inaudiofilestream)

    void test_read_f32(const char *file)
    {
        io::Path path;

        UTEST_ASSERT(path.fmt("%s/%s", resources(), file));
        printf("Reading PCM audio file %s as floating-point samples\n", path.as_native());

        mm::InAudioFileStream is;
        mm::audio_stream_t info;

        UTEST_ASSERT(is.open(&path) == STATUS_OK);
        UTEST_ASSERT(is.info(&info) == STATUS_OK);
        UTEST_ASSERT(info.srate == 48000);
        UTEST_ASSERT(info.channels == 2);
        UTEST_ASSERT(info.frames == FRAMES);

        FloatBuffer buf(BUF_SAMPLES * 2);
        float delta = (8 * M_PI) / FRAMES;
        ssize_t off = 0;

        while (true)
        {
            // Check position
            UTEST_ASSERT(is.position() == off);

            // Read frames
            ssize_t read = is.read(buf.data(), BUF_SAMPLES);
            if (read < 0)
            {
                UTEST_ASSERT(read == -STATUS_EOF);
                break;
            }
            UTEST_ASSERT(buf.valid());

            // Check contents
            float *ptr = buf.data();
            for (ssize_t i=0; i<read; ++i, ++off, ptr += 2)
            {
                float s = sinf(delta * off);
                float c = cosf(delta * off);
                UTEST_ASSERT_MSG(float_equals_absolute(s, ptr[0], 8e-5), "Samples for channel 0[%d] differ: exp=%e, act=%e", int(off), s, ptr[0]);
                UTEST_ASSERT_MSG(float_equals_absolute(c, ptr[1], 8e-5), "Samples for channel 1[%d] differ: exp=%e, act=%e", int(off), c, ptr[1]);
            }
        }

        UTEST_ASSERT(is.close() == STATUS_OK);
    }

    void test_read_s16(const char *file)
    {
        io::Path path;

        UTEST_ASSERT(path.fmt("%s/%s", resources(), file));
        printf("Reading PCM audio file %s as s16 samples\n", path.as_native());

        mm::InAudioFileStream is;
        mm::audio_stream_t info;

        UTEST_ASSERT(is.open(&path) == STATUS_OK);
        UTEST_ASSERT(is.info(&info) == STATUS_OK);
        UTEST_ASSERT(info.srate == 48000);
        UTEST_ASSERT(info.channels == 2);
        UTEST_ASSERT(info.frames == FRAMES);

        ByteBuffer buf(BUF_SAMPLES * sizeof(int16_t) * 2);
        float delta = (8 * M_PI) / FRAMES;
        ssize_t off = 0;

        while (true)
        {
            // Check position
            UTEST_ASSERT(is.position() == off);

            // Read frames
            ssize_t read = is.read(buf.data<int16_t>(), BUF_SAMPLES);
            if (read < 0)
            {
                UTEST_ASSERT(read == -STATUS_EOF);
                break;
            }
            UTEST_ASSERT(buf.valid());

            // Check contents
            int16_t *ptr = buf.data<int16_t>();
            for (ssize_t i=0; i<read; ++i, ++off, ptr += 2)
            {
                int16_t s = int16_t(int32_t(sinf(delta * off)*32767 + 32767.5) - 32767);
                int16_t c = int16_t(int32_t(cosf(delta * off)*32767 + 32767.5) - 32767);
                UTEST_ASSERT_MSG(float_equals_absolute(s, ptr[0], 2.0f), "Samples for channel 0[%d] differ: exp=%d, act=%d", int(off), int(s), int(ptr[0]));
                UTEST_ASSERT_MSG(float_equals_absolute(c, ptr[1], 2.0f), "Samples for channel 1[%d] differ: exp=%d, act=%d", int(off), int(c), int(ptr[1]));
            }
        }

        UTEST_ASSERT(is.close() == STATUS_OK);
    }

    void test_read_u16(const char *file)
    {
        io::Path path;

        UTEST_ASSERT(path.fmt("%s/%s", resources(), file));
        printf("Reading PCM audio file %s as u16 samples\n", path.as_native());

        mm::InAudioFileStream is;
        mm::audio_stream_t info;

        UTEST_ASSERT(is.open(&path) == STATUS_OK);
        UTEST_ASSERT(is.info(&info) == STATUS_OK);
        UTEST_ASSERT(info.srate == 48000);
        UTEST_ASSERT(info.channels == 2);
        UTEST_ASSERT(info.frames == FRAMES);

        ByteBuffer buf(BUF_SAMPLES * sizeof(uint16_t) * 2);
        float delta = (8 * M_PI) / FRAMES;
        ssize_t off = 0;

        while (true)
        {
            // Check position
            UTEST_ASSERT(is.position() == off);

            // Read frames
            ssize_t read = is.read(buf.data<uint16_t>(), BUF_SAMPLES);
            if (read < 0)
            {
                UTEST_ASSERT(read == -STATUS_EOF);
                break;
            }
            UTEST_ASSERT(buf.valid());

            // Check contents
            uint16_t *ptr = buf.data<uint16_t>();
            for (ssize_t i=0; i<read; ++i, ++off, ptr += 2)
            {
                uint16_t s = uint16_t(sinf(delta * off)*32767 + 32767.5);
                uint16_t c = uint16_t(cosf(delta * off)*32767 + 32767.5);
                UTEST_ASSERT_MSG(float_equals_absolute(s, ptr[0], 2.0f), "Samples for channel 0[%d] differ: exp=%d, act=%d", int(off), int(s), int(ptr[0]));
                UTEST_ASSERT_MSG(float_equals_absolute(c, ptr[1], 2.0f), "Samples for channel 1[%d] differ: exp=%d, act=%d", int(off), int(c), int(ptr[1]));
            }
        }

        UTEST_ASSERT(is.close() == STATUS_OK);
    }

    UTEST_MAIN
    {
        test_read_f32("mm/pcm.wav");
        test_read_s16("mm/pcm.wav");
        test_read_u16("mm/pcm.wav");
    }
UTEST_END;


