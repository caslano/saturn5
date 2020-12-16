/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_BEGIN_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_BEGIN_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/view/repetitive_view/repetitive_view_fwd.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_tag;

    template <typename Sequence, typename Pos>
    struct repetitive_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct begin_impl;

        template<>
        struct begin_impl<repetitive_view_tag>
        {
            template<typename View>
            struct apply
            {
                typedef typename View::sequence_type sequence_type;

                typedef repetitive_view_iterator<sequence_type,
                    typename result_of::begin<sequence_type>::type > type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(View const& v)
                {
                    return type(v.seq);
                }
            };
        };

    }

}}

#endif


/* begin_impl.hpp
IG1DYCzlmZTTAvd4eYPfbaG65LbAZGY9c5/6SGMJ7aFRWp/Qx9epvPwWOAPSllX3S0dWwAKLROzJF4Zcv1a4S4ZfpLnMLKDhvTE0N4tYoKooL/lAo2G0czb1Q0kL3LRIe+s4SbEHVLHADZs0Z5N/NaA53diCa6u0DOWc8n7QZYGJBmllbr/KRP3XzAJD9NKynL5XkNqzJc4xq7Q5vrXqUx/1wDnG6pm/lI3Gkn2QBTL6SNuULU1GauuRcj0bl/p3IzTMo2FJGgajvFsAWh8faSN/NN9JMUThGmmRVidaL++hY3D+WaU9q5C5KxkeFvySVtrZSZnLUT13WKCaQdrDwfneUz33WmArSHt7Pt5KsaO1ZPYEhtB4ce2zwG/MnEdDDJTnfhwTwvD/wWeKq+Tvd6ClMUnbYJxYgWI/aoHaIK3+HwuW0fhEm8TSlW9wL5DGxBkLROukpX3WW/6exjkLnGI2fXJVWnfjLlhgLSvv/IJDnSnPPyzwQy+tTeftK2geXbbAMGZZ29wdQu1yxQI/QdrI4dP/ouvmVQs8FzY+uYx/h96kdrlmgZIGabPC8h4gw4l5VCct0/rgXxVLPvTuoJf26UGxU2QeC4xidmflmsXU1g/F9UHYFM/xrFRPtIasvOZZlpSVv6dhgYEg7ebj2i2onmjdpamvt08s9OwzKvmvY8gL6ge0bXppN8pOo3sUeKZO9zVTlhjqWzQHs+FPFxWhPNFqMvtnfn7ao+OhGBRnNqPk3/L912hOVpekF+HT5HfVLbDQIO2I/9wx1GZvLZAPpKV8j0+0C1o3Ycn3cLYnR0tTee8sUJeZsWjEc4oBrRezSxsfRFE//CP6QVidAcdyUnloxwysvN+ju9M8+myB7yBtYfuTcyjdFwusYLau8bZbFN9XCwSLdolO3h/tfZSZxvwPvB/USTuSo9VVqif4wzmWrmy2ILo+xBv84RFLd6hc8xHU1j7+8FOkm5jcD2OqbZa/4+APa3XSyu56u53WLH9/yGuQdvzopUOULq0/ZPBPsUn/nStt1lFdcvnTc4spyf+u2yOvVXn8YRaz229z7yfL6w9lmJ1esqcMjc9Af7w/k7bt6KOsZPn94R+WrsmykACKoaA/bBAxTE2+l/p7dDT1X1F/yK6TdrD6HXluWswfKjK7tu77UFrPSvjDF5A2bNL76hR7SX/aI0xTnyfjPPWnc/bp+Lem6YKHykP7l06abmRxuidyBPuDSS+t4oHdcu9U1h+6gLRj//ZpSfOhHMbAbGzBVfLd7WgZWXnfBn9vQNe48v4wEaS9/Pi3H82jCv7QWtiM5P1Dr80laZxVxHZJJ21d7vAmVF4Tf1hcWFp355631H+/ec8zEe0Dy3NL03O0froW+tPv1c1Mjv1Z1/yKwSJ/+sxl8iIXWv7tRaqLhtkXe7d4tL7Cks9Bp7WZM43aeok/Xd+TL+zvWlUvRunQlPUzeYH4fiOb/NzvUu/mRhvLLOf22NKUbpk/fR4zeUxlzrvMTfGhKe8IST5jU70jZJ0/vSNkXup3hGz0p/eAzE/1HhDPEX/8zRMyPAt6YaF0l9V2u2HQI3lt9Kf3gCTvP1LeAyLSPfOHM9lTbCEA9K+6iX4PBaxWKC7m7aLkW8DNCZnIAqwwNkDa+JtXjtD4zG+l90EsTp7vBW7ReIlHczCL3OmZQ2MeTbk2LsG/y6dZ39M4K2CFpsw2NoqoSfMPrQCzPnUyz6Q80UYwy3ev4gbqo4JWqM5s/uzYvZQOrSqzko3G7KNxVsgKJXTSlo6V63xCYStcB2krTs2dT/MoyAoNmG05m6ELfYejiJWefS6FiIjiqyxr6fvhaBV10gKr3o5QzF3MCk1A2r8=
*/