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
MeTg556riWczuAUmw9/CdvA62AHeD3vCG2ARvBEugzfB8+DNcC28BV4Mb4Ul8Da4Bd4Or4d3wFs1nMfgDq2nd8N98B74MrwPHtDrHpfnGR1b1LFR4i99GW2o/C7GqhO8CmbCzfBMeDXMg9fAWfB6eAW8Af4W3gh/B38H74E3wcfgzXAf3AYPwzvgB3A7/Areqfut3gXD4Q5YH94Nm8N7YCu4E6bDe+EAeB8cDO+H4+EumAsfgPnwQbgQPgTXwt3wfPgwvBI+Am+Cj8Jb4R54P3wMPgkfh0/DvfB1WArfh0/Ao/BJ+BV8Cnr9/QkMh0/D+vAZ2Bw+C1vB/TAdPgcHwOfhYPgCHA9fhLnwJZgPX4YL4StwLTwAz4evwivha/BG+Dq8CR6EO+Eh+CB8C5bCP8Dn4TvwAHwX/gG+B4/Aw/Av8E/wM/g+/AEehX+DH0LLx1iKOZ9ex+HgTpfnoS+xag2/hr3hX7UcfQPnwe/gSvg93AR/gLQhJ90TNBv7rldHVe8N+l+2N+go8mQWZiPmFsw+zBFM5BbOMsaMwhRgSjA7MQcxP/ndrmH/UEwB5hLMTswBzLFrqvcQrf5V/6p/1b/qX/Xvf/H379n/b3qebP/3K/f/8+/z92Is63p0fhDjgPL7i87je86ex2fp/CAuHGLNBjpB8/dE3htw7ldWjn5zN/rdzXytb0S+N1A/V+c0GP10MxfsK5Hvs0LN2fxM3HeIPNb47xhyzuZ34n69Y37XInMG1ESPzA0jvWqpHXvAiV0nbBo7/OSauTP1xX25wy3HzC+oJW6bSK1p0TVDnLn/MuYV/99VmOO5xlPZNa+SF+a7u7HLtU4615MxJ/mNxdTFjMRMo4wc82gZsZcv5xcvzLf3KdL8dMzLUf3EivP+XN0KtRwYt5DzN53uupfbfGJj9uZzrHc4xznXKdar5Vf3QzybND+zEufyaRpqOss9nmSuZaHbPD3dw8+coyRxlvVVOi8mTPdHe8tLOH6/0J/u2V6XdM8qnJ+VW5xTOH1WxfTXMv29+IvS/LDD6Rx63xGj01t0tgXocE9atvPDZL4tayIjTV28Svzt0Ty0w+mm7sxyCffLXgmX9+pQeav+0kwb8BuRr/eW17EpZs5PqbgtdLhNMPf+sbhFq2xfv6lJq0htG2I0/ofknrKJYW9Z8xlraR3wyZpDtUORn0/C6uao9/1NG7ddrrvBEadBZv3jS+JW4HCbWj7fSNzGO9ZlLpw9s7B8bupOiUc9K0FkdlMReaBnPfPPHuNuGnm8jvgMMHn1gIR7wLPT08ish/pJ7rWXQ3+c1VzryNWif7m3gDDbeq7nu0snqyV2A70pJi19PnRwTxQ/KjPCGsnoVJhnpbXNU4/vHglmDU2kuHdx3Pdo04cckuud5Y3B7RaZH1cwn4MuswbwV6zuwbLC758QxzCDwcNVKqz/0bjXkPtayVzMJCtB7DSdmEUwFPtPSD+LeAVfq7+UP7mW6i/16HoebbdDmy91XQ/GtOt9MJdiXsM8pGt2bPk6zD2Y3mqfAXeZ9Tvoa5v0DcbuE7JP0jZtdWmbQu9hUei6h0Ws9iW3iJ3mQQj7/tpfdNJ2q0iHNMJ1TfUPmKn+/iJc2q38xdMLZvNM4Xp2Xq0IWZPO+KA5O0/9NXbo55r2CbeAfXFPEf8fMk7ocfbrph3YKO6RpuxuVzmmvJ7Nmj1j0UL+MOvY6ovOQZ6N2OeWclBL5/TeFVtmMpSvY15WYkTn+kr24wciTD8efPZi0H67uQFz9I9wDWk5mD/VFI6Av29CnGpIWnNqdFZuYSX6Z3/aJEdK/2DyYqGEkRwxz7ohXPNCw03X84hd+wzVSTL7N2WL3CWixDM=
*/