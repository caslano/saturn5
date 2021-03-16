/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY
*/

#define BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE std::false_type
#include <boost/callable_traits/detail/unguarded/function_2.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#undef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE

#ifdef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE
#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE std::true_type
#define BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE transaction_safe
#include <boost/callable_traits/detail/unguarded/function_2.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#undef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE
/* function.hpp
gs112mIaZ1xcDwe1KD/frQJYqlVGyIgzH2n7+/yxfpXtDsFkELdAWswfDkb6Da2wHuPrRr8/nhBOgRiMOimybOQCKQ97tUTEKikXl+nUZpaL2QfW4VC8F/qu3x+QadEgfx9UW8a8STE4VUhDyrVIMiGESS+Vw2EkEtcNP5kKiiuzFvAHuI88EeOipvyGahDfHsoe69UD63lP8YwWjAyGe2L+oG6UCXmj7w2McVbzM7QfdPw9OnQmMGJGgbwzifM=
*/