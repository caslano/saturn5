/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FOLD_S_HPP_INCLUDED)
#define BOOST_FUSION_FOLD_S_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/fold_fwd.hpp>
#include <boost/fusion/support/segmented_fold_until.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Fun>
    struct segmented_fold_fun
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit segmented_fold_fun(Fun const& f)
          : fun(f)
        {}

        Fun const& fun;

        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef typename result_of::fold<Sequence, State, Fun>::type type;
            typedef mpl::true_ continue_type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq, State const& state, Context const&, segmented_fold_fun const& fun)
            {
                return fusion::fold(seq, state, fun.fun);
            }
        };
    };

    // The default implementation of this lives in detail/fold.hpp
    template <typename Sequence, typename State, typename Fun, bool IsSequence, bool IsSegmented>
    struct result_of_fold;

    template <typename Sequence, typename State, typename Fun>
    struct result_of_fold<Sequence, State, Fun, true, true>
    {
        typedef
            typename result_of::segmented_fold_until<
                Sequence,
                State,
                segmented_fold_fun<Fun>
            >::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence& seq, State& state, Fun& fun)
        {
            return fusion::segmented_fold_until(seq, state, segmented_fold_fun<Fun>(fun));
        }
    };
}}}

#endif

/* segmented_fold.hpp
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
*/