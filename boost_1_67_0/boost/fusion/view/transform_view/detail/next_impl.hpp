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