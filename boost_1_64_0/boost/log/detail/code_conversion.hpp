/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   code_conversion.hpp
 * \author Andrey Semashev
 * \date   08.11.2008
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_CODE_CONVERSION_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_CODE_CONVERSION_HPP_INCLUDED_

#include <cstddef>
#include <locale>
#include <string>
#include <boost/core/enable_if.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/is_character_type.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

// Implementation note: We have to implement char<->wchar_t conversions even in the absence of the native wchar_t
// type. These conversions are used in sinks, e.g. to convert multibyte strings to wide-character filesystem paths.

//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const wchar_t* str1, std::size_t len, std::string& str2, std::size_t max_size, std::locale const& loc = std::locale());
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char* str1, std::size_t len, std::wstring& str2, std::size_t max_size, std::locale const& loc = std::locale());

#if !defined(BOOST_LOG_NO_CXX11_CODECVT_FACETS)
#if !defined(BOOST_NO_CXX11_CHAR16_T)
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char16_t* str1, std::size_t len, std::string& str2, std::size_t max_size, std::locale const& loc = std::locale());
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char* str1, std::size_t len, std::u16string& str2, std::size_t max_size, std::locale const& loc = std::locale());
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char16_t* str1, std::size_t len, std::wstring& str2, std::size_t max_size, std::locale const& loc = std::locale());
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T)
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char32_t* str1, std::size_t len, std::string& str2, std::size_t max_size, std::locale const& loc = std::locale());
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char* str1, std::size_t len, std::u32string& str2, std::size_t max_size, std::locale const& loc = std::locale());
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char32_t* str1, std::size_t len, std::wstring& str2, std::size_t max_size, std::locale const& loc = std::locale());
#endif
#if !defined(BOOST_NO_CXX11_CHAR16_T) && !defined(BOOST_NO_CXX11_CHAR32_T)
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char16_t* str1, std::size_t len, std::u32string& str2, std::size_t max_size, std::locale const& loc = std::locale());
//! The function converts one string to the character type of another
BOOST_LOG_API bool code_convert_impl(const char32_t* str1, std::size_t len, std::u16string& str2, std::size_t max_size, std::locale const& loc = std::locale());
#endif
#endif // !defined(BOOST_LOG_NO_CXX11_CODECVT_FACETS)

//! The function converts one string to the character type of another
template< typename SourceCharT, typename TargetCharT, typename TargetTraitsT, typename TargetAllocatorT >
inline typename boost::enable_if_c< is_character_type< SourceCharT >::value && is_character_type< TargetCharT >::value && sizeof(SourceCharT) == sizeof(TargetCharT), bool >::type
code_convert(const SourceCharT* str1, std::size_t len, std::basic_string< TargetCharT, TargetTraitsT, TargetAllocatorT >& str2, std::size_t max_size, std::locale const& = std::locale())
{
    std::size_t size_left = str2.size() < max_size ? max_size - str2.size() : static_cast< std::size_t >(0u);
    const bool overflow = len > size_left;
    str2.append(reinterpret_cast< const TargetCharT* >(str1), overflow ? size_left : len);
    return !overflow;
}

//! The function converts one string to the character type of another
template< typename SourceCharT, typename SourceTraitsT, typename SourceAllocatorT, typename TargetCharT, typename TargetTraitsT, typename TargetAllocatorT >
inline typename boost::enable_if_c< is_character_type< SourceCharT >::value && is_character_type< TargetCharT >::value && sizeof(SourceCharT) == sizeof(TargetCharT), bool >::type
code_convert(std::basic_string< SourceCharT, SourceTraitsT, SourceAllocatorT > const& str1, std::basic_string< TargetCharT, TargetTraitsT, TargetAllocatorT >& str2, std::size_t max_size, std::locale const& loc = std::locale())
{
    return aux::code_convert(str1.data(), str1.size(), str2, max_size, loc);
}

//! The function converts one string to the character type of another
template< typename SourceCharT, typename SourceTraitsT, typename SourceAllocatorT, typename TargetCharT, typename TargetTraitsT, typename TargetAllocatorT >
inline typename boost::enable_if_c< is_character_type< SourceCharT >::value && is_character_type< TargetCharT >::value && sizeof(SourceCharT) == sizeof(TargetCharT), bool >::type
code_convert(std::basic_string< SourceCharT, SourceTraitsT, SourceAllocatorT > const& str1, std::basic_string< TargetCharT, TargetTraitsT, TargetAllocatorT >& str2, std::locale const& loc = std::locale())
{
    return aux::code_convert(str1.data(), str1.size(), str2, str2.max_size(), loc);
}
//! The function converts one string to the character type of another
template< typename SourceCharT, typename TargetCharT, typename TargetTraitsT, typename TargetAllocatorT >
inline typename boost::enable_if_c< is_character_type< SourceCharT >::value && is_character_type< TargetCharT >::value && sizeof(SourceCharT) == sizeof(TargetCharT), bool >::type
code_convert(const SourceCharT* str1, std::size_t len, std::basic_string< TargetCharT, TargetTraitsT, TargetAllocatorT >& str2, std::locale const& loc = std::locale())
{
    return aux::code_convert(str1, len, str2, str2.max_size(), loc);
}

