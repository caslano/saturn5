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