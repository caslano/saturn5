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
H1NdTGVp5GZhaK1EWCCjf6G+Mt+YmDqle/WprtJ2B7AzMK1C9QBV5qKM45OIuXy2x+c0WAqtS/RREr3x6VNr6PyYGW0jg2oKRUrpqnXFMOUmXb6w/6p9SJeEVVvZfuRJ9iWlbKeXEL6iokJ1PfSMr4eWjWlGnYBI8P3WHXU153VN/P0yn4/rq1kzzLX7ceobpsCEJtzK/xkjqn/S0hq/vp8K2N4M6IaE2y62quZp24DI5YwVn40Fn6HOe5v2XYnyCuNWGj1ZprBK3VnuYSvVkr1+LyRt6ATUpUtCceVYJkKzZ5xVD8HlDkxDthmu6Yg1lrnFrXpm5jMid3/82SmlqCdWSN1AVSa/7y+x1/PygypDf13KPP761L/DHqtghqY/6VWs1HiRcqOtLDbf1irifpWlVYYs7vvr4WGcLW56X4FoOjv8mnryNB3TJodW6LqluAxctqPWIN84Ofq6nMgh59Q9ZrgZVVeu7NGz3vpTzgZMKS6Ld2nKKQTsNNobwNwmyhDLz87PoKCHqlRu6W2OQCzW1L9XqhNrRzmdIOVDHB/Ut8o1AOyZvCNgng==
*/