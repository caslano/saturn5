/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_END_IMPL_SEP_24_2009_0140PM)
#define BOOST_FUSION_NVIEW_END_IMPL_SEP_24_2009_0140PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        // Unary Version
        template <>
        struct end_impl<nview_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::index_type index_type;

                typedef nview_iterator<Sequence,
                    typename result_of::end<index_type>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& s)
                {
                    return type(s);
                }
            };
        };
    }

}}

#endif



/* end_impl.hpp
xLl9lis3RW6McBfLB74vq7LBu/7RX31SdcxUDgiT7nxiEgHxg4fTLIcqg9cJUDeV25clEBn2SlKOqyn466B0HenYRMK4wSflwSIVhPzh5lnvl1uXL3BtDjCK0CRAiSNbaZDag3xoLO6MoqQNLGUi/ZljTW2QXBUhYqLRx5QUy4RQLjjbym/TIqyWLJSmjNWB/04kTBqkNgka6v+EUMyHVOsEpCYiE0+/opKaILU6T15f4EAOXifZda4kJBPidYSGpCsZD2HC4FjCGVcJ5HSmCZKlA0/498UgGPRj6DAkAqGt4vNDJ+DnfxP2aY7I+zOCN+HfX/rkQUmaPiEI485Iv9xqfTFjNeHyMoscMg6JRIOw2GPjB3nbYzrUD4oC/xu/DAuC9X2TB4t7nmwuNSDhLO2LmH3UkL7Kg13cmdSXW+38++IQsJ9Kc+XFwpzbp7n2v/TAfU+bjWYXWn8pcoip14r4ZD/wcP9QfDhhsJW4pSDPrcXHpOm6U6+6iW93KWEvoDu+N/iEJau+aquIZO+OGKn5UmRH570Kbi4hND1wWsQ7Wz+k/06hfbZUPIhB5s7N34NYIm3FzC93BS/DO4is7ImT3t2bg7jp2s3zCpaGZ9aEOh6MxLEJCsMjLcWTHPwsZZO6tzER1UMQWLubMzYGzMwbo9nXyywAZBCjoYL5E2dZa7+ixy2o8vw5PQ+b2ppifgpq+TP9iArJmi+F
*/