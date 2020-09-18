/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-runtime-lib
 * Created on: 14 июн. 2018 г.
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

#ifndef LSP_PLUG_IN_IO_IINSEQUENCE_H_
#define LSP_PLUG_IN_IO_IINSEQUENCE_H_

#include <lsp-plug.in/runtime/version.h>
#include <lsp-plug.in/common/types.h>
#include <lsp-plug.in/common/status.h>
#include <lsp-plug.in/runtime/LSPString.h>
#include <iconv.h>

namespace lsp
{
    namespace io
    {
        class IInSequence
        {
            protected:
                status_t        nErrorCode;

            protected:
                inline status_t set_error(status_t error) { return nErrorCode = error; }

            private:
                IInSequence & operator = (const IInSequence &);

            public:
                explicit IInSequence();
                virtual ~IInSequence();

            public:
                /**
                 * Return last error code
                 * @return last error code
                 */
                inline status_t last_error() const  { return nErrorCode; };

                /**
                 * Read amount of characters
                 * @param dst target buffer to read
                 * @param count number of characters to read
                 * @return actual number of characters read or negative value on end of stream
                 */
                virtual ssize_t     read(lsp_wchar_t *dst, size_t count);

                /**
                 * Read single character
                 * @return code of single character or negative value on end of stream
                 */
                virtual lsp_swchar_t    read();

                /**
                 * Read single line
                 * @param s string to store value
                 * @return status of operation
                 */
                virtual status_t    read_line(LSPString *s, bool force = false);

                /**
                 * Skip amount of characters
                 * @param count number of characters to skip
                 * @return number of skipped characters or negative error code
                 */
                virtual ssize_t     skip(size_t count);

                /**
                 * Close input stream
                 * @return status of operation
                 */
                virtual status_t    close();
        };
    }
    
} /* namespace lsp */

#endif /* LSP_PLUG_IN_IO_IINSEQUENCE_H_ */
