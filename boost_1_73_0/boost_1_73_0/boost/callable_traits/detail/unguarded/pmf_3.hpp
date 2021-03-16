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
byO9TvP+H7GT6lXllFThTzzwjc+j8YDLM7DDTJxNLwf2JVnq1QGuI4Mer18sS73zALctC72dWerdC7hHM+jxeflalnqHAfdtFvXLvZORzU3PA7iTDWw6vYYs9doA9y8Z9Pi8vAAwV9txDnr3AeaxLPTeAMyhLPTG3AXr1F3p9fh4VNzFyOam1wi41Rn0eP0GAHO5Heegtwswv82glwP7XsC8n4Ue/yrdcXen1+P1Owkwy+w4B721gOnNoJcD+7Y=
*/