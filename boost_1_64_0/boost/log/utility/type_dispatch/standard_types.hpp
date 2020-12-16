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
Dw/XvmlHSEehL+xZRqdk1T7itVHhPql4Pa14PSX/mzGO/F8p/9mYJ+R/iPJvmPLvFPmfCKtLN6K+q2Mh+UHwNOlyjFR8T4dHyL4vHCWdijPhyTpL4BTp8oyRTk6u3OdJl6dEZxTNlA7PJXJ3hdztsfjrvQMf1XUjzAdKz2Sl5zzpnBQpnsWwLSxVfpdIB2W6zoCZCY/Snv4DtY/dIO1jd5Z0l8bLf672+p8qXZ5p0uU5H14JL9NZC1fL/TXSsVmkswZuk47N3dK5uVfuV8n9ap0N8Iiu35VOSk7ov0snpV8o4/9eL2U4eVCMWYhZg9mK+QQTDqOfgjk8XKmXUvmr/FX+Kn+Vv8pf5a/yV/mr/P0//36e+f8pTE79+Pn/5pr/33pN/Pz/lEn5uQSfhwPt8b8nTg+gYzl6AM7TMT2AuCD2O3cTJKS+GpsfWY4ewI6nLOxYqInKAPvVBdjxVMV1AXY8VXFdgB1P/by6AN2VT3WU+ZPIr2piRBdgx4akfErSlWipeYK/mtuRwT7UnIHk0umRnQEDYecWzPpAmn8+bvDPx5aaM/jQ7McFjyXMU4lxnjOb85MZZ8C8RLi++b3BV1fAm4satBF7RnCOIUzfMthQcf2BeLdv2pzHuOIZ/NtWcztfmv2wYA8nhfuFnIXwNRgKhJwbMY8GqiTpHrTXPMjH5vfs4FHE82T+WoHZgakZYMY+MNlZBjdjsiPukbezdI0OpDp/4WzXvlZGml9xqivMjk9G3PTdlx9vr8daKoPByi/iIZnrbzwpOdvpTV2tJp2IRVk2AIyeQKJ+BH9rziUmL25RkfmX6B6M2yzeses1T8b2ZCzlb+3J6O2r+O3G5H0at2xM3pPx2I3JeygesTF5D8UunqyXXad71z2cbK6nRa+n0ogUjIscpVIw7YCey33qfGhvxJOV5hY5ic/uFj27gzF2RrH0BWYntXGmCOKrB3K5uT22XD2Q2W4bRlkHTQ/kh+uCuPH+pIq/Lsimsm2OKYTsXz9r04aK64Js2lBxXZBNGw5cF6RM2R+QHoibP1s1eV2oci1Que7eVDZ/UAbZhy5Ibyu7HL88Iyzf9surFwHze7bTlX+1dp1nHFPB8k/WC0lM4ybpTLTR/Ehr6YXMTqoDhSUVqQP489ULqa79Zy8z+6a+dUJ+vXL+vMX+07fP+WHdOz69HTP895zomJReUxTx3Quh74Z97jtBWPved6Lrhn3uO4H/iu87gdt97nswasO/Z98JN793V5cuVTA6z9UtGNXNOOfxMvktBY24/PZ0DeaZ2+8CTZznOPu4WqCW2zdZH5EX01fp51cO3MNfX6Ol3sUFZt8yuJke1/P0ZX6L+QRTNxh2mmCkt6FwegV/wQn3bviS++9XofB7WPwyPP2LS8x9WrC9c2bgxkChb3kqzCS9i5bKi/PMvkXwIGaKf8cJ0puJ7xuBdOfDQCunXrCq2pyAc67du4rpYuxlf+US85cTLNvONFE9mW/2XwaW0hNZTV/xBbgbU8uLR15BSf74qF6K4vKG+fnGCfJfHepYL2et7NCCMbvH6WG1CfQLtHUuDnR29UJktz0Q6x9N8vo6mRbvPoEnnXzvedtjsjzaps5OE/V/dlgYlwbaMdOaGujq9A3UcIYHDrW8ru/d/1V2wp4UuCTQyUlXHaD2yg16QubmgUCbwBnONYGDdT+0pJ4ImsZWitMpLv0F0yZNGF3Ajtheuz7H4pXpZEtH61sL7w/4auqcxYxnc5O7cXk20IMnfgh6YS/zHo7kyVWBlpE8sf2v3TyRrkxcfy1RVybzX6Ir06vmo+vj+jbSlen3f6grc5Tpysza1PyhXrtPO/mg9z4vmVXnpnmVujI=
*/