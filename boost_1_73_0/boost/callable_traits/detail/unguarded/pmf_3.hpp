/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY
*/

#define BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#define BOOST_CLBL_TRTS_IS_NOEXCEPT std::false_type
#include <boost/callable_traits/detail/unguarded/pmf_4.hpp>
#undef BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#undef BOOST_CLBL_TRTS_IS_NOEXCEPT

#ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
#define BOOST_CLBL_TRTS_NOEXCEPT_SPEC noexcept
#define BOOST_CLBL_TRTS_IS_NOEXCEPT std::true_type
#include <boost/callable_traits/detail/unguarded/pmf_4.hpp>
#undef BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#undef BOOST_CLBL_TRTS_IS_NOEXCEPT
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
/* pmf_3.hpp
sT8Y8tGWP+JvFPH+Dcp20MRBRO8ec7Lk/RbKp8CtQ1XELg4/Up7a38jrdrBzrqO3JY2NoZuJP919z0VB0TU9hxQVTRxXmBdx3XwoZTjQusx0cK+PC96T/j9Q3dQNlF4DBRPz7NxF9AdPSjo7rKrWNW5b86rEtz54pbmIec+XAR1nuOd92OjR7jXyhYRvTlife74ulfABqS+5RttglvjGD5NXFNkDOknLb59V8dvSyuKaHWI2
*/