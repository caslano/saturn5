/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY
*/

#define BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#define BOOST_CLBL_TRTS_IS_NOEXCEPT std::false_type
#include <boost/callable_traits/detail/unguarded/function_3.hpp>
#undef BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#undef BOOST_CLBL_TRTS_IS_NOEXCEPT

#ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
#define BOOST_CLBL_TRTS_NOEXCEPT_SPEC noexcept
#define BOOST_CLBL_TRTS_IS_NOEXCEPT std::true_type
#include <boost/callable_traits/detail/unguarded/function_3.hpp>
#undef BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#undef BOOST_CLBL_TRTS_IS_NOEXCEPT
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
/* function_2.hpp
C2GT3cSzFA5L+rUM/0HbDgiPiFzxK9ARiQYQNM7MFdeAXgId58kVC0D3gT4BneHNFT8APQcq9uWKStAdoA9AJ/tzxXdBfwDlZuSKmaBbQW+D+mXmiiWgx0AZbXLFFNCNoL+BumflinrQr0BHQOOykT/oJdBxAeQPug/0CejUtrni26AlbbP1fCCozcfIcUXX/RWq+xzRBvXqI3qTfdyWT6PuoijPG7sxh+dgrJDH8G+E5X3C
*/