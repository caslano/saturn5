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