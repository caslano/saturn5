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
6GCBvMTgQBGj0qZcTPFll19KghfTxfSshd90r/3bRZT040VU9Bv+/RX8Zhf4+fG+nBTwufjJkaBMQ0Tsq0K7sAa1B+SI51Ku5XF+LuTnPKy1Ue0/hDz3976U0nsModY6DaHf47l8NKeP5t8j4PuILT+39giG2D2T+71hKH3xkXjWDPoC4x90Y40b9fVLePxDqRtP8+8a+F3s85b4cjziZ76oM+I9Ea6TZcGjultpcLnWLMo05PqvaUA7mFTdMFNgO+VksSvrgxo8OC5AYRLoJqHz7XcvpEuhdHkpZDTTaDZRWdZ66nou3SeVCFx3ex+DW+87+2huvf32DetkyN11V6BuTiewyyvRvXtvRnR3TFcZEOdYV1DQQfWTsk55ymbyJo5+rNVbfg0G8/0flyOasLFAcrBBILlJCiSllRt8BTH7dN2ZJLeuO1NjDH0lVWbBqHCytncDKaH3QGQ8iP72RneVxoMlmjA1xD0c+rjevo8ll6bIksuXeMmfuUTqcyhiJQsFUeVJdfvKHCyGLHlODwHw7MO83jmX5/nfLieSNT/rMlvlYuTg3ibMABJb70hBgr/sQhJcHKizg9nVs8VJnR9Uv/r+OJK5jyIKyw8iWlgQRfgVTa1+f7yTSRfguzG0d7AA78ynI8ac/bP4N0Ag+wGghu/P/1m963yTCc7TX5DgnW1zK7N/RtJgjA3nGbF8N2qRvDS9DjDIxnbZ
*/