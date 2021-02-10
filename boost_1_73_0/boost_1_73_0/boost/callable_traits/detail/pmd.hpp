/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_PMD_HPP
#define BOOST_CLBL_TRTS_DETAIL_PMD_HPP

#include <boost/callable_traits/detail/forward_declarations.hpp>
#include <boost/callable_traits/detail/function.hpp>
#include <boost/callable_traits/detail/traits.hpp>
#include <boost/callable_traits/detail/default_callable_traits.hpp>
#include <boost/callable_traits/detail/utility.hpp>

namespace boost { namespace callable_traits { namespace detail {

template<typename T>
struct pmd : default_callable_traits<T> {};

template<typename D, typename T>
struct pmd<D T::*> : default_callable_traits<> {
        
    static constexpr bool value = true;

    using traits = pmd;   
    using class_type = T;
    using invoke_type = T const &;
    using type = D T::*;
    using function_type = typename std::add_lvalue_reference<D>::type(invoke_type);
    using qualified_function_type = D(invoke_type);
    using arg_types = std::tuple<invoke_type>;
    using non_invoke_arg_types = std::tuple<>;

    using return_type = typename std::add_lvalue_reference<D>::type;

    template<typename C>
    using apply_member_pointer = D C::*;

    template<typename R>
    using apply_return = R T::*;

    template<template<class...> class Container>
    using expand_args = Container<invoke_type>;

    using is_member_pointer = std::true_type;
};

}}} // namespace boost::callable_traits::detail

#endif

/* pmd.hpp
Xsuuiqjt8ZNZc8yFRLL1WGYfbfnmmQ6KVLxaJHaQyXm2wxnd4ZwjEhg0G8zYu8JgxeLt8Dx2WefeieT6rIaTPIQkgoQjKflol9LTdL0Zv08rqTW9Yy+ZUx+FONNE3Mg2hWyNtcjei4lzQrr5oZypXRkLPWWoec1WjKaaLqZ/3EB//eEmrW3S4uEJNqTrKuZ5yNXWZD+vxah82AbKXGqbx/iMrAw/Ren5/gsCS0/UKwW2t78hsZe4IUZ+foGP1DW8ko+fs2w8L2dybVrG7Pt3w3U+B1f7RcOYRWOaGZTTclB5jqR5oOsqA+Pbt4cbRdamP5IsqvNIrl/FVB16537yPpwyIPneURV0/9FZ2Ozb1pVEQZjKIunbJvJ9YCzyDukPKAu7df2J7Uq3IHLlz73BcbM3bvZ6SWqeydjESp2qibRNiVS2r1m0ZDtudJgful2qMdoM/GqUfxzDsdlufjABm/kxfTkW0dtLFCDzE9e31ZSIe3r8EuFCZbW6B34cz6/fSw+uR2k1De+p9h7bVk2qSmHDqvPnTZuvaHG509iFLunVLCmXWILoozXnHr2jFZ/CiJ2KaaXvSH/GeCSgSnVlkG46nsCUfowiNa2FhunlVzHn6inITUPidgNMTidgeNRzGfliBd2LNZpYRcHn
*/