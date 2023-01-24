// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// (C) Copyright Jonathan Graehl 2004.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Used by mapped_file.cpp.

#ifndef BOOST_IOSTREAMS_DETAIL_SYSTEM_FAILURE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_SYSTEM_FAILURE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <cstring>
#include <string>
#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include <boost/iostreams/detail/config/windows_posix.hpp>
#include <boost/iostreams/detail/ios.hpp>  // failure.

#if defined(BOOST_NO_STDC_NAMESPACE) && !defined(__LIBCOMO__)
namespace std { using ::strlen; }
#endif

#ifdef BOOST_IOSTREAMS_WINDOWS
# define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
# include <windows.h>
#else
# include <errno.h>
# include <string.h>
#endif

namespace boost { namespace iostreams { namespace detail {

inline BOOST_IOSTREAMS_FAILURE system_failure(const char* msg)
{
    std::string result;
#ifdef BOOST_IOSTREAMS_WINDOWS
    DWORD err;
    LPVOID lpMsgBuf;
    if ( (err = ::GetLastError()) != NO_ERROR &&
         ::FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER |
                           FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL,
                           err,
                           MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                           (LPSTR) &lpMsgBuf,
                           0,
                           NULL ) != 0 )
    {
        result.reserve(std::strlen(msg) + 2 + std::strlen((LPSTR)lpMsgBuf));
        result.append(msg);
        result.append(": ");
        result.append((LPSTR) lpMsgBuf);
        ::LocalFree(lpMsgBuf);
    } else {
        result += msg;
    }
#else
    const char* system_msg = errno ? strerror(errno) : "";
    result.reserve(std::strlen(msg) + 2 + std::strlen(system_msg));
    result.append(msg);
    result.append(": ");
    result.append(system_msg);
#endif
    return BOOST_IOSTREAMS_FAILURE(result);
}

inline BOOST_IOSTREAMS_FAILURE system_failure(const std::string& msg)
{ return system_failure(msg.c_str()); }

inline void throw_system_failure(const char* msg)
{ boost::throw_exception(system_failure(msg)); }

inline void throw_system_failure(const std::string& msg)
{ boost::throw_exception(system_failure(msg)); }

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_SYSTEM_FAILURE_HPP_INCLUDED

/* system_failure.hpp
VzC6RU/QpgE41+SqoqUS+vwYlK6gf4JgyD1qSl2XGPJrOcwNqAhwXI743ZuD+E35DAy61FqrSTdxf38KmoUz49O+UEW60Muks6JNVbrAaiS/2W8na09pd1AA3y20C7U3SSJ/xC57OYo8im6KWYbK/ha25A4+dDXDMkYqQ2ZHZUeeRaYgxM5jKWrjL8r8LvCmj//DYfBIO3E28p7OVSu20WXvM4g9Dbiyo7cK/tLENY2HmcwO5XhzsLy4ZCksE/zRZ9xabrHrObNYgtDRfreUh/DozMPaQ3Da8lsepCFoixgkXztkeS/Skss2YTcPZSHmozcagUzoTZFEhamejqzj8Bzhegs/Spk1+qRxvOk6WhHLySb74W/UmVHlrIOiWe8nI19/cBE+cm3HuHz4lL3QskByHPJqwpXxrSz8N+CUgfMqOZganp7IM1VxciLCWdDYf04N+C3d7LSwqAfiNbfprbvv+mm302F9ct2DtCBfxDHvjJaQahBMvzTsipLucoEqYtmmdskAenfw6jgRjTo/bozC+ABGhhXmITaxc4oV6WfyrKDePsdCiUq1lAt5WTMz5+wuk4ZQ89ZhZDWkerazWnXqG0v3Xz58hSrciu3t8vTMo54uYiGKCAsm0Ynx4SPPCrwcVl4oYpWV61xzBtmyHlkeMhlYtNBpgnh72YykAwxl1p2zOJG23O5yxa2J1xecfuLYL/RPzv4iUj1J
*/