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
sRrhIyEZPTd38zCbryUn5v1+U0vMU2EsiHSZZne1IJnPMnFlX5is9rigueN6sWMG7Th3qQUl1joHKxgRdbHrKz1itDsKWT1nF61xP04ThTuCkTdJS2rTZ7LmTkgvlzPda6579KYlByIZGHXqkC2LI10bTbVpIWqP52lezJrOZZPve6udOV5dlOHduSBaUdJi3GEdutmkIyizU7OvcTODtVi2N5UHy5oXzdOOkx0GVH98obqyGrO1vtrbe3x+8u/2O2o5swZDbrY8KMKkkJQ5KzseVbe8QNkXDB/0H6mDofSyZmaQHbbjNZT9MVYTb6py5P5yt99dDt1jZ6FklHmW9KLXN+dJV+kEVHQsxtnEKsQJMXMdeq8vuENRO+pBixzxaXvlDpYFR/jyTVLoS+cxeTFCSTaGOr/KhqvTTtAbAdFZD4axfBhEzXi5vkjTNX3jKg/QzIx+71ANp/TaQ2xFHpzGy8f3zWaDcni2Ln9oRnqCR7Xrw2x5TH97osePuL9+dXjH9AuRW4MeNGGULw7wm3/x9bekvyX9LelvSf9Xkl7L5TfKWNnYKFs+n3F35Wfc0NDKnkquxYEb2EnV0KhIcJvlGyRAA+M2bmJXvRXMVbVX4Oc2sPKtb/lb/bT79KkquJ/LHsoT+qnxuUTh
*/