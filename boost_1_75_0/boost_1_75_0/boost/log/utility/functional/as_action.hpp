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
02Z06YQrGLFUARHJK3SFqoC45h4aJkbLb5AWqBMnmLEaO04CXkVpAeYFZgzLB974X1x18UIMMNgWoLIgFAnUjcb62Jl0Bb5iQZWgDSSGojtRVm5HKXKXIbGfpSenrjSKx2gK5KMNj72efyWej71VbczNrz1P0MBeGqqvnngKoYgdVCpvgLxvtL9IwvwhIrpbPbis5gwA0PnYVWt0ic8wloxh1WnVEGphuEZGfTVSmiR36gtGcpER9nYM0Gm1WXjyUGLxKBia8eVh1bUQnKVW1taVcYBfsx4WFHBDSzGE5d9N8YlRTTDsKmsl1rkWuYb4xSt7RjIhzCvP0CbWwqhK9eUhIkcxqv/xF9PajOrP8MQw3UVOoUewhIY8ta7tfUw/9OP7zcjKPOLccq/xGgC6UXCtI8G9/g5v+caSLv848Tpi0NSnq5TXruZ/iT8XfW3CWZSh/ClJNFdE0GP5o+m6ED3LuNul/2B8GQ8/ENmjo8d2MHoYFhttb36NQbg27ZvZ9vxi7ofsxVS/V3y4Q1En4Jg60n7WYbN9lJZ/LYhqYxd0JMUm17p48DUThqn1t2h8vyeevMazCZ4Sa7L8M5ysRc6F09sbn1gFaM4w/C4iS1BHvcszuD0jUqyTMipGpLY+kvE7mLz2tGtD0wx5HC5AfMLhIBW6oD6O/se430FSjHjioVR9vktJ8aUkXjoF1mkcpiwduB0zCoJL30dM
*/