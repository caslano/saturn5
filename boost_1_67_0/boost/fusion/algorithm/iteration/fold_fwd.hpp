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