/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   matches.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a predicate for checking if the provided string matches a regular expression.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_MATCHES_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_MATCHES_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The metafunction detects the matching expression kind and returns a tag that is used to specialize \c match_traits
template< typename ExpressionT, typename = void >
struct matching_expression_kind;

//! The matching function implementation
template< typename ExpressionT, typename TagT = typename matching_expression_kind< ExpressionT >::type >
struct match_traits;

} // namespace aux

//! The regex matching functor
struct matches_fun
{
    typedef bool result_type;

    template< typename StringT, typename ExpressionT >
    bool operator() (StringT const& str, ExpressionT const& expr) const
    {
        typedef aux::match_traits< ExpressionT > impl;
        return impl::matches(str, expr);
    }
    template< typename StringT, typename ExpressionT, typename ArgT >
    bool operator() (StringT const& str, ExpressionT const& expr, ArgT const& arg) const
    {
        typedef aux::match_traits< ExpressionT > impl;
        return impl::matches(str, expr, arg);
    }
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_MATCHES_HPP_INCLUDED_

/* matches.hpp
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
*/