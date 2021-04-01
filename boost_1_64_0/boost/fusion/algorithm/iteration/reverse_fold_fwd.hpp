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
U3t3u0Bm8nEYAut+y0BVEroBsD3qlxF1LsDHs/TBaZ3gQig/4NmAM7yGt9forL965n1repkCjqaFniebuyMHDjZO/OEVuw2VZvVfjp+tLY73Mmpej8eo1FmdV2plcNI8mOhPEWkOaMl88lXv35p7mZrMEhqGmIAVSR6LOtzm36RErfcKsVGRgvAcEb9ufm1hkoXO4XxfsfktlFqMX71bm2Uc15m2DOQKPUDbEdSPnjHUYN8xUxnHoSr4tXeAVdsY7glbucDxEFlFf7+Jo+0XDeAl5rCINcvHRSNrfROSeyj0+lLKZh6AGMkOW6YzxLBVOGvoq6iIPgCHXIlJBlww+kBCN0EI+z31hoC78MJPr4TvqCxN8JZXQa0j6U0CNwW/YJlD7+gAXUVmnb2T8CqCAB2/cQkbKOAkn+d7dcV42hcL+2UwgntT/ZX3Kh1hwSoq+KWd54LJHh7zofzKcPoNMXqI7nIBjlbeKWYzw9n9pG8cz3j7ndcVCkLpD6v62nyx+kypxHDokLjgRZwja7Pych14Ubp18Eyn1MQWIrn7N171Tw5QuEGmX22qfg==
*/