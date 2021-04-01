/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_DEREF_IMPL_SEP_24_2009_0818AM)
#define BOOST_FUSION_NVIEW_DEREF_IMPL_SEP_24_2009_0818AM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<nview_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef typename result_of::value_of<first_type>::type index;
                typedef typename result_of::at<
                    typename sequence_type::sequence_type, index>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return at<index>(i.seq.seq);
                }
            };
        };

    }

}}

#endif


/* deref_impl.hpp
nknsk6Y3Wu7Sd/nye9xZ92Oso7RQP9CNVPDkKbRxscBC0WrczjwPaEIlc5BNoYSXnzY/hQFE88MsDP6gVhx4UW0GWQ9dONFjjKkDatQzhwm/rbKToq2zQT4AT+umRPARmctTfYpFPF/Dwdq/5k6juf8xJGS1hhfSeUP+R81lxQXNronKJrIiLUy9wotx+K/XTWRVbzaEwjC46tSIprTDmLUuemMg9YwT5Jj/YvRXdlLcgsDbMb4Lf5zilHKKboUU0uFW2oxDFCgmQD7DYK5bQKkmDsWGvOCXfFavK2wVzJrHd2qk1WWuYUmwPOxYbfDnvhUyNQ6LvKETlM9ZyLYqIxE/Xjea0u4hlSm2ILxKW5oYg8O3r5GT4V50VctGcm5P0M05nulmEY75q0oBsWsBq9qO4Uk+h0rbhbxyE9Ye7OSeE6duyivfx6DGaESXzQhmVotsB25pWycciuvWaUmptYi2w5m04P7rTTc1pd4ptTyrCM+6qKT2hNdq4M+U8uKLDHlsnaHOeuiPdCtX7O9Lh5I403MaXjQ5aSuEdB0a5JKa9WBlKXZCpbLsRw==
*/