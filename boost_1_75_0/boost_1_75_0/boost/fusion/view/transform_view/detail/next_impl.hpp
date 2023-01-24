/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07162005_1029)
#define FUSION_NEXT_IMPL_07162005_1029

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    template<typename First, typename F>
    struct transform_view_iterator;

    template <typename First1, typename First2, typename F>
    struct transform_view_iterator2;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        // Unary Version
        template <>
        struct next_impl<transform_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename result_of::next<first_type>::type next_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator<next_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::next(i.first), i.f);
                }
            };
        };

        // Binary Version
        template <>
        struct next_impl<transform_view_iterator2_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first1_type first1_type;
                typedef typename Iterator::first2_type first2_type;
                typedef typename result_of::next<first1_type>::type next1_type;
                typedef typename result_of::next<first2_type>::type next2_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator2<next1_type, next2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::next(i.first1), fusion::next(i.first2), i.f);
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
LVNzZNXA2MP3BR6ZXuc1eRXTRd/T31grciCi8jxcsyae9QpmQ5BfdEdxbo+6pJ3gQ+60H2gE+8/4p3Av4kkz5cYzXveLf9DFyZIy6GyMYT4Pzib6GR+pD2Z1zYowQM5c5SPubHUr1uiO54VFzXgVPDewCGTFiQ5yvHennCUVtSluYX5B9EEtf82ZY+a5cL7gjWFenNeDIwXbx1MWcfan0HeEl2Z9Ck/frvMPj04uH5FYEed8ulF3gbja/sYYniRaBT2aMA1xDvP1KkUVi95QKa+P7tQiXH8zXxo92I0kveazwbiag4jcg7nbsEdnfauQJiRbYqZxbNy5Xq1YkBwMv+F5i3UUYbwAPtcibxb+HLRSd1mvlw6agw68Pso455eVR/6UmL2VR9TpbFJvKC7Piy/XKwuxhZHkrlu7/xJ9QJ8XO8LdyvMbXfJpyGJ2igdP+7aF8XBdGLO4ySKhPzad0fx5scqemgJ6+MRzmVV5Ck8fomsPT5x5le1lvV0Zk1b5zv2w573O3xjmkKQXx1PPmDxaXfQpSEN4a0EErEc+2zExWgW+IJi2a52mKZ2dXL+Ad8A+g5hxV49ZnG/6CbS355KsQRfIerG/XZCh7ZNf4Kc0/mo6fEx3h1RJS86KmMgn5v4GyKEqqECQ76xjkH9wzk8hX2q8Cv1/aL8phst9IwYHZwNitVeUz51fpGObw98w58Og3Ol60S/4922c
*/