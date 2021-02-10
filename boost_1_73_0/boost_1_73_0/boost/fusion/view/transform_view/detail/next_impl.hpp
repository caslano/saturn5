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
CiPbQDvbkOhAhfSKBsHFrJjGykTtlTTIKg26Ogcj45ho4TkljRNbwrg0T5u2QYYSK0svRqeGWC0inWxsRDsSlbDIU2SEdsBNgUYzt6HAVMp5M2tesShtygbe65qVvAHoFIWBo94YBuMjmAqjTBt+HUzeju4m8Gvv9rY3nHyA0WvoDT8QsZ8Hw2t0vUJmOchPWS4NMs9BJVmsZFDy/Ho/3UbjWKV+XAQSjsh7npG2yDrR0dp6JEy0ucI7RRDkKg315iOrEjnHwI2OoIu2RdlpBT0behaQ32qnMMuUzuJSyMDV+6XvjfuTv75nxKr2fY8SfUxQpB8bxzJFQvWBYX+CJuw3jgsGPpWySJ6t0a5eQX8aNUvRIbFOZzUdFLAXx9oXGFoy1cUswuBLdL6kSIg05glnUxHHkIqE6KE+iaC0APRx4VtDsUaOk3OZLzF50lkHRuPXFxQI96lepEQql/8oVM6ZEkthLLx48e0zmC6tNC69pkUYypzolFsDtpyxGi08w4SLIdPGKE63WAkjmTEMbiAtEkQQQ/yE7+s8oANWEy1ElzmCxAncpeoTDKVd6PyeoHaWiyShfc+QBvqGFMKE68Cfz59/By8uXpbC/anBHiutWReN/nDijQd/78PL8/PzxubzyeB9H2Pbu+2P
*/