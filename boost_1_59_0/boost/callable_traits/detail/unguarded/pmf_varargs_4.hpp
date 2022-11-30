/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY

BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS - the function-level qualifiers for the
    current inclusion (combinations of `const` `volatile` `&` `&&`, or nothing)

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

template<typename Return, typename T, typename... Args>
struct pmf<Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
    BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
    BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
    BOOST_CLBL_TRTS_NOEXCEPT_SPEC>
 : default_callable_traits<dummy BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS> {

    static constexpr bool value = true;

    using has_varargs = std::true_type;

    using traits = pmf;

    using return_type = Return;

    using type = Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using invoke_type = typename std::conditional<
        std::is_rvalue_reference<T BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
        T BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS,
        typename std::add_lvalue_reference<T BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::type
    >::type;

    using arg_types = std::tuple<invoke_type, Args...>;
    using non_invoke_arg_types = std::tuple<Args...>;

    using function_object_signature = Return(Args..., ...);

    using function_type = Return(invoke_type, Args..., ...);

    using qualified_function_type = Return(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using remove_varargs =
        Return(BOOST_CLBL_TRTS_CC T::*)(Args...)
            BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
            BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using add_varargs = type;

    using is_noexcept = BOOST_CLBL_TRTS_IS_NOEXCEPT;

    using remove_noexcept = Return(BOOST_CLBL_TRTS_CC T::*)(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE;

    using add_noexcept = Return(BOOST_CLBL_TRTS_CC T::*)(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;

    using is_transaction_safe = BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE;

    using remove_transaction_safe = Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using add_transaction_safe = Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using class_type = T;

    using qualifiers = default_callable_traits<dummy BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>;

    template<qualifier_flags Flags>
    using set_qualifiers = set_varargs_member_function_qualifiers<
            Flags, is_transaction_safe::value, is_noexcept::value,
            BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...>;

    using remove_member_reference = set_qualifiers<qualifiers::cv_flags>;

    using add_member_lvalue_reference = set_qualifiers<
        collapse_flags<qualifiers::q_flags, lref_>::value>;

    using add_member_rvalue_reference = set_qualifiers<
        collapse_flags<qualifiers::q_flags, rref_>::value>;

    using add_member_const = set_qualifiers<qualifiers::q_flags | const_>;

    using add_member_volatile = set_qualifiers<qualifiers::q_flags | volatile_>;

    using add_member_cv = set_qualifiers<qualifiers::q_flags | cv_>;

    using remove_member_const = set_qualifiers<
        qualifiers::ref_flags | remove_const_flag<qualifiers::cv_flags>::value>;

    using remove_member_volatile = set_qualifiers<
        qualifiers::ref_flags | remove_volatile_flag<qualifiers::cv_flags>::value>;

    using remove_member_cv = set_qualifiers<qualifiers::ref_flags>;

    template<typename U>
    using apply_member_pointer =
        Return(BOOST_CLBL_TRTS_VARARGS_CC U::*)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
            BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    template<typename NewReturn>
    using apply_return =
        NewReturn(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
            BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    template<template<class...> class Container>
    using expand_args = Container<invoke_type, Args...>;

    using is_member_pointer = std::true_type;
};

/* pmf_varargs_4.hpp
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
*/