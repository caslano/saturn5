/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PREV_IMPL_13122005_2110)
#define FUSION_PREV_IMPL_13122005_2110

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/prior.hpp>

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
        template<typename Tag>
        struct prior_impl;

        // Unary Version
        template<>
        struct prior_impl<transform_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename result_of::prior<first_type>::type prior_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator<prior_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::prior(i.first), i.f);
                }
            };
        };

        // Binary Version
        template<>
        struct prior_impl<transform_view_iterator2_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename Iterator::first1_type first1_type;
                typedef typename Iterator::first2_type first2_type;
                typedef typename result_of::prior<first1_type>::type prior1_type;
                typedef typename result_of::prior<first2_type>::type prior2_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator2<prior1_type, prior2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::prior(i.first1), fusion::prior(i.first2), i.f);
                }
            };
        };
    }
}}

#endif

/* prior_impl.hpp
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
*/