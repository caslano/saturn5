/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY

*/

template<typename T, typename Return, typename... Args>
struct set_varargs_member_function_qualifiers_t <
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    false, // IsTransactionSafe
    false, // IsNoexcept
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type =
        Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS;
};

template<typename T, typename Return, typename... Args>
struct set_varargs_member_function_qualifiers_t <
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    false,
    true,
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type =
        Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
        BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;
};

template<typename T, typename Return, typename... Args>
struct set_varargs_member_function_qualifiers_t <
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    true,
    false,
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type =
        Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
            BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER;
};

template<typename T, typename Return, typename... Args>
struct set_varargs_member_function_qualifiers_t <
    flag_map<int BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS>::value,
    true,
    true,
    BOOST_CLBL_TRTS_CC_TAG, T, Return, Args...> {

    using type =
        Return(BOOST_CLBL_TRTS_VARARGS_CC T::*)(Args..., ...)
            BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
            BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER
            BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;
};

#define BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE std::false_type
#include <boost/callable_traits/detail/unguarded/pmf_varargs_3.hpp>

#undef BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#undef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE

#ifdef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE

#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE std::true_type
#define BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE transaction_safe
#include <boost/callable_traits/detail/unguarded/pmf_varargs_3.hpp>
#endif

#undef BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#undef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE

/* pmf_varargs_2.hpp
MuKxzOfRcsVR/jfCqseraVY2OuZcpntXFIwGYpn1/BIgOf6b8atMjaZrSXZHAFlU81OwXkdFvNXEKp1Oc46fqvnp/P6XCFZK1Ec4+PyH7Texu97UxPuWVk18aG7iqfaa0DFgw564kzqDZLZiC2p1vFgzqj282PdcjIXvvn2OMeSWhez/slD4v/DPoQt1vLGb8ir7JhsT50F72F+jOYpz9kTNXvlh/2TKK4QT9dZNuKu1Bb1L19lEIvAH9JW4RYCrdKoOqiQTqAzodDZBRwdg5W5tj2m9hAxQPX2DEY5Sz2Gc9wIBYdAL+tnzDVqYG2arcu402Cqf/D3hMO+wGAMOWz9tNzMW+QZnlZ/5/CzaXIj8MiNA0SULYfwPHoxjbTjjB3lLBz9Cu25vVt+S+zEPYKFNSLMIgorRmozSsycr175FJQKONg/PMbeQcJKQBxx70HU5VI7KLVK118CbGpg/ax6eTz3UYEg1j9RRFeRQ9zjbZKOdUVqll4+KEwnCdvjlDSSlIqBpqOfvMrM4SSYWh8FfqHMhEZhKW/zpBbzFLxFbvAhWM1aga+YzjJXp4lr4bIwwYe77DE3R4GdNPoIRssKLt5tlBTpoN/Pl//wuLirF6Kz7Cy0lxbUJuFEtc5J29i974zghIwbmdDhtb9fRKbNFx7H+33WES79iZGtJgsdX+DSMpyvZsz+NA8nD6BIrYcbKdtgsoZ8fQjmI
*/