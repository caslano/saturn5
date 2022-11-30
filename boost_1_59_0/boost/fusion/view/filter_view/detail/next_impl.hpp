/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_06052005_0900)
#define FUSION_NEXT_IMPL_06052005_0900

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;

    template <typename Category,  typename First, typename Last, typename Pred>
    struct filter_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<filter_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::last_type last_type;
                typedef typename Iterator::pred_type pred_type;
                typedef typename Iterator::category category;

                typedef typename
                    mpl::eval_if<
                        result_of::equal_to<first_type, last_type>
                      , mpl::identity<last_type>
                      , result_of::next<first_type>
                    >::type
                next_type;

                typedef filter_iterator<category, next_type, last_type, pred_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::next(i.first));
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
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
*/