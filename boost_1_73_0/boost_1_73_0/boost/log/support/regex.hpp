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
y34f+KnVUOfitzLO7cQi95rsnVdbhpheoqz9B0mI01tZ+aFfQ+81TWPiz2wSFO9fk+8vhtPhh0O4QRvddEl5fYXze437ELp9iiin69SFQOHCsk8rB0v4vlKqTh7Y3emlhgvGFSrvqBS/fX1htWpECmNGsYQXg+pqR5OorcMTAYdiNQhXxlHbSl+mvYIHhh1bnUoeVoiHZdDDrn069Pj76Go0tRnio+bsBA962OxPh1fj84kdnHEjHGh8STDlENstt/nqSQ0Y6pmevT8V9wUEeu9j+4GFjs/UdUjt+9p3R07D+5vMEpomM2oHqfb55K6KoXWCYYjpgWK4jTPQd9XAsEmgkeKYwKVewCpXMChXGXpts2y2iG0yTuVJT9Ffr0KjTHIyy/u2kLBdkvvHBsWnBD5k2Ixh65sZ/WzRyhPWaVtjEzhqP97GQ33s0bq2Rk31sf17cu59GH142i48bjj5jgE4/5HctnFru9/rDo1efnEGFKi7mIMOPSWhd00p8NC32Qe1z9nb1iXd1zw8v+m2tT2bArwfnV3gNP7v69Hl1egtCmPrpnHyw3ByPTz7srP/GU0vUXhvPDk9/zIIHI5xSL6sD29Uc2uvjMqSbHFOYK8KNDbJ1Ijaryy6qrN/UiC3lUfa3RMPzqc9pdFi
*/