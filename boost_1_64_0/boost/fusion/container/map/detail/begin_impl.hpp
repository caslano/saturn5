/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_BEGIN_IMPL_02042013_0857)
#define BOOST_FUSION_MAP_BEGIN_IMPL_02042013_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map_iterator.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template<>
        struct begin_impl<map_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef map_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
SorrOPoBxwMhlYIZC5mfSqKlVyXusBS5b6vceqtyXawdNM7gjytXi52Wdm4Q/ZpTf7CAZUy/oJP0SYLMNj4MbHteh09LwzM+8UnY9zxU8fdoq1+SCCPfVNyJr1vZSb89xFq8ykmlfOt3F76ixdWsMjswZTBI+PNn0pvlTLn/Xu7iwJGRMMNcsBF1UCMFd1OQBZ/Q3ym2WvIM2iyVRtKGIrPRk7H7WKIcGROGXaiA6pxQ8USSWrLQ3TNNOJh6yz6Y5wF9tRRhjkV2vApCt46EVA7Vj0yQjimSc3q8cbyojMq0JSweo+OWUiphkwOU71PY6NiOngwJt1j1rhU6yR3CTOwysnRBtZHe2C8G/mnFwRfXdf94HZ5vZoaid99NkxB8zG4gOzd6pl2F8n67DigCZD6MECEihNYxmNwhsk994BXt8hTckVdlo9g6XugP44PLWc1de3LFfR5pZgQVxUjAT9dSl9GgIOv4RGoykwyAWpx2Mnv8MqR+btdTaSTRHdhfafpohnSLmv28QN7EOGeYsQnKHmDkQmOSlOk5/qWW2wVWtjsswvBVtwhARQ==
*/