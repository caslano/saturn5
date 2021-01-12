/*
Copyright (c) 2016 Modified Work Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY
*/

#define BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE std::false_type
#include <boost/callable_traits/detail/unguarded/function_ptr_2.hpp>

#undef BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#undef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE

#ifdef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE
#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE std::true_type
#define BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE transaction_safe
#include <boost/callable_traits/detail/unguarded/function_ptr_2.hpp>
#endif

#undef BOOST_CLBL_TRTS_INCLUDE_TRANSACTION_SAFE
#undef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE

/* function_ptr.hpp
Y/jnJVyarx65n20FzQpko5VgvoZatzTunMi2Re1izzcydTy2Qvystc6ipF8zrc3frNj9KnG57VSuxBW1QBxrnkiYmOu7MeaI0fGnSZrccx3GWGrQmCIjftvRDjrGv1me1RO7imrXV+wGiF2aHv/DYhfQsJb4e3aL0w+l22HVbp34C1px5oiGtyT8o2KfWHZu5b5XY73kuZvVkpWJO8wUU82q7j5rmSXp9LDriXuO3hL/QV94
*/