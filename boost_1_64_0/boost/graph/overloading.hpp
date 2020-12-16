// Copyright 2004 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

//
// This file contains helps that enable concept-based overloading
// within the Boost Graph Library.
//
#ifndef BOOST_GRAPH_OVERLOADING_HPP
#define BOOST_GRAPH_OVERLOADING_HPP

#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost
{
namespace graph
{
    namespace detail
    {

        struct no_parameter
        {
        };

    }
}
} // end namespace boost::graph::detail

#ifndef BOOST_NO_SFINAE

#define BOOST_GRAPH_ENABLE_IF_MODELS(Graph, Tag, Type)                    \
    typename enable_if_c<                                                 \
        (is_base_and_derived< Tag,                                        \
            typename graph_traits< Graph >::traversal_category >::value), \
        Type >::type

#define BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph, Tag)         \
    ,                                                         \
        BOOST_GRAPH_ENABLE_IF_MODELS(                         \
            Graph, Tag, ::boost::graph::detail::no_parameter) \
        = ::boost::graph::detail::no_parameter()

#else

#define BOOST_GRAPH_ENABLE_IF_MODELS(Graph, Tag, Type) Type
#define BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph, Tag)

#endif // no SFINAE support

#endif // BOOST_GRAPH_OVERLOADING_HPP

/* overloading.hpp
7e1jFHS3ICjtY8MGY38uGanZalOl/7a6lKj05+tdbFUYcWXt9LRHO10cqdppk9VtP94x3W87tTXYqbcPduo3Su3HG2u89eOfR9K3SridNtU12qnuaM1Om4/4b6f0JoqdFrrY6enIK2ejkx5ttG20aqPNo93a6N5efttotMFGBT7Y6Mxo1UabmTcbVUP3NIJio815Rhs9Nkaz0ZZE/210R1PFRnNdbBRc58rYJ1DyZJ8eY1X73L7LrX3uifbbPosN9rnNB/usHKva53aHN/ukQXcZgmKf2x8z2scxTrPPHSX+2+fzJMU+pS72GV/38tumrUfbHB+n2mbLd25tc/dZv22zw2CbJ3ywTdJ41TZbqr3Z5sQ4+q4Rt80dFqNtzozXbHPnAf9t0625YpvZLrbZG3157TLao11KJqh2ubO/W7tsf9Fvuxw22OVDH+yyf4JqlzvOebNLOXSfQlDscucoo10WT9Tssi3Cf7usaqHYZYaLXS7FXD6bLPZoE8sk1SZbN7m1yV13+m2T8wabWPp7t4ljkmqTrWnebBIE3QwExSZbdxptYp+s2eSubP9t8l5LxSbTXGySHnd57LHDoz02Tlbtse2vbu2xbY7f9ojr72yP1j7Y4+Rk1R7bqrzZYwt0TyAo9th2wWiPLVM0e2yv8d8erZIVe0x1sccd9X6/LQ57tEVilmqL7Z3c2mLrIL9tcZ3BFiN8sEVRlmqLu056s0USdAsQFFts72e0RWK2Zotq5r8tFrRWbDHF9dkz/vfZ4bxHO+zJVu1w93K3drizkd92mGawwwIf7HAhW7XD3Sne7LAPuucQFDvcvdFoh505mh3ucfhvh1fbKHaY4GKHbg3+eRvEmTzZoM1U1QbV77q1wZbv/bbBWoMNqn2wwfypqg2qK73ZIAW65QiKDapPG22QlKvZ4N5q/21Qr61igzEuNljV8J/j/zqP/O/LVfm/t5lb/m9/w2/+HzPwf9AH/i/mqvzfc8Qb/zXQvYCg8H9vRyP/1Xka/zvO+c9/YTuF/xEu/L+X4D/30zxy3zJf5X5HhVvuN+/0m/sPDNx/7QP35fkq9zsSvXHfBrolCAr3O5YZuY+bpnG/K81/7p9OUbgf6sJ9q0T/eF/rkffqaSrvO192y/umRX7zbhrgzHv0AO+8n52m8r6zxBvvO6F7BkHhfec7Rt5vma7xft8/8x4uVeF9sOt7uMa+c/6YR87rFqic3+f+PdrGEX5z3srAeQ8fOM8uUDnf5fU9Whx921Xl/D6X92g/F2ic7+noP+cPdpDrN58NcOG8flPf+P7AI9/LClW+dz+j8m0OxnsIPmW+/l2Vbt/5dhj4zvWB7yOFnO9Gu6eaG8t8J3nkeyV0X0dQ+N79ulyO/pzGzVDPae90/XuAVmobWufwuw3NM5zTah/OaecM9Zz2htM5RTeRzynJ3TlNgm41gnJOe+ca3xN1nSn2wt3f3daWNyDf2s+jnZQ+28el/TyX5L3tmMyGtiPqtGymen73fy6fn5lOL9rtXr8e0K1EUM7vgd7q+bXlZQUVKednfmAUDHYNGqHOXrdt9Nte2w32esQHe20pEhzva+gnxxu7KBz3cn1GbF47v63MHp//Zqnt+MHG+nbcTuVl7U9+83LKwMt3PvBSNEu1875XvbXjJOgWICh2fjDF2I4vzhIcP/iTnxyXdlM4vtb12tPSM7+zPPJbOVvl92HJLb+39PGb3+CBzvw2GOid39dnq/w+tNcbv8ugewhB4ffhCCO/o4oFvw9/4Ce/I7or/HZ2nT9Pds/tRo/cnihWua35xC23q1f5zW2Kgdu+PnDbskTltmaVN25Pos5JJSq3NeeM3O4rEdw+8pSf3LY=
*/