
#ifndef BOOST_MPL_SAME_AS_HPP_INCLUDED
#define BOOST_MPL_SAME_AS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/not.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template< typename T1 >
struct same_as
{
    template< typename T2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : is_same<T1,T2>
    {
#else
    {
        typedef typename is_same<T1,T2>::type type;
#endif
    };
};

template< typename T1 >
struct not_same_as
{
    template< typename T2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : not_< is_same<T1,T2> >
    {
#else
    {
        typedef typename not_< is_same<T1,T2> >::type type;
#endif
    };
};

}}

#endif // BOOST_MPL_SAME_AS_HPP_INCLUDED

/* same_as.hpp
DF9GI1jfi2/KYQjxET/D6Aoe6IUT4xGML8PLq5Cv3H6PRQsegm91YJtApmqPYkalw9IN4rpCn/7tZOYOhVgcy7IeZKiSEJiWH7AnqwuyyGBuMGskhZAS7ZSZlOqA1x8SFjWVSat8Uhm0zHItWLCX5IV3Eln5rMh9C61y3QR8oe1yKjLnKr7+GkLkuaZi9vS4Wm/in7P1+v5uvrrbxkzpwBEEjc0BUAoKbKYMJtD2AbT7hdoxhmxBIkdUTEWR78ZXo6/M0saRpsNBlUlLHkp5vlxv47tNeO6936wfY3lCeVKlk13dWwF/dgJY2A80eVpDM0SVOjTgMmxmAJmysEMsIbAZuUBEL81dBqgMOdK+jdt5DB+I4HX0fbEk60L4p6++uNEaK05dyIu+6HM/73hRmhcIXvkkKOhZdmvpkQM4UMLHfgF4xc7gAZ3VqsKGEtqhwoLrOedNseyKPppiaFEmpK30h4MOcdis0BnEWW6hIT2x3Gcs0fCuJrCrgS335Z9gnuQOlIOajgboVILJ7X4oRCett7hZbee9Nxu6eNT7e7963X79t6jd1p63gJ3xnfmJvVkv3//kP1BLAwQKAAAACAAtZ0pS4ACA4rIBAADlAgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEv
*/