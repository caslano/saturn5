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