/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   snprintf.hpp
 * \author Andrey Semashev
 * \date   20.02.2009
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_SNPRINTF_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_SNPRINTF_HPP_INCLUDED_

#include <stdio.h>
#include <cstddef>
#include <cstdarg>
#include <boost/log/detail/config.hpp>
#ifdef BOOST_LOG_USE_WCHAR_T
#include <wchar.h>
#endif // BOOST_LOG_USE_WCHAR_T
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

#if defined(_MSC_VER) || (defined(__MINGW32__) && !defined(__MINGW64_VERSION_MAJOR))

// MSVC snprintfs are not conforming but they are good enough for our cases.
// MinGW32, at least the older versions up until gcc 4.7, also provide the non-conforming interface.
inline int vsnprintf(char* buf, std::size_t size, const char* format, std::va_list args)
{
    int n = _vsnprintf(buf, size, format, args);
    if (static_cast< unsigned int >(n) >= size)
    {
        n = static_cast< int >(size);
        buf[size - 1] = '\0';
    }
    return n;
}

#   ifdef BOOST_LOG_USE_WCHAR_T
inline int vswprintf(wchar_t* buf, std::size_t size, const wchar_t* format, std::va_list args)
{
    int n = _vsnwprintf(buf, size, format, args);
    if (static_cast< unsigned int >(n) >= size)
    {
        n = static_cast< int >(size);
        buf[size - 1] = L'\0';
    }
    return n;
}
#   endif // BOOST_LOG_USE_WCHAR_T

inline int snprintf(char* buf, std::size_t size, const char* format, ...)
{
    std::va_list args;
    va_start(args, format);
    int n = vsnprintf(buf, size, format, args);
    va_end(args);
    return n;
}

#   ifdef BOOST_LOG_USE_WCHAR_T
inline int swprintf(wchar_t* buf, std::size_t size, const wchar_t* format, ...)
{
    std::va_list args;
    va_start(args, format);
    int n = vswprintf(buf, size, format, args);
    va_end(args);
    return n;
}
#   endif // BOOST_LOG_USE_WCHAR_T

#else

// Standard-conforming compilers already have the correct snprintfs
using ::snprintf;
using ::vsnprintf;

#   ifdef BOOST_LOG_USE_WCHAR_T
using ::swprintf;
using ::vswprintf;
#   endif // BOOST_LOG_USE_WCHAR_T

#endif

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_SNPRINTF_HPP_INCLUDED_

/* snprintf.hpp
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
*/