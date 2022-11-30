/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY

macros used:

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

template<typename Return, typename... Args>
struct function<Return(Args...)
    BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
    BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
    BOOST_CLBL_TRTS_NOEXCEPT_SPEC>
 : default_callable_traits<dummy BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS> {
     
    static constexpr bool value = true;
    
    using traits = function;

    using return_type = Return;

    using arg_types = std::tuple<Args...>;
    using non_invoke_arg_types = arg_types;

    using type = Return(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using function_type = Return(Args...);

    using qualified_function_type = Return(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using remove_varargs = type;

    using add_varargs = Return (Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;
    
    using is_noexcept = BOOST_CLBL_TRTS_IS_NOEXCEPT;

    using remove_noexcept = Return(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE;

    using add_noexcept = Return(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;

    using is_transaction_safe = BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE;

    using remove_transaction_safe = Return(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using add_transaction_safe = Return(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using qualifiers = default_callable_traits<dummy BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>;
    
    template<qualifier_flags Flags>
    using set_qualifiers = set_function_qualifiers<Flags, is_transaction_safe::value,
        is_noexcept::value, Return, Args...>;
    
    #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    using add_member_lvalue_reference = abominable_functions_not_supported_on_this_compiler;
    using add_member_rvalue_reference = abominable_functions_not_supported_on_this_compiler;
    using add_member_const = abominable_functions_not_supported_on_this_compiler;
    using add_member_volatile = abominable_functions_not_supported_on_this_compiler;
    using add_member_cv = abominable_functions_not_supported_on_this_compiler;

    #else

    using add_member_lvalue_reference = set_qualifiers<
        collapse_flags<qualifiers::q_flags, lref_>::value>;

    using add_member_rvalue_reference = set_qualifiers<
        collapse_flags<qualifiers::q_flags, rref_>::value>;

    using add_member_const = set_qualifiers<qualifiers::q_flags | const_>;

    using add_member_volatile = set_qualifiers<qualifiers::q_flags | volatile_>;

    using add_member_cv = set_qualifiers<qualifiers::q_flags | cv_>;

    #endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS
    
    using remove_member_reference = set_qualifiers<qualifiers::cv_flags>;

    using remove_member_const = set_qualifiers<
        qualifiers::ref_flags | remove_const_flag<qualifiers::cv_flags>::value>;
        
    using remove_member_volatile = set_qualifiers<
        qualifiers::ref_flags | remove_volatile_flag<qualifiers::cv_flags>::value>;
        
    using remove_member_cv = set_qualifiers<qualifiers::ref_flags>;

    template<typename U>
    using apply_member_pointer = add_member_pointer<type, U>;
    
    template<typename NewReturn>
    using apply_return = NewReturn(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;
    
    template<template<class...> class Container>
    using expand_args = Container<Args...>;

    using is_member_pointer = std::false_type;
};


template<typename Return, typename... Args>
struct function<Return (Args..., ...)
    BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
    BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
    BOOST_CLBL_TRTS_NOEXCEPT_SPEC>
 : default_callable_traits<dummy BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS> {
     
    static constexpr bool value = true;
    
    using has_varargs = std::true_type;
    using traits = function;
    using return_type = Return;
    using arg_types = std::tuple<Args...>;

    using type = Return (Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using function_type = Return(Args..., ...);

    using qualified_function_type = Return(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using remove_varargs = Return (Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using add_varargs = type;

    using is_noexcept = BOOST_CLBL_TRTS_IS_NOEXCEPT;

    using remove_noexcept = Return(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE;

    using add_noexcept = Return(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;

    using is_transaction_safe = BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE;

    using remove_transaction_safe = Return(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using add_transaction_safe = Return(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using qualifiers = default_callable_traits<dummy BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>;
    
    template<qualifier_flags Flags>
    using set_qualifiers = set_varargs_function_qualifiers<Flags, is_transaction_safe::value,
        is_noexcept::value, Return, Args...>;
    
    #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    using add_member_lvalue_reference = abominable_functions_not_supported_on_this_compiler;
    using add_member_rvalue_reference = abominable_functions_not_supported_on_this_compiler;
    using add_member_const = abominable_functions_not_supported_on_this_compiler;
    using add_member_volatile = abominable_functions_not_supported_on_this_compiler;
    using add_member_cv = abominable_functions_not_supported_on_this_compiler;

    #else

    using add_member_lvalue_reference = set_qualifiers<
        collapse_flags<qualifiers::q_flags, lref_>::value>;
        
    using add_member_rvalue_reference = set_qualifiers<
        collapse_flags<qualifiers::q_flags, rref_>::value>;
        
    using add_member_const = set_qualifiers<qualifiers::q_flags | const_>;

    using add_member_volatile = set_qualifiers<qualifiers::q_flags | volatile_>;

    using add_member_cv = set_qualifiers<qualifiers::q_flags | cv_>;
    
    #endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    using remove_member_reference = set_qualifiers<qualifiers::cv_flags>;

    using remove_member_const = set_qualifiers<
        qualifiers::ref_flags | remove_const_flag<qualifiers::cv_flags>::value>;
        
    using remove_member_volatile = set_qualifiers<
        qualifiers::ref_flags | remove_volatile_flag<qualifiers::cv_flags>::value>;
        
    using remove_member_cv = set_qualifiers<qualifiers::ref_flags>;
    
    template<typename U>
    using apply_member_pointer =
        Return( BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC U::*)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
            BOOST_CLBL_TRTS_NOEXCEPT_SPEC;
        
    template<typename NewReturn>
    using apply_return = NewReturn(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;
    
    template<template<class...> class Container>
    using expand_args = Container<Args...>;
    
    using is_member_pointer = std::false_type;
};

/* function_3.hpp
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
*/