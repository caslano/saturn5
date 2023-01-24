/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_BACK_07162005_0235)
#define FUSION_PUSH_BACK_07162005_0235

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/view/joint_view/joint_view.hpp>
#include <boost/fusion/view/single_view/single_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct push_back
        {
            typedef fusion::single_view<typename detail::as_fusion_element<T>::type> single_view;
            typedef joint_view<Sequence, single_view const> type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::push_back<Sequence const, T>
        >::type
    push_back(Sequence const& seq, T const& x)
    {
        typedef typename result_of::push_back<Sequence const, T> push_back;
        typedef typename push_back::single_view single_view; 
        typedef typename push_back::type result; 
        single_view x_(x);
        return result(seq, x_);
    }
}}

#endif


/* push_back.hpp
dJiyJbk6XlffPaHBS+GWZMat3rYknxSLleTdYqTDZcVea9MNP+Fzn/Xc+Ib7rKr/ap8VP96ffdb7t3h7qR9miZfaN8vLN3Me174L5T7TfrOP8jx8s6X4zUZanQPrMZoZFrzuV0VuW00Vi/F5Hr+KKJzCX6C2q7cXaD1Lk88Cazyi3MX4dfCBYwrguZRVjX2ECvgIFVj/5JFo9H1SPsIFC/8KptLLJOwPbtWc+1vHWyPRpP6PaQab/+jKzP7kwB7LPCua1JeYdpx7YWPtpMcjUSw3L2dPqgiNA2+bQFpsnnoHJnvfUAUNuY8gIwiOEYMpWgSfYZ4CFnbnKuVOBPjjfpHacuw6wthGvvcMr/NvJjVDAeO4MVzNYBFCVNVMLX3r6mc++7NP+l74cEP6Xo30nQP0PcrqjBrzNiMGc9HDAHQTBQ3DH/aHnI/e5KGWJoIcNVOQc+BMd7oQsH/1k0/YfxrnDfYHAfYxlorBuKwfkn9dHGHQcZhF4/yBvq1X6AfOENCnzyBZVcNHde9w8Uf3Oal7h+vHeatfOnMjvUsfa/GNBvRPHusPzI/Ge4N50XRveB76o088Tx7bGJ7v53ieusgNz4l+wfxFF28wn5ym7P+mIZ5nFXvB8/wffOL504caw7OFo3nmQ/6AHOAV5O7T9PWeHuAAnjmqAiiKiOprukc/5FbTPWnJSuRxr4sd4EISJ0QWg768bJASLXLu
*/