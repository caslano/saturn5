/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY

*/

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
#define BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS
#include <boost/callable_traits/detail/unguarded/pmf_varargs_2.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
#undef BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS const
#define BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS \
    BOOST_CLBL_TRTS_ABOMINABLE_CONST
#include <boost/callable_traits/detail/unguarded/pmf_varargs_2.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
#undef BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS volatile
#define BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS \
    BOOST_CLBL_TRTS_ABOMINABLE_VOLATILE
#include <boost/callable_traits/detail/unguarded/pmf_varargs_2.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
#undef BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS const volatile
#define BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS \
    BOOST_CLBL_TRTS_ABOMINABLE_CONST BOOST_CLBL_TRTS_ABOMINABLE_VOLATILE
#include <boost/callable_traits/detail/unguarded/pmf_varargs_2.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
#undef BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS

#ifndef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS &
#define BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS &
#include <boost/callable_traits/detail/unguarded/pmf_varargs_2.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
#undef BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS &&
#define BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS &&
#include <boost/callable_traits/detail/unguarded/pmf_varargs_2.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
#undef BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS const &
#define BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS const &
#include <boost/callable_traits/detail/unguarded/pmf_varargs_2.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
#undef BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS volatile &
#define BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS volatile &
#include <boost/callable_traits/detail/unguarded/pmf_varargs_2.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
#undef BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS const volatile &
#define BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS const volatile &
#include <boost/callable_traits/detail/unguarded/pmf_varargs_2.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
#undef BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS const &&
#define BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS const &&
#include <boost/callable_traits/detail/unguarded/pmf_varargs_2.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
#undef BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS volatile &&
#define BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS volatile &&
#include <boost/callable_traits/detail/unguarded/pmf_varargs_2.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
#undef BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS const volatile &&
#define BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS const volatile &&
#include <boost/callable_traits/detail/unguarded/pmf_varargs_2.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
#undef BOOST_CLBL_TRTS_INCLUDE_ABOMINABLE_QUALIFIERS

#endif // #ifndef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS
/* pmf_varargs.hpp
5aj/7UNKArVljcGKuugXaBqyUturXStBFrtysGvvrHTzG1TgQUkl4ci7csKKjBV0qjU92KYwzMFKXF8P60js5C/T8KsZ/nMWsCf8xaKZqDBTqZdSp5O2Qpe778ZmGyS7aWjfsYjIMm4yDK7DpEla6WcAByaLYL8uu70BzFWTkOU2YAIs92Had1jxfEQJeTxYJkvLivhU0epKudIqZVxmhWjlngk3+BHknNc5zJN4L7oDNHmpZzBdiVsTsrDVyAF7xlTsx2pRHaxVFd8s2jQ8iM1PlrGRNnsVC88qK664l13pmLSpP6WjBYMfLGXoR8VSmQ/ofYXbZg6YBBCS22XI5vnjqAsIjFjRY8isTxHbmROuVTIQWzQJugw43YPgCrZvTtT+ZdrHKdANm0dF9VPWzcgbwNJWh5VCwBBJWpbo2+f2apzV2jFSvVzn9NOxpq/80jp33BtiPqdBvJpOW39zYCR5rmSlGiPnRgvflMpar/HhsAFAoir5yiyARKwKyskAN/VvbPLXwhK60j6lRxG86kCJi0IXHFONalmZFFGppBtNLWgAQ/MDBKCxnQ==
*/