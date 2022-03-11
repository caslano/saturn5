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
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
*/