
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
4LHZlv168EEMHvdMu575SNlxKiW8OpCuXY3QOwSXlHz3PLQFl1pYNgP3czTxsK6Nh6p1ApdR3CZGQ7xi
*/