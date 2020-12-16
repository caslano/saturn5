/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_PRIOR_IMPL_SEP_24_2009_0142PM)
#define BOOST_FUSION_NVIEW_PRIOR_IMPL_SEP_24_2009_0142PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct prior_impl;

        template <>
        struct prior_impl<nview_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef nview_iterator<sequence_type,
                    typename result_of::prior<first_type>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.seq);
                }
            };
        };
    }

}}

#endif

/* prior_impl.hpp
39e+07SoVXkZ/mKVC3eT/01gA4sHGQIz3mIQ2PzLv6AtFYa+pFG2JIAmLWaNBJmR5fEjPEXeWUGZr47a38woFH18TjP6OTl7brFW9flx5LNokvcC4UhjVRtZ09a/y9P1dQpiVPUBl6et3OXW+ekIfTRQrZshb1jmq23d3DnGWhMd009na0edHmn/z/ZidIOxiA2RdqRi0NZnrE3bGYy2Bn1+4l5pk3qs0hxfiqJvHqMvoHvi9kqfzKOVZvoeiqLvTEbfDL1e2yt90o5YDNRlfpu2sxht5+srs/ZKm9Tl3aDvlIBN39mMvgv1+IS90idliW+er0GbrvmMrov1+Y690iV1mdes1Xxqs62cfg6j7xJ9j1f7W/ruwp9ejnE+P34Tjl4AfR8t+l6DuJh32Z/V4O443ifu7jiI3k//jB4YrbfG2NPbPYXiPvRO/G4JZvx9YukPr4gYUCuwYbv+GbYRYZcmmTCD5apXsgaIeBnS/UgUbOqUxzsJ+9FBg9sTbNjMkT1/F59L1+C5ZBtWccSu1SasCjY6NJEXGQdOmLviEnqn07U2X4PVVN8/Hin2n1yw3YIFe2vwbZINe2Tr5UETVutaOkgT+3MkyW3uz0kuCKskmKF7XfNvCFq0FJdqUEGwRKSlfM20URZs6T/CApCGm/4tBEuCIGQUL8i0YMWDNbgtCvZAz85fWzAYosHAKNi0708X7yxH2DeaDRtd4U+wYGuHajBat2HH/d5zvQVbeoQGA6JgBy0oJXxxEDxKg/MIXzLo0Lv32h4WzDFcgxVRsNG93T0tGIzQ4Pwo2HcD1o6zYCsRdnMULOuylA0WbN5I5CHBhr31+8SLTJgOO8ZpkEr8pRhzOr6suwUbNkGDx8GGHT7/i4tNmAbFx2rwA8HaI46fRnWYZ8Gml9PnCDZg7S3LrXeWT9SgkOSSaszFq4aVWjCo0KAAbNj95y/aZcGKETYj3oa9vvGsdAu29gQNSsTnzJ5d4p0nanBOFKzXpMLnLdhKhE2MgsGyT/tZMMc0Dfok2LDyswduEnt+lwa9SGZGaebrnVsOFrbArcFSsGEHx71yqjhnQVhC1Oc2vK5tE7bAyz836t3AGBPWF9KqNbiYYB2hCf7wdzzbgm2sJt4J9utnk38Un6vBP6Nge34ZudCCldf88+cuaQW2EWFnRMF++KTsSAsWrNUgPwp28md56yzYUoR5o2AnfTWrnQVz+Di+Ee+cnG/BprcCW+r7Z/62tvI5xymt4OMwjo/BuFy2chjHV6dBkmbDHtk591Ehs3oNXo363KBn5m60YPMayEYS7KWCGQELBn5cA6Jg3cYsGmjBdiDssyjYrMcP1YROBDXYEAXzz5vxhoDN0ODMKNiYl8cXW7C1Mzidve49+hqhEyEN5kTx1390ZaoFWxnRoC4KVjXl5t2Cvya0FboNe+K7OTUCNpvju65n5lyhn6dqcEDU5/rM6fCHBSueqzXvuWYml2hac95JysVJ8Jgr2WhtuECHC6uToLnhL9JM/zXH/gc175U95+7Lmo+rtoih10rdv1HKmssbNn4q3VVuOTlxsQgA9ubbAPj0OVY/SKUyqJZ08zIWAUBrvhh9+3phO8qDVtEnVpAYCEkqDhaLQciA+4cg/EOAGn0ezQXDxiWqkoHXLVkPDARcD7gfDMIPBqjWy2n/tjxRQX6sRaKvRrIaGAi4DLhPH33m5hV5FdtAoR40+MKSjaLAsLe9C4BHv8TKw1BpEwOybWKghU3kezQQ+zAAt15Me/SHVeSKWyTODMmqohmNgekB32+C2G8CVOlLyB6MQuFkSZdB2F/idJm1qCRdkOEouC7w/SyI/SyASx/ajuL2+MxUJAdPP18=
*/