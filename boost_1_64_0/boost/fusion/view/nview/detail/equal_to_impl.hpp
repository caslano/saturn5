/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_ITERATOR_SEP_24_2009_0329PM)
#define BOOST_FUSION_NVIEW_ITERATOR_SEP_24_2009_0329PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion 
{
    struct nview_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<nview_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
              : result_of::equal_to<typename It1::first_type, typename It2::first_type>
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
u675T0nn8FEI9jnP32/mt1MOa6JsGURqQ16XJyzxvCUawz7m+DfAw/+HDILNv0jaPbVAwmNrF+SKHu1/4MDUP0ZcbkLrYZhVJzlBQZ8NIlNelj9DwP3lRbmiBuCfrAZgHTh7mL8t7aSgRk0kjP9LzFDi77f5vyVXxJRAB9hVdx3V6DkFlmXQvikN5NfGNelzB/ySug/Z7+f5WY/mihi7pkfnpPhgnMpeM830yctIiXo9XxeR/wRaF3Xks+Cem56lqDpsJI7LExTUCW8mUJ53FPV6Hkd6MhdOIP7jkP87tvQgv6BGxA1WxinjP+SdgQdBPr+kbVILJNwWPpUrek/F69G9p6ohqSOtByp6q9hkNkZ89ZKOW1og4fHVF3JhAckiAWXR/ehHJ5lQL6yz+ter6KdBZIaDCvTCRsL9hNdzYQrNkXYoi2d/L37MhHrg/QMpszlbqSzknUBxHDxHQ88TdXIT9eg6uW6YR2vlkk5K5SB/fthI+LrROU/UL0vS8Tmyie5+VMGeA2jd7KxUFk3ekE/WxjIWC8/3PyQPRlD+UjI+x0z5+iiTWxfWcKM8NnW2wqSw0h2RdIM6Fgu/DzMoD1aSrUhBWQzOeKeWMrhgaSrpRaqCfXZkVqTSU2U+ZPkUHAWvLTA2T/iV7ZlfWQnjVOY6N/rwf3l+ZdTreQ/ocXlwMvGfivwn3LPBrOmHo+sPon1VhgI9aCZQnl8Z9XpuHyN58DTNgw7I/7TSweeb0JPE3ZclSQpibiaBxj+WlrHAUXA5FJ+VJ3L6OqIcHlz0MYVZnLBYp/2lrmwe4FImVQji/SLPez5afeK/E/J5Ud6j35kcToNUledxjT5JMSbzxWzuYwBteHMvyuD0NPqORRRSZZ2dxmC9z1/Xd1bZoEpZF4QZili/Gb/773LN774zyuH49PBXJvREs+cO1Y+Ily2HmbWh+mAgUO+cGaysqg/Iijy3RMPlkXZXHtxAc2E/5L/y4m1Pm9ATRB3HlQkKzmSjCJV4WTYWC+/HtDoPfiVZdEFZzPs8TD7jVNjUkXxGFT1tjQ5BzqrZlR6fJA+BIeD68GIezKA1Mh1l0O2iajqGOB7WtKNeGyrq/lokyiuvwjCwmp6b8uAz2jvsj88bd/5GIpoCU+PobC5elR5E8OKipPWRv9/2kzfniTOIrsi/e9DblKNwHEwlHZiVqI5/jAdJ5R/fz2MKn+bBnVS78gDk/5WjnqP7wRWw2Oqd0F7B3tGkT2JLMoaA5279ZutAhqEDD++iHIXJ4OlCdkBFz3uDtuY/sPaupEWBoYiNOaY4RA5bJsqh7oPz603oJNi0H60OHVXNhWYi3Q2SLkIxFLH+YzcHfEVyyEI5PDTnyt0mdCLEk9+0UUVdW5tIj6SsFYaB7RvyHOJcMluPPpcshz60LuxWLAOvpKM5hiJ2TqAcrDhKDoujHAtTVfYzFkTKi6UwFLG1dhwOUQu+G8rh1af+oLz3CbApjeSQpNQ2eGdJt5EmChZX6ekQ9+dzUQ5z54zqa0LHQ3p/ymnMVbpW1DfKFgNhEH5zuQPmJpoyyEMZ/L7rHepfOQ5GEdfTVdwHsilE8mQLwUTB7tCf6IDbaf/gMPaTpUfNN6FjodDq1afWRob6SQq6MxSxc8LpgGE0J/KR7/feD55uQsdAEtmGzSrqKQgiJbvRNgp+ll/jEOdz3VEORe8sKDahowEsXzpRqT6EvdJtpImC6UODA4aTHApQDnceUzSebgQBdKI7xClK14pISNIpJUMRqw+zHbCC8t8Ne1C140XaUR4D79NvxQlK9SEif800UbD83zMcsIT0oQfK4cixL1I/naOhvgN5lSlK18ym/rLFQBjEGe15Dng=
*/