/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_ITER_FOLD_FWD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_ITER_FOLD_FWD_HPP

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct iter_fold;
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq
      , State const
      , F
    >::type
    iter_fold(Seq& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq const
      , State const
      , F
    >::type
    iter_fold(Seq const& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq
      , State
      , F
    >::type
    iter_fold(Seq& seq, State& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq const
      , State
      , F
    >::type
    iter_fold(Seq const& seq, State& state, F f);
}}

#endif

/* iter_fold_fwd.hpp
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
*/