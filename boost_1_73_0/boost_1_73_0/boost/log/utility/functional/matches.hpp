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
AC1nSlLuYuxp+AIAAK4GAAAcAAkAY3VybC1tYXN0ZXIvc3JjL3Rvb2xfc2xlZXAuY1VUBQABtkgkYK1UW2/aMBR+z684otqUoIyw7mVdu2oI6EBjUDV0FVKlKMQnxJsTR7FDi9b99x0noYyuFS8NFzv2d/OxE6/9epcFbTh4BdUvoIvainFZyJ8Y6efRQfAA9YdYt9QeMvFgR3kIHDhMeQC7ogSNy5npB8Eho1uTzfx5hnkbmC6NEM0w+zLfFHyVaLD7Drw/OfkI7+C4e9x1YRBmHAX4GrMlFisXzlg18iUJ7+87Cs9dQA2h6DRS84QrUDLWd2GBQH3BI8wUMggVMFRRwZd0wzPQCULMBUJ/drkYT7+6cJfwKDEiG1mCSmQpGCThGqHACPm61sjDQoOMiU7ijCtNgqXmMuuQN4LGIlVGw9iHQkkI1yEX4ZKMQg2J1rn65HlRWQhK7zEZKS/aLr+T6PRxJQsKkYYbkLkGLaFU6IJBupBKxmPTUkFoMC+XgqvE3aUhq4x5sgCFQhgt4nFUdWwEvymPa2CQU2KuTaNkpozVXSLTPSDV0ajEZZGREdWBQExSmV0oM4ZFBa5WvrVoaloV+MWt2eVlIDMKA62eD2O/BctQceXCzXg+ml3P4aZ3ddWbzhcwu4De
*/