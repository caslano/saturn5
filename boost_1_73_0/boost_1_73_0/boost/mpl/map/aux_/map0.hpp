
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
AeaCTMCamW7bHRloNra6+hcDYe1yAWtHDHSNrmHOxBsT7SKJGcKC7dJKFRRNMMriIfoHzg6mYdPC9ohjmcSGOwhGtuEdnNInq563WXTcg/P+7dHTo2x/d7oRv3hplJg9d+S+q1LdI1vjRzZLws3z1hvZlbdZGeF3++BuvNTtLvbhajAAs9Ppgv/0sV3Es13KJIuVjL9o4phKOkRjwbM+ZOy+4Bnbr5lgLUR4H5Z0y+5zfoq00CuPq/pst1sIoOKlKKBI8kilU5XA2hEOaydHGqusNGG5PFkVNR9nr4YoyejuzEnFl4zKUjDldySqneQqdwkBzmnGjrM7uwu0lGsFmkRUJjxXRdqxCrBSndFc6byt2/Q17Wbiz4kT9G9qhMCfEe1zV9e+uqYzdZShLwP9FtollIpOv2CRYFL1P6Oo1xP9RtgzE8mygloz0KVkAhQPqHcO1rSAV8ZyuCrWXF4h/NbUKoid4JJHPFUr0unoYJmB+aCak7CFmsF9mNofiS30P5vQIPZgbk9ti4AS2gQ+wdgm1gR0ePBH4c9fTdCAqf/oL0g9wwtDrJ1pa5df6TdQSwMECgAAAAgALWdKUvOTLl1QAwAAbwYAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4MjJV
*/