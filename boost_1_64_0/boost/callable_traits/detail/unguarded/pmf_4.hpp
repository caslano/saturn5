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
w46Jm/H3/6E1s/+Oc2V3lMb+JutmezGfkYsuXxlZPxtREfW7fv/zuvNr7f+/JMky31HVdQrqvEpIn/QTHU/2U/oOzVWYY7Lk+vKQ/ermu1/dxpj32nyRJ4v7qbjDJBCsuUPyMrEfSr/FPXmYr8GsXO4hbRFXLa5n3Alx/eJ6xfj89eKaxNTkwkANJ2iv/yT8XCLhjLASzXOK8vNL88rc7+k3ipu25r7NjSJX3ieYpM/fRlgzAs+PTYhnw+9h7urjXVa/Taq730VDvk93+8z3KaUDNV/3BOVrfklenke+6hhAzNMBt900nx2/SWZ/aB+xx4R0xPO85ejLA+lISorxxVc/Kpb3c7xZOaTEfTfrzCTMdJwg5TBpTD1EGrfo2JF816MvQ1cLjB097U7jBArk4DQmaRrPF7fnWUP4fxJa06phJAXtzyccs3/5KrEfxDtNdXOm5Cy9u36vpi31MGnrFjZtcm+NqIl6tuV4dCxpS9joTlth3gUmba446vdeqrjtZ3E/u5TRViLZhXDnEE//WRRRVJSUi2M3Bru5AbsBAbuaQWX2RQJp03RlhEtXyPdxQx0jaappOEbTsCwoDaV546eW5ElSPNJiztUQP3Usp07NTvpl53aauqJxGad1Zaz+HrYFx6Usp6QstK6YMbFd4naQ1d3UE8d/ffMtOj9QB/6F8u/s3P8fU+l4tsZ3BjqGvMvc5MQ3c+jQQVn5kwonlVJHZFzhgMS5WOPmuE0y3/H5yNi76vS4Qvd++qliP1ZlRidF9pu01a33y363tfR3e0DSVlxZDpqunTpm0pHn1YMtYA3SZW0OShc/2qA0md/rMeKuln0idXozWtOq/o9xjd3mF+RMMO0w9jrWoWO9R4vcwO4mo5yzvPJEfucl4q6t2H8n9XJSGQOK5nyRPmJ/E3GNN+1AFnl0JfVgctKR51UicoYZL5A0BOVfbvWD79SlXrA5MCj/qBZlXnVC3SX+4vuSNV5BdTO3RqXD3uqhF9oK/K6D46BvE551U93Gmn3/94l8iuXV11Is6r6a6XvvFrlr2L63DlwjbjoccVoTg+40Jh4hv82EWP1O1d9mO3RUoA5vcdI/YmT3ngOdH6ekycae+QSNn57xIu6P0zxx/CdqG3fY39oAdx9J+MSV8EPbEY2rwqqhcc0MiatUGMs7rsRN3cceNi/1vSQ0Pqb+tomrdFxTPcWj/bjNDolPcVFxuLio25r/dFycvCmIr3S8Bt0YfSs6nj+KQ+MyVZrYsOV4vbi/VOPn+G+udTn4jnTqsto3MfNKC0WeXVmXpd2nMww0M6VVY7CbxM0ZWt/VTemk6XnaPzWEd1TGmzRGO202bdFh61GPcPVI2yL9HZAG99hk5B5mMyb6soxZ5r891pr6zepH60wb8tyFO2f8MdxY5pHfw/z/fN/yHL0/+Uv+vlz//o6/Z+jfddBz9e9kdLn+fTp6L+6os/p9KN+YYhcPCzT8jXiR1wMYC5+BteFfYAJ8FibD5+ExKjdRuQXcCnPhC3AifAkWq/+9MBu9R58/Wp9fA47U5y/V598K66qcBFfBNvBB2F7lE1XuAlfDYfAhqOnUbxbyzCOdr2m63tB0vAU7wvd0DPd9mAU/gXlwFyyCH8IS+DGcrvbl8E14mcp74RhLv03gRHk+Gg7S58/Ws+D/CJvDebAnnA97w4VwALxax5YXwPFqvlfrwzINv6mGHw3TNfzrNfwbYCJcBBvAmzS9S1zx3KbhjPOI51rNp0fV33rYDm6AQ+Djmu9PwtHwz3CsynrPtb53S5oPuuf6WJvwYVPYBDaDqbA57AyPh13VvB9sAQfClnAybAVnQOd+xu3m3VbeqeV5DaVeVt0=
*/