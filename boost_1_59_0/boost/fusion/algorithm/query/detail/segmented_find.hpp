/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_FIND_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_FIND_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/algorithm/query/find_fwd.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/support/segmented_fold_until.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename T>
    struct segmented_find_fun
    {
        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef
                typename result_of::find<Sequence, T>::type
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
            static type call(Sequence& seq, State const&state, Context const& context, segmented_find_fun)
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
                return fusion::make_segmented_iterator(fusion::find<T>(seq), context);
            }
        };
    };

    template <typename Sequence, typename T>
    struct result_of_segmented_find
    {
        struct filter
        {
            typedef
                typename result_of::segmented_fold_until<
                    Sequence
                  , typename result_of::end<Sequence>::type
                  , segmented_find_fun<T>
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq)
            {
                return fusion::segmented_fold_until(
                    seq
                  , fusion::end(seq)
                  , detail::segmented_find_fun<T>());
            }
        };

        typedef typename filter::type type;
    };
}}}

#endif

/* segmented_find.hpp
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
*/