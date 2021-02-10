/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_PRIOR_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_PRIOR_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/prior.hpp>

namespace boost { namespace fusion
{
    struct single_view_iterator_tag;

    template <typename Sequence, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct prior_impl;

        template <>
        struct prior_impl<single_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply 
            {
                typedef single_view_iterator<
                    typename Iterator::single_view_type,
                    typename mpl::prior<typename Iterator::position>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.view);
                }
            };
        };
    }

}}

#endif

/* prior_impl.hpp
DJKGTOJ/pwXIL4ADzEEqI7AaFMMKbt5hXbrkzBbdy1cXl+toEHdY+ZFJh8ONzsFqvSgQ0QhmwpEoxQNmvJVrWSaA8N8rlF9VhlOrDF1pot5DJf/DBPxny/F/rqLMMzm75XF8gW31UmBJWgT091JUn588IX7CcUggkFXyrn8DLXaeM4BSm6NWS80Pjy7IgXjx4tXz5/ATvSGvTo4uL4cXl9QiLhKpZwRFUnl/v0qPa3cYs8t+x2Vc3oyBUL8yfXAmwHwQYc0bdo3igTwfUF4p+1mav0c6RprG70AdWVrVLtmQf1P74J0kBJef4MSGHEE9J84E3AXoEeCFb3G0v3mL+RvNRKwptf58SptK2TKgAfVwGN2kIQ0lMgDQ/ahWe1JgYCfOImRlSgenbAIYYoKRZ5iHTkfFHQlCGC0SNXCjVTXKX/AJPtgWT7c2/0hU/X+JA0TSZl4V/tilJ8Pw9GfSv4lJILB0SMjoUn6MSGMVk5JtvAcCVCkFC5aCB1mpSJCrNFzoQxCPUot8oEiawbU+SCPAsiakGNjJ15WKyVNoBROXR787ukqNISf+BUXqNYXV4el6mSf6hXLPs5ECz0MKAO06gFnXOi1204sj/Y/C34jImMkBKF9GFP32QaGwvLJ6C62TwzDr1uMvUPZ1
*/