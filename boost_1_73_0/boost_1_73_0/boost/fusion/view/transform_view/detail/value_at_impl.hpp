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
4OxZe/NZ//Z2dEuJjs8utp6VnrvGZ3C+9eymP7ym6kzPLsi4WyKsG3k7s6FF5mkfwh/MeYRuH1MGWmRwwpyDBzBD2BsHN021jh0AXo/eHty5OydaLXzPb5uHFPYoijG0v0TxgwZ4mpZP1eFJRNYailKrxBBolG1BGRHe4OaXy/X0Utn8kiqgWcuwye1dH1SIhXR+iZAsE9cp4i6HXuydrdO7LYgCHMvYyFXl2Tz1qQmve+/G/bXmY10yrAwByoVA6N8jjkfCgRUqUUa8V/cGCVoKxaQtCbXXJ3NJlKYSS6yhqQFBYFs/hIsl9+6jn3coxsz3BAY8rHjQog9k8Y3KJ22Fx1TuDEMUlyzlI+otzmLsRuLNSt27GTD48NziunGji9x3Iwz3RtQ24T9DDRbWvrKEmXpWCYvU54bsjHGR4oLgluFwg1csltQnneLwgHrQ1GOx71JxcEZB1GRmS261rLiXjrghAmhTIoYMRT4r2PoPKtuqEj2wxR9IuL1J99TDn5Wb1YHWQiible6FsqAJwFlkrnRh4mVlUiwp6IgyhbsNqt27qsjnGmAPRuDbJtdLbqWo55MLFsD1R6uorxoSkon0YULJPdHiracPWxL6XRLP8gKTl3p/4kvjZZiXc+OqGdvQlrziWhg+ux8f
*/