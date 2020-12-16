//  boost/endian/endian.hpp  -----------------------------------------------------------//

//  Copyright Beman Dawes 2015

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See library home page at http://www.boost.org/libs/endian

#ifndef BOOST_ENDIAN_ENDIAN_HPP
#define BOOST_ENDIAN_ENDIAN_HPP

#ifndef BOOST_ENDIAN_DEPRECATED_NAMES
# error "<boost/endian/endian.hpp> is deprecated. Define BOOST_ENDIAN_DEPRECATED_NAMES to use."
#endif

#include <boost/config/header_deprecated.hpp>

BOOST_HEADER_DEPRECATED( "<boost/endian/arithmetic.hpp>" )

#include <boost/endian/arithmetic.hpp>
#include <boost/config.hpp>

namespace boost
{
namespace endian
{
  typedef order endianness;
  typedef align alignment;

# ifndef  BOOST_NO_CXX11_TEMPLATE_ALIASES
  template <BOOST_SCOPED_ENUM(order) Order, class T, std::size_t n_bits,
    BOOST_SCOPED_ENUM(align) Align = align::no>
  using endian = endian_arithmetic<Order, T, n_bits, Align>;
# endif

  // unaligned big endian signed integer types
  typedef endian_arithmetic< order::big, int_least8_t, 8 >           big8_t;
  typedef endian_arithmetic< order::big, int_least16_t, 16 >         big16_t;
  typedef endian_arithmetic< order::big, int_least32_t, 24 >         big24_t;
  typedef endian_arithmetic< order::big, int_least32_t, 32 >         big32_t;
  typedef endian_arithmetic< order::big, int_least64_t, 40 >         big40_t;
  typedef endian_arithmetic< order::big, int_least64_t, 48 >         big48_t;
  typedef endian_arithmetic< order::big, int_least64_t, 56 >         big56_t;
  typedef endian_arithmetic< order::big, int_least64_t, 64 >         big64_t;

  // unaligned big endian_arithmetic unsigned integer types
  typedef endian_arithmetic< order::big, uint_least8_t, 8 >          ubig8_t;
  typedef endian_arithmetic< order::big, uint_least16_t, 16 >        ubig16_t;
  typedef endian_arithmetic< order::big, uint_least32_t, 24 >        ubig24_t;
  typedef endian_arithmetic< order::big, uint_least32_t, 32 >        ubig32_t;
  typedef endian_arithmetic< order::big, uint_least64_t, 40 >        ubig40_t;
  typedef endian_arithmetic< order::big, uint_least64_t, 48 >        ubig48_t;
  typedef endian_arithmetic< order::big, uint_least64_t, 56 >        ubig56_t;
  typedef endian_arithmetic< order::big, uint_least64_t, 64 >        ubig64_t;

  // unaligned little endian_arithmetic signed integer types
  typedef endian_arithmetic< order::little, int_least8_t, 8 >        little8_t;
  typedef endian_arithmetic< order::little, int_least16_t, 16 >      little16_t;
  typedef endian_arithmetic< order::little, int_least32_t, 24 >      little24_t;
  typedef endian_arithmetic< order::little, int_least32_t, 32 >      little32_t;
  typedef endian_arithmetic< order::little, int_least64_t, 40 >      little40_t;
  typedef endian_arithmetic< order::little, int_least64_t, 48 >      little48_t;
  typedef endian_arithmetic< order::little, int_least64_t, 56 >      little56_t;
  typedef endian_arithmetic< order::little, int_least64_t, 64 >      little64_t;

  // unaligned little endian_arithmetic unsigned integer types
  typedef endian_arithmetic< order::little, uint_least8_t, 8 >       ulittle8_t;
  typedef endian_arithmetic< order::little, uint_least16_t, 16 >     ulittle16_t;
  typedef endian_arithmetic< order::little, uint_least32_t, 24 >     ulittle24_t;
  typedef endian_arithmetic< order::little, uint_least32_t, 32 >     ulittle32_t;
  typedef endian_arithmetic< order::little, uint_least64_t, 40 >     ulittle40_t;
  typedef endian_arithmetic< order::little, uint_least64_t, 48 >     ulittle48_t;
  typedef endian_arithmetic< order::little, uint_least64_t, 56 >     ulittle56_t;
  typedef endian_arithmetic< order::little, uint_least64_t, 64 >     ulittle64_t;

