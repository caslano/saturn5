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
dWA1+Ssd25QOawZJFTFuXlZJnF0c3U03KOcnXc/PwMbOPS//XQMp01C8rAOr22Tc2sk9wLvacv8vsQKVNN5dK9a2QMMnBe56mPuEjeTUJMZF+dlQGs+jiQmcwBS5WRiVj32l8RQnBbLELVPdArmElzxOirrPuI7z31jfXTQnRSiyWe//XSz3AB19AfIQslllqsoy5Ambqj8R5a7+VaZFvWs42n2OyvE08afu6jcGn6tcumbQ
*/