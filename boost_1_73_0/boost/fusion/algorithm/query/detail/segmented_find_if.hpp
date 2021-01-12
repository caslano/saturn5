/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_FIND_IF_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_FIND_IF_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/algorithm/query/find_if_fwd.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/support/segmented_fold_until.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Pred>
    struct segmented_find_if_fun
    {
        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef
                typename result_of::find_if<Sequence, Pred>::type
            iterator_type;

            typedef
                typename result_of::equal_to<
                    iterator_type
                  , typename result_of::end<Sequence>::type
                >::type
            continue_type;

            typedef
                typename mpl::eval_if<
                    continue_type
                  , mpl::identity<State>
                  , result_of::make_segmented_iterator<
                        iterator_type
                      , Context
                    >
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq, State const&state, Context const& context, segmented_find_if_fun)
            {
                return call_impl(seq, state, context, continue_type());
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call_impl(Sequence&, State const&state, Context const&, mpl::true_)
            {
                return state;
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call_impl(Sequence& seq, State const&, Context const& context, mpl::false_)
            {
                return fusion::make_segmented_iterator(fusion::find_if<Pred>(seq), context);
            }
        };
    };

    template <typename Sequence, typename Pred>
    struct result_of_segmented_find_if
    {
        struct filter
        {
            typedef
                typename result_of::segmented_fold_until<
                    Sequence
                  , typename result_of::end<Sequence>::type
                  , segmented_find_if_fun<Pred>
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq)
            {
                return fusion::segmented_fold_until(
                    seq
                  , fusion::end(seq)
                  , segmented_find_if_fun<Pred>());
            }
        };

        typedef typename filter::type type;
    };
}}}

#endif

/* segmented_find_if.hpp
tadVlLTG+expFSQt3J5WIULSgrOlVZe0Az72tKq2fEZaRDVN0m54G2lVbGnH7WmVbGlH89rSqofb0sp62dKqGf1q9rQKtrQP89jSwivb0trY0yra0s7kNtKMfvcYaVUjbGlV7WlGvi65bGlVXlxvMes2f362S3X/lP0lvm9Gd8kb+1ybpjnqdximqb/thC+xivjOj/21gO2eh6qMOiWpa0ZcvGr43V7+mHLUSfO+6meu1s5x
*/