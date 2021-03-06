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
kX/mieR+7U7amJQb+3IlG64Uyfjd3k0FejAQtRPuL8Wwn9Cbci4KzYW7yBjkP/M12BIKhrJ9tB+ASMRqw1OKvxbBgrxo/e9Yt5BMgvvtsrJrfvPK44WAyVE/Kl+OOO0sAxaRuqs0sWT+ZbXO5md0Ivl1b5zd14ETvujCCnZRxL8qtLeM0er7309EbQgNJuNfelHElRqhokb3lCt4eXnvH9z00OyOl9/wuXDMgcDC1kvrIdENulAi3SAQ0f+zunXf+Gb6IZXfq40DO3gr3jW3UpVWSuLHZsOdS5CmqgMKURXJirNrF98djmg4Jc1Nfns0MyeET/2W1B1a8Rv80qFgt+HM/VzR1xyFv8Duld4L39JPUQDI94X+QH+YijxSsO7UgJ2j5eNg3DTqJv7KXXX9dDp1mzps1erZlFgHE/HcUuLGiyl402kzxoDM1WSsXzecK49CRUaYyQhNYsUd2l1OK5HHz0TJA9/jWp1caLcsLTtxx6b1FQq0D1fWVJFJ07wCFKpw4jOTRcIQAtQ4b0VRUdy8Qm97mlNQAYZmaCD9xcR+RbAT9HZeQBgkrg==
*/