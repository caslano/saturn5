/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_ITER_FOLD_FWD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_ITER_FOLD_FWD_HPP

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct reverse_iter_fold;
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_iter_fold<
        Seq
      , State const
      , F
    >::type
    reverse_iter_fold(Seq& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_iter_fold<
        Seq const
      , State const
      , F
    >::type
    reverse_iter_fold(Seq const& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_iter_fold<
        Seq
      , State
      , F
    >::type
    reverse_iter_fold(Seq& seq, State& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_iter_fold<
        Seq const
      , State
      , F
    >::type
    reverse_iter_fold(Seq const& seq, State& state, F f);
}}

#endif

/* reverse_iter_fold_fwd.hpp
x3nPFrcpSaTBKuJ/ynDUznitWhUr7Ntk+cax8u+YW7aTzz23nDZKz8bUcxIeh6xJcm68S1yZOSb3748bi511ttP2D0VaSp3hsZYhwTUscZe3LSdeLrYvD49PnpU9D5UE08RMR3qI7t8f44Z7ny9sbW+KmBlrlyOmLrG8dk87zrXvh1vu6av5o6U8b0L9Emv6LpmiN8NOxO3BtLbbrGusy3B/gh1VSh9Mx9hi7092bSfHIMs4
*/