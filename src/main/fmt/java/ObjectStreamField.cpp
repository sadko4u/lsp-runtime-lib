/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-runtime-lib
 * Created on: 30 авг. 2019 г.
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

#include <lsp-plug.in/fmt/java/Object.h>
#include <lsp-plug.in/fmt/java/ObjectStreamField.h>
#include <stdlib.h>

namespace lsp
{
    namespace java
    {
        const char *ObjectStreamField::CLASS_NAME    = "java.io.ObjectStreamField";
        
        ObjectStreamField::ObjectStreamField(): Object(CLASS_NAME)
        {
            enType      = JFT_UNKNOWN;
            pSignature  = NULL;
            nOffset     = 0;
            sRawName    = NULL;
        }
        
        ObjectStreamField::~ObjectStreamField()
        {
            pSignature  = NULL;
            if (sRawName != NULL)
                ::free(sRawName);
            sRawName    = NULL;
        }

    } /* namespace java */
} /* namespace lsp */
