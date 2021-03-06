/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-runtime-lib
 * Created on: 05 нояб. 2015 г.
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

#ifndef LSP_PLUG_IN_RUNTIME_COLOR_H_
#define LSP_PLUG_IN_RUNTIME_COLOR_H_

#include <lsp-plug.in/common/types.h>
#include <lsp-plug.in/common/status.h>
#include <lsp-plug.in/runtime/LSPString.h>

namespace lsp
{
    class Color
    {
        protected:
            enum mask_t
            {
                M_RGB           = 1 << 0,
                M_HSL           = 1 << 1
            };

            mutable float   R, G, B;
            mutable float   H, S, L;
            mutable size_t  nMask;
            mutable float   A;

            void            calc_rgb() const;
            void            calc_hsl() const;

        protected:
            inline Color(float r, float g, float b, size_t mask): R(r), G(g), B(b), H(0), S(0), L(0), nMask(mask), A(0) {};

            void            check_rgb() const;
            void            check_hsl() const;

            static status_t parse(float *dst, size_t n, char prefix, const char *src, size_t len);
            static ssize_t  format(char *dst, size_t len, size_t tolerance, const float *v, char prefix, bool alpha);

        public:
            inline Color(): R(0), G(0), B(0), H(0), S(0), L(0), nMask(M_RGB), A(0) {};
            inline Color(float r, float g, float b): R(r), G(g), B(b), H(0), S(0), L(0), nMask(M_RGB), A(0) {};
            inline Color(float r, float g, float b, float a): R(r), G(g), B(b), H(0), S(0), L(0), nMask(M_RGB), A(a) {};
            inline Color(const Color &src): R(src.R), G(src.G), B(src.B), H(src.H), S(src.S), L(src.L), nMask(src.nMask), A(src.A) {};
            inline Color(const Color &src, float a): R(src.R), G(src.G), B(src.B), H(src.H), S(src.S), L(src.L), nMask(src.nMask), A(a) {};
            inline Color(const Color *src): R(src->R), G(src->G), B(src->B), H(src->H), S(src->S), L(src->L), nMask(src->nMask), A(src->A) {};
            inline Color(const Color *src, float a): R(src->R), G(src->G), B(src->B), H(src->H), S(src->S), L(src->L), nMask(src->nMask), A(a) {};
            explicit Color(uint32_t rgb);
            explicit Color(uint32_t rgb, float a);

            inline float    red() const        { check_rgb(); return R; }
            inline float    green() const      { check_rgb(); return G; }
            inline float    blue() const       { check_rgb(); return B; }
            inline float    alpha() const      { return A;              }

            inline void     red(float r)        { check_rgb(); R = r; nMask = M_RGB; };
            inline void     green(float g)      { check_rgb(); G = g; nMask = M_RGB; };
            inline void     blue(float b)       { check_rgb(); B = b; nMask = M_RGB; };
            inline void     alpha(float a)      { A = a; };

            inline void     get_rgb(float &r, float &g, float &b) const { check_rgb(); r = R; g = G; b = B; }
            inline void     get_rgba(float &r, float &g, float &b, float &a) const { check_rgb(); r = R; g = G; b = B; a = A; }

            inline void     set_rgb(float r, float g, float b)
            {
                nMask = M_RGB;
                R = r;
                G = g;
                B = b;
            }

            inline void     set_rgba(float r, float g, float b, float a)
            {
                nMask = M_RGB;
                R = r;
                G = g;
                B = b;
                A = a;
            }

            inline float    hue() const        { check_hsl(); return H; }
            inline float    saturation() const { check_hsl(); return S; }
            inline float    lightness() const  { check_hsl(); return L; }

            inline void     hue(float h)        { check_hsl(); H = h; nMask = M_HSL;  };
            inline void     saturation(float s) { check_hsl(); S = s; nMask = M_HSL;  };
            inline void     lightness(float l)  { check_hsl(); L = l; nMask = M_HSL;  };

