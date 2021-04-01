/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY
*/

#define BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#define BOOST_CLBL_TRTS_IS_NOEXCEPT std::false_type
#include <boost/callable_traits/detail/unguarded/function_ptr_varargs_3.hpp>
#undef BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#undef BOOST_CLBL_TRTS_IS_NOEXCEPT

#ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
#define BOOST_CLBL_TRTS_NOEXCEPT_SPEC noexcept
#define BOOST_CLBL_TRTS_IS_NOEXCEPT std::true_type
#include <boost/callable_traits/detail/unguarded/function_ptr_varargs_3.hpp>
#undef BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#undef BOOST_CLBL_TRTS_IS_NOEXCEPT
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
/* function_ptr_varargs_2.hpp
Vr2Nzjv3vFX5KyfCHU5INGX68AYFOj+WR5DvbhK507Cdaqd+ywbdaw/4GcsjAPGOtBNtD0rloLEnb+PvWQJ3drKi0foOUi76EkhVOUhaakv9dyDCazxxQPKAnZae8VFfv7AkB6pbCbBNsKqYlq8yXUIb6QTJWLYpMP2hmrkY+pZ/E6LZPgQ2ezZoLUsOoSppAftAtWFaRaenMelYewon7UUukrpKpZfSq9c4CbOl7A1U8dK4q10AjIBYq1lPl8FUE0ElQ5sbhpPBF4LzS0xCCjUwR4WfeFnGE5UH6BsBAKUdBJNBKgPu48q9yecdhwcw3ot+qxXn6YtXrTz1EUW5CSJR+sUNKTWuhuCOKsl9EUDANn/wj2MDK3jMVTef+RQhNqnDrCmoJTa81Ctn57ZoPiQV/MqBQC2mhTOPAPmKwHCtKup8XL0rDd1Ny9N7WO931jigb+cqZriv8g7Y3yT2EY4UjOFEbr9KqMlei+6V2aqJm5o+o2oO3twQlixR2mfYd+jHxczTMq3P1+tzZNSe55Z1vFDle0vV+/QWJX2OZjUjCWzG1PgHaNvOQQ==
*/