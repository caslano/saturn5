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
4fyDqO2G9j7Qsmoz9Zqj+er3mW8GXk9NkHTdtu+KvA0/a/V9+8d7F9VF7T10aRkv+K63T/TSOx3VU+jdhcUTy/oZD6LfWNL1u8JE39mh47XfZf5+zgefvIlueM9uph3msk91ZF+kAS39aR36Wn+9P2RpX9yhrw7XwDuatgEiz/dqhz7oL5POjl1C5mt1DU9BHzbvUjyev0kQuBZCHxG/mboX+i7FdXU9nsLPQ8a4eoj2rm1d
*/