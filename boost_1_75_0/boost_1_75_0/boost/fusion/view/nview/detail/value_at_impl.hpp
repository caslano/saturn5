/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_VALUE_AT_IMPL_SEP_24_2009_0234PM)
#define BOOST_FUSION_NVIEW_VALUE_AT_IMPL_SEP_24_2009_0234PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion 
{
    struct nview_tag;

    namespace extension
    {
        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<nview_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename Sequence::sequence_type sequence_type;
                typedef typename Sequence::index_type index_type;

                typedef typename result_of::at<index_type, N>::type index;
                typedef typename result_of::at<sequence_type, index>::type type;
            };
        };
    }

}}

#endif

/* value_at_impl.hpp
kdZW+ERa8u5Z/axdu+Dt3ChxLfzewTA6lsWJVhA0XU5ILfLTz/HbJuea8PLMyew2Ff4U0PlNtejulXB2+327cmt8Ahemu/JxK2ViPoUrDaVCYQciET9o7HvfGsV3vI/GVZ2BNgbYH8WSL+x9qp4nPe8D3r2gRoxbRjy89nfF9g5ASvCx13g5AfJolPgodtjtHiJpMP1zo9a6o4VUrtb16arDPl1nHJ2yXqC/Ew5pl/uWgQH0Hn4Mp6ObTSimLHIdatYdvBQ07v3DJqFzTQDU8BDQK8GBjTSIU/auUdPAoHvhongZTtSkxLC4MFbbwKjX7Z/ulMicS52q8trPQubU4kGWTmRyXnHDPnNP/lbCLCBUxka6JwqwgEHPmsxCDHoyWWd0y7/nmGJ+Q8KVSyV5r6lu+JKdkLXNX/ogdoDMP66BOSPBmE1D/JPMPc/uhgY79krRM3dF5MaDPklObMe63B8ptPlYEwMkL17fjOSOto84UlGGdGJh9U2FkfbZ65M86y3ahqVueHYcbzcxiXF6nUwoSTvuofkordGLt3GPwc51+G8XsZhUivKEOiln9mK4QdBEDvm9dW8zxCEv3orVNtHrICMyDIxPeF4/alEYFWFxANb68OdHzxWGqu8BTOHucogLbAGRij/1S7rbbINjXtvbuwRFh4d7kGWEWjqJMPtuuJ729apB9t/7tDggdFnSTuOi4Wl1YWs+qIJ1
*/