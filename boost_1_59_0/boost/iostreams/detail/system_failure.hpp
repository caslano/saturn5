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
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
*/