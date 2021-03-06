/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-runtime-lib
 * Created on: 27 янв. 2016 г.
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

#ifndef CORE_NATIVEEXECUTOR_H_
#define CORE_NATIVEEXECUTOR_H_

#include <lsp-plug.in/runtime/version.h>
#include <lsp-plug.in/common/atomic.h>
#include <lsp-plug.in/ipc/Thread.h>
#include <lsp-plug.in/ipc/IExecutor.h>
#include <lsp-plug.in/ipc/ITask.h>

namespace lsp
{
    namespace ipc
    {
        class NativeExecutor: public IExecutor
        {
            private:
                Thread              hThread;
                ITask              *pHead;
                ITask              *pTail;
                atomic_t            nLock;

                static status_t     execute(void *params);
                void    run();

            private:
                NativeExecutor &operator = (const NativeExecutor &src); // Deny copying

            public:
                explicit NativeExecutor();
                virtual ~NativeExecutor();

            public:
                status_t start();

                virtual bool submit(ITask *task);

                virtual void shutdown();
        };
    }
}

#endif /* CORE_NATIVEEXECUTOR_H_ */
