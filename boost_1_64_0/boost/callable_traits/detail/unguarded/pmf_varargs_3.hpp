/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY
*/

#define BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#define BOOST_CLBL_TRTS_IS_NOEXCEPT std::false_type
#include <boost/callable_traits/detail/unguarded/pmf_varargs_4.hpp>
#undef BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#undef BOOST_CLBL_TRTS_IS_NOEXCEPT

#ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
#define BOOST_CLBL_TRTS_NOEXCEPT_SPEC noexcept
#define BOOST_CLBL_TRTS_IS_NOEXCEPT std::true_type
#include <boost/callable_traits/detail/unguarded/pmf_varargs_4.hpp>
#undef BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#undef BOOST_CLBL_TRTS_IS_NOEXCEPT
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
/* pmf_varargs_3.hpp
5+8MDUVfLeLw1pVXIcAhvBBYfTzgCaz3uroPBb+Rhp/Pg8/UagWH4JFIYUsfCwK8Tz0Zj+7PMnjcHsny9ksNbT65+st8sWouaWvoVLpAqwSlKH5dWiVEFDLPhj96e+zN6QlUg8sY7XoM21LloNbd1pJgb41Wms1Q55pYEGb+UhNRGssf+Us3Xi5jEcCa6v6lIx02tCIqn5vL6pUu9eq0NgwOCiHi+o1KNl+LSkkkvHjZmz0ERAUvC9wJVquPz21B9umLzpEYTOYI8ceNwjPqXBCU1vSvxKjdAgQL+JMPaQ+bA6YGK/jz186NClSqQrd4AhGRswRLhJ1fePl5OSrNytZns6Q7PCkFUteA8lxK0aOBiF9dCi2HZuGIeKnLSPvtwSBvGlhWWJ1h33gL22B+Ur+a58u29OcgBolRQ2xI6iI0HbjMe4Wy7W6OYKi0xz7Fsm2L4KX+Wnf0Hb0dFrRkS62sjkLrdoR+UvDTjHLQrlF3I9xvnCgoNFSVgPKVCLirOOBecBl/Y7sBZ71Yzm6N6fxuXR8XifqhR76ZRb8/5gFn9K7cbRNEraVbPQ==
*/