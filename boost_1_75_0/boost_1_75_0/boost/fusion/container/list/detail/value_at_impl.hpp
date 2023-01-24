/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_IMPL_07172005_0952)
#define FUSION_VALUE_AT_IMPL_07172005_0952

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<cons_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename
                    mpl::eval_if<
                        mpl::bool_<N::value == 0>
                      , mpl::identity<typename Sequence::car_type>
                      , apply<typename Sequence::cdr_type, mpl::int_<N::value-1> >
                    >::type
                type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
JvNfD7uY/1roev6rmbPxFTYIWYp6Ocx/NWvQ/NdvTue/Hq6zjsH3YK1U4bWMIzJbyyB7vo7j18kKg/xV+FUoWMso8RO2YQ3H76U27d0Cr2Xg97zNuodmKduwugewbVgTg9j6keEK9CwL9sIMCUuGvq3QkpdEkvOKJU38AXh3PRm2A0cZ5DeVjYGd4Z2AiL0uR5hSeNXVtB82MU0MSzFwbDxFocbU30CwlkKxFt8csAZI+9YLkIb0Q1lRyPRS9jqRBR5EeE7+RrKsZfZJ7ELPe9gSg5EdB+/+77V8olOjIWlYBunwxfthn3V+FpkJj8RvCAwJS0fohBb7w4Zw83bop6FH96xAA7ydP0sDL1t1hzMFAD5x8l9xMWc0prvY7meFSXp5nyQTgqoC6+x4uu3JdjyZA8ssy2J8Va4L/MoLyO3w+RTpeFtzKdmXrZn7FlbAKM1cvB1W3ptmiumpmfs6utjyJCiabmcz8j5QWpw51hOBYEFveFFor023qgV+1WkAmYFET54tRvCAd5em4SfZLfCwbJY800yzg7pq4nZIXrX4bSwjNgbyIXhLzrDdV0XOAUD4laraoKqr4PWXoSUBqPHJQeT9N7BQdGNZb4O8C28sewxvLMvqan/9WntpGRZZWo8h+rtZzZB9HQtCGQvbvd5BwTQSRXZT1DhcH0Yha9VEAOR4LJwQf3+8iIJ61xQlwbSZW2LD8kgQvO9l
*/