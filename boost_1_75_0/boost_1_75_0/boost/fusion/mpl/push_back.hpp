/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_BACK_10022005_1647)
#define FUSION_PUSH_BACK_10022005_1647

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/push_back.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct push_back_impl;

    template <>
    struct push_back_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename T>
        struct apply
        {
            typedef typename
                fusion::result_of::push_back<Sequence, T>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* push_back.hpp
SjPXj3muBmHJJjRJymVmv5O5lDzXt8ISjB3rvw5qQ3m+X8mn2lz72dfOvCnN/l5u/qJeuYK/qJfviXMuU+mlxbXs9ImqOF9y4PBpKvPVM6pasOhr0Kqwqnq4cy1S/ZaCQapbvjlN2QQP4CJV+Zhf2JT38ALY6Y1nECEo8hK/SFWe5Rc2ZRleQJGFWPey6sgYqsqnV/WgXtXvtKru0Ku6Ra9K0qu6SavqevhbYdZGKMn/GVyBW017e58Xtg6Oenbadss2aIsBxXTSsq81ygbLfgyWwW9DsOxb5dBT7aj6ShPQKbRPo9Pqp2Oo+ten2lF1KpZ+Vi897ekoVTFUhX+ETlE8uuEfYlD0/qc4ReV7zHmzmv09DYoWPqVT1CKup3cWoGwrgqZAI3jcjBNUXaETdL2ZqPCfFRoVvluhUeFfKzgV/rFCo8L2FRoVNq/QqLBhBafChys4QSWqao1e1Yt6VU9rVQX1qubrVc3Uq3pEq6p0Bc/kzqlZ4js7NdvGMlfeIuYYBz0y1qa8yG9g3hqbqsj8BsgxNi0ariI84xkj5myH8TP4dkWdcmY6F3zRc3nGebwJ9xrn8WTriyUWbY52Z2nnHX5+D21lk9BQO0Y/A3GQP0vX7KjVcci/jsoqwx8wlXII6PlvslrlD6Aw6LGx5V/G2si0g7HlvyBzD24HwrJGtjdu4WEWU2kiH2FEwC95z3wBWW2+mcbxjj0Y
*/