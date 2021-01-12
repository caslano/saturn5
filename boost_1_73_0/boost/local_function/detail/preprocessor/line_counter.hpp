
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
m62eHOy2vnjt5fy/Dv6D74FDcjRi/V/yCOVXBrW9uco0S3hujs4k66eaQKdhUgjX+Tpn0GQ35dho4Z/fQfmT7OjmDXEL+TBdSgr+ezsFOiFYBRb8j55f76ij/ArOtY5wXyxVxknPTjhNuyqObUViJ+zU51hacJpVy7EkSDu0g6RFZNuN56Nwo+2XRXrd4teMfU475j0FegwmnCcEv4FSDw5SeuRFFKFMJbU7p1Nq1erxRkcv
*/