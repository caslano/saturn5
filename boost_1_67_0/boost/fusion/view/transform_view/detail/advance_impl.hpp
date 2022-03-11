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