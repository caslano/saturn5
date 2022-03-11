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