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
nARo0wv6bHw+TIn/jats4P/5VNv4LeiPA/T8w2oRA35DjpY8/IB1DD7VVA2dGFkF7rrgbiW4czjJXV7nnwC0FhLCqQIKo+8eTZCCOWg7Fcir7EpPW2r5evlKLl/Tzu+LZyZSlTfaFSnl9zCbUP9Z/e3sNUsHBl6ExoXkryGWzXgElvPgiLQ8N4El2RCgh994NwCTJq4nmZ+5HA5yO5GcvRAht/h9GvK5HrLsBOqDj+xbPGWJPB+0L0yAUsAYaWG0AHyCghBtdZ6wmaqqFFRVIUI9jJEWRgsgplsAQak6n35vsgM+FrQmdI7UARIXtZ4wn42TiQF+wBSXcmc5TRXQfF+afCNlvpyppn6FoMbUUKg5pOXh69wT8TvsdHV4FtcqVqoZlc37IAlozTLwnmW0wue6J2I9MC8KwOSSJMS7ZizJAxXp+ZN86K2nMKEGk01qMJmowTdZNRgYNRh+WVYNbFOjVAMi9kGT2MvS7XGCVpjlPUjk3fsgSQbVCFYugIxWqEnSELM+/Ej04RlSjQOKBQEjljeFUCFICN0r+o8nAEd8cRBllg9HRHvbjOX55dzs9Xdctdr528sXJJxAYYbK8JHJWYjlMTNUhhZED2OkhdECyGJZRsQysEJR5eRUkTGlgXir9LuaHfBd8F9II8a8UsJvZB4gG8kAX/eVzVKY6nOYVRSm+b40+UbKfG2m4GLFomYhocYhh/15Av9+u90Z/4p1Kf39Bvzg8bmobzAWwFyDf5HdO3Os4XDwma0Q+dE8BRuO3cpAPrDgILZ2gA37wPYhKaGBsA1CA4DRDrBhH9gmZHhG1OBpsA2KPOKnSAulB5yoemdPY75io2CuHB+Z7DayPMZTOVauhzHSwqQFYNZPlWe1fjoi0sJoAcAzsOxUCMibWWSbXU6sY5K5DNGv9HdACO/lOWazGDJ5JywhYHXfmqjxaGIkNTH3LU2+kTI/VWaAV67P96XJN1LmazN7jiQLpCCGS70z33IxSSWv418MwI10BRZ7hVtHMLLQKwyQ2d0wToPCEKPK8545wkkqO4A8k4XcT0N98faZp9Y/V0jWcxfEl7Cu7jbJgiQD3TYEqduGQFph/GlhJG3otqFS3TZUU0WEgBlQOe/pyMp5Kjk3cz4brTKAJJlv1gR2AQ17gLagAnYJDNglMGCXwEB6qJ4SlbtQHbYxCmNgwg6wYR/YPiSPc9ggFGMVdoAN+8A2ITNwF1qz7oIEkJGZfL1NMpMgQmAZKxdYQxZVNPl/bzLL+SZfEN6eoxOuwlNZEVxWEdzpzGUQwYRP1pTwyZoSPhisE9WhD1ZHeqiO+GAlzAerIz5Y40bogzVzH4x1c3cqGeiWBShNvi9Nvj9V/uiUmWkqH52mcqvqWmUaNp3bHXWr7Y661XZH3WpbUFV2CayyS2CVXQKr0kMtJFAOBs239fN9xDwyDgrD5w1yHCZkjcOEWPyl4ck5xV2Fji8fL3Q8Q/7uIH9t5O9A8ldD/gLk74xFhY6DyN+W5G8U+csnfz3dhY5F5O928vd89spe2St7DdAl7+KAXSqF0zGqajovq4FkJIbnoCmvnp2BJZtAKZ0FExHFjE4wrGQNebg7YR5Xx409BNJNIOXwwBo0oxR9jaj7Lj9GU+RYeXsX8QGm7QRf6zqVD36JjAN2xQxizvsgicfoeXbtHrzcRB6fF3mBfXheqJ0VZy94VRBwNyRL8Q3pWDcgeHJ5OeGm4gmZl9VMvGx0p4aXu3fk9YbNvFy0C8+oTWLkxN15Xl0SI/vuzfPq2WsEYTehupLAVkCa/AYOPzKMcxEgXFSauFjFxMVRd2i4+LKeV9pg5uLlyTxjchIXDzTwvL2SuLhkL8xjMdQ=
*/