/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_09242011_1744)
#define BOOST_FUSION_BEGIN_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/std_tuple/std_tuple_iterator.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef std_tuple_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
SMBzgkAdg1KpGn4RBZohQzIuwj3hNFnkxTo+EYo0vhwpb5jGC7U5TZHWb25pv8FRUVCwm88v1C2odKF9adH1HCq3wIRSLXJj3251GR30c43GP1biI0+46Z5sUCg3qLFxGWCYCLnStKnIY6aGBsH18/YNSRL+k4lZReGAAC42ZaBZRD9R0jG+k/VarQ5PvKlP+Bw4/hRpKFIlmgAQU1oHzunbrYDL8E61eeswXSM2UEPsDUjaXyXUGctXc6ahRMvQ7Z1o7gYzP5kYUG1zcF7LMtXtAPpcFyS9o00APAPp1YQW39NQIlUooO2Y/qrYfPWkRaD6TDkB2fQORqZOq1OA05zBCyTzJM9ZoGqGuN9bTmchx7qFA3B9sAGti42c8hMsTcrUzKwfr0OHYoZogCFrAVTDAVXrhZl6AUw0/AB5gJhqMYW/ZXOtx7Z2QCoEU9hR8xeEn5OXDxIMM10bpsYlkaRGQmvvLUEx/Ii8c1GLBm02g1q54vtQurizVAQm2AMk1U4zanHazipU4jwVWyp9WNnTIZJiFXvaJdnfBVkxC3fJ6M5U38fs1Y9NNw==
*/