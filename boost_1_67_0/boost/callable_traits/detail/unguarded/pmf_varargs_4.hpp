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