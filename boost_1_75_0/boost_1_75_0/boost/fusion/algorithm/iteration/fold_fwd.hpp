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
mqSxkbJZ/XM4aC1PBM39iWlQSV64/VWaS7e/yhnUnDPkvzY/6hUT8VaGQpSLxLQPcaVOTervEgRlLrgN9v6OOT0QUeU6XCs6mLQr56S1QXtSNmoFRzbpesUplZGDdsVJGveCoDLpVl4Y7ha8OTs1gy4n6rPMcumfFohPXcGNTSMEgOUqo6WG4PUiOdc3vkAjUVOpOUvDOJ4kObLSLm7letDvIgSXAp5BqvZ6f9G95ISTs2wkLUBykqWV6DGucUjSP34jBEa2AO8z/8bWefXsVUYCX9cF1HWdbr2c7csEGEBGtvKXbzzZSo3E2d9JVjRf3JFEyniC1D1UXJE1xNsFhQ/FvhETxXqIWgbVN7nMkDB+omCocmx1/YrBW0XlcSjlqjhxbmkiPIbYqkClMHeIaOEzzPL1gijGL4E82m9/56dOIOJQT7/ACrxpV6OFzsuXYSt7ERbs8eup5B8DsWRv7I5vRJHxi1L64lX6opjrXktf9Iz0xRX4RWCGKD6Ciz9CxXtsGlEUxbhElu5MpfMwLdd/XxSOsDQBTvam4yeDQS7366U2naf5+VJWmorgldBl4Hlvj26F590Sgbepp41/zQpt48M+E7tebDugYJwI5NC8h/viRNudncDcYEQnBy108lXNFEMpFxg5OO/FkcMkgRlVJ5uJIlKMXnQ6XSrdovzIob7crNgoMLv99D9STMThTu+qYf+eXAo9odiA
*/