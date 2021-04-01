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
D7F0mObFXlfTMZyCCrhKxVE9x1fNGKL3r+CNTTMrexTSK1YewnXRN3AUJ6tC4ILEh0rQ4UOmmyJz+5uFhHMhGjze+Ne9OATClyXs4NFOw/qRLCUPOJRVtB2pOCvcJtUfo2dJfIFjjYzgPVY9yRnatjjjgSWaik1tD0F+H+MD2Xw5qXPbRO9qngebF/esgTfQ+04t+lM23hKC+C3T90kwBMqhEimSOzYse+NRVOo9D8RRPcuKDi3AaWqcUN4hrYbge99rWdt8DpCI8oHhC7dEwBcvzOyzZ6uEWPtx8NguBG7xqu9llFs7vu8NjF+JW4bwNEzxkZIALI36jq14wX549yjdbe9DxrWZIreirpX/lmA1AEdXiAWhWmt8NZ0Z/57vm8lTMDH1TpkQ2TtHTvOF8FP4Tp1n4268Tqwu2YYTPTPTV3Nt2PEG3hA68zbBH0vxHqK+aAgqUEoBHZouuUGCY/jia/9TcefUN19O7ddG8RU7KCDJQ5v9JNERDA0/+87ugUeUj2fwk/DnGdsrL6dnmd1MpaF0TPLFxoZmvra8dsQoUQBNECh3NYtrgA==
*/