//! The function converts one string to the character type of another
template< typename SourceCharT, typename SourceTraitsT, typename SourceAllocatorT, typename TargetCharT, typename TargetTraitsT, typename TargetAllocatorT >
inline typename boost::enable_if_c< is_character_type< SourceCharT >::value && is_character_type< TargetCharT >::value && sizeof(SourceCharT) != sizeof(TargetCharT), bool >::type
code_convert(std::basic_string< SourceCharT, SourceTraitsT, SourceAllocatorT > const& str1, std::basic_string< TargetCharT, TargetTraitsT, TargetAllocatorT >& str2, std::locale const& loc = std::locale())
{
    return aux::code_convert_impl(str1.c_str(), str1.size(), str2, str2.max_size(), loc);
}

//! The function converts one string to the character type of another
template< typename SourceCharT, typename TargetCharT, typename TargetTraitsT, typename TargetAllocatorT >
inline typename boost::enable_if_c< is_character_type< SourceCharT >::value && is_character_type< TargetCharT >::value && sizeof(SourceCharT) != sizeof(TargetCharT), bool >::type
code_convert(const SourceCharT* str1, std::size_t len, std::basic_string< TargetCharT, TargetTraitsT, TargetAllocatorT >& str2, std::locale const& loc = std::locale())
{
    return aux::code_convert_impl(str1, len, str2, str2.max_size(), loc);
}

//! The function converts one string to the character type of another
template< typename SourceCharT, typename SourceTraitsT, typename SourceAllocatorT, typename TargetCharT, typename TargetTraitsT, typename TargetAllocatorT >
inline typename boost::enable_if_c< is_character_type< SourceCharT >::value && is_character_type< TargetCharT >::value && sizeof(SourceCharT) != sizeof(TargetCharT), bool >::type
code_convert(std::basic_string< SourceCharT, SourceTraitsT, SourceAllocatorT > const& str1, std::basic_string< TargetCharT, TargetTraitsT, TargetAllocatorT >& str2, std::size_t max_size, std::locale const& loc = std::locale())
{
    return aux::code_convert_impl(str1.c_str(), str1.size(), str2, max_size, loc);
}

//! The function converts one string to the character type of another
template< typename SourceCharT, typename TargetCharT, typename TargetTraitsT, typename TargetAllocatorT >
inline typename boost::enable_if_c< is_character_type< SourceCharT >::value && is_character_type< TargetCharT >::value && sizeof(SourceCharT) != sizeof(TargetCharT), bool >::type
code_convert(const SourceCharT* str1, std::size_t len, std::basic_string< TargetCharT, TargetTraitsT, TargetAllocatorT >& str2, std::size_t max_size, std::locale const& loc = std::locale())
{
    return aux::code_convert_impl(str1, len, str2, max_size, loc);
}

//! The function converts the passed string to the narrow-character encoding
inline std::string const& to_narrow(std::string const& str)
{
    return str;
}

//! The function converts the passed string to the narrow-character encoding
inline std::string const& to_narrow(std::string const& str, std::locale const&)
{
    return str;
}

//! The function converts the passed string to the narrow-character encoding
inline std::string to_narrow(std::wstring const& str, std::locale const& loc = std::locale())
{
    std::string res;
    aux::code_convert_impl(str.c_str(), str.size(), res, res.max_size(), loc);
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_HAS_NRVO)
    return static_cast< std::string&& >(res);
#else
    return res;
#endif
}

//! The function converts the passed string to the wide-character encoding
inline std::wstring const& to_wide(std::wstring const& str)
{
    return str;
}

//! The function converts the passed string to the wide-character encoding
inline std::wstring const& to_wide(std::wstring const& str, std::locale const&)
{
    return str;
}

//! The function converts the passed string to the wide-character encoding
inline std::wstring to_wide(std::string const& str, std::locale const& loc = std::locale())
{
    std::wstring res;
    aux::code_convert_impl(str.c_str(), str.size(), res, res.max_size(), loc);
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_HAS_NRVO)
    return static_cast< std::wstring&& >(res);
