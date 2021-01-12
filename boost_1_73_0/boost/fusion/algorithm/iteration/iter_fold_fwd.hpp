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
XKAXuScimyMoLN3nGnw+ljbBY+wZffc5KjMe+l7M7LCe53+XuSjccF83qqt5s95pmcuSrwLjkCusdvQsFjDTEqP5l90DZxwzW3j6l8jyInFElBKxGkeEYQCujUamIdchTyEHkci831jzkV/snrUfYb6nl805nEgmMgd5DPkYKeubmR8ljPGehYx4v7Su497kBtYL9K++s+NNnyYsDK5zZo4yIP74g12FMNRBGlkd7GC6Jsiz
*/