/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   support/regex.hpp
 * \author Andrey Semashev
 * \date   18.07.2009
 *
 * This header enables Boost.Regex support for Boost.Log.
 */

#ifndef BOOST_LOG_SUPPORT_REGEX_HPP_INCLUDED_
#define BOOST_LOG_SUPPORT_REGEX_HPP_INCLUDED_

#include <string>
#include <boost/regex.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/matches.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! This tag type is used if an expression is recognized as a Boost.Regex expression
struct boost_regex_expression_tag;

//! The metafunction detects the matching expression kind and returns a tag that is used to specialize \c match_traits
template< typename CharT, typename TraitsT >
struct matching_expression_kind< boost::basic_regex< CharT, TraitsT > >
{
    typedef boost_regex_expression_tag type;
};

//! The matching function implementation
template< typename ExpressionT >
struct match_traits< ExpressionT, boost_regex_expression_tag >
{
    typedef ExpressionT compiled_type;
    static compiled_type compile(ExpressionT const& expr) { return expr; }

    template< typename StringT, typename CharT, typename TraitsT >
    static bool matches(StringT const& str, boost::basic_regex< CharT, TraitsT > const& expr, boost::regex_constants::match_flag_type flags = boost::regex_constants::match_default)
    {
        return boost::regex_match(str.begin(), str.end(), expr, flags);
    }

    template< typename CharT, typename StringTraitsT, typename AllocatorT, typename ReTraitsT >
    static bool matches(
        std::basic_string< CharT, StringTraitsT, AllocatorT > const& str,
        boost::basic_regex< CharT, ReTraitsT > const& expr,
        boost::regex_constants::match_flag_type flags = boost::regex_constants::match_default)
    {
        const CharT* p = str.c_str();
        return boost::regex_match(p, p + str.size(), expr, flags);
    }
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SUPPORT_REGEX_HPP_INCLUDED_

/* regex.hpp
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
*/