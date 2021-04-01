/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ACCUMULATE_FWD_HPP_INCLUDED)
#define BOOST_FUSION_ACCUMULATE_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename State, typename F>
        struct accumulate;
    }

    template <typename Sequence, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::accumulate<Sequence, State const, F>::type
    accumulate(Sequence& seq, State const& state, F f);

    template <typename Sequence, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::accumulate<Sequence const, State const, F>::type
    accumulate(Sequence const& seq, State const& state, F f);
}}

#endif


/* accumulate_fwd.hpp
axwntZoapeje4EohTzgt8Z3XG5RDCU/PE/rbUaLD8TQ1qk6mwAwVUDzk84F2UQm7XrTNEcqEIQkqqCOeFnCwRzHYCVmcwP0a1h2yiYq48ORga7QwRIVctnzkzhBnlp7BXZSiJGwEKL8ZNPvnex4RtsWDYOBllgOPyGH8Qlg3XyvcpRz566oGWMjVYtVLwg0PHL++H4tlYNFQyDMu1H4VBggcPc3LOPzDtHAlN4Mg0xwQaIzoQZE+1V0+aOpBiazMWq/WQmttxyUhwz0mVIZ67y+AQbqg1ouPXl8/h0F974QICaPK0vTMtXN3DN9fpzoDhLv1z2zFphWZ1lp4hwfBqD3dKL8BdWgUkIop5tk1uAoI7WRqk2J6PSDKT5xxcf8RK/s1GBU5IKFW09U1dIEyvkRA4u9OBYeBLhQqiK2P4maoLJPNlr1MsIhDMd2EMgUodoqPkuCDwQR1F2MKs7cz1YTQEd6P2zXu8iItLdDIiebchfJkzg5T99IhaAF9O34LzL+tLhUl4LI9CBDW1GZAuvL/vqRsiR3wou2S+0mr1FxoxFOHiCzyqO9OUw==
*/