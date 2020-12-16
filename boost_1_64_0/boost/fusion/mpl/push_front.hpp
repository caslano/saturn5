/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_FRONT_10022005_1720)
#define FUSION_PUSH_FRONT_10022005_1720

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/push_front.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct push_front_impl;

    template <>
    struct push_front_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename T>
        struct apply
        {
            typedef typename
                fusion::result_of::push_front<Sequence, T>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* push_front.hpp
zzq44jEScIXCO+pc30mPDbL7QQ0c3Q8wvwo8nfcuMOgv9y86l00Y3as0X10sT/uwrkh3V+Py3Phu+lv/xtkVsWf/fA5fnI2O9K/wfqDznZf83tsQv0+8wcl5jyPlhUqtWq3wWKN/bxzqDPF4EPbavENz/BafIcr5Lo37bT7Ad1O4z2AIW+ltrqzOUDp6C3ds2t1R7Oa86AnDHPNGWbx1R2Re/u0pHvmOQ+lthXlID/pxgwOK5+/3bUHHbmjxBu0IXB7kuuhz79B5sTzMqd0okA7FsIeCs2vSgbxd+LLemcWhWz7F+L6dyg/GvPCbjd6l0/Iy8z0o7w7gboemSGMvlY9fpvM+gBtr3Gm0wzFu3MTicRacx2Zajs6UuqM2/x6N+zproX3em8ZREORR62s5Yntd2GsbGucjC+zbqp3RHLd1lHjrBPHdxR8QHP9aXHcNGwuG6Jc3FTx3Z0dc6AF8eTfTuPN5rbeW+y21tZfaATa75vs3/thG2gnhka3GZxuzOQ2q7wHa9CNBnqvPBtIKczbck6Gy7Sc+Kniu2fybcBhfzjIuiu6bj9PZkvVFOub1lM9Qvu86CkeLiFjPWHOMbbfjZQXO9QNO7hNpDuqG7UzBie88jUcK9O33sxyJnMlCHOX5gOIM47pbdeee2c+jOf4aJD77vJvCfb86hfHhg4z7uoA/AGm8wa0JeaHsz6PzOdwU7t+/B775xhTe2lD4Tgr3AgDPvSmFO5taxDd2UvnLeXqU+jZ9T+5uGh9Q2rJsb7Y4hRlZF/5+LeCLdM7k0NJiybtDwWmevrbl+DufcSYN6RhO4uUdIIb1j2yu9/KC2/znvtyh9OvXVq2cvq34TGqAgzvgcb7O5hm1WWy58Z2Ymbzu8ftTl1Bj7r8tl+9jF7aMlU/dAzq2eGK7nUPsIpSXOy6Rkn/nfPkwT8gPu+BDyDe6gqa4BL/bcYyTHzYcdS9r3uLxPkXM9YyT2xH9GL4ijat3QmsaU/tttzeAkUWHaIeSfW/Nclz6wG0aKo/8GYXPlRaPJDdGHcc6LchxqTCn8EBwvPXpVvFnKBjX4rzy+RQnOkwTzc4YswzHUcQdpxeTuN9APNigxdJxvvf64ppDo+JprHVV+jpQhXXTEzTHvdQNXbi7LCeulTuL/dNnNU69eIC2VlhcyejfGnM9jMaJOOKO+fpciAOHOt+/ftDyeHpnXj7AW10eDNPrkEKAt04JpnlNy+OwrbwLzfBohXG0erfSjLiT59r5NIdy5Pdeego3gTnItKN4Jig3xNh+nRTPBuQGKGeY62cfXtdvGR6CcXy3ra4LviJStueU4XAzUX5YByr9gOfJr9uZl7fpcXMSD3Oj4tlDhnKc7RkuAi9t9D3dd04Nh73GuvPqS5tCl6EzlHej6H69tjxcOSXfit7V39IAxfZY7mvXEhjOhHZhr3xT4VihoG51+dxsIxuhhX0dlicrt8Vv2aV49mDyAP3vFpoLHYn3p3bBM2mq9u9CL016aKtl7Kdb0Bxqd/Z71A0Wmb8YA2+p8W5/yPa5wnDYGHhPlwEHjuFTeBxwXCTn7WLE7UcPzxtOlk3X3LTctE2HOS6Qd9pO2wxxvJ2GfVuPsHm6HoOhRu5JC3IR0FuGnfbIMM+bRDx/BeSTdtpOAPd22v0Rdw7lNQjLPwpyrfz5R4V4Vv7eO7AukPbQELr3TuDG1tm6IfKoVKt3W6pRC3t/FMqWv1GAc4JWZ+1+MmYM0I4hru+ZflLmPnzjAHewkdirHdjRhueCT2zvjT93LY3HF+UB790k/b225XofTX/vlrVkx4i7dfdMGhSFlm+D3DSFxwrS4nft0vjg1MawRYe8xBrkNtCzyJNDbw8=
*/