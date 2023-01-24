/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_END_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>
#include <boost/type_traits/rank.hpp>
#include <boost/type_traits/extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<po_array_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    po_array_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , extent<Seq,rank<Seq>::value-1>::value
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* end_impl.hpp
+JCChR8HmbQuybUQCGGh640Xg4VXhktNxXPDET1yhxvPe9Mcm++7pO7l3kG1dS+FBt1LLegeTdAdpHv5+7Erge6CpIvNaOYbckYfvWHSK5rm0ufXYDw171fBY3Xs18DCgn6C168BLg29OwM1/4+3d4GLqnj/x5eboAJnUVdJTbfSxKykqISoZJXVQy6Klkp5iT59JMouWGxhamoLynZao7tdPmV3u2rZJ9BKQUswL5BWUlZiVh4kE7sIanr+8zzPzDln2WWl7+f3+vcKz56ZOTPPzDzzzO153g+e9EOXGMPz4n8F7RLjIgwr8MGQjirwywJ/XTZab03hq/3nvjNW+y4gnBitkRHeCKV/fCNBeRV1Zws+ELJs6RmFoh7Y7YZ80CYFvCy2hk7ognBZGb+zn+Ot8PG9N/qRLgdwE67Yj51rrNitwcTxoAXt7K7v1rUXvt8TkodO5QXyUKHFnQs8NIMtgKbcD6Bqah7cUUbrLV6V1xmWGXUutXiOjH4aTC1eNF+wzK3z27W9oHtwaLrHBKf7eqD7BkflGFwa7lYnPA07Y9Pw7dIpyssGd0T5unmC8tXzcPhOXuzH8351uPHbkHPTAzfwOnRnC23g95Q9xDnJixayuoySPeei7vKkGzpD85eDOqK5y7wO2rj6m5Bt/OPMkG08lrdx81Pt2vilmZ2hd1CH9E65T7Sx6z5s4yMLO27jkw2h5/+ZIdvY
*/