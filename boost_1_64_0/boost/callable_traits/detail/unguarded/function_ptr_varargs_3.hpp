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
struct function<BOOST_CLBL_TRTS_ST Return(BOOST_CLBL_TRTS_VARARGS_CC *)(Args..., ...)
    BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
    BOOST_CLBL_TRTS_NOEXCEPT_SPEC>
 : default_callable_traits<> {

    static constexpr bool value = true;

    using has_varargs = std::true_type;

    using traits = function;

    using return_type = Return;

    using arg_types = std::tuple<Args...>;
    using non_invoke_arg_types = arg_types;

    using type =
        BOOST_CLBL_TRTS_ST Return(BOOST_CLBL_TRTS_VARARGS_CC *)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
            BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using function_type = Return(Args..., ...);

    using qualified_function_type = function_type;

    using remove_varargs =
        BOOST_CLBL_TRTS_ST Return(BOOST_CLBL_TRTS_CC *)(Args...)
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE;

    using add_varargs = type;

    using is_noexcept = BOOST_CLBL_TRTS_IS_NOEXCEPT;

    using remove_noexcept = BOOST_CLBL_TRTS_ST Return(BOOST_CLBL_TRTS_CC *)(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE;

    using add_noexcept = BOOST_CLBL_TRTS_ST Return(BOOST_CLBL_TRTS_CC *)(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;

    using is_transaction_safe = BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE;

    using remove_transaction_safe = Return(BOOST_CLBL_TRTS_VARARGS_CC *)(Args..., ...)
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    using add_transaction_safe = Return(BOOST_CLBL_TRTS_VARARGS_CC *)(Args..., ...)
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER
        BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    template<typename U>
    using apply_member_pointer =
        BOOST_CLBL_TRTS_ST Return(BOOST_CLBL_TRTS_VARARGS_CC U::*)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
            BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    template<typename NewReturn>
    using apply_return =
        BOOST_CLBL_TRTS_ST NewReturn(BOOST_CLBL_TRTS_VARARGS_CC *)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
            BOOST_CLBL_TRTS_NOEXCEPT_SPEC;

    template<template<class...> class Container>
    using expand_args = Container<Args...>;

    using is_member_pointer = std::false_type;
};


/* function_ptr_varargs_3.hpp
sZagPJf5g628C6WeQP9IBYz3lS+I98XER0fF+xhCF/ubW9FWYL/Jwz4J+/XYt8R+c8A+unwxNlL/prrG+xIt4vG1jl3jZwd+muHnmcow7wyM/7p1ssZroxMv/4y28dGt5aEBu3TMKzROLjuJTybm6018ZowJjY8zdv+AxOcS+rD+EqcC/KwzcZoxPjROTl6Nbe3k1YxW8f7Y+Oi4qrzagv8x2G8Ktde8+hj7ka1N3LqGy6sfJG4NJV7VcZ+J1nj1Dxevr6viFRvvj4qPrlUVr2zs9ph4GXsTr3LsdlfFq1G4eO2QeNWXeC3D/cdV8WoRrgwL2jhlWP5NfFR8PEtEpAz34Xcidps87OphnoveHGwnz03FPButz60eLj+qtzV1Z0e8v1p81FHx/poUSMC+GP9R2G/ysA88fwH2Vlt9ftSMHyttLHeemHb9Afk9tZW4rcLfj07c/JfVDY2bc5eSrD3Rfn/iIcew3PeVjNMzyZ07kaT/M2NS9FeY0V+p2Trjjr5Jx6kqjJn2Pc66EO3X57S3RE1Fx6Lz0L0bE/Z34fr1kUO1V9dviqA+Xf3VFHkEcluRJ4brw9V9J5W5o0HkBK/+WNrCk8X+TO2fHf/JB/XLWlZqf5LKJnyvPln62ZbB61TVvx3ax5k+taPYt1PZhC/lbHmrAU45V4dtXOWc4FHODT3KOcWjnFuGKefOWs7zpafDv0YiYDiScq6oLGdZ75PDRFBgzU9W3nlebYG69Tl2ptzrGrtEaVvmU6f6pTpti08aHa/wnhI/0fI7+hE/vVKd33hNy/y2w+ZjSlA+TnWN5yaobO6G0TxY1eHgPBhOHuz0zoMsLovR96qgeKt7n9oF5wN2Jh8WkJ6CDtrmVJNkiXkUZhM7HD5/3nflTyPc56Ld+XOkeVTmziMjjwu6Y21MWqVPJ8Da6FHkkbXPI4+YZJmeV1KErWf88WPiv4a4N0vT+JPgI4m3lm1QWX6g8ayuPqppPFO84jmldFyYOKp7v/XPxOVr/i6O3P9gzpfpK+fatDrqxS1tltyx67hZR7/06bDPKZhVAwLmG86f9sm9V43p3fTzqQO/mz+8/pHf/+B9Ps7/370Q3xJ/vY9Rfk8p+M+3aE/078st2hz9myKxNurfN1myPkbOuPcTx73Ieyxn/w9u9Xz/owO/L7Sl5+s0gu1gOkyFI2AHOAqeASfAdFgGO8FLYAa8HHaGV8GT4E3wZLgCngqfgKfBrbA7/CvsAT+BveBnsDfcD/vrefcDYBM4CKbCwbA37A8HwWEwB46EBfB0eCEcA2fAM/Tc/4lmD4rsvZF0x8KxaEvvHWgKr4ad4EI4HF6r6b4OXgivhxfBG+GtcBG8Dd4M18O79HlzfM5eAdkDIs8bwt8X6/lH7W3NX9gVZsA/wJPgLbAbvBd2h8/AHvBF2Au+AXvDt2FfuAv2h9/BwfAAHAhjbWRYG2bCBnAYPBYOh23gCHgaHAnHwrNgPhwLJ8Nz4MUwGy6EufBumAcr4AT4NDwXvgQnw7dgAfwAToGfwCLoI+0lsD8shQNhGZwMz4dT4QWwHE6D61TeBGfBbXA2/BLOgVF+xuVgNTgftoRXwiKV56n8kMoVKr8Br4W74HXwI3gDTIjiNwObwsWwOVwCe8KlcBBcBofC2+AwuAJmw3thMbwflsGV8DL4AJwFH4RXqvvb4Fq4HK6Dd8FH4Sr4Z/icytvgE3Av3AT90fzmYS34KmwNt8OO8A14CnwT9oQ7YF/4NpT679O1jroWvLr8tihnzC0h9QCeDfvB8XA4LISTYRGcC4vhAlgKr4NT4W3wfHgnnAb/BKfDCngJfAZeDF9ReTucAT+Cs+FXcA7cB/8Ia9g=
*/