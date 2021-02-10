/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   support/xpressive.hpp
 * \author Andrey Semashev
 * \date   18.07.2009
 *
 * This header enables Boost.Xpressive support for Boost.Log.
 */

#ifndef BOOST_LOG_SUPPORT_XPRESSIVE_HPP_INCLUDED_
#define BOOST_LOG_SUPPORT_XPRESSIVE_HPP_INCLUDED_

#include <string>
#include <boost/xpressive/basic_regex.hpp>
#include <boost/xpressive/regex_constants.hpp>
#include <boost/xpressive/regex_algorithms.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/matches.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! This tag type is used if an expression is recognized as a Boost.Xpressive expression
struct boost_xpressive_expression_tag;

//! The metafunction detects the matching expression kind and returns a tag that is used to specialize \c match_traits
template< typename T >
struct matching_expression_kind< xpressive::basic_regex< T > >
{
    typedef boost_xpressive_expression_tag type;
};

//! The matching function implementation
template< typename ExpressionT >
struct match_traits< ExpressionT, boost_xpressive_expression_tag >
{
    typedef ExpressionT compiled_type;
    static compiled_type compile(ExpressionT const& expr) { return expr; }

    template< typename StringT, typename T >
    static bool matches(StringT const& str, xpressive::basic_regex< T > const& expr, xpressive::regex_constants::match_flag_type flags = xpressive::regex_constants::match_default)
    {
        return xpressive::regex_match(str, expr, flags);
    }

    template< typename CharT, typename TraitsT, typename AllocatorT >
    static bool matches(std::basic_string< CharT, TraitsT, AllocatorT > const& str, xpressive::basic_regex< const CharT* > const& expr, xpressive::regex_constants::match_flag_type flags = xpressive::regex_constants::match_default)
    {
        const CharT* p = str.c_str();
        return xpressive::regex_match(p, p + str.size(), expr, flags);
    }
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SUPPORT_XPRESSIVE_HPP_INCLUDED_

/* xpressive.hpp
sNpb7Znw0Q485sNVwoIBi0YmvHfkyK9j+/6+E7NdE1gCtt9JRfXHXgwxd5OpHTHAz743ZEHMHLBjcFg8jLwBfvECSMYMXM9nsH9+8en47MiE6dgbjknIAxcQj7nwHRjbdwwiNmTenZIR2lEC3EV2FO54cYICReLxoINrM0hYNIlJBi1v+zEH+872fHuAC9kJjJMkjLe63aGIfNS+6/Bh3B1q8zvjZJJZ8gmVmNgPwMMEEg4iZiYQpQkT7nguPdEhOBiKge/FYzPXBpcKnC6PIGa+T7KQz2OxUpvBVeoek8ggRI29hB4xD2JaajrmkxIh+pGkuCIKcCH0AxI5HN1sgggcFkliableIvWpdPDc0OT6OsADVAaae1dwfNWEgR17sQl/HPf/fX7dhz/2Li/3zvqf4PwQ9s4+kbDfjs8+Yug9XCwCdh9GLMbFI/Amoe8xJ13zx726jVdeMPSFw6CZcO5bMUtE2Bk3q+McHWknrGYmjPiI1KyZwgTyabjxymGuFzA4ONv7cHJg7V9fntxYF5fHZ/3DRrdNSQBcRMCnAYSRFyRuy8CwBENKwBhKWlKK3Uuh3bZMzZAjQ5a6mgumMs8HjIIaoVERRgIoMMFIR9MLQpGAYye22cDNjBGDgN2h430ejGT4MXZvMct8
*/