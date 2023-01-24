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
PJYA+opwusEI9v7Mwa1mrzhHtj3K9lciFY9sfg9rCOlwer6xtRH+bGXhxROPc/51xSkjB5jPHB27AZ2MsRXfoC+MPCk1nJY5n87OZp0A/SOOEz8k0zLgKd0CCZupUOGqgRvSfTNRBuS5h8gPBx5Uv7fYvwd5D5EyU7UCHTC8GWVLPZ4rIz7JsRF6GjHqe0cxeZpdN5AvXeVRNPNp/4OT0w4xVmeL5IqpTS6vO/YxvFnaQl+pSoM87ls9/txrFF9DhIFbJozs2Gtms4/9v//CXVkV5BKzboLhmTiXNa+K2qTbghXNMpt6JvbgcL2QoM+CNicyay+wLFyHxCweXfHzXxMC6OuzhklL6vh4dNgJzT25hhziwU66yJk4xLAwXoMzSVjaPb40PV6asWU90rfca/SgNa4DZl3jkk202AyAJCPzmfLGd6wAZfQPDRBFkLXb+I+7FYsPsLY76vYvFnuj6Lm9zyKV6ibKN/9Y5M+jKz2657R3fZNBeH5mIXqjpLp2CzZ+xRL47rP25lX9zjALhjxjuNqFremxdq/qoUtmwBcdhQ8/tZt1erPHi+be4G/XFd5WT1mmCUjPLJXG6wuFS230vpA6zWFmBK5nBR5ILnGlz3PSxDlc5w5Sj8HXDi7X6oH0U8+DgLDvsDaxZMA8aT8w6oMP+0b+Ij8yKbhel/UAesAlKyTgXZfQ77CfiDEtGuSMcljb/T3YGmI/
*/