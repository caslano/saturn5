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
Pjdb6H72wPgxbAr/AJvBW2BzuBy2gGtgS1gBW8Et8AT4CmwNt8N2Or6fCr+EHXTcPA3WCPTvMAmmw3TYCZ4FM2AePAkWwFPgefBUuBh2h5/BHjCZOPeF7eEg2Bn2g2PgAHgWHAwnwCGwFA6FF8FMeAUcAZfB0+GL8Az4NjwT7oFnwdZ+ZHgyzIWZMA9OgRNgMTwXXgwnwzmwAF4Jp8CFsAiugefBtbAEvgqnwvfg+XAPvACyt1/kdHgp7AHL+dcbzoD94OVwIJwFi+EcuAzOhcvhH+Gz8Cr4ArwavgevhR/C66AVGK+GifBG2AAugilwMUyFS2Camp8Eb4WnwmVwGFwOR8E7YTG8C5bDe+AV8F64AK6Ay+D98HY1vweuhg/CVXCtyn+Da+CH8GG4H66DvsB4N2wNN8BOcA7sCyvgVLgRXg03wRvhZng33AIfhM/C9fYv3OcaGQf/TcfBs2fEHvFYePGSyNh3REVUREVUREVUREVUREVUREXUv2v+/9fa/3+fa/9/iq77DJypmgRnwMD+/4RXnPl/Hhxm/z9ugu75aCPyFLu7uas2eG9fK7HfZfXTOz4GmjCOMvfiX/BqQD7+oHt9Mo3blmaOOUPkLLujVS10ntvMEXYSNxO4/V7v5DPhND9oLjZR501OEftsOz1obmuSmZutJXF0ZBNnzzmpAsJ7X8Jb7N6HXuK+o/0asd9HDONcc7nnmzUT94r9x1YP5hxq636ZscFzDeY+9PvhaN2H8ie4UveXjj6C+2guJj3uvYjZIffRTAzZU1IccqfQNI+zBNK0vrFtSNTL6Mbo9XqHdsJrrvUm4eucuksxeZMq8l3u+mb293cRu+ur6prIbYLrlpbBSWJ3t8iZxm0r99oLM7feUezu0frkuG16yPuzcWPWE2R73J8tc6RwrrgbQ541w9/RrjtKupt0TBc3tc196ffr/qlV6AfRq39ROf+y+8C0XPV8g+C5mexDnBkxR9cVTY7GD+wLK3Cb8npIOesETsi6InPHxWRxn6L7Tx3/Q8yewUKRP1CZX/pbAflor32p6ndUcPnrPH2p2DWMdsr4SpFf0Prg+J1i1vNc8SYyuwHEvXnucQfVl8EBt+J3uV/ri4aVp/asYBC/XTzX6kyE08V9nWin3RspcpvoDlEnBtUxwjV1bI8dfk3MGHiZuK0R7azjmPFXqVPmrJPVIh/PzGmUeUZqyDP22eHvgT9B/Eer7ORPU/daFbM3sa+47RV1r32We42JKePhYl8/KqSMsTdrQ3IsVLL+7vMljk/a9zNfvJE4LLZraJvg5PVpoWsxzDqm68Tv3ihnHcY5Ine2vNZXPCB1oDuz0/HmzqoT3giYvWXmpxeIm++tY3GVQSldT54G3Vmlv/vrtwfc1TVz6BvF3wjT5nwi9n3tSvf0oiJHqXtTh8z6nlTxP8buZ6316pekn9svafvKFtnkzUkHzdE7fVUSHC9+LvO18w3TNSWOv67mfIdrxM33Ua69pGU5JWUm31pI3JqxDuwBrR/uctG7wSV9S3xBayT0nnfyQ9SZWseoi9IHueb08wpzkTXO0+V5K0Pj605nZQRd67EaiZtq5p1gt8Qny5fqq2aFzS9dC+GE0wBOk2ev1bMEgsvlKtrvJtqfP6R7U531BGtce0nnHWI9wSNh1wvonZFm3YCuCzjM+oA59qHXBxTbVesDSH/Q+oBtCGZ9gPYx2+3gPmWnHdynfKyy9im0WwfN99POeM/3F7vn9kPuq55W3xL1doxFrRJK/7NnRyDOM0L6n6zxRYWlZbwtU3YH90W0f/KuEWiLO70d8L8oRvsjDW+IeQfuKvareTvwmT7plZ2h7x05JsxMi/iLn0s=
*/