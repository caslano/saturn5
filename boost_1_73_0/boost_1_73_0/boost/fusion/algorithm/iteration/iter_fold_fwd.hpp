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
Hz3Y4ycZx7ETf5eRYd13y6wFxL+AELDq2H2jMhfPLPRuiGXA+m+S8PaQmPzwjIJl+cmMfNV1gco29i0p2FlxFSbeQRoytSat/SqDNTEvYPpDIgLTT2QF1mRatgqmyZNYNXZByWOQmVttuocSGLbwG2fAkmL3LLvee4fDuZvi8cHSAiY/oIxOpAKmvBCuYcoui95BCpge0iqkPZjzNo94mJ7AlN7XMD3oT2IiCpZi7tu6brV5Zg+ddx/tC78ElytKY10zxDeGnj3BWG5dEghE/nqE7c4RdbShqw8Ii6PyKcmINPRkG3oRA6U5ZA2tnS76UD0kbFBomP3mncFF1etz2pqY5IpOPTBmqoh8ogT5RBGmPLKulS2TQfAa5kLLac9pWJGntId5WyvVLpuKt/VGqfaHKtd62/9Gz+KXd7JPK9j8+a02pQqVffHHoEgefYQ85emeNQjuU+fidY8DbO0HsjEWToF6rL/pu+M3IOcMy/2H+6AeSYjsx/Onx0rzmD/w0JxbinUMFM5+nnK/74JFINObAbPfoAVpfYXJsFytKaZuaBKzX4JK5RPxHPMKQ5+zxOpq4oWtcInTYkI10bHxDTlgjRl/FwtNwMZ/RLvsniyijmiB2U+KZg1M/FGs/5SU+/50Qd9hwRh01L6M
*/