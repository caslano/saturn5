/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_31122005_1508)
#define BOOST_FUSION_SIZE_IMPL_31122005_1508

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/size.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct size_impl;

        template <>
        struct size_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply : mpl::size<Sequence> {};
        };
    }
}}

#endif

/* size_impl.hpp
YDTbnPAMjpccz+EnJeI1fERG8dSc1nCIZHkGF0vgJVzVZf/zOp7/Wmsa3y9+SXbyGu57vucxHj9eKeviOkbd9gbPYr+s5UXcc659GV8LZ/a0hiKv4KhebXge31Vwj7yB2XnWmufxrVLnZfyuHHS2NliY3xpaeX5Ba3iTjOIVHLPIvMWOQxbri2fwu5Lj4XWt4TkylUf4TinwCt4ii3gNf3yBcfLMha3hRFnKc9gpJV7Az8oKXseHpcxjpl/vOeUxD5ObeRbPky085htlO495mTRNNQb8kQznudvsbYl4/iet4f2yLd7b+DVZE68pNqTGw1brL8P0OXgMHoPH4DF4DB6Dx+AxeAweg8fgMXgMHoPH4DF4DB6Dx+AxeAweg8fgMXgMHoPH4DF4PHn8emsmRsgknJBwasJCwjcnXJHwlT9Fx4iEwxM+LeHwpN3WhN9O+MWEH8P/xtGXjG9JwisTVhP+OOGMhOFn/5lxfnub6zh+HjMeV8Ld7kHHSxKekHBqwo6Y8X0lLCZ8a8JVCdcm/GbCLQkbCZ/+c3Q8P+FxCacm7E5YTLgqYSXhjQmv3YaO9feg453b0HFhzHheE05IWPwZOlYkrCSsxozHm3BLwl8kfCThc+5GxwsTHp3wxIRtCfMJF8SM5yfhqoSfSViNGV834Q9jxtdN2LQNHamE6YRHbvvP7JN/9TErmceTE2b+zft96r36d2RjxuuVcETMeD4TDk/4zIRNCX/7c3Q0Ev7s5//e8f75sZs4ikMS7p1wIGF/wj0T7p7w6Qkf+UmynxLWE/aKo3hMwpEJ9004NGFTwn0SPjvhcxM+J2Eq4f4JCwn3Szgs4dMShv/y8dZkfd+dsJzwYwnXJfxiwpsTfjvhloQ/S/jLhLvQ4X/Xio5UwuclTCcckfDohNmEkxO+OmFHwp6ECxIWY8b3kfCdCVclXJNwbcJ1MeP7Sfi1hN9NWE/485jx/STclbDpPnRECY9LeELCkxO2xYzHm3BRwjcmXJZwecIrE34y4bUJb0y4KWY8zoT1hL9IuCtmPN+/QMezEo6IGc9vwmzCyQm7E749ZrzuCb+S8IcJtyfc7X50DE04POEL7//Pvg/+3UfhR5knfOjWTMh8JxOy33+y1vZTXlO/88laq3d4Qy37wydrA2phcybc/EftbvfuXHprJlT+qN0iz0shbld/snbk/dp9NzP48+Pgz4+DPz8O/vw4+PPjP3EM/vz47zkGf34c/Plx8OfHpx4fDrM7B9o7Ovq6emb1hjVhVl9n5xMfw9XxV3va53bGH8PZU46cftSRh3d0d5unMK6zr3N2V/9AZ9/4BZ09A1N65/fN7Awf323yU6tnh3C9eqG3b+DRqs8bwti+xYWBMTPnze/q6xzb2zPQuSiu36muPrmzu7O9//F6uFVV9aTOnsntPR29c0P4qorKuM7+gb7exad0Lg5bVFSmdA5MaO+fk2vva58bvvv4eQO5vt4Famrfe6J2Zn9nX3zmt1RUxi+KBxgXwsbHe58ZI4SbfCZj+zrbBzrj7sNX/uT6cSmErckIumb3xAV3882k5575c+MBdHV09vWfHcaMO2tMbuLjM3lOGNvZN3B6obNnykBvX2d4Vog/j+3u7e9UUAgjQlyJO4nZNatrplH0T0zavzzE1RO7ejr+6KuPfzEcEuLquPmF7kfrTzZ5Ym6zj51v3f/CF8OJQTWerKd+0R0VFBeHsZPPybUlt/P+IY9N9szO/v6zu6zVwikD7QNdvT1h45Bkyk+f8drOmQMT7ai+uY9+6ewwa7dTtW+f3XlC76Kzw5lTxk9+fHY+EFxtwaM3OKOzr623bY416Ahh9eN1BYW23ke/HsLFe0w=
*/