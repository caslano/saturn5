
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER_HPP_

#include <boost/config.hpp>

// PUBLIC //

// MSVC has problems expanding __LINE__ so use (the non standard) __COUNTER__.
#ifdef BOOST_MSVC
#   define BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER __COUNTER__
#else
#   define BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER __LINE__
#endif

#endif // #include guard


/* line_counter.hpp
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
*/