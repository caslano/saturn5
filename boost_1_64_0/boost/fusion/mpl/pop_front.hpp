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
2qVDGG7V/upVhO0NUyqcCbbLvrgl/wpRJtVOCciTS3Dc2U/fz9vut9Rw4B0V71UCWAAMOEZcQq4F36VhUx7iDzxog1H/c+9LIvMbiRtW8lXGxqkrvZK3+XxzxqDJ+FQn8xaRg0NGkdUMYaiZFmJf68oYzA2g8wdwSQl/NEJ4b4A6QLz4UXL7ONBkGKmT+Bt8R8cxM8ZvjmAclrD9CNSF8ffcFAEXtgsJD0BuWeAwp9U31QVGwbOEhFtiZB1m8uhRwwsR0KzwQ8mH/Vlxhnh2wrd14B+o85R6tv3OTa3SDdAaVP30qImPTrItZS2cdZ89VrYzWR3nA6N0SGO+lwxF77dYX0p4z8XbQz78o9fhAtFhV3XHfF+T57RjB0mbPdl+akXv6yat+nxN5jn/DKgWyT0h0xk/xB9HaARyyoC2WbjXevpL+np9PlTKEmEIGrZItdHNcsQlsWjvlboPb8oxAotGjWdGJd9xcMnwllVI4KFgClz5PxSihYgiuzS/TZpx3/p6wkOXp2t5tkvtQNEUKbUDxXX7XL3jjAoyEJNdBMv7nBG9mAyT1tgqFQ==
*/