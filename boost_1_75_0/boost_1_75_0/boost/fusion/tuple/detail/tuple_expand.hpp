/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_TUPLE_EXPAND_10032005_0815)
#define FUSION_TUPLE_EXPAND_10032005_0815

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/tuple/detail/tuple_expand.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
#include BOOST_PP_ITERATE()

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    BOOST_FUSION_GPU_ENABLED
#if N == 1
    explicit
#endif
    tuple(BOOST_PP_ENUM_BINARY_PARAMS(
        N, typename detail::call_param<T, >::type arg))
        : base_type(BOOST_PP_ENUM_PARAMS(N, arg)) {}

    template <BOOST_PP_ENUM_PARAMS(N, typename U)>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<BOOST_PP_ENUM_PARAMS(N, U)> const& rhs)
        : base_type(rhs) {}

    template <BOOST_PP_ENUM_PARAMS(N, typename U)>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<BOOST_PP_ENUM_PARAMS(N, U)> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* tuple_expand.hpp
jJyrjv++0sCPTWisxM3eMnFDdOCGh64nG4oIIXtiGcgjyUCmErphPsuvwuhT7OBenqUC6PQN6voAyJLbSWTz0msojAm3KSelowpBtA3k4Nq4SueKsNTOIrDwd6sxPXAspmG7Zv2OSLTDfQlwvV/UyiA+s8yj/z78jz1HIFGDF1Ol8JNLt6wzVhhhutS3vMuWyjaFT73Iq4pNvfgauzKqLqJ6ohLN9n2zIy9rf9/+gks4IfwrQhuu7nRlfyV4zNNa3Lg4AvWCz+IdLFaJPSp9H0iGI5QtHJNLCXGBTNF5G3XFKZFktuk7YVbhbQoMFwBigTiwlEvYGoL6ZUHvXV2xQuUXY5TfykpPVnOh9g8REM1z69admjlUJGlHHpJoB/IfLl7s+KjwsXXIOFxOGRjQve6f1wOveW1JvdJ2pZziIxydLGenRcsbd8omLD+jJYcxDJINUOmXp5a+f2Av6x4d6uk4+bd+Ft3aHHafql547qDfMw1jXzvj8TTxHU43H0K3CYfSTXVn6er4fl6ljG2/7uhSnUl/B3Klk07f3M/iirLZO7AF0YPwbPD9pb5MkeHTq9NjtmS8FPZcgZc0w2AW9SbgGe24mp4a+vremeA7zctjutVzhy1kf5GqvK/xaQpmBxqNyA8Q3nVF2LIbBh73F9PRf8OQzvLomeL0e+k1WW5snY54DyadZ97AZNzDVdDnGHMZZ9BMijpolTSe
*/