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
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
*/