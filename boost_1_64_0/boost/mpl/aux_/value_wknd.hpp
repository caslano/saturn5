
#ifndef BOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED
#define BOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED

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

#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/config/integral.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if defined(BOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS) \
    || defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)

#   include <boost/mpl/int.hpp>

namespace boost { namespace mpl { namespace aux {
template< typename C_ > struct value_wknd
    : C_
{
};

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
template<> struct value_wknd<int>
    : int_<1>
{
    using int_<1>::value;
};
#endif
}}}


#if !defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
#   define BOOST_MPL_AUX_VALUE_WKND(C) \
    ::BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::aux::value_wknd< C > \
/**/
#    define BOOST_MPL_AUX_MSVC_VALUE_WKND(C) BOOST_MPL_AUX_VALUE_WKND(C)
#else
#   define BOOST_MPL_AUX_VALUE_WKND(C) C
#   define BOOST_MPL_AUX_MSVC_VALUE_WKND(C) \
    ::boost::mpl::aux::value_wknd< C > \
/**/
#endif

#else // BOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS

#   define BOOST_MPL_AUX_VALUE_WKND(C) C
#   define BOOST_MPL_AUX_MSVC_VALUE_WKND(C) C

#endif

#if BOOST_WORKAROUND(__EDG_VERSION__, <= 238)
#   define BOOST_MPL_AUX_NESTED_VALUE_WKND(T, C) \
    BOOST_MPL_AUX_STATIC_CAST(T, C::value) \
/**/
#else
#   define BOOST_MPL_AUX_NESTED_VALUE_WKND(T, C) \
    BOOST_MPL_AUX_VALUE_WKND(C)::value \
/**/
#endif


namespace boost { namespace mpl { namespace aux {

template< typename T > struct value_type_wknd
{
    typedef typename T::value_type type;
};

#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
template<> struct value_type_wknd<int>
{
    typedef int type;
};
#endif

}}}

#endif // BOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED

/* value_wknd.hpp
yrSjr9fmI2+QO4nJ9EfX9CWEMzUazhlYwpVJ8RjMmAsj927iw0Qxoj93IcRHT8PDY1NAoEUHFLcHATfvAxJTtRGFlSVhwqFA8OTLppXCU5HVQRD5Fp7Cx++c6VIZZXRLscK4F4agrzuZdiwZD5cCjtJt2ouYdzOq9OFscZS4e4h8WZqAvsF76JPHjtDBHkeTo5agvfhnCDrug8fXVeLCtxMBZvVhs38DDkk8pYMsOWA7pkGqZ0hh1bLPWFe2EN0WyIDc0wpcFOBF+zYw80hHIC6RrARtZwHC2lyMbGGtsGL7DTh0qQ3HtjzAN0nG5EZuLPZZZ5Lhsk9wUvUhoQslQZzfCQ8oUbjbfIseDrwGM7aK4Fv7HGjoiATWlez4wT8cVMPm4ZzPgVgb6IxWDnNge/w12PKknUraR4L4IjlyQrwS/D330S4Xb+wvuk57338C3aPv6eLX8WiX3YyHUz+CT99pIlsbAxEsTvTZxTFcfk6deU+P2LlBnEybWo/G91ZS49F5sOj+BrL62hC6OMtjKzcPKPnvIZ/bLuKA6wO6be4F3Dffj2ytuwWct2/TQ6VM/z5YYsLzFLB9Fk9ir86HdMmzJKt1Ik44B8DQ3A3VpkhWxCwArv5cusZFFdvbDsODJXbg3ZpBb9m64oqpMaibrISOwU7k410ZvC51G8PG6WGEdxg16twA+1rkaLEfJyyunE215EzwYrcH0CMFoJE9nbgJLsDe2ex06/NGZNeLoJtnumDchSiqyv8KWzgVSaCPJdQURhCXTAM4weuLB+/Pgulem2g2hwo8T0yGz2FlaLMohGinVWHj+BEquV0QL0pWouhyNjzu/Yg6mzeC8SlNsvdlCNyZO4tc2zwe72fKoZDeQ7jqkAoTWXeB+sBM4nLcAOZFpeGpaBsc9RGl+v6sWPYujLpF6WGVxVlynkMA1u/lprbRgIVtt+D2hHRMPVMLH44JQlejB1n11hIUEllJmb0sim/SJk6POfE5hwDGBpRhnW4+1Tm5Bc57tZP+k9642JcBG202Yc5WA3KjsgIS14VhlHoRXJMtICOPr2Fd336yY8cMXK1qT52jlkC88ExcpkNhb60T2XPEBF61m+KcDjbIKDlIpzx7iEdiN4HD6SEwGJEiiVm3UUgyiIYUXkKJ0E/ApukJIufLqb5bA5D972G8+AiEcOnCHNsOaP54AJPYCzG/9QTaFc4HQ7FKkiB3D7QLeqnCtEAYCJUk1eay4G4TTmfe2QhRX3cS9uAQlBWaA/MPLEL2e64QXVAHkdOc6aCKHN78akckb9RCvBk3ujZVgHvmGDm8zANPKxTD8ltuwNnvD1V1beh+rpeGn8vDlqkFeERkLs6ZX025FbZAJa8QLjE2hQOWuYSlaBbY6T7H8soSfHDaFVwqQ+HEXFNSUuoGe+OHSc/2I8BXPwOqUnbisNRTEijUjkceAo29Mhsbh6eDQz47ap78iBot/TgSthYaDyZAEkcm8sbywPONtcRk32YcmJeJCnIKqHLtMX5ZV4tByR8gtjAaU+keajpvMgRqteP+ADmcsqIerjx5gMOVT8hrtThUiMmhkh1MOy77wWZff7gkKgsdAatAwWgldTUVwEjl98SwaAST8xzJ+JEVqGltQp689ob9ZonEU8kBzPaGQeIdTphXlQ2Nk1PRa1EHLs1+DaZLLuDQpMVQ8PgGYZsOiKvCqZ+4F+6Y4Uw9FjnCqEwfdfP2xMovSfQS876g4kY/nAxUgk/HiohdGgJMCyVCj92QXfgYBI3oYWD5I+AwssKJA6ng3ekBSeQwZdw+g51dH0nDWgccc46jfU0vsWprC7DnrQDXIWXivPEGKg2WU2UeIbRZ2kllXtU=
*/