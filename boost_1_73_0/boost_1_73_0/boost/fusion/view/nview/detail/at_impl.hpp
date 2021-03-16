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
acntmk7BeB8RnAathsaXmxnPXdBdU/E9oGZK/1vtSobfgrUQx/VSh3vb6aLfVVwL3wPEfA4BDla8C85IResrtHYCqiO5COA5ugtD2dGmIaBIUn/8CSBqAf/P3LWHR1Vk+brdTYgk0gkg8hKDZjAK8gpgBJEkBrhZg0RxMYqSBIgQCSRA9wgY5EITpb9LJIiMz3FW0ZFdZxRfY9RxTcyngM8M3+igy3yD6+cDGF30cyIPNXseVadvd5rH+O0fm48=
*/