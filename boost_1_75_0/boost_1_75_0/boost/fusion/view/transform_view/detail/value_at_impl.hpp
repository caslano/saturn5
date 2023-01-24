/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_20061101_0745)
#define BOOST_FUSION_VALUE_AT_IMPL_20061101_0745

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion {
    struct transform_view_tag;
    struct transform_view2_tag;

    namespace extension
    {
        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<transform_view_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::transform_type F;
                typedef typename result_of::value_at<typename Seq::sequence_type, N>::type value_type;
                typedef typename boost::result_of<F(value_type)>::type type;
            };
        };

        template<>
        struct value_at_impl<transform_view2_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::transform_type F;
                typedef typename result_of::value_at<typename Seq::sequence1_type, N>::type value1_type;
                typedef typename result_of::value_at<typename Seq::sequence2_type, N>::type value2_type;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
pfQpn8acQOpeTPRkpnku35x0eCX7S9+u+xfOnupR2V+6wRvZoVnWOl+vPmIkT6S0f7CG+QkbxRB0f4Ng69M5vNane0mIHa71lM4/LzpDgyzjLcjPkf0m/0a9Ol+PTA8sT9aYSziT7xlGi7y5Sh4HusLeb74e1XpmZXCKPe/kZG2qFeOQPUAH9kk7F+m9XNcrAwwg89RPPtD1iN8q+TSDou0+yTfqWXL5hnAP8CiNdNYvwW+yH1hn2Picz8cHqC/6oFcGBsQmuRbzQQ3S2cxXJBvfBny/aMJVdy+XrwuQYI08ipNPq1f8C0cG/toqH4u8RC2df10PDuQqPJttPfwh8x0akz/Iw4AlZE1nZbvsx6gI6mQAYa6W40F7GY3yz0RShdZs07rVRT6qOa1iA/LZxvvMYfwVZ5IOJhAK8NaDn8vlA2EGBotTbDyNO+HAL+IdLspwgbRzd1O+Hvwlxi5gD+2fep5Irf2o5H8yDaGU5Ll81Cvp8QbxcdYD9iNfzITWm2Ii+yhDtMqH5PKBUxqk/0A9uF5RSL90yrQV+nR0ODzEV301y09fw3zmRbh/hs4Qs3iMYTZOJqqWiqry+eJ9wG6Lf2xuQ9e7PXVhlp01P2slPwCen+1yf1edM8+36mSTeX/u0h2O/aB3mzwGeYL2cn/xnc8uRHpme+mXNc5+0yXMlkKXlrVSPv+jP7IARITG19keNeH5Ub30FT6f
*/