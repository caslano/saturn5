/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_NEXT_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_NEXT_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_iterator_tag;

    template <typename Sequence, typename Pos>
    struct repetitive_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<repetitive_view_iterator_tag>
        {
            template<typename Iterator, 
                bool Last = result_of::equal_to<typename Iterator::end_type,
                    typename result_of::next<
                        typename Iterator::pos_type
                    >::type>::value > 
            struct apply_nonempty // <Iterator,false>
            {
                // advanvce to next position

                typedef repetitive_view_iterator<
                    typename Iterator::sequence_type,
                    typename result_of::next<typename Iterator::pos_type>::type
                    >
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return type(i.seq, next(i.pos));
                }
            };
            template <typename Iterator>
            struct apply_nonempty<Iterator,true>
            {
                // reset to beginning

                typedef repetitive_view_iterator<
                    typename Iterator::sequence_type,
                    typename Iterator::first_type
                    > 
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return type(i.seq);
                }    
            };

            template <typename Iterator,
                bool Empty = result_of::equal_to<typename Iterator::end_type,
                    typename Iterator::pos_type>::value >
            struct apply // <Iterator,false>
                : apply_nonempty<Iterator>
            { };

            template <typename Iterator>
            struct apply<Iterator,true>
            {
                // eps^n = eps

                typedef Iterator type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return type(i);
                }
            };
        };
    }
}}

#endif


/* next_impl.hpp
bk2biD1WlsDSOI41uCkwLJrYLoSMa3xAmFU2xO+m22K6E1pexJSrm1ki7djJjQU+p4GsMdahlk02GGz1vryKP02TnYgWUAwBSkHMBsHVNu8ADSb7PLxJnOWa9clenjzHpiLmJXhfvTT4LHL82J43ug5xsSJ9LzCmz5HVFlaXPgVBqIhGQjg6UKD3zEy6q7PTLSK3J/MjOXCAju1W6AdbzLlBpuBzVNjSSYyl5ntLfWFBa8SyziISElsSG0o0pf3AH9hGMPCek0RVAKQCls8um0kBndwzhhCmqFFhdXl6IOEJEE9JMC9shbRUJ2Y27Sz82+L69mHZrOBSxbDF6p5CEY1fMEqidYSAJc3WCYFyH7IUGaqU/jTDeQ/o8CSBXqbv5ea7STL/LrKtkGV8YJzVFkVvB0tOvOFo9x9pOnqLFysKiuksGf0NhzZkDWkMzgb9+TlpNLBbrpVizyxDOMT4rZlov9XV92/cq3Ob1Vg/FPbH7QgizakVgjoC++6PdEd2l1Ytr8CKaDv+CGDLBeLMef0mVfEOMhLwCGl4g/zhVeD8J+3ki7H6nspTQQ==
*/