/*
Copyright (c) 2016 Modified Work Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY

macros used:

BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE - the transaction_safe specifier for
    the current include (`transaction_safe` or nothing)

BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE - `std::true_type` or `std::false_type`,
    tied on whether BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE is `transaction_safe`

BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER - `transaction_safe` when
    BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE is enabled, otherwise nothing

BOOST_CLBL_TRTS_NOEXCEPT_SPEC - the noexcept specifier for
    the current include (`noexcept` or nothing)

BOOST_CLBL_TRTS_IS_NOEXCEPT - `std::true_type` or `std::false_type`,
    tied on whether BOOST_CLBL_TRTS_NOEXCEPT_SPEC is `noexcept`

BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER - `noexcept` if
    BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES is defined, otherwise nothing
*/

template<typename Return, typename... Args>
struct function<BOOST_CLBL_TRTS_ST Return(BOOST_CLBL_TRTS_VARARGS_CC *)(Args..., ...)
    BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
    BOOST_CLBL_TRTS_NOEXCEPT_SPEC>
 : default_callable_traits<> {

    static constexpr bool value = true;

    using has_varargs = std::true_type;

    using traits = function;

    using return_type = Return;

    using arg_types = std::tuple<Args...>;
    using non_invoke_arg_types = arg_types;

    using type =
        BOOST_CLBL_TRTS_ST Return(BOOST_CLBL_TRTS_VARARGS_CC *)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
            BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using function_type = Return(Args..., ...);

    using qualified_function_type = function_type;

    using remove_varargs =
        BOOST_CLBL_TRTS_ST Return(BOOST_CLBL_TRTS_CC *)(Args...)
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE;

    using add_varargs = type;

    using is_noexcept = BOOST_CLBL_TRTS_IS_NOEXCEPT;

    using remove_noexcept = BOOST_CLBL_TRTS_ST Return(BOOST_CLBL_TRTS_CC *)(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE;

    using add_noexcept = BOOST_CLBL_TRTS_ST Return(BOOST_CLBL_TRTS_CC *)(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;

    using is_transaction_safe = BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE;

    using remove_transaction_safe = Return(BOOST_CLBL_TRTS_VARARGS_CC *)(Args..., ...)
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using add_transaction_safe = Return(BOOST_CLBL_TRTS_VARARGS_CC *)(Args..., ...)
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    template<typename U>
    using apply_member_pointer =
        BOOST_CLBL_TRTS_ST Return(BOOST_CLBL_TRTS_VARARGS_CC U::*)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
            BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    template<typename NewReturn>
    using apply_return =
        BOOST_CLBL_TRTS_ST NewReturn(BOOST_CLBL_TRTS_VARARGS_CC *)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
            BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    template<template<class...> class Container>
    using expand_args = Container<Args...>;

    using is_member_pointer = std::false_type;
};


/* function_ptr_varargs_3.hpp
uScXlNgjFYoJ+0VXNJTljB6RyzY1ZSbtsZoPtcvjcX7cxav6vtWdTZpkZ2/cJLF9pb5r1cYjbtwl13ZMDbPLfDKJh42GX6j7TeBQfJjypjmOW4ZwLpRZbaZ37EugKnVz3z7cJFnRJKejlaU/arYoOaNjapK91bHFZPqGbc8ndNFTKF1VG92QqQ0m0k62Ty0l5Y8Nt8u3W8ebJE+z7LyxHEe7THcbjBvoPJ057CM/Zlm3o7bjJS25bl9b9HVhJcsjTmdUQl7XRLEYDTYX4SZJWJ0XE9V2atJ0Zwo5s9qFqjnIVkPycrKNqTlQ3ZYmaCKX1onVtCCnWr4kW0m76Tt6x81Wd7FLvF1s7WPjcIH1u+Y5/lGLvN3kIBCk2x02OMlqKHkjWBzUhUGRwSXZyLKZUO0FvSz6zbt8UmJLEKy9yc2FKGOFSEhstzVytVp9kfhkMl6tUk1Oxue+IfFGN/BCIaGInCEIDVaM0c5vkmx7NJmSdbyKTdoWZJIU5FTi9MZ0d2nPtXm/11omdHxK9gelLlFkmENFFOt7kmP1Kccqd5L+ilMbDqJRkkMNEKZEu6wZlDMdrfxBBvWCFiTGuqsqZF5RnKdrbSTWDTrMeKhEZtF5WxeWXM5VFZpmzh4tLEka16m76jucRWqzE+m+
*/