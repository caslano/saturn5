/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_05042005_1058)
#define FUSION_NEXT_IMPL_05042005_1058

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_iterator.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;
    template <typename Vector, int N>
    struct vector_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef vector_iterator<vector, index::value+1> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.vec);
                }
            };
        };
    }
}}

#endif

/* next_impl.hpp
LO2H/jHsN2EmphK5xBKimGi6yWhDNCZjMiZj+i2m36L+3ze67q7/P9jOpI5rj63qC+V3RBdsjd/zIrcrv9uk/u/y6P9qxwHW7Tg1tX508XFqDZ3rPaU6402ja/A8f4exbDLmVL1vvow7c6/39NbmSQOPY9ZC/4ue5R9UoKQfeGbSM826bzIP9jpVXv/0lkNyjz0v+XzI56YYw4kih2f5d8G2GIYBOAADcRx2RAt2wqXYGddhEDaXcTLBGIwPYlfcgyF4GLvhKeyOP2IPXCD98WuxJ/rIeJoQDMOrsTdmYDgWYh9cgWa8BSNwA0biTozCpzAa4+SZ/1djX3wL++FHGIs/YH9sK/3woTgQt2EcPomDMKoh9Qocg/GYiVfiAhyC63Ao7sRh+DQOx2dxJDaivBOwNY5C9q3Gz2QLM34XGpMxGZMxGZMxGZMxGZMx/eLpN6r/W9LrqP6/n/rrYKn/T5X6f7jU/3viOV7Em6T+L9e1OzUC/AZtAMq8q3WusSzWucayROe661KddoLtOu0EZTrtBLEu7QRhOu0EcS7tBKE1aCeIrmE7gVmnnUBtr5Hrd0+3on4qnlfeL1+398vpus2D1YzZKHMZs+HfyXlMxumOzn8fdvm7rKM2ZuP7Drx2GXfxpqQ5jrvYLmmO4y4WS5rjuIsJkuY47sKspsWo4wEaaWmxap9+ezVNHQ9gbe0+FmOklqZuo31r97EY37RyH4vxmpambmNLK/exGHO0NHXMQaKWFq2WSzP38RmLtTR1G+O0NHUbvbU0dRuNtLRotVz83MdnPOHnPj5jnZamltXBpu7jM+5u6j4+I0dLU/djlJam7kdnLU3djzNN3MdnHNDS1P0o1dLYDxkvoXPcqdA57lR6GLNx0sPx6LTO8ei8zvGIDLkdj3y83I9H/l7u4zpKcbu/87iOeMd8Ohx/gms5hkM7rmW5Xctbs+ORNl4jTGe8RrTOeI1VzZ3Ha0wJ0BuvUfv2z9qO79AfT1H7dlT98SCexn3U3TgL/fEjtW/XHVugpL/x8oVQr+bfxm0OPv3d6Ar/Y1XtunLel98DmV7O7bptpV23HYZhexyAnXAcdkYLBuFS7ILrMBibSzvundgNH8TuuAd74LsYil9gT7yAvTBArqO6A3tjC2m/DUczjscIzMVIXIZRuAGjcSPG4F3YF5/Efvg8xuIIabd9DQficYzDL3EQXibjQILwCozAK/FqHIKv4lAcKe21aTgCi3Ak3ooJWIqjsBxH4+t4Fb6FV2MHyvsa7Ilj5Pq10npyXpfzfCYvruX1RvnNNlHGz0zG63EKTsXpOAPTMBstuBrT0Y91ZOBtOANLMRMfxSx8Fm/EN3AmVmI21mObs3AX5ZaDh3A2foy5+BPOkevU8nA7zsPHsBCfwvm4Hxfga7gQj2ARvoc3YSUuwnO4GPMb2q9/PI1LcRblsww/x+V4tQ/HCLTgKrwZV+NeXIMdfbneEYNxLcbiOnwG1+MQxq1swJFYjIn4B5yIt+GNeDsuxI24Du/AR/FOvIFxLX/EQtyEi3EzrsItuBHvwbuxFO/He/FhvA/L8H58CbfiUD+ub8RyfAAHNeP6RtyLO7Ar16s9jANwJ07AR/BOfBS/w8fwJyzDVv5cp4934S7s1Jzr87EfPoFJ+CRWtuD6fPwe9+DPuBc7tOS6fCzBfdi6Fdfl43h8FpO8TBcbryNjeoxxOzUZt5NI/4zV6KP5r5t+/fr/9LS6HP//vMP4/031ZSc4vnQRz/Ki/J9+Ji/p/9duAVR9vb+qPlh6geUd/l7C31X1w6a8dq1TnPrBz61OcYg01zrFTtJc6xQbSHOtU8wmzbVOMYY01zpFH9Jc6xQdz6o=
*/