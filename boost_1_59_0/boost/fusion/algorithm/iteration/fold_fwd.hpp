/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_FOLD_FWD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_FOLD_FWD_HPP

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct fold;
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::fold<
        Seq
      , State const
      , F
    >::type
    fold(Seq& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::fold<
        Seq const
      , State const
      , F
    >::type
    fold(Seq const& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::fold<
        Seq
      , State
      , F
    >::type
    fold(Seq& seq, State& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::fold<
        Seq const
      , State
      , F
    >::type
    fold(Seq const& seq, State& state, F f);
}}

#endif

/* fold_fwd.hpp
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
*/