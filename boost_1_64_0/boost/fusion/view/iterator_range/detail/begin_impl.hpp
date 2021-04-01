/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_05062005_1226)
#define FUSION_BEGIN_IMPL_05062005_1226

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<iterator_range_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::begin_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return s.first;
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
r4iJKwJYsmWY8OKkiYousUM2+FdXoYidDLtNVJYMuCX+4h9CH5EDY+7c2/bkXz9KOt7kxXQ766uzXx5d31v9KHhciY+lWa6hl/1emeGMzRButQj/ZGsDthhIKdeeJeQGk0ueEhFMKKEd7yvM87J+PQ8GhvjXE77boiDZY6RTJhX5o0MgtHG9WNTmUnd40OS08cvxtD6x1vOQjG1WuvmkOfYKcMr6h8ajoen/GhRYUHsBmZHxk6E9HaJpVLpnTFraQg/trACjDBuL7laucCl55YPTzSrg7x7PRNMGVghSC6/lkxtGXp+tOGMIN19YcolL5rfVFjLDeFoxqaiWb43ZjU1xhCYpzozPhKJMDblh21jCB8dsDXTMuL4tTrOCCB4wowzV7GYV0A3Af2uqIfUyBPX/vzfJFPuhybkQC/M0xm3MbqtV7fIzz7/ZACl6QGOO/7BVtF1jAYGs4ULveTj5DHcNrCEf1tzlfjPne8MQhTZH2ftBu2ARoeAMmOFLelqcy7wcGZ++qbUg2vJk58JEb+v1cL8RhxWzPT7LbJJZzLnmhLI2n5Ms8BNIBw==
*/