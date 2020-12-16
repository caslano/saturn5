
#ifndef BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/erase_fwd.hpp>
#include <boost/mpl/map/aux_/erase_key_impl.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct erase_impl< aux::map_tag >
{
    template< 
          typename Map
        , typename Pos
        , typename unused_
        > 
    struct apply
        : erase_key_impl<aux::map_tag>
            ::apply<Map,typename Pos::type::first>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED

/* erase_impl.hpp
8BlMxS04B7fiWnwOc/F5Od48SshzpvH5k/Q1lbcmy+/p3+V4H8JaeBR98QP8GxZgAJ7EYDwldd1nsDt+IXWfhTgCz2I0foUJeE7q7r7GdPwGp+K3OBPP42IswafwotR9/iJ1n1fwdbyKb6ML+3VUAT9GVzlebngOb8PzeDv+jJXxIlbBa3iHHE9P9MQacjzvRG+siY3QC5tiLbwX62AbrI8h6IPR2BDTsJEc58a4GZvgC3gX7kI/3INN8QP8G36MzfAM3o1fY3P8HQOkz/d70RNboje2Rl8MxhBsi5HYHqdjR5yNnXAphuBq7IxPYyg+jz1wN/bCT7E3nsE+eA774VW8D5X3mAfgXTgQu+Mg7IPhGIGDcQQOw+k4AmXsDHn+5NyV64167Ix4Ob8TsC6Ow26YiFGYhGNwvPwuTsB0TFb3Kf2wuc6WdZfWp7TMV/c688XIfLV05iN9lL6nr9vvtLP1v9KvtPo9VHU/0to+pNX9RVM/7LB/aOkbWr+++DhB28dzbrGpX+cIgrn/5kWETQRNn83avpot/TNHEDLN9cxIXbP0uWzb1zL9LEvds36/ytKfstRDW/pOtvSbrNRHF6KjfpKnERYRVP0iq+uspd9jHGrX17F+P8dSjx3Zzdy3saU/Y21fxtKPsbZ+21GfxY77J/b/xM3SR3EJllYPHiV14eq+hfcQTkj9eBFeJkRMpr9fQg5hB6GAUELw5oG+PSGKkEFYQdgx5d9Xb/6/8vmL6v/jE25C/b8yfuZFpU4jgWcMpXQ4aAzVDqax/1ep2gWskfuyCYQ6hNGEX1guvIemLjI+KMlcbubr5HiQpZVpn1PqAFJcLOVod0rdhbY+Tj22oYHCV2PdipRpd6+vPOfb1vNyOhk/wwjVCIMJPsxX2MO+nQO7dN1+Bm/GPijfvTXl9D6aui5lHl8ZWyXVQFm/jOFcj21neEnbPqOmSP2t7HOJ7HMjgiuhAeGycgzDrPssOcDpemTZVlU9kjww84mWtB1FuEI8WaZ4TM0ZEhPiJkQnpMa5ON+HozodPTTpeE3qS0kXm23xlLb6laVOyw2vduKPntptMVYYXLdOy3SckQ1OZQl1HXKGMo3EUNch+yrT5NiZj7fBTdmPsabjLd/j0k3H0kezn77W/USOtbk9fqaBmEx1FP7WaRKTadkATT4JVOUT9djJBlauN/Z3kaTrJPl+WZXO6vJ+ZWu09a6yNTZtCNpLG4JXpW55J/7G8cjprToeqcnJCXEZ161PNueL6FrG+k2nzzcDgfR36nxTj5sen2DISES9tPuDD+tWjqVxnt/5boqL2GSeYt30tK2D95G65yel7nA9Kten/L7WdOK6pKmDd2ac+0o1QgYY73Pp6NK565bkZVS+G3f4lly7JD/ZpetvqnQ1p7P6GBar6ihrq9JdeV0hWhpQ6NX9l6jSv7rU382T/OSgHYacE2yjqs1FCHnam0R8hWkD+kldoJxLvsq+qs4D9bngXdX8bMExFnsq1+OBNu1p4oKSnBmr2NSeZs/91vY0Pw6ybztzZJD9u0FLB9m3p4m0TrO00Ws7yL6f2sX36+cl9bVRm4aeKO0QVG0c1O8UWa6N6uMo10jbfFesGUf+nCo/2LavmWhQt6XZWos4k6zbdE3TJ2aRtEdLlZ1RjrUvO+hW1fTMuXuQ6p01Tdscc53vloGmeX7vZPu7VCLHfohcBwchhW6MO2M99mMZVJpWnvHOtK1x5jfSU3Xtc3QNqydpMNn0W8IlOIH4+Yl28tplrtc8J/Wa3lXYN5FrFwUGDt+hjDfn7wgn8ve00db8nR9p6RPZ8j7cq8PM01pb2pDNsEwLspwH2UPt37+8FGF/vjQYreo=
*/