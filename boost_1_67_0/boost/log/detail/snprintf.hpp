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