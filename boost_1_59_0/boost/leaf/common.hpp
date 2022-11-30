#ifndef BOOST_LEAF_COMMON_HPP_INCLUDED
#define BOOST_LEAF_COMMON_HPP_INCLUDED

// Copyright 2018-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/leaf/config.hpp>
#include <boost/leaf/detail/demangle.hpp>

#include <iosfwd>
#if BOOST_LEAF_CFG_STD_STRING
#   include <string>
#endif
#include <cerrno>
#if BOOST_LEAF_CFG_WIN32
#   include <windows.h>
#   include <cstring>
#   ifdef min
#       undef min
#   endif
#   ifdef max
#       undef max
#   endif
#endif

namespace boost { namespace leaf {

struct BOOST_LEAF_SYMBOL_VISIBLE e_api_function { char const * value; };

#if BOOST_LEAF_CFG_STD_STRING

struct BOOST_LEAF_SYMBOL_VISIBLE e_file_name
{
    std::string value;
};

#else

struct BOOST_LEAF_SYMBOL_VISIBLE e_file_name
{
    constexpr static char const * const value = "<unavailable>";
    BOOST_LEAF_CONSTEXPR explicit e_file_name( char const * ) { }
};

#endif

struct BOOST_LEAF_SYMBOL_VISIBLE e_errno
{
    int value;

    explicit e_errno(int value=errno): value(value) { }

    template <class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits> & operator<<(std::basic_ostream<CharT, Traits> & os, e_errno const & err)
    {
        return os << type<e_errno>() << ": " << err.value << ", \"" << std::strerror(err.value) << '"';
    }
};

struct BOOST_LEAF_SYMBOL_VISIBLE e_type_info_name { char const * value; };

struct BOOST_LEAF_SYMBOL_VISIBLE e_at_line { int value; };

namespace windows
{
    struct e_LastError
    {
        unsigned value;

        explicit e_LastError(unsigned value): value(value) { }

#if BOOST_LEAF_CFG_WIN32
        e_LastError(): value(GetLastError()) { }

        template <class CharT, class Traits>
        friend std::basic_ostream<CharT, Traits> & operator<<(std::basic_ostream<CharT, Traits> & os, e_LastError const & err)
        {
            struct msg_buf
            {
                LPVOID * p;
                msg_buf(): p(0) { }
                ~msg_buf() noexcept { if(p) LocalFree(p); }
            };
            msg_buf mb;
            if( FormatMessageA(
                FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
                0,
                err.value,
                MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
                (LPSTR)&mb.p,
                0,
                0) )
            {
                BOOST_LEAF_ASSERT(mb.p != 0);
                char * z = std::strchr((LPSTR)mb.p,0);
                if( z[-1] == '\n' )
                    *--z = 0;
                if( z[-1] == '\r' )
                    *--z = 0;
                return os << type<e_LastError>() << ": " << err.value << ", \"" << (LPCSTR)mb.p << '"';
            }
            return os;
        }
#endif
    };
}

} }

#endif

/* common.hpp
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
*/