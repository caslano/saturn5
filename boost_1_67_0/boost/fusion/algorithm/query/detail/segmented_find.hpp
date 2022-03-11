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