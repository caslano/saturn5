/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ACCUMULATE_09172005_1032)
#define FUSION_ACCUMULATE_09172005_1032

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/accumulate_fwd.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>

namespace boost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template <typename Sequence, typename State, typename F>
        struct accumulate
            : result_of::fold<Sequence, State, F>
        {};
    }

    template <typename Sequence, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::accumulate<Sequence, State const, F>::type
    accumulate(Sequence& seq, State const& state, F f)
    {
        return fusion::fold(seq, state, f);
    }

    template <typename Sequence, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::accumulate<Sequence const, State const, F>::type
    accumulate(Sequence const& seq, State const& state, F f)
    {
        return fusion::fold(seq, state, f);
    }
}}

#endif


/* accumulate.hpp
nNdvJ5P+k3ioj8zE982TW53XysZTzevz1/zv83rxif/jeXXN0eb1yu4h8+pWz7u/tXnddXV75vX61Dbn9cF7cC7vFw/1EuID7r2n1Xk99/NTzeuVV0ea13hz6Ly+FIm+Qo20PX8mIU9WgSvxcUOb8/thS56soCVPtlP9fpY2v7+kEk82j3kyCqS7QErRT9PORUiJTAmMv6o98/59lzbn3Xo38b/ioX5Shu9/3YXzHmaHDNP+/uY25YM7C0LN03W7SzjS3La6BxfBRPnioPBzBe0REPbtIs0w9RsR6viYu0JsuulOygAiCYa+2uq0s32b6Ow2aP/sAuJ603W1lvRsW90H2EXXkJMoBPRhfz9ehDK9rUEM4pehy/QyVqUaRXB4Us5AQPCeK8piXSiw2xShtCg7hsRz/bQlnT+6PUtqtdOklMCkeOSioiD88km4hJmTQuXhxr1z8NNT7R3raM2ifDPvHljHPCB+fiB1H9pEXdzgLe+BkE10BSKnKYLsUB87ivip6JT4aWl7+b/pOv9nR/w0WeAnD3ZNGV7kIswkiJ3tqP8zilc4kHCKCf2oU5t75Jc7cFL/LR7qs0Q577qjVdxU03Cq+X0zv835bWrv/F7c3M75fa69+L9Mx/+dcX6niPmdil2z1Q2fWBw2w9/ktXeGbzytzRmuLsFZnSse6lAi3b0lLWyDaX4zNunzqymthRmB5+WF31Tk+kel
*/