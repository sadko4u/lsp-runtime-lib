/*
 * InFileStream.h
 *
 *  Created on: 13 мар. 2019 г.
 *      Author: sadko
 */

#ifndef LSP_PLUG_IN_IO_INFILESTREAM_H_
#define LSP_PLUG_IN_IO_INFILESTREAM_H_

#include <lsp-plug.in/runtime/version.h>
#include <lsp-plug.in/runtime/LSPString.h>
#include <lsp-plug.in/stdlib/stdio.h>
#include <lsp-plug.in/io/File.h>
#include <lsp-plug.in/io/Path.h>
#include <lsp-plug.in/io/IInStream.h>

namespace lsp
{
    namespace io
    {
        
        class InFileStream: public IInStream
        {
            protected:
                File           *pFD;
                size_t          nWrapFlags;

            private:
                InFileStream & operator = (const InFileStream &);

            public:
                explicit InFileStream();
                virtual ~InFileStream();

            public:
                /** Wrap stdio file descriptor. The Reader should be in closed state.
                 *
                 * @param fd file descriptor
                 * @param close close file descriptor on close()
                 * @return status of operation
                 */
                status_t wrap(FILE *fd, bool close);

                /** Wrap native file descriptor. The Reader should be in closed state.
                 *
                 * @param fd file descriptor
                 * @param close close file descriptor on close()
                 * @return status of operation
                 */
                status_t wrap_native(fhandle_t fd, bool close);

                /** Wrap file descriptor. The Reader should be in closed state.
                 *
                 * @param fd file descriptor
                 * @param flags wrapping flags
                 * @return status of operation
                 */
                status_t wrap(File *fd, size_t flags);

                /** Open input stream associated with file. The Reader should be in closed state.
                 *
                 * @param path file location path
                 * @return status of operation
                 */
                status_t open(const char *path);

                /** Open input stream associated with file. The Reader should be in closed state.
                 *
                 * @param path file location path
                 * @return status of operation
                 */
                status_t open(const LSPString *path);

                /** Open input stream associated with file. Before open currently open stream is closed and it's
                 * state is reset.
                 *
                 * @param path file location path
                 * @return status of operation
                 */
                status_t open(const Path *path);

                virtual wssize_t    avail();

                virtual wssize_t    position();

                virtual ssize_t     read(void *dst, size_t count);

                virtual wssize_t    seek(wsize_t position);

                virtual wssize_t    skip(wsize_t amount);

                virtual status_t    close();
        };
    
    } /* namespace io */
} /* namespace lsp */

#endif /* LSP_PLUG_IN_IO_INFILESTREAM_H_ */