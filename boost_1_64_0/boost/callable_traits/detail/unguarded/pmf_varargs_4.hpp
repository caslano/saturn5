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
R/lNe3EX1TU/Sut+35GNvIkTuzfNoV33tbj9dc0l824Ujz/cZqIN5DRLeK/zLVt6pbTmQkAPVfL/zqjd/32ZKzIwhK4Pvz+bLszq2gYuMMlxC82IxDUShEQRkcvOU8CS5C2AQAtifyBtrgb+kpCNtXyu141kTpF0+RZ3IGs6+2kTJ6L7XzYVjt5HYK0UG9B5z/sZVscAaMbr3YAfrw1erhNDtUiezJEkuC/6WMdxTv6fEEDKHJPCpIOb25Du1qBftYXbvSgt2BrTkds8hUdqFJq8mN/hdXEWWpbEMuYuVPYfmdqpxlVfTAqnzCICvvH+LgHybpn3/e0ONlFAjE7XB/S/N5Kqi6S6cluMU0URR1WySGyvKvJ6UWSIgFBYjAUk8SnnjeYOcl+ly90Felsas46Ok1vjKYzkJjx2rswxUapyo5384k+NloLF0mk2aLEGkfi7bfLqNJJZdRFvBRCWHBcxVfk9L2FixhQru1Wlc15IYgVtjgXmvLoC3W/BOJG/BXqiFOwQfzYb/zESDOy7lQ5IFOzRpydPx1r6npYKPmblBRbK96w79iQtbA==
*/