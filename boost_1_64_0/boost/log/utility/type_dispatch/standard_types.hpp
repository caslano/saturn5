/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   standard_types.hpp
 * \author Andrey Semashev
 * \date   19.05.2007
 *
 * The header contains definition of standard types supported by the library by default.
 */

#ifndef BOOST_LOG_STANDARD_TYPES_HPP_INCLUDED_
#define BOOST_LOG_STANDARD_TYPES_HPP_INCLUDED_

#include <string>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector/vector30.hpp> // needed to use mpl::vector sizes greater than 20 even when the default BOOST_MPL_LIMIT_VECTOR_SIZE is not set
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/string_literal_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
#define BOOST_LOG_AUX_STANDARD_TYPE_WCHAR_T() (wchar_t)
#else
#define BOOST_LOG_AUX_STANDARD_TYPE_WCHAR_T()
#endif

#if !defined(BOOST_NO_CXX11_CHAR16_T) && !defined(BOOST_LOG_NO_CXX11_CODECVT_FACETS)
#define BOOST_LOG_AUX_STANDARD_TYPE_CHAR16_T() (char16_t)
#else
#define BOOST_LOG_AUX_STANDARD_TYPE_CHAR16_T()
#endif

#if !defined(BOOST_NO_CXX11_CHAR32_T) && !defined(BOOST_LOG_NO_CXX11_CODECVT_FACETS)
#define BOOST_LOG_AUX_STANDARD_TYPE_CHAR32_T() (char32_t)
#else
#define BOOST_LOG_AUX_STANDARD_TYPE_CHAR32_T()
#endif

//! Boost.Preprocessor sequence of character types
#define BOOST_LOG_STANDARD_CHAR_TYPES()\
    (char)BOOST_LOG_AUX_STANDARD_TYPE_WCHAR_T()BOOST_LOG_AUX_STANDARD_TYPE_CHAR16_T()BOOST_LOG_AUX_STANDARD_TYPE_CHAR32_T()

#if defined(BOOST_HAS_LONG_LONG)
#define BOOST_LOG_AUX_STANDARD_LONG_LONG_TYPES() (long long)(unsigned long long)
#else
#define BOOST_LOG_AUX_STANDARD_LONG_LONG_TYPES()
#endif

//! Boost.Preprocessor sequence of integral types
#define BOOST_LOG_STANDARD_INTEGRAL_TYPES()\
    (bool)(signed char)(unsigned char)(short)(unsigned short)(int)(unsigned int)(long)(unsigned long)BOOST_LOG_AUX_STANDARD_LONG_LONG_TYPES()\
    BOOST_LOG_STANDARD_CHAR_TYPES()

//! Boost.Preprocessor sequence of floating point types
#define BOOST_LOG_STANDARD_FLOATING_POINT_TYPES()\
    (float)(double)(long double)

//! Boost.Preprocessor sequence of arithmetic types
#define BOOST_LOG_STANDARD_ARITHMETIC_TYPES()\
    BOOST_LOG_STANDARD_INTEGRAL_TYPES()BOOST_LOG_STANDARD_FLOATING_POINT_TYPES()

#if defined(BOOST_LOG_USE_CHAR)
#define BOOST_LOG_AUX_STANDARD_STRING_TYPES() (std::string)(boost::log::string_literal)
#else
#define BOOST_LOG_AUX_STANDARD_STRING_TYPES()
#endif

#if defined(BOOST_LOG_USE_WCHAR_T)
#define BOOST_LOG_AUX_STANDARD_WSTRING_TYPES() (std::wstring)(boost::log::wstring_literal)
#else
#define BOOST_LOG_AUX_STANDARD_WSTRING_TYPES()
#endif

//! Boost.Preprocessor sequence of string types
#define BOOST_LOG_STANDARD_STRING_TYPES()\
    BOOST_LOG_AUX_STANDARD_STRING_TYPES()BOOST_LOG_AUX_STANDARD_WSTRING_TYPES()

//! Boost.Preprocessor sequence of the default attribute value types supported by the library
#define BOOST_LOG_DEFAULT_ATTRIBUTE_VALUE_TYPES()\
    BOOST_LOG_STANDARD_ARITHMETIC_TYPES()BOOST_LOG_STANDARD_STRING_TYPES()


/*!
 * An MPL-sequence of integral types of attributes, supported by default
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_STANDARD_INTEGRAL_TYPES())
> integral_types;

/*!
 * An MPL-sequence of FP types of attributes, supported by default
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_STANDARD_FLOATING_POINT_TYPES())
> floating_point_types;

/*!
 * An MPL-sequence of all numeric types of attributes, supported by default
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_STANDARD_ARITHMETIC_TYPES())
> arithmetic_types;

//! Deprecated alias
typedef arithmetic_types numeric_types;

/*!
 * An MPL-sequence of string types of attributes, supported by default
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_STANDARD_STRING_TYPES())
> string_types;

/*!
 * An MPL-sequence of all attribute value types that are supported by the library by default.
 */
typedef BOOST_PP_CAT(mpl::vector, BOOST_PP_SEQ_SIZE(BOOST_LOG_DEFAULT_ATTRIBUTE_VALUE_TYPES()))<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_DEFAULT_ATTRIBUTE_VALUE_TYPES())
> default_attribute_value_types;

//! Deprecated alias
typedef default_attribute_value_types default_attribute_types;

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_STANDARD_TYPES_HPP_INCLUDED_

/* standard_types.hpp
N0I4mlOit+zbcNhKojjJDy2SmcU8pUypDRWo538aJIMhxagwI/fcysdbLDcYFY6q3gB0R0E8YjR2AG1ZQRQkfakstTE9vx13zTi4prDEFOBEhu0CRCX+UeCwStR7OyCc+rmC2Fnf+AJlwldskHBHDc8P66QqFYa6TBe06UnoxneMKiNS57WgBh7w52MxnCrT3uYXp+l1b8wxWs2DwRyjuJnMmnktKljBsgzlwfJzGW4g+Dys04pv/WJIuosLwx3+ktKzpXC9UzL/QbJe/hpsCfSsyz3FDC6oikQBdUg7hrzQhhJytyA/oh7Rjyi7nNdc8IqUKGQCoj+oakknm03bDvugY0s3wxel6QoauVV+2w8pjNt4IjMuwLokMuBFG+SHPXuTz+CSPdwjrgT0UB/90UYTH3Fl3mLsMsuW+asw0tIHM/XH77mXebXC10WvcgyisfZ8/SqfY0dt9gYXApE6tZu61vz7GG//cDePCMuCQv+B4BUIITGbGzkQ6PvlGzrlDph6MFAnssgERZ6R8ozYXZ2+5RQFxNG3miqguJQUQqU+wJslCTBhi6xcYA==
*/