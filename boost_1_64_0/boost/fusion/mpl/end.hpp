/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_10022005_1619)
#define FUSION_END_10022005_1619

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/adapted/mpl/detail/end_impl.hpp>
#include <boost/fusion/iterator/mpl/fusion_iterator.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct end_impl;

    template <>
    struct end_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef fusion_iterator<typename fusion::result_of::end<Sequence>::type> type;
        };
    };
}}

#endif

/* end.hpp
ES/3sA52uO0RLxLQSKVNMJSTTx+t0Jr420wVmvIAj47QdBmJB9KtWClM3xr3MCUpjUOL5yx09zJ4U4c9QdTuTQCEmqVGrHb2ghG/rLiBqHBIYWDg3k4G/GkptkPnN+YbEoywDEbmS6RS2670G24CuwWNjfc2I4/cIVRQJ0Ao+aQyUbOEcp11mXQVZulBganQ0g60RTychPDTjkKs5sqkXsND8Wgo6nJKPliKP+LOSLgH1w/kgFX49F8A0xjdYETdlxcCNobVHttKisnZO8PCGPISHmEAaPxyAuLkufySme6BQQWLxIAWdl/OC60fnWAuAg/bliczEeDXHPH3p0aKsu0+XIQeoWj9HjeH5xLWrIhNgeh02WctwDqMh/5fCfBzzsQ8SdGXhjOq3wJPpyXnAkWdpod9xh3x1BqUXwoXGR71TYuvDrzc/rRtxpDhabSan1EPY5W1hlrLl5b7poOUhzUmTFFOEL6H5AdpXeEhKt55C/M43hPnfeT9cXHgbLZX9cTCTxh/juaHePUzMVptcQ0lmw9pki56Uc81G4nOtP6458E4oVDSKezQqw==
*/