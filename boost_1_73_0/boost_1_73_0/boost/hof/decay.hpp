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
n+FAvCK1f2mVI5KqEUuAia1xyHCOuK1xZdjqlyuJrQKQaXh3NDRd7MOEieqAVtGoLWDxmqG2MSTJbAfpJmmYTgWgWkWMzgQwo983+6ki1XLMjsBLNGFz6A2bf8YWl85antlRcGtcmxO4IcIaTpRNlQuE/2nx1cBwLycj9aIyLVEJYP9Q/rY0o/KPvMvsjQbnF++Sb9tKSDmRXu6Xv4yTnRZ9apbstJ54jcv5xIKMOUxSYdwToZbdKL3oZmjZlEsJT4RbHkdpSXF6LeAT4Y7HHSSxx6cy3Mj4kDuOodrlMxQwgKtD0uWadIHAiXDDY4acDJAZkEoO8aP/MrBwVnFsssXAvwsItanbUrHPuAF+s2kj8OLcVJRaBuqbQZdQJrKFaFceN04zJiEjegZDGadf1ZKSFqJy44l3Rde4FqJxgEhTuBaucNBp9m8XZC4uu6QePjxpCUEp7Qetu9g+TaNP2v1iG0frxJG8/Amb8+GXxKp8v707SZ53EiIkULT2fNaSP+OW7nhofqCSIiZMMMZo45f75WKmMYNFC9niFHMHstS1TfivlzDaRihn4A3X/KWWp5RvZVIg4t2LKFbf9Hqu1SVb0gUww7adibr7to2CeaY/GVPt6ALSeKhcyu8UBzLU3ZxnKJJvGi5UAaBa
*/