/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_IMPL_09232005_1058)
#define FUSION_SIZE_IMPL_09232005_1058

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct filter_view_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<filter_view_tag>
        {
            template <typename Sequence>
            struct apply
                : result_of::distance<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>
            {};
        };
    }
}}

#endif



/* size_impl.hpp
Km7S4t3aewvlaRrUZzRaFytZh8px3RlPujNEujNIajOEmy1ctXArhDso3GHhEpF4e4/EX1dom4kt8bExJI67duMY+w6Je8H8sibypnXTC8h31bnanMRxHhhf4sYX8R2SOD4p4Igccx+vMfdoL5bjujue1KeJ1KdpU6eZmyVctXArhDssXINwiUi9g0fq2A9dEUfqE2JIHX+UbmHJ8jP2DldmNp6hpuO8+WfW9EZ3TW+Z1GeK1Gdqo4AyN1e4m4U=
*/