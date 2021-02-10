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
d7A01lGm49R6o9d2lc90Zg+kOngE/1CQfQ1qkzIXyvnuWKdRHoJlWj+UBXCcF9Ic9cZZRg9KLxXVOP6pFzDVcBxmRUvBnCtndFomNUGcD17CN4lVlc499K12quJGy3sqCx+riWId9C/VPS3RAhp9vvoDiPRBKhhBlRCT1cZVmIgqDF6ACOtnZq5LLquGCkvLQGxZZwwkVeYYcqaUcehBrLqeC58u0HXpwHSFn2vA8myCr6bmxl+lTBeMvtNjvLBjt0UPbliRmK6al882vhdv/RarNjxIFiJ56BcZfdni5w5WLV0IFY571D7p96NMzniuox80to0z9Rl0ikGrla/oF7R54DdG5IMWupaJ8GT8rkvfWhxYzsMo/MrkfvlKE3W316W9sL/XjRoDXnAPA8TqUQCVuO4wDI6wP+4Otk1O46HFZLgwov2oMUUWjUmAVL4xzHoYxF8O7wbUgYoqrpde2I1yNj5ID7bHd9vZ8OpUh2JVv5/zWs3VseGP0pkANk8tN437k8VoopO5+A+UP6CBYUQmYrv7FlXkm6SP7zYVr1vVbwvfJNNWhGOu1pYzQmfrfD1zaE13eDqtqWCmbMPUpM9MsUEFbITD8UeBBT97R4dY+9gf+T3vOIF11ViW0qCSxYhlEZxdffwTbtsC
*/