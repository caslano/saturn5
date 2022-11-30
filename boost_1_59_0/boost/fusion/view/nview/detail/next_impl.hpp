/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_NEXT_IMPL_SEP_24_2009_0116PM)
#define BOOST_FUSION_NVIEW_NEXT_IMPL_SEP_24_2009_0116PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<nview_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef nview_iterator<sequence_type,
                    typename result_of::next<first_type>::type> type;

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

/* next_impl.hpp
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
*/