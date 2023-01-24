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
4NTQiDgCk4/ziylCeLxnwJzWibi/uRbCkzqBJwV1wh4brZ7ygv9pZETxaoiCry7lUabRhsGjvO8n8yhhZ8PxFSqp/zqK4rU/tTBP7gqf1MVpFIHMmrXFzd6ohFjfxSJ+Bp1MzqCiHJm+gi5WInHLhw0FygVWsqh24EsS1RrovDsneLs1V17nqbqB0iAWNADf85oCfE+f2FhLDrI4jJENysIusRZ2JBddTicPppxAGiHr5Qdga9CNJSoJxDsEouDsCO9DLRfdTYeYv7drRexaEcL3EeK1k89UrUxsQv8h5cS/U5D4lG/0n6kFc81KGlDSBFJlkqCTyvIuMZZll5L9cePvqGlbdgn9+AF/1GVUk819UIrJCbr7AIRcQw9g1vVyIFAWmAfE0geJBgJeB/LqKvIaYbsgqogGKHmNmAiKDVUqMdZDRnVmbqP/dFw+ZV8COQ9iPaqrK1TqCZRbbObv6t63tvFdnfm7Lf+l7+JseAb9BbvrPnIb7sUIfmA5AStK4zWswKA2BslHIfXRJwXCf2chxMAwGHmAEla2fShWZg9H33mYvNyMX3D+dGEvcv6EiHRX69l79lfz7EGRyNn796/G7NFrp/Ea9sB/4GstqSo2GpdK1pHOSuGSBQzX335FbiaIfCqyvuOL41BhjHxsdIRa53tCxHLAJx6gXi+/Kx6cOMgPHsMHLHyNegeFpW/vOaoKY+RB77A89Pd3
*/