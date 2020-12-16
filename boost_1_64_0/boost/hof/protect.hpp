/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    protect.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_PROTECT_H
#define BOOST_HOF_GUARD_FUNCTION_PROTECT_H

/// protect
/// =======
/// 
/// Description
/// -----------
/// 
/// The `protect` function adaptor can be used to make a bind expression be
/// treated as a normal function instead. Both `bind` and
/// [`lazy`](/include/boost/hof/lazy) eargerly evaluates nested bind expressions.
/// The `protect` adaptor masks the type so `bind` or
/// [`lazy`](/include/boost/hof/lazy) no longer recognizes the function as bind
/// expression and evaluates it.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     constexpr protect_adaptor<F> protect(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(lazy(f)(protect(lazy(g)(_1)))() == f(lazy(g)(_1)))
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [ConstInvocable](ConstInvocable)
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     int main() {
///         auto lazy_id = lazy(identity)(_1);
///         auto lazy_apply = lazy(apply)(protect(lazy_id), _1);
///         assert(lazy_apply(3) == 3);
///     }
/// 
/// See Also
/// --------
/// 
/// * [lazy](lazy)
/// 

#include <utility>
#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

template<class F>
struct protect_adaptor : detail::callable_base<F>
{
    typedef protect_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(protect_adaptor, detail::callable_base<F>)
};

BOOST_HOF_DECLARE_STATIC_VAR(protect, detail::make<protect_adaptor>);

}} // namespace boost::hof
#endif

/* protect.hpp
Nm8eqYsYgUslhnL/g7L1TmfRni4cDQQV12DtDVzOWbxiwzLu6a5IzvxR9+GC5V6yRw6OpTH6Wj16rRDnHcBOUnNgGWOHLzpRvgyPDXplo7iygjY0E+isT7ffJgdA+HIwBxhJf0UbZMHil3mkPpaBws5pz2otKctvLZx0OD+jOS9OTMmvGCYVhDekhYuXfpyOn22dlaI+Gt3i0ZtS4gNM1nf79angvD/iTGQznfcTfeY28t5av1thp9FVZota9SPl7vRsiVq7ImJuXZdMr6T1wP3p3q+WdBHStny5cWExlDG3dcVyCFyD/R9b9ckK07KlTKzuw6DG17zcqr3pXetc8ckZofy1VdbS8oZBpRc29l9blVE6LtgXjz3xmLWisdu4oK1pV6hEOzjin1621RQHZ8lbDTtClSvOszTXI7REIMPvuLifS0YGl2Dyjn4i4MFuVe0/8A/OMEh5dokihQYa/HD5hypgoHsgRPY/WEb9x8VL3MYl8tHK9d+E2y71MewTS/WLtqPGZgVP9nlks9+0ztCzBbM5CTNopdz5Rsdj4zA2qw63INhw8Qj4HaRTnSP3nZu8p6Bf+suwQsvmJflmqKnlzZG3eYG9rcpGCx8pjvLF+Ft0107RYZHPYK+nRwbWQhat95j12CruDVetzWratmSQc8s2T+wlmSo1N1mT3av2Nr6FLAXN4Vi3z9Z2j+eTORwy++TplI89MyLzNMY3nvP1j2PL31FpyV/rtrqrAD3RBA29297XuSULSaUyyb2m0lJVWfJZwyPs7W1EISsfCuUAnN1VjnZsHzV/jX/inBuS5JNDZvllQDKcyyv5pPRes3zC5Q14nhlu2HPWFMewN119i9qbjiM1He1Pa0QhGF0A//mJFXI4RvyrhaVPvR5VbUnfmm6H3OL8W9Qm9VmtrauWmPsr5iXJk8z3mZ/FbknFz/a/c7PJ/89NpvuLtyY/bzbl33iLSf5dmvx8rgnfffUm+d2Ef6YJf7UJ/w0m/F5T/mcT9fXKX+sZmvQ/muv1sb24XP9CsNujXXoMn+IYbdPFmUGKT2BBtEGxm9cHtuWDr4xoiMLq0zgRv4MwSmbZJPP1J/kRBYr3csyVH9xk+LD8GQdYYaA450Z9AtMEGFthh7iwZr0ykqcIWOxKVmxeYsiS7yBRq7BHkV+ucB13Gwc4zqa7pen4jGb9/EZ54cMNFWI1az5TDoCXwOqyTmENBkhDAXoqmNb2G3WFsfRfCVgByb8lX3Dh4k6Mw7H+OtVY7GZ6BFfoIGeYQDckWulgt7M1IksWosa0cuzA2Uy1l6/SKfGxSDTcxGI8PAaoxoQmYi6T0b77uf/KR+4vnFGOh+ZT3nx5XOTw1dA3b+be5qg3B+QNo/xiGiPigXVqcs/30bPnhngv58hevvdm6jXqMor26+V1+vlFRi/fYvRyDtyqPRoHNAEAlFXCvU4dx9zJLIOkGbQ528UduJC1LvAMLPp5ddYRnKpV2o2cJISguZWD4HycT6KM2g4UivfWcbG2St4KSHNvYmde8cVsrpfGK2f3iG3I689B7yrhdbcUXq9qYBwwQ0fpf79mRvrj6RYaKA+OyBpu6o0JLjPhqyd0JsGgaBwJ4bc5bBdFyCAa8Aez4XPeAzjq6yhaA12mFD/5Nt1L7Go4W//Pzlf6z6aU55M29n97rTQy1MMdQAasjSzFjmS6V7uKpA24CC/6gYqme0HrDOmGg7wnkrgg/Skd59+Aov7PqbUnBhZDJspahlfQ1Z84iUPBo0cykPSccRg9E5ieUq3cTm67iAAb/JFm8d43UlpgCQ4/rPrV39dvMb52A1Nw9Mp1/ZM2kwPoZGkZJAXrDqn7aRPoIh+e8S0=
*/