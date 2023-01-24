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
WBP4t6qMilGTyzAt+n5kiR933vHtQRvA9V3VeMOjQ84d06useyZZ6dlW9SfrLWxfxXP2IRU3v8XYkn7lixgi7j9QjBgPaa6ICDPVDZwm39QEjtDtXA8cPKyHJoXObTH2OjS8PV/ZGye0aS+7ebDMfgp+9fQBQTxLWZBfr6sfbXxb0Y3SCjV3Al+HDp1LXF0cv6tTb6soJomb41KyftmgJQN59TruKl6szbELtu/y4fFLqy7OLDJfBK/NgC9YTnhL44IZwW/0Ui9W95whd5DxGN69uD23uD62E1w3RLQeSmbB6v0g9yrEaOOCbiphxHHo4t2V9PjY/Qdm2GhsyeVzRaPwCpdzRYKTP9MTZyAxjO9C5AAiUnQzBlfwx2udVQhBfVRD4AVRvJ81n10vOn2DMPZHbzFnvjkIUfotXiv+Il6Z9pmmZzA1PcD09y/WTouOmmNuZtoOJM5FRVaLzmbAU+AZ8LT6J0A/pBsXvIAJ8cEedkHLr7AQhGxbO0fe3G4n2pdS7Yu6Mb4znxm5vqhqqFLTzbo0PGksmEAP315tF9LwN0QP6RU24QsSAcKaiD5ltSc/oSU1gD2y/Afz6AoGeZWmY/xYbo8nRYBNZwP7JoKzOulLZ+Rd76++wKUKOW8XBG/bZrJM9zMvoacB0zkT5oNXHlW3BgCewlnDmYR7eg6ziWq/VSu/UUfRu4jWxtX2QCKBAW4HKk8VTGZ+
*/