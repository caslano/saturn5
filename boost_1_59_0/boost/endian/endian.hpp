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
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
*/