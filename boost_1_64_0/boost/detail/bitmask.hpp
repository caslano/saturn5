//  boost/detail/bitmask.hpp  ------------------------------------------------//

//  Copyright Beman Dawes 2006

//  Distributed under the Boost Software License, Version 1.0
//  http://www.boost.org/LICENSE_1_0.txt

//  Usage:  enum foo { a=1, b=2, c=4 };
//          BOOST_BITMASK( foo )
//
//          void f( foo arg );
//          ...
//          f( a | c );
//
//  See [bitmask.types] in the C++ standard for the formal specification

#ifndef BOOST_BITMASK_HPP
#define BOOST_BITMASK_HPP

#include <boost/config.hpp>
#include <boost/cstdint.hpp>

#define BOOST_BITMASK(Bitmask)                                            \
                                                                          \
  inline BOOST_CONSTEXPR Bitmask operator| (Bitmask x , Bitmask y )       \
  { return static_cast<Bitmask>( static_cast<boost::int_least32_t>(x)     \
      | static_cast<boost::int_least32_t>(y)); }                          \
                                                                          \
  inline BOOST_CONSTEXPR Bitmask operator& (Bitmask x , Bitmask y )       \
  { return static_cast<Bitmask>( static_cast<boost::int_least32_t>(x)     \
      & static_cast<boost::int_least32_t>(y)); }                          \
                                                                          \
  inline BOOST_CONSTEXPR Bitmask operator^ (Bitmask x , Bitmask y )       \
  { return static_cast<Bitmask>( static_cast<boost::int_least32_t>(x)     \
      ^ static_cast<boost::int_least32_t>(y)); }                          \
                                                                          \
  inline BOOST_CONSTEXPR Bitmask operator~ (Bitmask x )                   \
  { return static_cast<Bitmask>(~static_cast<boost::int_least32_t>(x)); } \
                                                                          \
  inline Bitmask & operator&=(Bitmask& x , Bitmask y)                     \
  { x = x & y ; return x ; }                                              \
                                                                          \
  inline Bitmask & operator|=(Bitmask& x , Bitmask y)                     \
  { x = x | y ; return x ; }                                              \
                                                                          \
  inline Bitmask & operator^=(Bitmask& x , Bitmask y)                     \
  { x = x ^ y ; return x ; }                                              \
                                                                          \
  /* Boost extensions to [bitmask.types] */                               \
                                                                          \
  inline BOOST_CONSTEXPR bool operator!(Bitmask x)                        \
  { return !static_cast<int>(x); }                                        \
                                                                          \
  inline BOOST_CONSTEXPR bool bitmask_set(Bitmask x)                      \
  { return !!x; }

#endif // BOOST_BITMASK_HPP


/* bitmask.hpp
RSbVbW7+wCNsvcK2JahzaFIW1H1wdZzUvTtOsszS8WEsRxFfhay/NX7jdZ+QL9CsdCiF9yVY7pnNV1erxy0rKWjpSFOqNdDpGjVs9p8iWjXIV09pGEYEDPPZQEV7fefT1/0nExPfQPeP47sUMEV18USFWqEa2MgN2sFj+yAMqt6VCzgQdK35IFw6LJFM/DBWuezUohD8NXYeq886XO4OjLd1S6gIF3aup29/7danSpHlQeXhhpv1wCUEDrVSLo548HqP0SauY6UD43dTGvNLHkoEoAjH7qGyrvTZiMBFv6Ts23ViIlRugkvKfhU+SSqK6EukwpBrfzbmFJLoviwEmek962+aVRBcUNpkh7129zyF8kHXeqx2S2jp92eyYmxEI0xD+XWhGv3RZ/1Hcvgc8AgZHgUyTmpr3E8M5s+y8GPNHmcVNqiJJXYFmatTcUT4QejPXE/veRZmIm1V/kfJ20+obibM/6tJ0dhyJZlazT5gKGO+Pf1gJkscywVaul5cVBKRAvbe34v7lqfpsm4A0UUiUtQIEWkqgR7vyh+TGgiENWZAYxeysdqFwA==
*/