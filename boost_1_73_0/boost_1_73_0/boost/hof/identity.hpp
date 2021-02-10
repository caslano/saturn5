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
ZXIvcGFja2FnZXMvT1M0MDAvaW5pdHNjcmlwdC5zaFVUBQABtkgkYOVae3PbNhL/X59iQ+eqx8ik7Ot1mjTuVZFkh1frcaKcjBM1MkRCFq8UyRKkHTfRd78FQJCURNnONX3MHDORKHD3h93FYnex9METY+76BltWDhpf7qocwIPXTPyf4YXfnGEUBf+hdlxOPJt9AvkPmab4/cAUBuQcn2Z1eJDjE9QExyyd4wW/n80emGbKBeMfBmeczvgtjlQOkK8ThHeRe72Modapw9GzZ9/CIRy3jltN6BLfpR5YMfXnNLpuwgtHjPywJB8+6Ix+3wQaA/F0ATRZugxYsIhvSUQB7z3Xpj6jDhAGDmV25M7xh+tDvKSwcD0KneHo0hycNeF26dq4tnAXJMCWQeI5sCQ3FCJqU/dGQoQkiiFYIDdiOy6LES+J3cDXcWoKMY1WDCH45MRjAZAb4npkjtOQGJZxHLLnhmEnkYeSG05gM8NWquvLeJVqcYkSrMgdBGEMcQAJo03gdE1YBY674N9oChwMk7nnsmUzFwUn8h0jiIBRz0MoZHMpkyJTsFLLNDkVhCitG/MvFviMz3S7DFYbhGhCBFkkkY/ToAmQxgnQwE1IfIdGglYorWZIrSlMu2dJclkdCHyUBLS2Baal
*/