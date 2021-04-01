/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_AT_IMPL_SEP_24_2009_0225PM)
#define BOOST_FUSION_NVIEW_AT_IMPL_SEP_24_2009_0225PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template<>
        struct at_impl<nview_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename Sequence::sequence_type sequence_type;
                typedef typename Sequence::index_type index_type;

                typedef typename result_of::value_at<index_type, N>::type index;
                typedef typename result_of::at<sequence_type, index>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return fusion::at<index>(seq.seq);
                }
            };
        };
    }

}}

#endif

/* at_impl.hpp
4TBkT3JmUAXbqjELbkcZwxsbGpLlGA+x59WGPlgjbL17pGdmydAIZrMzCHM8RN8cChdmyAgsOjtkbatVAMK2FEaNTzkWCjcP/yCjuPFS8fmx+hC9KoxHnwiXYuGckVFiD3yTwUZXbpEzc4wx5pKsb7p0l4vEDdXpAKARTe/zC8waag8y5FriGPEiVZVyv5LF19DPP6h7J+GDt3JypNMXDv0WMHUqYvmZPikg2IeJvPngMOk9jyfVYWsWULPwPZvbZsDkh6GUZNIlh/xddq46jjDmd9PonILrJVe5ZkMZ0iSUXU8fCpQ7CG+sErjgvoRRPzAMqgwPhu3w6ugO1utms2Vlpzwk24q9nW7Awkaceg1MH9s5XaLFCF814kvX8N3wk061rr1qrFTrPvkBumJkBo6MEajd/w1dVoxS2zK7CulGoYImxf0Kqgkxdlii1R4dfMmZ5wJa+6TTS5eqAVp7Sr/iTrURpCsMoRK3F5FlUOgmocHqg/5KirEHrp1e++mUNNRbK0qiKPoxOnTxCJfU+4SBEbv3Jaawq9T61mvQJAl6DeGXDm19LX15tQ==
*/