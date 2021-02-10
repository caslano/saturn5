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
VAtSe1my+oTWVda4P7Z32nbhevZyNn89i+a2x/Mm6ErLhEE4mZA/Dee4aP2w/JvgaQDyuDS4nWbWQAF+WU/CVT/p/AVQSwMECgAAAAgALWdKUpLoClUOBAAAxggAADEACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0lPQ1RMREFUQS4zVVQFAAG2SCRgrVVhb5tIEP3Orxj5pJMdUZw0p8v1klRHbNJwccAC3JwlS2gNS9nrmkXsksS69L/f7IITxanUfCiRA56deW/27RvsrAZw8NMuy9Fw8MMrNZ8UL7zviuaN+Jdm6vsFafoI3R8WrvD+BqoxPFc9piN4U9UjDE1V2nOd6ec0fQPdSjep/4118SrVjxjpKvv6iai3DftSKhhORnD04cMf8A7eHx6d2DAlFaMcYkWrNW2+2HCWm8hfJXl4cCT9aANVQLjzAjApmQQpCnVPGgr4zFlGK0lzIBJyKrOGrfELq0CVFArGKUzC+dIPPtlwX7Ks7HG2ogVZipbnUJI7Cg3NKLvrYGrSKBAFIiB+zqRCzFYxUTlIT0HRZiN7GN0E4VIAuSOMkzXSEQWlUrX8czzO2objTsa5yOQ420nhlGqzt6sldrMhWxC1AiWgldQGnW/DRuSs
*/