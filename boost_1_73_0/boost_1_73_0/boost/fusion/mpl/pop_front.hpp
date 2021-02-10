/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_FRONT_10022005_1800)
#define FUSION_POP_FRONT_10022005_1800

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/pop_front.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct pop_front_impl;

    template <>
    struct pop_front_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef typename
                fusion::result_of::pop_front<Sequence>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* pop_front.hpp
fHkK/5fxUYBAL+0YKIVgFi1keQFAaIVcBfdR8t3rapfSo9lDMtmUAAvjIr+blrrmRa7EFmmsOMwL8Z0wDVBk51r9gSAhVRmhcEVJ728Tbso6i5KiNK8n/Dz0ydVMTjYLDUCRbaRYxOkEVKU4Pqatps78LIhANDaapKfcx9NYhslmDW8AnrwAeToFTQTbkJBuB/MIO0ZhHP1Dzs50izhNFtYkwRbBPA4X+ZkW4cwTooHTpaRZeA2GXvMm6q1MKrlJcj5FjTMNQYnhEPfhAygu0Gmo7Qlv6xQBAg272gCiAaG6MxgTqBJ4k4/zzZo0lwKCwEmpwRRE+ySc3vJIABQM6iwPIMjAQCniB1YeIL/0FI3gc6//3evgc6fb3PsDP1TzBWqt6l8QYzH029cdWfqNhxc319t64n58dbrncktD08TIVwvf1agTfOoOm+Lw0D68uLykBwaaILgedDpBAKAIEBnhYhUKZM8oWTTAiEDj6s2fX3/3uonS4mr0qQN6FgzGHHYMrKI4BqMgBastmoFuRlWLWFLQ8Mb35iJUe328yWFYK6EacXQrFfFJGPSOSGCDFuVEArlKsq+qJAuNcOPkDOxKKRLJVhOZk7CpudS7CaxGBmwmw5naQeYe6JxOA7P5JACn/FSci0ZdoyZ/
*/