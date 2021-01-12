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
nF5G/O4R832tzu7xi3uu9YUJ/wfyvJoJf8pR6S+4znslofpYzHeihUkuc++lR9ypKV8XSh9G4zFwHneUxp3HXHQwr47oXmxxkwd34Wp4GH/XPuoSj9JwuMSl1p0dxM5iT7wnxS0ucbOs9kH73WLmr9wNM4tvlMq5f/t61DVNTJp2k+fXeXye1DLz7tvHtA7Uuq2L2JvjudmeZkV5Kpk03XI8OAeJOaOOKXV+qY+409HDl+0e
*/