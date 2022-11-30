/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_FUNCTION_OBJECT_HPP
#define BOOST_CLBL_TRTS_DETAIL_FUNCTION_OBJECT_HPP

#include <boost/callable_traits/detail/pmf.hpp>
#include <boost/callable_traits/detail/default_callable_traits.hpp>
#include <boost/callable_traits/detail/forward_declarations.hpp>
#include <boost/callable_traits/detail/utility.hpp>

namespace boost { namespace callable_traits { namespace detail {

template<typename T, typename Base>
struct function_object : Base {

    using type = T;
    using error_t = error_type<T>;
    using function_type = typename Base::function_object_signature;
    using arg_types = typename Base::non_invoke_arg_types;
    using non_invoke_arg_types = arg_types;

    static constexpr const bool value = std::is_class<
        typename std::remove_reference<T>::type>::value;

    using traits = function_object;
    using class_type = error_t;
    using invoke_type = error_t;
    using remove_varargs = error_t;
    using add_varargs = error_t;
    using is_noexcept = typename Base::is_noexcept;
    using add_noexcept = error_t;
    using remove_noexcept = error_t;
    using is_transaction_safe = typename Base::is_transaction_safe;
    using add_transaction_safe = error_t;
    using remove_transaction_safe = error_t;
    using clear_args = error_t;

    template<template<class...> class Container>
    using expand_args = typename function<function_type>::template
        expand_args<Container>;

    template<template<class...> class Container, typename... RightArgs>
    using expand_args_left = typename function<function_type>::template
        expand_args_left<Container, RightArgs...>;

    template<template<class...> class Container, typename... LeftArgs>
    using expand_args_right = typename function<function_type>::template
        expand_args_right<Container, LeftArgs...>;

    template<typename C, typename U = T>
    using apply_member_pointer =
        typename std::remove_reference<U>::type C::*;

    template<typename>
    using apply_return = error_t;

    template<typename...>
    using push_front = error_t;
    
    template<typename...>
    using push_back = error_t;
    
    template<std::size_t ElementCount>
    using pop_args_front = error_t;

    template<std::size_t ElementCount>
    using pop_args_back = error_t;
    
    template<std::size_t Index, typename... NewArgs>
    using insert_args = error_t;
    
    template<std::size_t Index, std::size_t Count>
    using remove_args = error_t;

    template<std::size_t Index, typename... NewArgs>
    using replace_args = error_t;

    template<std::size_t Count>
    using pop_front = error_t;

    template<std::size_t Count>
    using pop_back = error_t;

    using remove_member_reference = error_t;
    using add_member_lvalue_reference = error_t;
    using add_member_rvalue_reference = error_t;
    using add_member_const = error_t;
    using add_member_volatile = error_t;
    using add_member_cv = error_t;
    using remove_member_const = error_t;
    using remove_member_volatile = error_t;
    using remove_member_cv = error_t;
};

template<typename T, typename U, typename Base>
struct function_object <T U::*, Base>
    : default_callable_traits<> {};

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_FUNCTION_OBJECT_HPP

/* function_object.hpp
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
*/