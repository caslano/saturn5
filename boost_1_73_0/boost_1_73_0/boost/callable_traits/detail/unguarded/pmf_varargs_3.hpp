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
9jpfrdbmq66tb15hwYYRGG9tfXOnj8CeE5XoaNW81Y2NNdXelQCvb2mr71ij1TeLTmfTAPZSEzc9q6VtpXJr72hphcJRE/6PtWsBb6rK1jstdCqgNBQQkZGCVYoI0/Ko4PVq0yQ0kTSpSUpBq7FNU4j0EZoUQbwOD1H6BfE5Or5GHUHxMXPHx6f4uoKoKHIVdXzMVefiOHrxyoxeH8gnCHf9a++zc06aiqD9Pjgn6+zH2uu91jn7nD/TxQCej/M=
*/