  // unaligned native endian_arithmetic signed integer types
  typedef endian_arithmetic< order::native, int_least8_t, 8 >        native8_t;
  typedef endian_arithmetic< order::native, int_least16_t, 16 >      native16_t;
  typedef endian_arithmetic< order::native, int_least32_t, 24 >      native24_t;
  typedef endian_arithmetic< order::native, int_least32_t, 32 >      native32_t;
  typedef endian_arithmetic< order::native, int_least64_t, 40 >      native40_t;
  typedef endian_arithmetic< order::native, int_least64_t, 48 >      native48_t;
  typedef endian_arithmetic< order::native, int_least64_t, 56 >      native56_t;
  typedef endian_arithmetic< order::native, int_least64_t, 64 >      native64_t;

  // unaligned native endian_arithmetic unsigned integer types
  typedef endian_arithmetic< order::native, uint_least8_t, 8 >       unative8_t;
  typedef endian_arithmetic< order::native, uint_least16_t, 16 >     unative16_t;
  typedef endian_arithmetic< order::native, uint_least32_t, 24 >     unative24_t;
  typedef endian_arithmetic< order::native, uint_least32_t, 32 >     unative32_t;
  typedef endian_arithmetic< order::native, uint_least64_t, 40 >     unative40_t;
  typedef endian_arithmetic< order::native, uint_least64_t, 48 >     unative48_t;
  typedef endian_arithmetic< order::native, uint_least64_t, 56 >     unative56_t;
  typedef endian_arithmetic< order::native, uint_least64_t, 64 >     unative64_t;

  // aligned native endian_arithmetic typedefs are not provided because
  // <cstdint> types are superior for this use case

  typedef endian_arithmetic< order::big, int16_t, 16, align::yes >      aligned_big16_t;
  typedef endian_arithmetic< order::big, uint16_t, 16, align::yes >     aligned_ubig16_t;
  typedef endian_arithmetic< order::little, int16_t, 16, align::yes >   aligned_little16_t;
  typedef endian_arithmetic< order::little, uint16_t, 16, align::yes >  aligned_ulittle16_t;

  typedef endian_arithmetic< order::big, int32_t, 32, align::yes >      aligned_big32_t;
  typedef endian_arithmetic< order::big, uint32_t, 32, align::yes >     aligned_ubig32_t;
  typedef endian_arithmetic< order::little, int32_t, 32, align::yes >   aligned_little32_t;
  typedef endian_arithmetic< order::little, uint32_t, 32, align::yes >  aligned_ulittle32_t;

  typedef endian_arithmetic< order::big, int64_t, 64, align::yes >      aligned_big64_t;
  typedef endian_arithmetic< order::big, uint64_t, 64, align::yes >     aligned_ubig64_t;
  typedef endian_arithmetic< order::little, int64_t, 64, align::yes >   aligned_little64_t;
  typedef endian_arithmetic< order::little, uint64_t, 64, align::yes >  aligned_ulittle64_t;

} // namespace endian
} // namespace boost

#endif  //BOOST_ENDIAN_ENDIAN_HPP

