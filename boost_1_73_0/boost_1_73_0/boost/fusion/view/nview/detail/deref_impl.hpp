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
CetljbFQLpCdwRzgqfYBgGXQ1nThmymwK7xgiHuVe0tqqXSupnCkAmUhLPzbXi8pXY7oe6lNfC/ZpN/NQrHN5BpBFGpNdhEoWCo9RySaERU21TO5gxAIF+U01z6L7qOBK5P2rCPPeS5YsNPs67CZxg09kajRAhHrIDdvjRdXq8wWjxTBo6DMSmfgCDxAKbWgOaLSpOwq5SrzjYuG04rg/yzNfbwpWYNgaGcwptF4h6bKax/RZHT5y9nVJU0GFxeD08trOvuZBqfXAvbr6PQEpddw5ohvF449nDvSxSLXnDY+v93Va7V2tUnyMmXakerFnkO56GY7Dw6O5KCubfbua/2CC+vWjw12IEx5Ws4rsQ8q6ISSTDna+8DhvVm2E9QkNKKlcloaqdP6DIgZ2nmmDafteDI6fXkQT4bvMcF3W/Hw6uKjHJ2cTcbx4Py80yJqL61OOxugPiQOaThDp1cfP/Zbu5w/wK1gxarXFA896GmiTWpXngbnI4yRD6xSqfqQXGmCLpjmjGFdtjvSJXiu+gEC7awp2IRWtRA2IZAHF/i1MESWZg4PaA/zXIZ6pdaeltprUQSaIOUqoNO6tPvq8PAVoS7UsDMtZ3Tc5LGRhWIhLyeTs4sTgoLXf/O9wCUweFFpVyzX0kLdQvzy
*/