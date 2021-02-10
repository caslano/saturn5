/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_05062005_0903)
#define FUSION_BEGIN_IMPL_05062005_0903

namespace boost { namespace fusion
{
    struct filter_view_tag;

    template <typename Category, typename First, typename Last, typename Pred>
    struct filter_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<filter_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first_type first_type;
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::pred_type pred_type;
                typedef typename Sequence::category category;
                typedef filter_iterator<category, first_type, last_type, pred_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.first());
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
6/iRQ8KJMvbA7z9F0UzF7FFqMx5JqjWddU7enJ2evMECpednDQR6TVkl/Ji/ATkiHSOVbbq5iUCEH02ibPPleBJe5sEDygqEQUO93rEV0eoHTtw1aGJZcmn8arW4B3U/jaSE1RIw5JdTJgJSn6FCwSmmpV5GdaoVJMxMQMwmw8soiTIAcw0BKjJDDlJqHMp6W6beobg1aBLBZRkpOTg92NvbWZM123G/PpchIb4Vocs+1ec2dH9q6Mb2wx/zI+hobNX40vgJ1boaiWzBV4RiKB0vZk+KopHCgHQrpDgw0t1LTHh6GgBeIvwUZagGp+xI1Hknmc2BAmeXukK2rmCG9FvSz1B8aVzcbNWiKJpxDX4yb2LLue+dU8JWM4wRgV2+I6+0UortH0ZnczuSHr/wwv2XFJkie20WXp+xSV7lLZVOUUl3HCV2gD5qa9zAfJusS1wo77NVcKO2ut+++4aTzuEPjuqueAWFJpHzKp6iBuds+XMsBX963q94wS8IveAVndDOe+fsoNvvHBxXPXJqFHjPqnRQ/uh+Yd3qLso5+ax3uJwI2Rn2Ffb3K7kWSMfg3n3mGHnOca3LxsJFvcJU3kmkfVBFKtsUsUyomxn09Pd9VgZzPdxwPKbCCTysF8e8kctdtQrv3rPupcPE
*/