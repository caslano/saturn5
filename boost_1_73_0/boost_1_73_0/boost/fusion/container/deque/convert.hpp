/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_20061213_2207)
#define FUSION_CONVERT_20061213_2207

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/detail/convert_impl.hpp>
#include <boost/fusion/container/deque/deque.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
///////////////////////////////////////////////////////////////////////////////
// C++03 (non-variadic) implementation
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/deque/detail/cpp03/build_deque.hpp>

#else
///////////////////////////////////////////////////////////////////////////////
// C++11 variadic implementation
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/deque/detail/build_deque.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_deque :
            detail::build_deque<
                typename result_of::begin<Sequence>::type
              , typename result_of::end<Sequence>::type
            >
        {
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence>::type
    as_deque(Sequence& seq)
    {
        typedef result_of::as_deque<Sequence> gen;
        return gen::call(fusion::begin(seq), fusion::end(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence const>::type
    as_deque(Sequence const& seq)
    {
        typedef result_of::as_deque<Sequence const> gen;
        return gen::call(fusion::begin(seq), fusion::end(seq));
    }
}}

#endif
#endif

/* convert.hpp
u/LUpkharC7IIjXum+2E96Jfeg4hX5fNdNSkGep6Rcaz3z0RajrJ25L1Um6ZYfK/I4v/zxskB72Jn87iv9MO6XaRLDCWzi2Tcb8EK/O596vpZS6O6GsfG9agCQQrlpu/hyUER7WcnPvN6gqVDUfNvmfkXpclSj9ICaK6+KUBJ8xUXhniL8Crvh/geKA9lhsMaSn13CaJe6NRTGXDNgiJ3dU8rUW7zXT+S8bMXsyTzuCkcszFzPNmzGf/c2M+qxzzcRXfqx0RtSmszMX7Q6fnJnC5zk7KaBA46d6gx4r/BSvFdpAjvSHhU0hHIUwlHDOZCNPSVTgQ+r3medefEEQnqWqUUn2Mo9n93QcCkO6RnGXYBE6jE0RrFfVpp1wKsrlsVeZmcTcTjPF/0pW1focUV/tTnTJISQ5KeQFJUXs1s5grAZpldcC/DuAFT/Ce8LNrWMUCtyxSmVqQxDRrRBrwP8os4i5jWWGCfrIUZSOXLJ/NuNqEQ4N7qQtiCd6XFPyQbvp5Dba5zBtZUm95TFF/9CXX5KlIf5d+oAw6v1P2O+KDen5b/LKqk3s2jo+shULRvNi7WkQ/lclbSycl+Zw6X7Wz1BPZ9hrHWSpflvvYdv9AEelNGeebrsZo3BxfuZH1uFHeqZK8OQQ6mCeh
*/