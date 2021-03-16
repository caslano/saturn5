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
8lIFzd1iaeRtaACeoUz3NRpCKRSaoswwB+eUKiiEn4mFMzRV3S2FBFsjWKNg9wn2W8GeEexVZdajd0sIBgrk/TFAZkYc+h+595jci6XsRiG06OVY/M7xQy7cs5Gb0GX8wuLdDkivS9Jl0HbXxLEWjvcHUMIeVnwHMkDGXtmEWSp+LbaQxkvj6Pqwuhy6iZ4QOtiHR1w45sMuwvvDxSj81Y3lH2Jf9omNzrJU0r8kozNzjaWZYVUr2Zu8w3Mf1gM=
*/