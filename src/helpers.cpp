//  Copyright (c) 2014-2017 Andrey Upadyshev <oliora@gmail.com>
//
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "ppconsul/helpers.h"
#include "s11n.h"

#include <boost/beast/core/detail/base64.hpp>

namespace ppconsul { namespace helpers {

    namespace {
        inline bool is_char_unsafe(char c)
        {
            switch (c)
            {
                // Reserved characters
                case '!': case '#': case '$': case '&': case '\'':
                case '(': case ')': case '*': case '+': case ',':
                case '/': case ':': case ';': case '=': case '?':
                case '@': case '[': case ']':
                // Other characters
                case '\x20': case '\x7F':
                case '"': case '%' : /*case '-':*/ /*case '.':*/ case '<':
                case '>': case '\\': case '^': /*case '_':*/ case '`':
                case '{': case '|' : case '}': /*case '~':*/
                    return true;
                default:
                    return static_cast<unsigned char>(c) < 0x20 || static_cast<unsigned char>(c) >= 0x80;
            }
        }

        inline char to_hex(unsigned char c)
        {
            char table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
            return table[c];
        }
    }

    std::string decodeBase64(const std::string& s)
    {
        std::string r;
        if (s.empty())
            return r;
        return std::move(boost::beast::detail::base64_decode(s));
    }

    std::string encodeBase64(const std::string &s)
    {
        std::string r;
        if (s.empty())
            return r;
        return std::move(boost::beast::detail::base64_encode(s));
    }

    std::string encodeUrl(const std::string&s)
    {
        std::string r;
        r.reserve(s.size());

        for (const auto c: s)
        {
            if (is_char_unsafe(c))
            {
                r += '%';
                r += to_hex(static_cast<unsigned char>(c) >> 4);
                r += to_hex(static_cast<unsigned char>(c) & 0xF);
            }
            else
            {
                r += c;
            }
        }

        return r;
    }

    bool parseJsonBool(const std::string& s)
    {
        return s11n::parseJson<bool>(s);
    }
}}
