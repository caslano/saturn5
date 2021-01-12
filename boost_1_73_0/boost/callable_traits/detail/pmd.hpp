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
f5sr0nzVS0ZxjSaFI7r8VSTvIbu88aGGGi3vc8RbZ/n3O+RVzZOM02y/2R5KyM+KR34Ufxjx8re3PIe9u//2Ju2hkO3B+Z1h3e4UHrC+1Wlr31KE51n8jnZUadpZv8fpdqF8Sdd9Zb6sf4SRDolX6VnLVmFOnebbf9NTeiT+Q1aYU2cUd9iKc+qLfqO7ROoeceP5TOo69u8rUf4t7P+A/TvZ/yH7DyT4xQ7ln8byguw/q9D5
*/