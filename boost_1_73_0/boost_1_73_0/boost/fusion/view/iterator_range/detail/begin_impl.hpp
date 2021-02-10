/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_05062005_1226)
#define FUSION_BEGIN_IMPL_05062005_1226

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<iterator_range_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::begin_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return s.first;
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
ft1d9euGK3zXk7V6jAcKZdNyS8ehfGQpto9L1i84lA1wM4dx/F+idNuWQdVnbINxARykCLIQGEkpq/v6dkCQCLW6DmHdwn1Vsn53hoXtEddpDSCLQp7YI2LEcPDmaIGWYSqpBOrgDaS1aA5OXHnisKHPn0WpJHURNeww2bPryQ1IeyOTvlIOWGaPdwRDyRDkWiwyeEFGOiV1nOUUUHXL9+E39YJNpabAhIK4HcPpm7DiKavGGF5MBAMpYuqSTreUh5kv37Gl0eV03ivMD4dyBlBVJPyCLcPceATalSiH8R4Ga2IJRKy+DT4Q9g1hhFdPF8aSOWZlXc5gYZFFYuUynatKbDTaIP4ubq2jOZHlbkpUUM/Dc6hn6fMgajV0URQdezAuDRKvajhdrntlYCmCe76hg4jPPUCMZ1hW8Ym54xZQgUzbTs7RFqCs9DeCnEnkPeGlrzFUAXYV4m1wOcPhgIMdGgBN4EcQRBhEOUg49qJGEvPr39HmwM3mh8dcy0/LE/9SafLkXyZHBcYhvS4rc/rs1yC2n4wQhFm+/ohiXJh501KApaFSVyMDqVf/cZwlvooCo+A9LKgKfOoEsKJHMUTDi3d3LgDTUuRlKyPJbKmFvyk4xzncXVDPPtWoqpYTQq4A11lVaa3qXQyU
*/