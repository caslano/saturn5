/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   support/std_regex.hpp
 * \author Andrey Semashev
 * \date   19.03.2014
 *
 * This header enables \c std::regex support for Boost.Log.
 */

#ifndef BOOST_LOG_SUPPORT_STD_REGEX_HPP_INCLUDED_
#define BOOST_LOG_SUPPORT_STD_REGEX_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_NO_CXX11_HDR_REGEX)

#if defined(__GNUC__)
#pragma message "Boost.Log: This header requires support for std::regex in the standard library."
#elif defined(_MSC_VER)
#pragma message("Boost.Log: This header requires support for std::regex in the standard library.")
#endif

#else // defined(BOOST_NO_CXX11_HDR_REGEX)

#include <regex>
#include <string>
#include <boost/log/utility/functional/matches.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! This tag type is used if an expression is recognized as \c std::regex
struct std_regex_expression_tag;

//! The metafunction detects the matching expression kind and returns a tag that is used to specialize \c match_traits
template< typename CharT, typename ReTraitsT >
struct matching_expression_kind< std::basic_regex< CharT, ReTraitsT > >
{
    typedef std_regex_expression_tag type;
};

//! The matching function implementation
template< typename ExpressionT >
struct match_traits< ExpressionT, std_regex_expression_tag >
{
    typedef ExpressionT compiled_type;
    static compiled_type compile(ExpressionT const& expr) { return expr; }

    template< typename StringT, typename CharT, typename ReTraitsT >
    static bool matches(StringT const& str, std::basic_regex< CharT, ReTraitsT > const& expr, std::regex_constants::match_flag_type flags = std::regex_constants::match_default)
    {
        return std::regex_match(str.begin(), str.end(), expr, flags);
    }

    template< typename CharT, typename StringTraitsT, typename AllocatorT, typename ReTraitsT >
    static bool matches(std::basic_string< CharT, StringTraitsT, AllocatorT > const& str, std::basic_regex< CharT, ReTraitsT > const& expr, std::regex_constants::match_flag_type flags = std::regex_constants::match_default)
    {
        const CharT* p = str.c_str();
        return std::regex_match(p, p + str.size(), expr, flags);
    }
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // defined(BOOST_NO_CXX11_HDR_REGEX)

#endif // BOOST_LOG_SUPPORT_STD_REGEX_HPP_INCLUDED_

/* std_regex.hpp
7S3ko1RartlIBlQhNP5rluWt05w+K2zus/y1/WEV6j+drDhELZ9hm4Bg0XpKEZEpaluoMlYeCB827VorX6VvadjKFJl18KR11GKeIr+NTVjsxpNGGBpOrEIs3hofrZ4qW/8F5DlGlbJ1ho14DgwqLI85RcsPluvAXeevFruZdgP+79W85S1gDYdBb7TAZNHDWnrlU9xNllez2yXuRvP5aLpcYXaB0XQVxX5Opmd89YrNHGjTOPJs7qDqRisqdp4ft7Kkr0yu24LQC9Zq4Sm0zbDqJYkyIf4qPOXWlOrhgIsPyCvpMIj9G1nzqLnVlp/bS23XUo87JAZbxuG3JOmT4UtFNnjvDwgc4zdQSwMECgAAAAgALWdKUrhMV9ECDAAAqycAAB8ACQBjdXJsLW1hc3Rlci9zcmMvdG9vbF9wcm9ncmVzcy5jVVQFAAG2SCRgvVp7V9vGEv/fn2Kuc9JYRtjmERog0BICXE55FcwpuQlHR7ZWtm5krSppMTThu9+ZXa1eljG0Odcplr07Mzuvnfntut32j3s1oA0LX5b8s/CFT8lxEfH/smFST21Z30H9Q64v+Fy0SBdylu+WAYtZvkNLsljpKu/ps2UtWugL6UZvXeL8YtFHHEE24tzn4UPkjcYJtPYNWNncfAfL
*/