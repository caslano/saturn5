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