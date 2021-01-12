/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_FOLD_FWD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_FOLD_FWD_HPP

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct reverse_fold;
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq
      , State const
      , F
    >::type
    reverse_fold(Seq& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq const
      , State const
      , F
    >::type
    reverse_fold(Seq const& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq
      , State
      , F
    >::type
    reverse_fold(Seq& seq, State& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq const
      , State
      , F
    >::type
    reverse_fold(Seq const& seq, State& state, F f);
}}

#endif

/* reverse_fold_fwd.hpp
OZXE5P9u3XZySOgcMTnvDFYgoON/Gy+F+WWc1zJDzD9ud8H1o0hbyukfkOBcqrjHW+6z2oTHl+rbZn90rOztKZ6/rK/9XSklYu7Pdjt8UEQZeIrceJjfp62VYi5Z3csScw/YHXk2F3MvEqpv+O2xl7t/54559/Zbv/GS5w/zXp91GGlOHZ1vl3dJX52r/lnmnHnrBWWm734x19OqxL+IesSczXKDvPt22/kObjfifHs3xq6g
*/