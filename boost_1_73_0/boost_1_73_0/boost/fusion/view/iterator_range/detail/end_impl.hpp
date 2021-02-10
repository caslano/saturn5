/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05062005_1226)
#define FUSION_END_IMPL_05062005_1226

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<iterator_range_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::end_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return s.last;
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
nQJejUsI3JbFRfRmW7lEK3AUj7COgq1hgmw8HgGplZFkhmNdEy4rYd1KAulekG63byp8SEiclH2iKoR439CtB4KjwlsDy05EC4r3H4APnlqty8W46hOaG2FjaCpA7GeQ9HKKkAQAtAG8ECIOJqOfSVklQIMKDzBd6HBLr+guBINLOiC1nmCJjj0O3DmfVvbFuja5+tC4yadBdnvxDDZaRORIoRIuqwdQgmV5k+XRxD8MblRLBBBAKgGIkw+YTAoLtmfN0kySYSbXSJE6it20YgrdkfwcWFPdwtAXEK2rH3NSW7iwcoGI8VsIN/V5Q/filz73qqE8S5fwUuPDsUOjiNM4Op7gTvGocUguPPZzjips++x8fuuXpl/oKaCx1ZJww8fjsLdXmvW6jrV9OZoRYA2lwCUUibGph5Hsde93uCMIXsGMdE3OziaZ5fpSFiLFfLA5unO2wxmc3MyXt708mWhZOo58XUPMzHJ5W9yA/S0wERez7IhKAhxdCILWdysr1Af2w3JcBuoN4jPCw3qRwenAej+GPog0lSiEGmdIPAfsNKeyC4RxDC8AKW46qaJsq9aWB7C/DwI7WYxu8+8Mx6Go1S3CKC767h6+bmenWhpz+fSi2KaWxOHNadzZkYFaZ5wO/lsfb5KjXnn2
*/