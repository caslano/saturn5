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
upwTE5PnrFurk3Ye46Bzmbhbpo1/8bQPdtIus7xw8P5CnfbUnnOmvSrThj3ifYkicM6R9gRP+/GdtLOwcnHuuC737n3nLvdLOmlXaYgDMI59jrR387Tf1Ukbp1uqCO+HqbSndm1uT5z3C4LXs9wSW09OObI94d8T4p4Vzrsb9px4cWarJkx94M878kO8fIRT+ekW8qe4/H8K+RXOOKZlFEE+UKZfflfnfB+6ET+vIB5jBWwT
*/