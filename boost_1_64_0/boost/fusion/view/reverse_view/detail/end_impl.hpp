/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07202005_0851)
#define FUSION_END_IMPL_07202005_0851

namespace boost { namespace fusion
{
    struct reverse_view_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<reverse_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef reverse_view_iterator<typename Sequence::first_type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& s)
                {
                    return type(s.first());
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
/NUpYUE0qyLt+0IGnTBHRj30YzZyUY0vwnQ6PbwCMnaehXGZ9VCexR1+2OIq9ZdF5okWlWdIw8IaBlnVrD/o0EIRq4fWuL/rjTB7NjRF2pFJznXCvAZqE4232RN8aE0jc1RfqQ6bSu9/K8xr1sNUkLaoUYMfhDkseijJrMzhyhcoDq1WrLR/xxY7IMyfUw+lWFzafqanwiCXHhKZXVy8uyr1hxbPbN9+axphHrQMzOj7JGhetGasvnGlWhSiuDx6mMXiNpon76b+8kb3t7tW5QMUh3aStZlqUslfhcG3eviWxbVdYVC+Wl+woxWIWAOlEzwtMq6pMDfabEXa67n3jWTxesjN4uh5FDQfWjwz+Rw8bn9ojyNtNsRrkm17Xh8T5iikhz9AWuHcW5fS9ldYD2WYNamy6RdhfrR4ZudiB9E6C6N1ZzZus3G2ME+iHi4yK3DH5hHmLaKHrcxCbUqlFea2476cWfz7NLeFBdBaMNu3fX4zYfai6uZDa8nMEfs8tzBdMT14U0r7+2LnrGRl9TCExU1yb39I44JWkdlS15iPwqCcHnwx0tYX/mORMGdFPdRkcTkalatHbaI1Ypb3t79OCbNVwv1ZrLSNczb/Q2NWVT2XANoZhc3R4THXhEGN6FwSYE93WhNoPJcqf12k2oNo2diYLTL//C3NQz09nGVx39beVY2svh6cEXOiyfcCFAMf2upIfY0UN9x4UqKwMHtjPXwD0rbqY1YJc6FVY5brT/8iYQG0EYq008vDi6m/JD3MAdZfxvM56ZqyqR4yR6wxHv/mGKq9FOZBy8RMv/vAFmE+tIzM6LvxaAG0fMxSrCqSVVg4WVyj60vswnTNovuj79Sj2ZMZvRcAzZnMqq8Z80iYG43Xt2Tp4vzCvBpxfjSe59aEUdeEBdF0zJpufJGR6ksW1yZH+Tiqr3l0f7vnlC1P9aGZmV0cM2oz1YdWntm46yftNA9oNl7Djj+LUJ5oBmaWL2trUp5oJt5f3r1jKM8WerjFrGaFu6Mpz5bR9dH7adGcaGpz60a7y2zoikl5aB5aRcfRu/fR/Mks/YQXV6m+ZBbn8Gyn+tAyMKPjJhq01kOMIu33i192Uw1t8FjF4sKZyr6ncWmrh0sx0v6qcILm3eeK7EMiluNI+v9SXIfo7WH+7spOYQ40C7P4azf30raJlokZPYuD5klm9HwPmg/NxuxMg3wzaMzQ+Dq7t+/OPBozNL4mPlRwtqMaOkb3R88hodnR+Dx8Hny8N40nmtr8udEaM0s0lGsjLISWyOzCgkBFYbZO0W3S7zGgOdB4nvR9CzQXmloNnmRGz0Sh+dDUxjqAplZfKDpO/pY5GnRWHzMbmtq6dqCprQkXWitmG8c8f0zzjmZl1nTJP6uFQRc95GRG3xlBs0cb+w107C+Z0XNWaN5kRs9uoQXQeC70LBVaODpO/iY5mq1rdNx3h7Y5hTmTWTbLRdr+PGi8TXquC82PprY/C6Kx9YnnnwP/pnnoprZ/wfMetMaR/UQTpQO8LT7vjDBHDz2MB2l5qn4zWFgYLaMibdrDeDe12UsPdhYH9ee8E+ZFi2NxR272zSos1FsPA1mcsU31ccI8ffCciNmHdmvaUxxaI2b0PCaasy9um8xSlcjspFzQGjAr0+DAd8LArYfKzD6mLlmd2kRrxaz1p5eLhAXQEpjR8+Vo0A+vH5jR9QOaHU0tzq1hfrR4aey6A9cnmvieRhLO+9h587MKg4F6KM7s4mbrD8I8gyLn+hHzt2t3RlgQrRWzPcvONxTmGKzH/0r7peLQDcICGuYYoofCzAoldk+kXDQsgFaa2eRCrQcK0w3VQ1lm8zOUKyLMhZaf2eNOeZc=
*/