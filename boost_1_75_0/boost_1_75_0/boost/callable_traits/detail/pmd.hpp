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
8M3mwp9HFb50iCkXZG5dxkbl+LYWEQaixA6MVIhyLgcmVuvxzarNejYPa5+rCYPXWszaxlShbfwPkXeXZEVt49FhDMxniS4UVKMV5JCv4+hZBWnQJ1bpGr0qc/wINBDkoBFQYAvmQup0ggOpVc2pLskR47nVi4T0ZjsGfvhAg+2KHBKsjbnadkhVOdzBdwNjLZ6Hj+MQwt1FHX2pjrxqZCNZ5ZzktTEMgrZ7buF505R3vTHmhE9wiR496ESIjLcpLhmp8GKWkzReaooQS+q7G+JZPTcsXtMB25H6cgAKSYUFgjas3WAZIVnwZq8sceUFYvJgicKfExZbsjWEvggZh7PutZfAEnE7vdkDnCXd8HW4M66s7JiSWPjGK8P3ckPoE7J2vQnuO0tB7Hpnr2yVsusc5WsEUXRnTkl2zPkMZ0P2QnUbSrxYBIgsUBm4g/d9SnBFQudivWgUJydI2RKsVR+u1W6ol8m2l9h8AVi48AgoWqJP3uELdA7H+uQvPDWeZFjpsSBz2N0V9ySLW5+cSBQZqQD1QW8DV310Iz2IeGRLTvrthIqBMAS8ztBmC8Ydn5JcchY2g/CJbirfHvpAHCdlN5Tk4bjkOhRrpAAaCetN5+PwJK1lnd51p+HlO+knNCwF7Ez9dkiBzu0NzYtwawN8bQ2tOw8tGoABkEiA8vHkoAsD0kEcH/KYdjRVlhFvYCNN1mxEZuDvPl40
*/