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
4gAfnDwfhRrzIpd582YQsKCsnPcOS66nl3cq/VkHyRtPHDI8f3JN9pnC4ke79+4fQH1TCCJSZvu9Q5fHaongjcmRFkTciwVGcRiG44pyBd8qBbagN1tkpiHse8+9RJylQXbeP7VPtaG5MFJefJovKpQjUctPrnPTB+ZvTBmRMD6R9Fb2dyWz8HesVJsbMWlX7IgNRqLHXEyj4TigjKqYRCeoOu6xDyJxHJUt8A9ipNhbg2bZbrzBuIGkPjhJoqyM/acRyjuw3EtuZCTShOb570xrr1IS7WHfekJHb79hXS+BbP7NB89zjrkgNNojqlci1TJyG/Ez9qc3z3HG4E9H8kv5O3cYDn+Fn1pOlms11Eql04yQ+VH7wGfBqqpMY/b5XaK91PI4MMwzkp/qdoiJxiz5u5hpi7nuIgC47WyzQruY0Rk4xM5AFLDtS5TqQ4lMzwFQM2gbObflxR3aY21lxXWfKjcwvs1kZy9PBGN6ZoHAQQF1JmgrV8bPtHuNA+UTUJI/plJI0RxwX5hdatQBoTa9gj/Xn0Tw3BOBMmjRDy8Btfnz4qX4nROK8A==
*/