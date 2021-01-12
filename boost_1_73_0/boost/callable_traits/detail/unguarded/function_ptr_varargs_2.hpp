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
Pbyv46Xjp17byYCfi/+z/CPN51a6jplu3SX58odMkXWLdbUVcz1M079cyqKqXGvJGmfSbtuumftulJ/kmKbSC99g2XV/A/kqlHCXJ9v565XpPBtfMFZfyKR14bqfYt8rztR0qm+34xgS7zNBavZHgd7Bhb7wMRSK2+nxQ80209TaHorV9qbrmKGy5GVl8oP+F+MKEk/zZ4o9I523pW1IyDYtTJ45GOwU18hkRr6/RV8FouNy
*/