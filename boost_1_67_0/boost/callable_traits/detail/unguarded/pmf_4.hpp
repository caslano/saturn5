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