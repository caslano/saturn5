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
rugTzAwOmLvnOoHZO9F54c8LUEnx+mTtk+5MOE1OieqMQwwPnRiYk73JqaxgMKDw5u8wa3JL7IZj5U7ZbXTMLsNQSqtw93bHPcGeo4Ob3fymwpqWTT23IcopMOp0ZkMYYWRGswkNmAskkRf+Vpjp7hf3veSlsVXTYu5K7QUMOlBf9slCf2pk4FAvjfyGb5SQfDJTl4obkgwZx+i3zHEjZeZpuDjmriP5+6Nk9ljMXXMeCBXLt3msh2ojBja5g7ViLzDK3fbNEJnbYRXsLfxuJtPARq5NWIjGJWLjBTdRDuaSdtzFHDgDxhd9gnXroKY1sjeexmypToCmUX6PgLwUnmfmu3V2xlGOZrftzNFv4T6SyMfGs1WwlYiaYtU9XB5OE2i8M8KW9wQrzFMkHoGy0rAJp1qMMzq6tCmqMcsb9Sx8Q2p/zxJxN58muGN41NpCZ9ASx5w3FnOvNlyoh1sFJUNKbpVKKclpWytMqY9OoAizDlNjI7lW7pcBaX/MBSOND7pULmn+nXGn3PTGq8fY8xks/y4wU6vKhmKKUcDst870lNNPdIbFVFWFMvzK3owtfQ7y/tEL+VmseOK3nymjHCGJru8wfoakY8KdrWJSY2VKKMe8xqpiUhVVM5WrkopZ9629mz00MF+PfCwu
*/