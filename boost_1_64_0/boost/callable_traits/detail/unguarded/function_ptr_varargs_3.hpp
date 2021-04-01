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
gHz2DPJatQTPzZLqe4CBpWCkdB/cdS/HxG5IznnDxVXvposCheiBhwtxhntr1ECCtRnEK4xk/gBYgA5MYHeeQpc5RdS47SRggRL5unED0ek6gSJx6fJuG/gwP8OUiT0wnHe4w+ssszStctGs9DtoK2mQCTpLkqiZR/BKDUvfqKyolTRhzu6kQIMbz9pqP2zd5TxORzAYvvgguxhkJDCnr7RopIadJzLNOLjWmTQLW4eRiPsjt5vZU7i9WdKztpaaZGFskfwmrZ4pyykTzGKEEvDrE3zyf+RR2EfLcMn+zUBvT/77fcjjB1+w9vOcNWQpsIOP7zb00xpQYWKva02YJDL+bdA+QX5gFfFRMcdHaPQBQhEAatA+ou+J88WDsalGYQAyyHGxdExNlc73EHJjJCG4Y3NsmzWxSxv7hHrMtYAEcHN2MDzlx8ELeNuCV5bEAGhCFb3ZZr83qpnmF3b8cGs/SuMtgZ5JpDUH2J1WJ4QeuNj4ejKJqmwV7qgF4B1ERr2JKiMspdYwRpkT9KBFXa8uHg/TQpKaW/9P5SPE105m76QL4LyrkOMnQw==
*/