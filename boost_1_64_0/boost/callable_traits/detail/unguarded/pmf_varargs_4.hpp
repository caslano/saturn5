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
dZCxNN4QSze21uivrBrWKICbgI/het4L9bE0MDw0wL831Pp7G7k/y3UxvdfcpSPeUC5iq8jfRsbOYSRnVvvcds5VfBdHXkve58h8HUmeBnkMyanVRFq5Fu0r03YjeSrkiSQnV6tom8Ce+vZ9eqkYH4r41jDILufJ8WQ21eOoiy5/r4p4CCnErr9gc6RvR/n99el76Mda7y+x66+KsQLSL7LL51x1dhyit50pVP7W5hgvbWUk6WP1theuf7+nD+nHWMbzKdDPJH25RT8SY2LStxW2i3l+kseDsdbKPjNHtLOj/daR3Ij6TAPHu8vonJe+3Mb3kpL+fX3/kNeLJJ23ZsEZ6Q+T3sOKM6pTOek7WXFGddxH+qFWnBHnz5J+mpKz86TvI8flu0geAtlDydkLlKaptONLgh9whvGheNerqJfKz3xD+ol6zuT13lByJsZnQRTLlZz1Jf0IK87IjmqQPsyKMyrbPaRPUPrrcNJHSn9dleQQ7W4m/o+mNE1ku0ST3Nvgm+vRueFWnFG540nf0dIPTyVdSyVnR0lfS8nZAdL7KDnbRvoZSs6eIL06xn1L+sWSswdIngbLq6Xk7M0gYzz7geQWBs5K6FxzJWfXSd/YkrNXSNdNydnARbydtSD9RAVnQNLPUXLWivRJSs78SR8sObtI5U3UJjN2NnSRkbMgkkcbOKtP59opOQsh/QBLzvou4jkrJb27krONojwqzraTfqCSs82kT1Fy9i7pF1bY2SLHPIm7krNDJs4+IHm8gbN9dM5NydknpL/PkrNy0t2p5Kw1xe07lJw1XMxz1mIxz1lj0i9VcuZL+tmSs7riehhpKDnrQmkaVfgfyOa+2W4xz9nMxeq+2ZF0nZWcPbCY92eppJ+i5Cyc9AuUnGWQPlHJ2V9J7yc5G0NytDaW8WeFlKadrOMbFpxF0bneSs6OMZztIl1bBWfAYJ6za5TfV8nZ30k/V8nZL6SPUnI2AL+vf57qOUofB3+m5qx+sLFv3gPZzNlFuk5rJWdDg9Wc1SRdLyVnaaRvquRsMemnKzmbSXp/JWehpM9RclYebPRnPUlO1SagTCrOVgUb++YTkM3+bA6da6Xk7OlgtT9LId0AJWe3gnl/9l0w789+Ceb92dVg3p91DTH6s6+CnfuzGiFGznpANtuZSwjvz/qEqO2sagjvzxJIX03J2dwQ3p/5hPD+bAHpM5Wc7SB9e8lZ+xBH36ym5CyZ0jSVdSwhuYOBs4kh/FhjL+lbWXIWE8L3za9J30DJ2SchvD97K4T3Z5+TPkvJmfcS8neSs0co/UptEsqk4uyqqK+jjm2XVL4POE5puio567BEfR9wU7SBirOkJXwM8F/C3wdMIv1MJWeLl/D3AUWk95ecDSd5utaXiQHLlxhjwE7I5r45U5xTcbZnibpvxi3hx7SXnHB2gvRjlJwdIf00JWenSL9cPT+41Hi/WUjpo2HZas6+NnFWf2nlGPAXStNGyVmjpeoYcH4J788WLeU5u4/0M5WczSD9YCVnvkv5+4DVpL9XcjaA5GlaV4azkKVGztaTPNDA2fylfAx4iPR9LTkLIF13p3Ol9ByMaZ2+v5T9SR4iZPPzbWXiA48jWmI+FNgTaJ8PPRJaaT60v2o+dFkyzYe6ddSec3W0F/LL+dAZkM+R7Nlydc2HayjnQ0U+/XzolyQ3aWkxH4q0xvnQb0lu2NJqPtQH+ufC7Pp0F8e7EO6JpH7SLNjtq4aOOcvOmfZzMVUgU7kjE+zywzVUc6SuBdBjF7/jmm/Tb7zSLMLlakPHXHC/aJoXrftRtQ813XUMtvQ9XaeBvM7OWLtcUG9SjXNyTvlYOI3Xm4e4BjdSzan+EMo=
*/