            inline void     get_hsl(float &h, float &s, float &l) const { check_hsl(); h = H; s = S; l = L; }
            inline void     get_hsla(float &h, float &s, float &l, float &a) const { check_hsl(); h = H; s = S; l = L; a = A; }

            inline void     set_hsl(float h, float s, float l)
            {
                nMask   = M_HSL;
                H = h;
                S = s;
                L = l;
            }
            inline void     set_hsla(float h, float s, float l, float a)
            {
                nMask   = M_HSL;
                H = h;
                S = s;
                L = l;
                A = a;
            }

            void            blend(const Color &c, float alpha);
            void            blend(float r, float g, float b, float alpha);
            void            darken(float amount);
            void            lighten(float amount);
            void            blend(const Color &c1, const Color &c2, float alpha);

            void            copy(const Color &c);
            void            copy(const Color *c);

            void            copy(const Color &c, float a);
            void            copy(const Color *c, float a);

            uint32_t        rgb24() const;
            uint32_t        hsl24() const;
            uint32_t        rgba32() const;
            uint32_t        hsla32() const;

            inline bool     is_rgb() const      { return nMask & M_RGB; }
            inline bool     is_hsl() const      { return nMask & M_HSL; }

            // Setting
            void            set_rgb24(uint32_t v);
            void            set_rgba32(uint32_t v);
            void            set_hsl24(uint32_t v);
            void            set_hsla32(uint32_t v);

            // Formatting
            ssize_t         format_rgb(char *dst, size_t len, size_t tolerance = 2) const;
            ssize_t         format_hsl(char *dst, size_t len, size_t tolerance = 2) const;
            ssize_t         format_rgba(char *dst, size_t len, size_t tolerance = 2) const;
            ssize_t         format_hsla(char *dst, size_t len, size_t tolerance = 2) const;

            // Parsing raw data
            status_t        parse3(const char *src, size_t len);
            status_t        parse3(const char *src);
            status_t        parse_rgb(const char *src, size_t len);
            status_t        parse_hsl(const char *src, size_t len);
            status_t        parse_rgb(const char *src);
            status_t        parse_hsl(const char *src);

            status_t        parse4(const char *src, size_t len);
            status_t        parse4(const char *src);
            status_t        parse_rgba(const char *src, size_t len);
            status_t        parse_hsla(const char *src, size_t len);
            status_t        parse_rgba(const char *src);
            status_t        parse_hsla(const char *src);

            // Parsing LSPString
            inline status_t parse3(const LSPString *src, size_t len)        { return parse3(src->get_utf8(0, len));         }
            inline status_t parse3(const LSPString *src)                    { return parse3(src->get_utf8());               }
            status_t        parse_rgb(const LSPString *src, size_t len)     { return parse_rgb(src->get_utf8(0, len));      }
            status_t        parse_hsl(const LSPString *src, size_t len)     { return parse_hsl(src->get_utf8(0, len));      }
            status_t        parse_rgb(const LSPString *src)                 { return parse_rgb(src->get_utf8());            }
            status_t        parse_hsl(const LSPString *src)                 { return parse_hsl(src->get_utf8());            }

            inline status_t parse4(const LSPString *src, size_t len)        { return parse4(src->get_utf8(0, len));         }
            inline status_t parse4(const LSPString *src)                    { return parse4(src->get_utf8());               }
            status_t        parse_rgba(const LSPString *src, size_t len)    { return parse_rgba(src->get_utf8(0, len));     }
            status_t        parse_hsla(const LSPString *src, size_t len)    { return parse_hsla(src->get_utf8(0, len));     }
            status_t        parse_rgba(const LSPString *src)                { return parse_rgba(src->get_utf8());           }
            status_t        parse_hsla(const LSPString *src)                { return parse_hsla(src->get_utf8());           }

        public:
            void            scale_lightness(float amount);
            void            swap(Color *src);
    };

} /* namespace lsp */

#endif /* LSP_PLUG_IN_RUNTIME_COLOR_H_ */
