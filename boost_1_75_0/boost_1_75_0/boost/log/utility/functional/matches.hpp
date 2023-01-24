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
EhD0VsAfNRMuGKSq0a82wMf/RD0ndph+oHhtr7VdCtvPcLgGrVfcrny4Sog7X1SFRFcr603zDdRNLS5t69Tpp6mCdFWuyv3sHHROLxBdPajS4MzTIZuRXwcLKIhSV4sI/zeIfzGotn6I10F24grnYvPRqev74WXxDWmU5J+mKnPuJok+9DaimmNMQw0zG3FpllMUe19pOSJJM73um1EgzsZZpU1xsdyrHeXu+Uz3X1BGvrq/WAZ9ncDnaNnaqq+SY3qNSGEvg2sFBiIeveHWVcIxAQGittA89Rw9GJhjkevpsn7Ix3u7ZCEdRxlb8oC3ow6wpdbqKn/cikw3SRvUiiH/IlAllMtT699huIuNAyN2uZlLMNXb4Gp21zB0ir6mDGYdkjzbuPAyD4j8tUeSIYqKSJCj/ZUpSOWeZtE7L/ttXZFlJrsTOmOR9lta+fXeoHqmkt3NdfcL/ASxYYMYDjwTKSMjiscEUHu/SK9J38D+kBnXybuRgR1lpvUHorKT3lGba+c6vKB6TavCPF23g2SvdYwavEYP0zx2XXW75T6iDFpJBPUTIbCPzh05GQZaH2IEwpIZ4ktApq/EWTdVfiV+qwswmmXGMbCbH5+VzB4TKreclXAPtJn/8wmKVHjepIVvQkeB9lbYucR+2i5Ojpw1Hvvg/FVfldPO9JhKfDI3Yo9u/UZmoIoH1nybq5jrYTq5MJjXUmoJNMQl
*/