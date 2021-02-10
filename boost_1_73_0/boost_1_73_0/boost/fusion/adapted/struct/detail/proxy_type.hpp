/*=============================================================================
    Copyright (c) 2009-2010 Hartmut Kaiser
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_STRUCT_PROXY_TYPE_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_STRUCT_PROXY_TYPE_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/detail/namespace.hpp>

#define BOOST_FUSION_PROXY_PREFIX() obj.

#define BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                       \
    WRAPPED_TYPE,NAMESPACE_SEQ,NAME)                                            \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DEFINITION_BEGIN(NAMESPACE_SEQ)         \
                                                                                \
    struct NAME                                                                 \
    {                                                                           \
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                                \
        NAME(WRAPPED_TYPE& in_obj)                                              \
          : obj(in_obj)                                                         \
        {}                                                                      \
                                                                                \
        WRAPPED_TYPE& obj;                                                      \
                                                                                \
    private:                                                                    \
        NAME& operator= (NAME const&);                                          \
    };                                                                          \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DEFINITION_END(NAMESPACE_SEQ)

#define BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE(                            \
    WRAPPED_TYPE, NAMESPACE_SEQ, NAME)                                          \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                           \
        WRAPPED_TYPE, (0)NAMESPACE_SEQ, NAME)

#endif

/* proxy_type.hpp
b4MBgEEoOfDnUonioiR4psMGMWVcdKEG7IspzCAKWkAcnpPTZMzRGUS7wh4hPeL0+ZB/R+ygRnS2dGR6HidBBbE9rxMVn6ZY4KiY4UyMq7yZcdy5amPdgBQLEZDSI9Q5L0MTMYnQRDpCAXgEZw+rACCnt9IVwPeIJCGFUIJYBUfGceJNAqwiBADuk9Ij0hRsIZiThEXknA2RCT5PAo7TQshEeCIfjSjAFng8oIWoBCsJmFxfINMjRhXktaU/G+wTCQ4WSwzCk5zaiZiSTJ9ozO5okkvfaTSJ2NP+lYAtiZeRMU6CmusgPEJ6RGs6TwoSo4N9wqVSFkKyPFuGPc5LQnj3UCPmclyymcyJWLDyxrrKdqIS459dm2IQgnkl6IQqLQ06uw2hSjnxM1fEf7BPZ21EoOBlIUIBVp8olgUEAGMQlDrjjB5RZuPQSplEYKF0Al6roJA+wQWbndLIqJmnZFRNov35mYj25y0xxhB7B8oNPYKWasP9KqgRHGcZW8gKIh9VZ5I0NxPvHpFzsNaQE0qfOdEJCvFrOcZJnOdURFeK+9tg4u/RRBvteQJkk5iCM8xIFw1YEiqdgIWVk4yNVASrls0fyaRs6q17mASZpMEap0aoMlTr1CNnTm4LZahfX19Lj0d4SYwxzVge
*/