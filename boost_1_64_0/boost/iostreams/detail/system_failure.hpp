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
tJD5fHeER5MeuRRnSqrIbQ1huZdMvqIO1nN0/EPTGu31zjdTaH53snPTb7ez9EMKkhSJ+XwCynqw6/XVMgWk9Q2Qt7FQuE1iQsKCg6tmMFjIU6oDBNcO4hqZhJae89RXj9WfOYlkloPNb+y5Fl+6rfW4SJKKnH/YpJ/G3BcjyP2iev+xgHafhnw35In/VIYYWXAQI7doJDlqfJlzBKfYwiQ1QXKTLn4ifLORoXsBGFT8W5DlX9lJuVhNLKszPVis3kUd5tKT5vV92JIwzWN7fRx+Dw86eVGfNTfHaCjVdywYKDLSZy7NxgBW16gCFDaZ/+Drz+OB8r4cKt/WZbkxR9ZCDH5+sDI0ARmUmyaZLDnuBFbuFqNozotChzgBEX8In1IDOwNmGw1M4AZSLZStt98eNQNoTBQ1CimsCW/GRpBRRCS+JTHBtdZ49sJTygwp9gLxo9d6NaIDH1hB210xd029OEdecDcEEVBPHpd+FYxFGMOjp1Pj1/lTGWChVF1xpGlgvny9cRiWb8Ual5bcuU0RKYu48OxYCOF0i6FUabY5XCxkQY56GkUYLg==
*/