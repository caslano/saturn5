/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_IMPL_13122005_1906)
#define FUSION_ADVANCE_IMPL_13122005_1906

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>

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
        struct advance_impl;

        // Unary Version
        template<>
        struct advance_impl<transform_view_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename result_of::advance<first_type, Dist>::type advanced_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator<advanced_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(boost::fusion::advance<Dist>(i.first), i.f);
                }
            };
        };

        // Binary Version
        template<>
        struct advance_impl<transform_view_iterator2_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef typename Iterator::first1_type first1_type;
                typedef typename Iterator::first2_type first2_type;
                typedef typename result_of::advance<first1_type, Dist>::type advanced1_type;
                typedef typename result_of::advance<first2_type, Dist>::type advanced2_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator2<advanced1_type, advanced2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(
                        boost::fusion::advance<Dist>(i.first1)
                      , boost::fusion::advance<Dist>(i.first2), i.f);
                }
            };
        };
    }
}}

#endif

/* advance_impl.hpp
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
*/