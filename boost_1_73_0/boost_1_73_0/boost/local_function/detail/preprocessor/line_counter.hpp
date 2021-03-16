
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
kwWMpURjft72TbmfnX8u5+tn71/fY/PghxlbTvnLnn7ooy/2JCUt3VPY5F7z1AnGdlD+Nxl5AxoT167e1W/C2u6HfwAmMVyE+f3/e/Hqc78qee3Opskvrtj5/H7GJlP+9rvm/mbE6pbKI5f+c8t3iQNTGGum/A8Wfbjv/Hd3nVrgu/LSbatnQtvfAr+9j+88d4j17ilzznGRKFV3BA0fiCaPOr+jOi5HnbejMoHt8uvcjmopL9l0ZuSu+voLrUI=
*/