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
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
*/