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
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
*/