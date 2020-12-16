
#ifndef BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/map/aux_/at_impl.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

namespace boost { namespace mpl {

template<>
struct has_key_impl< aux::map_tag >
{
    template< typename Map, typename Key > struct apply
#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
        : is_not_void_< 
              typename at_impl<aux::map_tag>
                ::apply<Map,Key>::type
            >
#else
        : bool_< ( x_order_impl<Map,Key>::value > 1 ) >
#endif
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED

/* has_key_impl.hpp
J36Dd+LvWBNd2XYvrIx1sDp6YwDWxVZYHzuiD3bFRtgTfTEGG2MCNsFx6IcTsSlmYjOcjs1xJbbAJzAAN2IgbsZWuB+D8E0MxlPYBguxL17AfuihtAPCGjgAG+FA7Izh2B2HYD+MwBE4FKNxGE7F4TgDR+CjOBLn4yhchlH4BEbjJozB/RiLb+MYPIpxeBzj8RNMwAs4Fjk2LuOwFiZiQ0xCX0zFADRgW0zDzpiBPXAyDsIpOBQfxAfwIYzFqXKdpI2YlM2yz/J74qvkA1Q+2fJ78qj8nszHBrgAm+NCDMbF2AlXYE9ciSNwleTP1RiPazAJH8c0fAIzcB1OxQ24CXPxDXwS38an8ShuwuO4GX/EZ/Bn3ILXcKvkz+dQaSe6DWvhC/K78yL64nbsgnnYHV+W36FXcBDukPQJrCTlu1Leq6TP0/ztJ/WvWXJfOBO9cLbcv81BP1yILXAxtsIl2B6XYm/MkfvG5TgCV+AUXIUzcL20J9yAWzAXX8Cn8BPcjG5K2Rx64PPYDl/AzvgiDsXtOBJfwTG4E8fjLkzD3Uo8uAeX42v4DO7HF/F13IVv4IeYr8SPb+If+DZWVq7P2AHfw6H4vhIvHlbixaM4GT/AuViAj+GHSnz4kRIPHsNDeFza73+Mn+MneAk/xav4mYxPcgqD8DT2xEIci19iMn6FKfg1ZuA3OAV/wLl4HhfhP3ATXsCt+CO+iD/hq1iCB/ASfoi/4Em8giX4K17B37CaG9dpvBtdlHaXboBtsSKG4m3YB2/HgVgVI9AdR6EHjsE7cBXWwHV4J+7AmvgaeuEBrIXvYm38DOvg9+iNF7AuFqMPXsIG+Ds2xLrk6UbYEJtgR7wLB6MfDsdmmI7+mIkt8FkMwB3YUokfA/EDbIUfYhCew9ZYgm2U+LE93s2DVifsgiEYhp2xL3bBKAzFMdgNx2F3nIg9cCaG4XzsiZuwF27FPrgb++Jr2A8P4H34Ng7B4xiBn+Ew/BpHYRWeS6PwDhyNtfAB9MFobIJxGITx2A7HYU9MxH44AcdiMs7EiTgXDbgCJ+F2TMMdOBWP4TQswul4AR/Bn3EG/oYz0ZPn7Fnoi7OxCWajP87BUJyL3XEe9sYFOB4XYjIuwnm4GBfgElyOS/FxXI7rcSXuxNX4Gq7BL3AtXsR1+Auul3asHFcpJ+dclt8VP/4OQOWzRdrJvog1cTvWwzxsgi/hvfgKtsVd2B334UP4Os7AN3AO5mMuHsCt+CZux7dwNx7EN/Dv+Bm+g2fxPVSeF9/HyngY78Ij2BwLsD1+iKF4DCPwOKbhx5iBn+IUPIXT8DSuxs/xcTyLa/FLfB3P4dv4NR7BImlH/Z2kH88VUtbNNVnuEwfwdwbTlc+Pkn4lkn4XJf0uSfr9Iul3RdLvVwxBl4qcV1ABB2FFHIqVMBarYhK6Yxp6yHNNNXmuqY4z8Q6cj564HO/Ex7EWvo918EP0xvNYFy9iPbyK9dFV3rdxxwZYB5tgI/TDltgUu+Df5DmmGQ7F5jgaW2AmBuB0DMRHMQgXYzA+iW1wK7bFd7A9HsaO+Bl2ws8xBL/CLvg9dpX3cLphIIZhT+yJ/bC3PLf0wRTsi/OxH27A+/BpHIBbcCDm4SA8iuF4DO/HEzgYCzECvTjuw7EeRmIbHIEdcCR2xVEYhlHYCx/AdIzBhzAWV+AYXINxuAHj8Wkch89jIr6ME3AHJsvzSqKLlIHjbOU7f1TFKBf5SLlQRSl/csX66IZBWAkH4G14P1bGiVgVp6K7lAN5oLRXp1zb2v692EW/XXuek/MVyHy1dOYrYIJvpnuZ2rf/p4+xdG1Pxf/KcZbc9praeLfneEQQMgg5hDxCAeE=
*/