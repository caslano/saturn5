/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_FORWARD_MAIN_07212005_1105)
#define FUSION_MAP_FORWARD_MAIN_07212005_1105

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>

#if (defined(BOOST_NO_CXX11_DECLTYPE)             \
  || defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)   \
  || defined(BOOST_NO_CXX11_RVALUE_REFERENCES))   \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_MAP)
#   undef BOOST_FUSION_HAS_VARIADIC_MAP
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
#   define BOOST_FUSION_HAS_VARIADIC_MAP
# endif
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# if defined(BOOST_FUSION_HAS_VARIADIC_MAP)
#   undef BOOST_FUSION_HAS_VARIADIC_MAP
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no decltype and variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/map/detail/cpp03/map_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    template <typename ...T>
    struct map;
}}

#endif
#endif

/* map_fwd.hpp
w774LPbDL3EA/oCD8HbqVyj2wDDsi8NwHA7HeByF9+FonIL3YA5G4Coch//CSPwKo/BrjMYOyv4fe2IcDsGJSvwYj5MxAZ/BybgbE/EgpuAHaMJzeJ8SL6ZhK+pXOrbHDAzBKTgAp2Ea3o/34wxcgA/gEnwQ5R1p0paEdSvfKfU70mYzX02cg40xG9vjXOyC8yQeg7u0CZG2Ipa2Tj6oDIOovwYMxTYYhik4HGfiCFyCI3E9jsI9OBoP4d14EsPx3zgGv8Vx+BuOR2X/GIW1MBobYCzegROxHU7CrpiAA/BeHIGJmIpJOA2T8XFMwacwFfMxDQ9hBl7AKfgtTsOf8X70ovzTcSBm4VCcI9ftTrlJuxIYK+tJuf94RNb3Otk/PIlGzMUQfAoH43ocg4cxG9/G3XgEKxPX++iNx7EenpJyn8Z+eAaH41lcjR/jevwEd2KhlPNf+Aaew+N4HuuS38/xLvwCw/BLHIX/QTmfk3Yn7PMcnM89LvvnlbJ/fkLOu1ZjNq6V/fM6fByflP0qZZK2H5zjyXpTmgp7SP3a40W8+DIacS+Owf0Yja9hPL6OJjyA9+NBXIdvYB4ekusch/EQvoWf4tt4C2m9g1XwKNbEd9GABdgc38cQPC7XH0/gCDyD0fgxJuIneD9+iq/gObyCn+Nv+AUqx8sXcBB+hQvwG9yC36Jc55G2Iux7HVzneUrWy3pZLxswGDfiQNwk11c2YxRuwSW4FffgNszH7ViAz+Ep3IFepLUTG+IL2BR3Sb4y3aT9B94h+arK34mSr/vk+lMqGjENh2A6jsIMTMIpmI5TcQ5m4js4HesQ50ysjw+iAbPk+hd5l/Ya/PZL+j5KeST9HyoxP17CNvgjdsXL2Bt/whF4BSfgz5iBv+AM/BWX4G+4Bn+X8+Zr+DK6kY8CqICn8RYsRA/8AivhT+iJnuTNC6tiZcl/vpu0t8DnJf+3u7F+LfefZP1Vl/V3Gwajt1y/qynX7+rgRBwl63M0rsRwuZ47BrfjWDyFEfgVRmIP5fgHh2EsTsA4TMRJmI7xuAgTMA8TcTsmSTn4zkm7C5aV/UEVjJByuCvnbVgB62El9EdP7IBe2AMr41CsgnfjrTgGq2IUVkPjLRwncaHSl4YS7QlhhERCDmEjIZ9wlnCF4MOFTCMhlBBPyCbkEvYSThEuEby5yBlI6E+IJWQR1hD2EE4QighVuQAaQOhNiCLMIKwh7CWcJVwh+HBx1LYv8OVsAPU7QRNDPKzvBS3a5umwf3B/NpJtH+He2z01/YQXceLsqK/wjWzYzizvqM/wvZzQnT/nodt3uLGGV7n6DzeSl1h5Z2cm5cnjIv3e0x6afsV71/C6rr7FI4g7ql3pfYyH2rxrMyra066v8XRlXATrsT/rhrykE1YQdhFOEa4QfLmI3ZkQTsgkrCTsIZwlXCX4cXG7OyGCkEXIJeQTCgluPmxrQjAhipBN2Eg4SDhP8Lqd+kLoT4gn5BDyCIcJFwhVa1PnCKGEREIOIY9whHCRULUO0wmhhETCYsI2wmHCBUJVX+In9CfEE7IJGwkHCecJHnW93PwJwYSouq7+1l2Da3ANrsE1uAbX4Bpcg2twDa7h/234w/v/j02YFJeWrrwA4Ib6/1f68m7Ahd0gSx+Tcn33VXm28UXCOwFu3ITwsfQz19ucslvZz75ans+r5C3PHEZrn8+T53vk+TPLMz9Jsern8zPM49IS7o9TPddUU/ssV7xyX7qW+RmmJFNiyfNKg22ef/LXPHet7V8vTO4X9iP4EXopcRKJqYNNufsmJEcnlr/stnno76CcYQ7KadDkVdvXoEFeknhW8vqh5LXAYV4j4zKd2FbXm18=
*/