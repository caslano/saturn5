/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    decay.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_DECAY_H
#define BOOST_HOF_GUARD_DECAY_H

/// decay
/// =====
/// 
/// Description
/// -----------
/// 
/// The `decay` function is a unary function object that returns whats given to it after decaying its type.
/// 
/// Synopsis
/// --------
/// 
///     struct
///     {
///         template<class T>
///         constexpr typename decay<T>::type operator()(T&& x) const
///         {
///             return boost::hof::forward<T>(x);
///         }
///     } decay;
/// 
/// References
/// ----------
/// 
/// * [n3255](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2011/n3255.html) - Proposal for `decay_copy`
/// 

#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/unwrap.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/detail/forward.hpp>

namespace boost { namespace hof { namespace detail {

template<class T>
struct decay_mf
: unwrap_reference<typename std::decay<T>::type>
{};

struct decay_f
{
    template<
        class T, 
        class Result=typename unwrap_reference<typename std::decay<T>::type>::type, 
        class=typename std::enable_if<(BOOST_HOF_IS_CONSTRUCTIBLE(Result, T))>::type
    >
    constexpr Result operator()(T&& x) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(Result, T&&)
    {
        return BOOST_HOF_FORWARD(T)(x);
    }
};

}

BOOST_HOF_DECLARE_STATIC_VAR(decay, detail::decay_f);

}} // namespace boost::hof

#endif

/* decay.hpp
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
*/