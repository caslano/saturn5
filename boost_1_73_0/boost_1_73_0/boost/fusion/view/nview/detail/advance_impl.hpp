/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_ADVANCE_IMPL_SEP_24_2009_0212PM)
#define BOOST_FUSION_NVIEW_ADVANCE_IMPL_SEP_24_2009_0212PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<nview_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef typename Iterator::first_type iterator_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef nview_iterator<sequence_type,
                    typename result_of::advance<iterator_type, Dist>::type> type;

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

/* advance_impl.hpp
+om4O64/l1Ms1LRClIgiqd7K6KFXzWU3/x5kB1JrH9ET50sYSfQceiWAMudci4+wRptXwoW1zs9iL7b33S58LrusmWJGwcpmmqF6e8iy95EtbpbTDf6jAysZXgbK2q6Trf04KiotPsaD/tBS+ikemt15zYM9VnkOgdSPi2L5h0TIDxRJw0ZW5p+3TXVQvBQsKPHg3WeMIHEsNx5j7uGGh3uMB32+HH+WKD6niooo88QTxSELdni35OMqoocvFQJc7jTwUgtG2tChPuCg9A7JPWHNj5as0xGXPD+QIk/vhh/0+MDanHAum+/jgtNAHmhppsww2O/T5KVMmRiX8dVLreTcZ2V2WcJ+qim+KpuECe13dgcaRWVqUnah5z4y/iWxRzJPvse6TuphPZkH9ELqFvnfFBXiaZvM5yFs/ihmDmR/YwMb7/Gngh/hcx3JYk5M91Z6FCv/UcrodysygT7xBOrST4nMlJP4CZF3GwpaofBvkGrZE0pr6tc/kbr/B1BLAwQKAAAACAAtZ0pSRuO/T8wCAAB6BgAAHwAJAGN1cmwtbWFzdGVyL2xpYi9mdHBsaXN0cGFyc2VyLmhVVAUAAbZIJGCtVVFv2jAQfs+vOJUXijLS9Wldq2kM6IpWAYJUFVIly0kuxJtjR7ZD
*/