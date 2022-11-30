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
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
*/