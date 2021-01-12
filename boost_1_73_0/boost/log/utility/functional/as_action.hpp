/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   as_action.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains function object adapter for compatibility with Boost.Spirit actions interface requirements.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_AS_ACTION_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_AS_ACTION_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! Function object adapter for Boost.Spirit actions
template< typename FunT >
struct as_action_adapter
{
    typedef typename FunT::result_type result_type;

    BOOST_DEFAULTED_FUNCTION(as_action_adapter(), {})
    explicit as_action_adapter(FunT const& fun) : m_fun(fun) {}

    template< typename AttributeT, typename ContextT >
    result_type operator() (AttributeT const& attr, ContextT const& ctx, bool& pass) const
    {
        return m_fun(attr);
    }

private:
    FunT m_fun;
};

template< typename FunT >
BOOST_FORCEINLINE as_action_adapter< FunT > as_action(FunT const& fun)
{
    return as_action_adapter< FunT >(fun);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_AS_ACTION_HPP_INCLUDED_

/* as_action.hpp
7mWM3lL+97DxNgv9xAqxExL+NPo5QKqU1kgvSn+BFB4mz5bvhZYeCTl/X2mEhfQP9UqtOm/VLdIv1xfrS/Sl0Jq36Hfoy/UV+kp9lb5aXwOKntTX68/oGyBfr+ivg77N+hbQ+LH+Oegs9fb1DvAO8t7hNTAWZB3pxQwhPgTrFuyHGF8/3zDfO4TmVG5cTsW+7DLM1HvY3wtDxbD4S3EU5uBF8hr5M3kiLJv+qoo17G/qYdoE
*/