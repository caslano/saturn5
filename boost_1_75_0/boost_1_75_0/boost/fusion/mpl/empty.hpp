/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EMPTY_10022005_1619)
#define FUSION_EMPTY_10022005_1619

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct empty_impl;

    template <>
    struct empty_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : fusion::result_of::empty<Sequence> {};
    };
}}

#endif

/* empty.hpp
SPZT01zhpGyUxkrD+b7wCuhGWufgcVIhCbu/a159bP13cp4iv4WzFOoPB5MW3Tcz14z6EPgylNzYDgWGlrkLbwoMLgvdNC7ocUXmzmPc8xPkk4AoqsFUOZJxKYLxK/2P4RpMYVVfogrZHrOGuN5CRySPshPzo29A6N3ff4jZU4Kpnsg93YDukkvZVRZa1XMUHJF3yFbVT0VnbkhheeLnH1K6DsmLpVb0HOWlUk2ojp1GnhMyP3DVBgE16+QH0gll1i+5v/VaO1CBgahbkwvHTQm2CRzw6H9IIY6h4hjASl7ZxQyZjQXeVR+u4jC/Yuhli03TfU8uftPxo/zCSAYsMJER0pU0D5SfF0WDv5kEEN4fSD1007jAssism6jlz31AZA6WuiNFCJB6V5rIrb7qBHkPyHAdyG+7EbHqULU45wRn2o4U9YxMBSa4uucoyV0nW1vJT0u4mZLWePg67koexngVvsnRHVDzrKNmDPtilXUXMfGRjF6P4Vjncrn82ugRJkLbuQ4tjgZ23V79nxkxezVpDC7gjoG+v8Dix5k29zIxml5BZEarZjt5xLBd2DnfIbptPnCURUg6dWKjN6N7UmTGSikzFfM6Zk7PxJyOUuYUu9TLaYffefA7D3474TfI99OL4Xcx/C6F36WydTtcWgyXWmXr93KoxRx8439XE03ApiNkLL9eDl8ZQyEnu/dffhdn964w7N7Hz5JA
*/