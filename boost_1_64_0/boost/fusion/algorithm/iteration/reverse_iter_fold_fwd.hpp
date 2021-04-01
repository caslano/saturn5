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
qVzGQQf7naiSUmC+4Y+DC3JTJkadHurVhr2Z0Ws5xOauVNUT+LP+WFljgVDHOsE2AjzedWuv/J89UaGbyVI3Jzyobu8gGjtaOPnBU0/Km81MdOQRcKgyaVb24f0SNcElWvfgV9jW6oFOtwrjB2qu7g5W+j0ZBLvLsBwE8OshDvtQAcAXCTD/RPjGeBxIOzve673z4m5HQ/+p/FQ5C9lV0pSJ7d8d7lYufhbw9c8WQZig9Tu5MtCZDwopOekPfQTu5uwPgAjsoQGUk+HU4Qm2WBP+KRCAW3odaq4I6ZDdApaJrfd4y3hdLLIe3sS6lgzm21xgyOsvE3AypoxacDPtG/h0jOW49cRc/nBeK6dKdRFCGUbqtluAnYKm7p304Xvr1osCCUZu9G7mDZ4uUTYdWFGYsLJXjhz/i8KXa989Cefsd37WZT6munKXgxLRtt7AQG3jYhrt4WdIzyxNXj8CK4qczMXtZxGnfuvmtfSXTzQUprp/bxX+KEOR2qJtZFoFAZOdUSsUoTZfXRQqn7nwXYDchpFKD2lT6a9veBgLa6cdo9OklWQDWg5cmQ==
*/