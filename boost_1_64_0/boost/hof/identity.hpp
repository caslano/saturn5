/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    identity.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_IDENTITY_H
#define BOOST_HOF_GUARD_FUNCTION_IDENTITY_H

/// identity
/// ========
/// 
/// Description
/// -----------
/// 
/// The `identity` function is an unary function object that returns whats given to it. 
/// 
/// Semantics
/// ---------
/// 
///     assert(identity(x) == x);
/// 
/// Synopsis
/// --------
/// 
///     template<class T>
///     constexpr T identity(T&& x);
/// 

#include <utility>
#include <initializer_list>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof { namespace identity_detail {

struct identity_base
{
    template<class T>
    constexpr T operator()(T&& x) const 
    noexcept(std::is_reference<T>::value || BOOST_HOF_IS_NOTHROW_MOVE_CONSTRUCTIBLE(T))
    {
        return BOOST_HOF_FORWARD(T)(x);
    }

    template<class T>
    constexpr std::initializer_list<T>& operator()(std::initializer_list<T>& x) const noexcept
    {
        return x;
    }

    template<class T>
    constexpr const std::initializer_list<T>& operator()(const std::initializer_list<T>& x) const noexcept
    {
        return x;
    }

    template<class T>
    constexpr std::initializer_list<T> operator()(std::initializer_list<T>&& x) const noexcept(noexcept(std::initializer_list<T>(std::move(x))))
    {
        return BOOST_HOF_FORWARD(std::initializer_list<T>)(x);
    }
};

}

BOOST_HOF_DECLARE_STATIC_VAR(identity, identity_detail::identity_base);

}} // namespace boost::hof

#endif

/* identity.hpp
Ot4yMVKX807ZQqswHPjIhmFwh99orTcle6n3OKF7e12iEO9kSQYUTt1urhHm8cOJSGkPGs82whE4gPc0oCJ7RLiG+2FQNcYNlHZzUbT25xGiQmFiH6Sz2PRl22NN9DMiHYzezCbNtlXk3r/YLJE/3CAJmYs2xWRmyLzkJMzguAOdmSmv3QkKMjxi7NJoX+FqldwTfirBNEZPGGhX4X+DmAc4Mrf3R2qvJn0x38QnhtCf+aTrobwlPQuxNNX0NvnG3etJ66dt+bZmomEQ0BvpZh9Gf3BdEnTVNN0VUtWmUrSjhA3Y4Sn7g71yzs9CW33vuvUZXCwywNXvlEH4ATxqYEH3KMpGMbIIIQAgMlU0op5nC+8qXbMPAAJnbCbkpqYMfZFtul/XOg65xzqRWfeH7PzlcxKM97XUpvMl9CZGDx6Ee9DeTAUZmDTWEINR1/o+/Wwi3QyIJgast694/8LtpQ0Er43o1j9ajnAntEhRt2PtBGFQD7EEHlaTxIGueFA3kU27GLpkkRYkdyDNtWs2ytlPaPCh6772ByJjdXhiklZsZJUfMj+1qVS6IQ==
*/