#else
    return res;
#endif
}

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_CODE_CONVERSION_HPP_INCLUDED_

/* code_conversion.hpp
OlgbPgPbwRdhCtwAu8Pn4Fh1HwefhPnwKVio7kfhdnNvlHFVzxuHbNLz1lJ7SXVgJKwLE2A92BC2g41hA5gIE+AF8HzYDjaE3WFreAm8AA7ReENhE3gZbAonwOYwE7aA2bAVzIOJcD5Mgjdqess1vQc0vaNwrblHyLWl5amOrNLyvK71+AaMhDthAnwTNoJfwsZqF6Iz/BT2UzsPw+ABOA1+Bq/U8NlqL6JA7UUUqfvV8H21n7IPXqfuxfA9OF/1o3CpuW+Hn+Y7Bin1D+TaDn1hOOwNo1RvA/vD9vBS2EHd+8KL4QD1H6z+Q+FAmAEHwb/CwXATHAp3wWFwj4Y/Cnv495FgZc1fmKXPp2m9TtZ6TYdRqntUPwo3yL6OvZyxyKOazkVqf6EnrAz7qH2O/rAtHAQ7wcHwEjgEToJDYTrkOpNyjYAz4EhYCi+Dt6n/IjgGLoVj4UNwHHwWjocvwgnwLTgRUg+mfa1h/j0V2EzzHyH59B1faz0c1Hr4RvvXIdgQ/l372WHYVPWjcJJ//wO213SjfPnngNr+l8EwOErbfzSsAsfAGnAsTIbjYFs4Ua/DCVDtZ+m9v/Tl0+xnzdD6n63tNgfGq32f+nCujjd/hR3hw9oe82E3tfPTU/U+8E9woNrLGAVL4Rh4h7bbYpgDl8Br4J1wDlwK58F74K3wXm23ZfAeeB9cDe/X9lsBn4R/gW/Ah+CbcA3cq/n9UPO7H66Gn6qu46/eC1OHDuNvhNZ/JVgdVoG14Xk6HlaFLWA1vf5iYWdYA3aB0TrOeeAYdVd7bXq/ShgH+3idtT91gZVgV83vCbmXtLdjXeSwxjtP41WDUbAWrA7jYTNYB7aCdWEPWA/2hh203RrAQTBBx72GcDJspPNIY1ik4a+GTXWcawYXwOZ63bXQdmsJH4Ct4MMwET4Pk+ALms6LMFntvrXR9mqr7dVe26uDeb3ofRps53C9dND26qjXSye9Xjrr9dJFr5euMAl20+umu46nF5nzid6rwKcd5pMjer38AGuoPZ868ATsAH/WeSRU7aud0vr8FY5Uuz65atenQMPJ/Sm8CbphKQyBi9V/CTxG+BV6nif0PE+pv98O4hHNd18HO4hTtH9kwUh4BawHr4QNYKGOWzmwCyzQflFotW+44Oz2CMW+4VnCncJh27iK27PZUPL/8Rx3me2aitus+Xef5y7HXs3/zFbNl7SbMZ62Q7ohY5A8ZCGyBtmOHEBOIDETsKuDDEPykFJkzYSgvZrgETyCR/AIHsEjeASP4BE8gkfw+E8d/6Xn/3lG5495/v9kMnsN9bz7YvJTdmG+PL1f6N0uEf+MFPbv6lv988lWbg4B5P2A3xoY5rNrGbLPaf92/6pY/vE9u953+HB5titVUyIvBeaz9lGkUBKDVOCZM/9viJGu8n6DK/+3tl/lN74BcV1XpF/edn73lT8u7H1F7+Tyf7Nz/m2uvN/I/rjfvM71t7ajso+vda1tkKzP2HXz73PrvtRoWE336evpPn2i7su3gRN1f/HE1Cij1rQo27v9xbL/Y9/vOYiU6n5OrOzh2PdoQnUPZoF930X3VHQ/RfdNlgbsk4xBOk0L7mMEj+ARPIJH8AgewSN4BI/g8U/2zgM8iiIKwHfpgQAhpFGNUow0A0ZAQQyIiggYBKUIJpBLM4WQAkFRo2IXjYodNfaoqNixx94VO/aoqKioiKjY/W/ydrN7mQt3BrHt5Hv5b2fnzb6ZndkyMzvjuH+e207z/3mK83JKm1oA2tYGwDs8us78f87YW2f+v2DHizjz/znOcY5znOMc5zjHOc5x/2+3nfr/PWrq/23w7h/ivPs77/7Ou7/z7u84xznOcY4=
*/