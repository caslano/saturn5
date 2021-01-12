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
X9zYkqBnb+SH6q598v54uzrzMUe17tp/tvSzN7zyzkM+5/mmZKmjJoa3AS+Ie5/Sb30FPZ3bRo//idt3ytzLfOgHx1wPDV8wHj7VeKjn3eGtGNY3zCMuQvXnAPHXR9Y2SkzNSPuMNNfYHr6uv9L6xHMifJ6haHqY39eLG+1Rx0g9cpB4uEb0rvZt4VTpy30VeIbd1OK6kEWTjMLcfFM33yRmqxSPkbEb9n2YaUtvFTOTmSeO
*/