/* endian.hpp
WnhB0VL6hXVchI2z028WworJBUrdPaKYacsLKFi3VAi43kK0xmNVwEP4OCxR2tqBGAQJSx3CbSOh1oIyGIIjd6SmjhBnCWXQK9iQThcC0CECfmEp7f0lXskD1f6y5t3HCvH8FhDw73rGpdEjqX12yvb4i97rCdwetNXwdKBl2Ko2C7/w7U3BzvZWsGjq0lflfFLLpfppwF4qTn00lSqgsT5uYfSeL9jqMEGZ13LTjf+Ca7lP7eP4/jH/n2mWymDLhVHxCpGwLnu3bpOHvB72E6WEylIc/8Ij7zbK7ZR+9z8oPa/D9e36buxMfOKC1NAT7xN6WHHB/eiWJdI2QO0zaU+rNc//TvLfVDx8D8AXDJhgWmh6/RJuleRLAIlWQ/xwFSLEYvGnLVEEVqXhKHztJbHhPbH3lFTQ8oSHgpYjopfEhvfEHlMmmlOGCsN+hUdxuVaoPYgdfcnVC5TZDq5cmXgUqPiND1ynMiKeMY2RNU3WBFSIUpdClFL+jGmMrGkyJoDfw7GEI2UJ8YgIE9Oz5nABEy2vCcZVgB9TYYB4oyWNjINgo2dmqA7Gkb2Qgi4JXk+S4PWyBPUUH8kSb7jGZ4zk0srSlGP93EpD8ZEs8YZrfMbI9OyPuoUD+X+ULHspQJyKx55t5LONbbPU6Tfn2CsyIfxEvISQkhJb3LySKw8VOxV4hi3Yb+6Ac8tlS+vOG4I6Nd107gbJLbyg8UCnB0bq9MCQ9jTRrGmwVirCw5Dq9DA0nQrBafqUz48t6OdzNz7Xm0LJEkKSntO3bBOvCQ1vCT2lKvdawHKvBSz3WsDy7KnSA522C7GEh1U4hizvJbHhPbH3lFTQyoSHglYiopfEhvfEHlP2YrvQ9HnZLvSYoT4X+we3abIEzgL0Usdwchop9px6tkoOLv9M59DPesosw9ElV/zK9Bxzq/B4PwvuLQteHdgLFjT3ZPWaVT9zD4avvDViD1YDPVQDe7CBcg9WA3uw5I1iD7aE92DUzZ1uPNCpM1CW+EiW+Khb/HDXyCzEh2chbh+6dp7GCyCvq27M66ob87rqxjylqvRawEqvBaz0WsDK7Km2QiqfTC1bNqZ2e2oPiuNDvTcwj28F/saMPBYoQN5drzzozCG+D6cO8f0W/n4Bf9fD3zz4Ow3+YvB33fQhvvnwdwb8HQd/+8HfP88d4nsZ/h6Gv2f6P/2f/k//p48+9lu9f70uTlUt3j/B5zTq6gxqhT+Yi+Gn7gSU44MQH6T46OYo52eLvWxGDY2QyLkT5muYihFR+W4wSu4xWjtIhBeE7cCUu0jSGi7rSEeGdWBSzAd0MPEw2qYYXftg4Acvifv2Yf7udoZUZh5KiQBuTQblUK5BmRJEZYKoNQHWT5U3qMobzFpe1S6YWJY3KMobtJY32INaFKuI5yaKalhRDWelGm6FP6IallTDgmrYSjXcs47YREgVs+Zo1COKeiQr9Ugr/BH1iKQeEdQjVuqRHtQjRJUKTM/UBrLnw9iM8jlIz1RaKI5MHpXRg6Bg2Iv9fNbPZ/181s9n/XzWz2dZqfbzWT+f9fNZP5/181k/n/XzWT+f9fNZP5/185kjG4WzMWLk0+UzbDXKDDVb+hr+6ngtUsgHj8r+awEXBLvRIaFfJfSgoND/6f/0f/o//R9PH0d5/nph/6kzrey5t8GzsFw6li7m8WecleBwKQFp//Uk7Z+X4/NJ+8pJ/BbSInE0HwWRbwWEsaexvpLLG6VoT6ku46fb3ec4Fu1zSWNkTZMxgUVIBoRoEtZSVTqh2eX4MpUqa5qMCSwyOlSqa6X9dTS7sBHNSekdoAvlJpyEcktb/BYCFB/JEm+4xmeM5NJ/LkpjaSiMaYA=
*/