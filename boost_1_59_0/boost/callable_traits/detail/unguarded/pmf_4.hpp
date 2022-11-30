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
    BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE is defined, otherwise nothing

BOOST_CLBL_TRTS_NOEXCEPT_SPEC - the noexcept specifier for
    the current include (`noexcept` or nothing)

BOOST_CLBL_TRTS_IS_NOEXCEPT - `std::true_type` or `std::false_type`,
    tied on whether BOOST_CLBL_TRTS_NOEXCEPT_SPEC is `noexcept`

BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER - `noexcept` if
    BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES is defined, otherwise nothing
*/

template<typename Return, typename T, typename... Args>
struct pmf<Return(BOOST_CLBL_TRTS_CC T::*)(Args...)
    BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
    BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
    BOOST_CLBL_TRTS_NOEXCEPT_SPEC>
    : default_callable_traits<dummy BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS> {
     
    static constexpr bool value = true;
    
    using traits = pmf;

    using return_type = Return;

    using type = Return(BOOST_CLBL_TRTS_CC T::*)(Args...)
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

    using function_object_signature = Return(Args...);

    using function_type = Return(invoke_type, Args...);

    using qualified_function_type = Return(Args...)
        BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using remove_varargs = type;
    
    using add_varargs =
        Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
            BOOST_CLBL_TRTS_NOEXCEPT_SPEC;
    
    using is_noexcept = BOOST_CLBL_TRTS_IS_NOEXCEPT;

    using remove_noexcept = Return(BOOST_CLBL_TRTS_CC T::*)(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE;

    using add_noexcept = Return(BOOST_CLBL_TRTS_CC T::*)(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;

    using is_transaction_safe = BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE;

    using remove_transaction_safe = Return(BOOST_CLBL_TRTS_CC T::*)(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using add_transaction_safe = Return(BOOST_CLBL_TRTS_CC T::*)(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using class_type = T;

    using qualifiers = default_callable_traits<dummy BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>;
    
    template<qualifier_flags Flags>
    using set_qualifiers = set_member_function_qualifiers<
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
        Return(BOOST_CLBL_TRTS_CC U::*)(Args...)
            BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
            BOOST_CLBL_TRTS_NOEXCEPT_SPEC;
        
    template<typename NewReturn>
    using apply_return =
        NewReturn(BOOST_CLBL_TRTS_CC T::*)(Args...)
            BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
            BOOST_CLBL_TRTS_NOEXCEPT_SPEC;
        
    template<template<class...> class Container>
    using expand_args = Container<invoke_type, Args...>;

    using is_member_pointer = std::true_type;
};

/* pmf_4.hpp
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
*/