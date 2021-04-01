/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_BACK_10022005_1801)
#define FUSION_POP_BACK_10022005_1801

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/pop_back.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct pop_back_impl;

    template <>
    struct pop_back_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef typename
                fusion::result_of::pop_back<Sequence>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* pop_back.hpp
HpF3gmGM/hPq/UtMD1M+iNtwDE07iKnkDWXTRWPufp28XFS9QFKAUF4yCWHgy0DLn+puBeUzKFwv2mEl/w0ItzcQ6fLV00PtL0KaPvxeVT5X3a5NTDmjDO5B7Mz06JXd4BHZW/b5NLubmw1I0BTFeXUr/nBqUFzolu+Xo9OLTZ4qp9bxeqHud6N1e6RWOBYTkAjLevTSgvYUiH1anjYYbKxueZ336lVxN8ARpMgdC8gR9ieosyCaCGCGAsLWyCkbQNw/Jwl/uoSbmVybTO3nJfxUeJOcfD7CQ/hBk8Ql25jehe7nfFLkPPCDi/LtAs643LFS31kMn+Cw1OwmS2a5P0T7JyF8O+XW751LvZVQ6QKizu/cGGgDvWDrtwbopTaFxv+tx2I04Plwlu/cwse2f7Szqxmwq+1hV1OWkHZeDYgT5nss/VOhe5ce+83sVpTrF4tnr7Gp2J7NBZqD1oxmogHb3tmEfX+oGRpK37ubYPVU/vXtkVJp4Q4c3iQ8QQ/Vzil/woWcGzXOK9rXgPgBczXopIJeBhYOpkqMMIp6dqUcDSsbtC7oq8/Q5g==
*/