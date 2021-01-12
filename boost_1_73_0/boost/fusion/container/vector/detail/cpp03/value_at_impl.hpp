/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_IMPL_05052005_0232)
#define FUSION_VALUE_AT_IMPL_05052005_0232

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<vector_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::at<typename Sequence::types, N>::type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
MQubuna/6Fu6NfXB0uU5hdY0aE/9TNT6+S1K383UVSH1Ndqn7mKvs6NrkeMo+UTeYSZ5J/V1mNZXB3Opw94ans7vl2K2r7WtvnoyH81LwSo7W+SDtcGML8LcTkpb6qn67VrejypfQe7vdX5vk4Uc4/4Wz72Mj8rNHvgkef6jzs328wy4r338nwY3ix9Naxyjd/b6XsS9MF3HLpOrj3fDJzJYpxMdOIox7yR5Zv4Rx3TDxN5Y
*/