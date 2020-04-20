/*
 * IObjHandler.cpp
 *
 *  Created on: 21 апр. 2017 г.
 *      Author: sadko
 */

#include <lsp-plug.in/fmt/obj/IObjHandler.h>

namespace lsp
{
    namespace obj
    {
        IObjHandler::~IObjHandler()
        {
        }

        status_t IObjHandler::begin_object(const char *name)
        {
            return STATUS_OK;
        }

        status_t IObjHandler::begin_object(const LSPString *name)
        {
            return begin_object(name->get_utf8());
        }

        status_t IObjHandler::end_object()
        {
            return STATUS_OK;
        }

        status_t IObjHandler::end_of_data()
        {
            return STATUS_OK;
        }

        ssize_t IObjHandler::add_vertex(float x, float y, float z)
        {
            return 0;
        }

        ssize_t IObjHandler::add_param_vertex(float x, float y, float z)
        {
            return 0;
        }

        ssize_t IObjHandler::add_normal(float dx, float dy, float dz)
        {
            return 0;
        }

        ssize_t IObjHandler::add_texture_vertex(float u, float v)
        {
            return 0;
        }

        status_t IObjHandler::add_face(const size_t *vv, const size_t *vn, const size_t *vt, size_t n)
        {
            return STATUS_OK;
        }

        status_t IObjHandler::add_points(const size_t *vv, size_t n)
        {
            return STATUS_OK;
        }

        status_t IObjHandler::add_line(const size_t *vv, const size_t *vt, size_t n)
        {
            return STATUS_OK;
        }
    }
} /* namespace lsp */
