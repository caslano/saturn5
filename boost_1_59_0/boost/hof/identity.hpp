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
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
*/