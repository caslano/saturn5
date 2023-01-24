
#ifndef BOOST_MPL_MAP_AUX_MAP0_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_MAP0_HPP_INCLUDED

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

#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/overload_names.hpp>
#include <boost/mpl/aux_/config/operators.hpp>

#include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_USE_OPERATORS_OVERLOADING)

#   define BOOST_MPL_AUX_MAP0_OVERLOAD(R, f, X, T) \
    friend R BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f)(X const&, T) \
/**/

#   define BOOST_MPL_AUX_MAP_OVERLOAD(R, f, X, T) \
    BOOST_MPL_AUX_MAP0_OVERLOAD(R, f, X, T) \
/**/

#else

#   define BOOST_MPL_AUX_MAP0_OVERLOAD(R, f, X, T) \
    static R BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f)(X const&, T) \
/**/

#   define BOOST_MPL_AUX_MAP_OVERLOAD(R, f, X, T) \
    BOOST_MPL_AUX_MAP0_OVERLOAD(R, f, X, T); \
    using Base::BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f) \
/**/

#endif


template< typename Dummy = na > struct map0
{
    typedef map0            type;
    typedef aux::map_tag    tag;
    typedef void_           key_;
    typedef long_<1>        order;
    typedef long_<0>        size;

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
    BOOST_MPL_AUX_MAP0_OVERLOAD( aux::type_wrapper<void_>, VALUE_BY_KEY, map0<>, void const volatile* );
    BOOST_MPL_AUX_MAP0_OVERLOAD( aux::type_wrapper<void_>, ITEM_BY_ORDER, map0<>, long_<1>* );
    BOOST_MPL_AUX_MAP0_OVERLOAD( aux::no_tag, ORDER_BY_KEY, map0<>, void const volatile* );
#else
    BOOST_MPL_AUX_MAP0_OVERLOAD( aux::no_tag, ORDER_BY_KEY, map0<>, void const volatile* );
    BOOST_MPL_AUX_MAP0_OVERLOAD( aux::no_tag, IS_MASKED, map0<>, void const volatile* );
#endif
};

}}

#endif // BOOST_MPL_MAP_AUX_MAP0_HPP_INCLUDED

/* map0.hpp
rW3dOsqJGLx23HkmC4n6Yn3kKZwAHUxy3zKAxecNNSxo4ddF7ic9PjYYXdGSPXWOuMZwQUejn94sZ1GVir4tsC1WRaI7jOscgOlh+ueUncPRwtE2/l58avrCR+tdQ+sA0PQ+r/5KCPgePj9QJqNTaJM7x7RQj/KYKdnKevVnbXOR9AqS/Fdtv/nP2pY2szZzMDUy/Edpgx12QjJjmEITDBdDQXFyHxMkL2Q+5soNMpz5CS3lSl4xDYUy6Ki6yNqf7J64uSgSwSfTngjbis4MWKe/ESOqE1NBLwrpMguFxVYAcWvBRKZI202St5+FjUSXcvksd6Jq63sRxsbQdpn0M9M8KZ+RbhuXvZORVv6ztuTVlmQwLEjeBrlosbyeHXP92+xE2S6mBqjDgEPS/NXMj13N4eFhGo976KELixf63UbDaDktvNEhcx7lRgxt4ikvymiHuy5apVLgEytUDV92MUrbxOXxMuS+HVz0a8KbAXTB3M/+yo2atZ+bieLkNQcyU69EODJszEhgtMP93QFO8Rc2VO7zCEbVMNiGV8x+AZmRKX7us0X6CX0KCvXv2z8iPYvDYW07rBoOLJOLKPh3ht5vHxZ9dyayNyZNdw045EZ3DDwVzgWVizwpPw/EAieQ3oWcMA3D0csSGqDL0M3KHRbmHr30XUhQ+wvRWkzK2lJxb9K3h5zR6xCixbZ39+EVUiL5LPHj0+v8bpeQ
*/