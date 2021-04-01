/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY

*/

template<typename Return, typename T, typename... Args>
struct set_member_function_qualifiers_t<
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    false, // IsTransactionSafe
    false, // IsNoexcept
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type = Return(BOOST_CLBL_TRTS_CC T::*)(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS;
};

template<typename Return, typename T, typename... Args>
struct set_member_function_qualifiers_t<
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    false,
    true,
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type = Return(BOOST_CLBL_TRTS_CC T::*)(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;
};

template<typename Return, typename T, typename... Args>
struct set_member_function_qualifiers_t<
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    true,
    false,
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type = Return(BOOST_CLBL_TRTS_CC T::*)(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER;
};

template<typename Return, typename T, typename... Args>
struct set_member_function_qualifiers_t<
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    true,
    true,
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type = Return(BOOST_CLBL_TRTS_CC T::*)(Args...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;
};

#define BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE std::false_type
#include <boost/callable_traits/detail/unguarded/pmf_3.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#undef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE

#ifdef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE

#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE std::true_type
#define BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE transaction_safe
#include <boost/callable_traits/detail/unguarded/pmf_3.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#undef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE

#endif

/* pmf_2.hpp
Prig1SHQKEto3W3hEgiGB/rTy5oSO6GM+BHGFatW1yjVOPPuVI8pnkatrU90fpfSA1RUBH9iN58N1SaITvW/1MXn1H7BGZr1VnT7iHbEwiOFhzCMRSrAgSQD4NQxCe+PqHo1W6Bh24bQxPRhXbmEAymgZUosodNDOOfMndGkLUIGpYPPrTVAQIb4xMYisGRhN03thK/HTz8QLNOtLUC3x9nVQ55VvAN4zUxeDT2ICZawftpTrdQWrb6AhAXNuNpUcy/gbKE53txUSUQMdg4VFaFi0uLwYR9D43oXeUbStidvP4gEFuCE5iNaAkD5Ev5pZF2WaGTXHwi1FheSI7DiVpZqn15bnc4zaFqHA6mPDuENwJhmhZT2/P7ki7fvHgKPrpZ+LJ5RnR+EAyaccHTphKJFqvDP0J9mYgvc0i7sp8HJd1/bfc+WWAPZAbDVOrBtxNTg2LXG4gh74q7XOZqLTYVzi75c8hCmvBKlh2k8yyXKP+t5BpEbDcvOKV3D34ZK45/+9uZPMX6XvFU3oDnansgpLnZ8F8k10htq/0jid/StEsrE9lm/lRZi9Q==
*/