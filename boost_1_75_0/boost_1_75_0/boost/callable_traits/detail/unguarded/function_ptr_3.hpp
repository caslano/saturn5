/*
Copyright (c) 2016 Modified Work Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY

macros used:

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
struct function<
    BOOST_CLBL_TRTS_ST Return(BOOST_CLBL_TRTS_CC *)(Args...)
    BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
    BOOST_CLBL_TRTS_NOEXCEPT_SPEC>
 : default_callable_traits<> {

    static constexpr bool value = true;

    using traits = function;

    using return_type = Return;

    using arg_types = std::tuple<Args...>;
    using non_invoke_arg_types = arg_types;

    using type = BOOST_CLBL_TRTS_ST Return(BOOST_CLBL_TRTS_CC *)(Args...)
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE;

    using function_type = Return(Args...);
    using qualified_function_type = function_type;
    using remove_varargs = type;

    using add_varargs =
        BOOST_CLBL_TRTS_ST Return (BOOST_CLBL_TRTS_VARARGS_CC *)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
            BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using is_noexcept = BOOST_CLBL_TRTS_IS_NOEXCEPT;

    using remove_noexcept = Return(BOOST_CLBL_TRTS_CC *)(Args...)
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE;

    using add_noexcept = Return(BOOST_CLBL_TRTS_CC *)(Args...)
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;

    using is_transaction_safe = BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE;

    using remove_transaction_safe = Return(BOOST_CLBL_TRTS_CC *)(Args...)
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using add_transaction_safe = Return(BOOST_CLBL_TRTS_CC *)(Args...)
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    template<typename U>
    using apply_member_pointer =
        BOOST_CLBL_TRTS_ST Return(BOOST_CLBL_TRTS_CC U::*)(Args...)
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
            BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    template<typename NewReturn>
    using apply_return =
        BOOST_CLBL_TRTS_ST NewReturn(BOOST_CLBL_TRTS_CC *)(Args...)
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
            BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    template<template<class...> class Container>
    using expand_args = Container<Args...>;

    using is_member_pointer = std::false_type;
};


/* function_ptr_3.hpp
xG1ijxPvaIc9ds5pxe7+XnYS9nh3Wavya8riTDmNVNdfupCbr2pifLvzo6YIlnaXhkS7dJb2fKSuZ5aJM/5TsLSfrRUs7adJGks77Ever19ay8zi02v592Pi98Pi93lf8u++eFX885jVdIqnE0Rpy5cxnMvesCEA2gxEcUqKR2jxDlJkWNS4kTIWPWLJ+/0NugE68iIBCfkixKZ/0a+2lXG+wPRSIEPAybXWw/kCU+nYWHtn1sNJganFMA2SpqOLUMEFhxZKgelTTCpF6IvbJ0KppHjGhXbFajvRntoYtkF0FuC5nZ6U5q7HTaEztxvKrYXKfWWw30hlExsQXxay2qTBoNMbSNQcyngJL1gttIoja4ri2wzy/b5RnONf4sNXI0rvNDaNBebSOw1dyZyID3Yb2q2p5g92G0qa8fR8RCmMaLHibT5KzvCL+fO9gswPNn+711D+XMmNidKKyEh1gbm0YojefSJK7wcuGp92Npfeb/SXc+PR87IvVaGK+y88LJu4xDTCJYZObbv4ghRqS4RCTReWV9FBwcQ607d1hlLtbat5rupYUYUvnuXPqk2fVRsqtYciPoMXuzVFHH9WZfqsylCojYv4DF40is84QjHHVeisur6x2/RaqsWzGn5GHaoTz97nZ3UMXubEJi62GIc2DaJggAsKhGX7kIkLLToBoigDz97PQQwp3tXs1YhZRHB8tUw9cmqZPlwl
*/