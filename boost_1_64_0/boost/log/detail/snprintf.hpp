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
nda9d17Pz4QNXrfe6Gyfy/l7A3S2YcNUMZ3tQil3SpDONkBk5c26+FpXDVp/7ktJuzNjAhXNN/EHRFZAu+YEfAsePNeig6TdPORb7Zig/uhsA6nc8Lf3w/PpdFWL6W9JJa2FLfUSbC+5p6hf4feP50yi363224lG0j1Hjhir9LUQJ6k09pyEco0z0Vl8dhotGwdbVkbG9Q0d59cbM6zT16/C6XWzF1vI332kVeL+i5o9vDV9/Dun7vV8evr6Xjg9dpeE35ZQfmO/3NyXW0fVbz666kVVwumrp6/3ljQ3/FLf/aCfBfm4aFx7Xfk1A8bgEmF9mAYbwmtgYzgLylgWzIHHJB3d5jBb+z24ln47xDTfd+yxsAqsAdNgA1gVZsFqkDHV09Z7KrQuWfd5tJT6Ty9c0uOxKvPxiA4UOSJH5IgckSNyRI7I8f9+nB39P+eM7f+3JkD/X6n1tC1a/9+Iq8/L/L5NRk/TeUtpwur/X28Kq/+T1m/r//1E9yjjpP8TP1T/z3LU/53DZjvq/85hc5TjWv6ELf1+eoQt0a7wvZzPKdGuMPiFULvCrcgC7QrhbATXSLhm+I3dIei797ZyvjIp2SbOMSlT58A4Qeufn5TzjX37osm332sz/r22h6yQb75py9Bvvmmz0uzXNWzY7/12e4vo/z8+szyjYWzz1T+3aLrlseV39j1z+n9J+nl/X7/S92omLhbXTQXv11URJsJKsAVMgR1hZTgBpsEbYTW4BGbAjbA6zCzhG+v2DnM8O0V04cgROSJH5IgckSNyRI7I8X94nAX9H3fmxv/XBcznb6b1f8tCN4IKXt4E3mn0/0GDpSA5Ad//DxowjtzMnGwJe9JJ9ycdR93dQc93DpvtqOc7h81x1vMJ6/xdfznvX3Iu1ui5P+AnpNnXsKz4D6mBzKwNGsfX8a+T83/kq+cZZhy/vMg+Z/f4zMBvR0XHraPjlZMw+cSLVuW4IvnWnb+bwJYBax5eIeGq6u/indNaJGHaK5t4ZYhfAWbAujCHtH1pfSrhkskzhv97l3MhW5+hncO3FDElfbcqfSD0u9UsBz0+20GPz9G6uG8firkJSo5zo9BNNetih7p0evA6lAOvGhhki8K+YmxReh93HedVO0v1sAP6opZTA2I3CbJDSdwYE2ad3V/VNXG1POw6kpWJm2DCHHJPsV5X39rvqFT3vMA+y3mHe8GxzzqHzXa0TTmHzXG2TRHWce1H8w3FQDn/sLu6qmK3sXNZY6K87bDmI+k42MN0PWaY8/fZNyuPqUctd7KNmT760gy5n1z3qv22b33IoRIn2n25VdGS+xRfr1l67369l/8Dd3n9g+082i1w3UQSN/Yyp30gd0raR7lXNhlb2Hopg8d8V9H4bq//Oqu62mbWHT0i8b6wElhDUcLhu1TCPYVskeWrh7cknMf+wbvvgt5zsZOEa2C/Rq88bAXuOThx5Jgsf12UkXDV5PngW5+yhsji7RjunlnM2oijr/n6fWU5d6Vd1Q5MkzrI9LfvVrm2e1z1SPcy6u92ZpH4nlsnphedu0K9byfqdUt6SZrrzJ6hxyX+bS7fnqEV6YENuUOas8qGxDH1wDNG3xdvSJwnXLHWANtXL/1nyt6n1h7K4GTHTIYLJMwgs67nCCnfV+6B9Mja7qXKoS8Qjl+imb51Yi8PrAcSzzRpPytlrGPafK7EGWrWv5woee1zt7JvtSVMQD76Oo0/OI8sU9f3SZrt+eVgTRVcM5yvbadL+i34RjzB7Cn5vMgectO2fKt9jbKtKvSueFXBPqbyXB2tonQplaS7kNqPUvG4dNYTLVZG8zxbLWnucNe1qXvdHisk/uv0n4yQPUd8feE=
*/