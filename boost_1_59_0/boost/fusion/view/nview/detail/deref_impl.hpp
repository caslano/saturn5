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
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
*/