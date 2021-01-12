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
+XzG/gi7X+lRPi3AQ+bK2mrc8qZrHbKeemxQAU/xeupxSrO77aPI0Y+bqGeB/CYQdAPoNVA3T6GIgH4J+gI01lsorga9COrkw81E0GbQx6Bh/kJxBehZUFFGoZgD2gh6HzQ4s1BcCvo9KKdNoTgHdAvoLVDfrEKxGLQd5M9G/qAbQK+BugWQP+iXoC9AY9sWipVtC8Rm0B/bBmht5xVW/fe31e2vwzBe6XtEEX3n6gDFzYJu
*/