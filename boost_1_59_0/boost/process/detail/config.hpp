// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 * \file boost/process/config.hpp
 *
 * Defines various macros.
 */

#ifndef BOOST_PROCESS_DETAIL_CONFIG_HPP
#define BOOST_PROCESS_DETAIL_CONFIG_HPP

#include <boost/config.hpp>
#include <system_error>
#include <boost/system/api_config.hpp>

#include <boost/process/exception.hpp>

#if defined(BOOST_POSIX_API)
#include <errno.h>
#if defined(__GLIBC__)
#include <features.h>
#else
extern char **environ;
#endif
#elif defined(BOOST_WINDOWS_API)
#include <boost/winapi/get_last_error.hpp>
#else
#error "System API not supported by boost.process"
#endif

namespace boost { namespace process { namespace detail
{

#if !defined(BOOST_PROCESS_PIPE_SIZE)
#define BOOST_PROCESS_PIPE_SIZE 1024
#endif

#if defined(BOOST_POSIX_API)
namespace posix {namespace extensions {}}
namespace api = posix;

inline std::error_code get_last_error() noexcept
{
    return std::error_code(errno, std::system_category());
}

//copied from linux spec.
#if (_XOPEN_SOURCE >= 500 || _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED) && !(_POSIX_C_SOURCE >= 200809L || _XOPEN_SOURCE >= 700)
#define BOOST_POSIX_HAS_VFORK 1
#endif

#if (_POSIX_C_SOURCE >= 199309L)
#define BOOST_POSIX_HAS_SIGTIMEDWAIT 1
#endif

#elif defined(BOOST_WINDOWS_API)
namespace windows {namespace extensions {}}
namespace api = windows;

inline std::error_code get_last_error() noexcept
{
    return std::error_code(::boost::winapi::GetLastError(), std::system_category());
}
#endif

inline void throw_last_error(const std::string & msg)
{
    throw process_error(get_last_error(), msg);
}

inline void throw_last_error(const char * msg)
{
    throw process_error(get_last_error(), msg);
}

inline void throw_last_error()
{
    throw process_error(get_last_error());
}

inline void throw_error(const std::error_code& ec)
{
    if (ec)
        throw process_error(ec);
}

inline void throw_error(const std::error_code& ec, const char* msg)
{
    if (ec)
        throw process_error(ec, msg);
}

template<typename Char> constexpr Char null_char();
template<> constexpr char     null_char<char>     (){return   '\0';}
template<> constexpr wchar_t  null_char<wchar_t>  (){return  L'\0';}

template<typename Char> constexpr Char equal_sign();
template<> constexpr char     equal_sign<char>    () {return  '='; }
template<> constexpr wchar_t  equal_sign<wchar_t> () {return L'='; }

template<typename Char> constexpr Char quote_sign();
template<> constexpr char     quote_sign<char>    () {return  '"'; }
template<> constexpr wchar_t  quote_sign<wchar_t> () {return L'"'; }

template<typename Char> constexpr Char space_sign();
template<> constexpr char     space_sign<char>    () {return  ' '; }
template<> constexpr wchar_t  space_sign<wchar_t> () {return L' '; }


}}}
#endif

/* config.hpp
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
*/