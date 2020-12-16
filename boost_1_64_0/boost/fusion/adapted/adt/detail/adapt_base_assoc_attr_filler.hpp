/*=============================================================================
    Copyright (c) 2013-2014 Damien Buhl

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTER_ADT_DETAIL_ADAPT_BASE_ASSOC_ATTR_FILLER_HPP
#define BOOST_FUSION_ADAPTER_ADT_DETAIL_ADAPT_BASE_ASSOC_ATTR_FILLER_HPP

#include <boost/config.hpp>

#include <boost/fusion/adapted/struct/detail/adapt_auto.hpp>
#include <boost/fusion/adapted/adt/detail/adapt_base_attr_filler.hpp>

#include <boost/mpl/aux_/preprocessor/token_equal.hpp>

#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#if BOOST_PP_VARIADICS

#define BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_0(...)                              \
    BOOST_FUSION_ADAPT_ASSOC_ADT_WRAP_ATTR(__VA_ARGS__)                         \
    BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_1

#define BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_1(...)                              \
    BOOST_FUSION_ADAPT_ASSOC_ADT_WRAP_ATTR(__VA_ARGS__)                         \
    BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_0

#define BOOST_FUSION_ADAPT_ASSOC_ADT_WRAP_ATTR(...)                             \
    ((BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), (__VA_ARGS__)))

#else // BOOST_PP_VARIADICS

#define BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_0(A, B, C, D, E)                    \
    BOOST_FUSION_ADAPT_ASSOC_ADT_WRAP_ATTR(A, B, C, D, E)                       \
    BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_1

#define BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_1(A, B, C, D, E)                    \
    BOOST_FUSION_ADAPT_ASSOC_ADT_WRAP_ATTR(A, B, C, D, E)                       \
    BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_0

#define BOOST_FUSION_ADAPT_ASSOC_ADT_WRAP_ATTR(A, B, C, D, E)                   \
    BOOST_PP_IIF(BOOST_MPL_PP_TOKEN_EQUAL(auto, A),                             \
        ((3, (C,D,E))),                                                         \
        ((5, (A,B,C,D,E)))                                                      \
    )

#endif // BOOST_PP_VARIADICS

#define BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_0_END
#define BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_1_END


#define BOOST_FUSION_ADAPT_ASSOC_ADT_WRAPPEDATTR_GET_KEY(ATTRIBUTE)             \
    BOOST_PP_TUPLE_ELEM(                                                        \
        BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR_SIZE(ATTRIBUTE),                     \
        BOOST_PP_DEC(BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR_SIZE(ATTRIBUTE)),       \
        BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR(ATTRIBUTE))

#endif

/* adapt_base_assoc_attr_filler.hpp
1f2Ly/OrR7H+2rtYMztr0F8FCw1SwYA+HM5Zc0fn9W5FCCKHCELaiT3YMpqpzSwuwCdOY46tpYhhpI9BncNeb68PJLbxdu1wAEyXyqC7iwfSDfaCVOWOHYJoYr0pt2d+HzY/IAtCUMHsLPw4dAFfPWgp5YPr9c1253SAoW4eghqc8jODI+gNe41ex0cVGg9zNkqte4Elw+L8omrHempYbIxpF0AMaNASMA7MicMYg/pJqh9hm/XjLQ/o9wZUE2hscKLd8MqrNxotaJaCcLqaUt1iyEDVW+vtAFOjdQ9TiXjKj9dAh1+Da0QPGnQ0Al2ZNaWhe6o1VmlLy4OhrAtXpsNwjkWz1Aat4UBrlDJCAGKBh76IP5hbYSDyOCcHcMa1jVF9UO8O0QaW2ceIC10QAJ1W5nTSiQ37XRtt2GppaGNQx4jS66Lhh/VOrTUY9AaaA4dtA+gaFF4nHC6lCbcT0ogeQjYVvBe8ZbsLCoZcKN4E1+qqtWtHSaAdWgNDNNr9Y5botLstj7vZNIEuxlIsfFF/Q486HR2EYjrtws2BhINN1hiwOtYbdZpOi61D+prtMOgMFMB4oHNHa5WW6NgCUKvqEMBia7BhwSbkKAnYsk+jx2He3rc0fDjlj15XqPeURWzvAaGrUQMVIDAV1euWICo9GjZ7Jy0wLnLt9Libl4i29mOQjfqh2/SYcljbRvuoYaurg73e8ZGWfRP5FmojChn7fSxgQcyhHz2OBZuGSL3TPoj/ykcwzyDE9jwfQY9zy4NyiVDVsqqErMDiWLGsKpJVRbKqSFYVydqDQaO5iCabtdXAb23m4EoZLjYpLbF01szKGSVljNmS6FVw6e1BCXhuDrR2IiWFbkTBNnqcJfo2uIlZJrqwpanb0EDWHVeaQtt0cLS51hpofRBdaKO0ua5WDQWLlHoWWvSm8ZCioV4hkZ4yr+vgcGDbDe2gjk0gYBuEylWOjkBAQyZEqgFV9ORSNyDXTWLSi4IqDJe8lUILNyxOygER+hSV8ikAyWOCJBcDInAxoO14Bsp1MCCoNVTKeajAeQDA/LLRr8EzdOqnNdQl9RZVIYcLUi8ke0RR6aBCL20ZkZ82SqIg6oHtjI4LdMtWwgjhVhoDEuYBRfCEdVAnrNQIu3Uoe95Cbc+B+YVZvRvZxSJkmMKgaxc2fgLGCKPwGCjYy5S2ej20HZfUThWEib1ZEpQTfo/bgUY8AJ3Qo9GQW6VXKeGwNgjzhW6bqC+gYoWDqUgZRH0tjKqWQchhgigDArQ8BGuRIuY+bEjvKezeUkWGRG1AQHQHApANERDfJbAC7UAwAHunNjEJd8KDwVS/h+lwCWALxQ2PI3h0s30ipMM4aKl+SEdx0KghHcXZHHVCOowD0++caNXOG6H90nCc4ryITsUZRoAXa6y0KQMcXFww623MiF2gbDMC0EoejbYJadguenNRneW5mSWbjwcgH6IpnyNnbscOFPYLUHn0aCxj0GsMTptPR/rnhaAfvb6mxv3rZG8AMUA2yx+CVGNqrYsQRoZuGUKg7YT6aBNNYFlpQphhmVCn5UXZ7Ld1qPBdWBE0QerliA2grKElrE6wJ4ofvXWHvVGspE7Wx0jZGtBHKSuM1fzAITb6JmwrhZk7foz5lvnjtze2ge5wo7fZgjMGtNFo4od011R1eHLsHQMNNAokqWP9eKaLmaRBJ8+cSsFTUzuS8M5dKXj77mTsnVOTgH2PC0J7aUsN1htTO7adWcqzDSUnOWfs2u0wtu+c2lUm2bl9V5oztW1HRZrt286YSnNQYEVuuyZ37EhzdpMWbavC5Ezzw6RhQaavgEIv2qgP0VcM2YOdm1DXYNSICFPzEYnRG2Y=
*/