//  boost/endian/buffers.hpp  ----------------------------------------------------------//

//  (C) Copyright Darin Adler 2000
//  (C) Copyright Beman Dawes 2006, 2009, 2014
//  (C) Copyright Peter Dimov 2019

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See library home page at http://www.boost.org/libs/endian

//--------------------------------------------------------------------------------------//

//  Original design developed by Darin Adler based on classes developed by Mark
//  Borgerding. Four original class templates were combined into a single endian
//  class template by Beman Dawes, who also added the unrolled_byte_loops sign
//  partial specialization to correctly extend the sign when cover integer size
//  differs from endian representation size.

// TODO: When a compiler supporting constexpr becomes available, try possible uses.

#ifndef BOOST_ENDIAN_BUFFERS_HPP
#define BOOST_ENDIAN_BUFFERS_HPP

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable: 4127)  // conditional expression is constant
#endif

#include <boost/endian/detail/endian_store.hpp>
#include <boost/endian/detail/endian_load.hpp>
#include <boost/core/scoped_enum.hpp>
#include <boost/static_assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>
#include <iosfwd>
#include <climits>
#include <cstring>

#if defined(__BORLANDC__) || defined( __CODEGEARC__)
# pragma pack(push, 1)
#endif

# if CHAR_BIT != 8
#   error Platforms with CHAR_BIT != 8 are not supported
# endif

# ifdef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#   define BOOST_ENDIAN_DEFAULT_CONSTRUCT {}          // C++03
# else
#   define BOOST_ENDIAN_DEFAULT_CONSTRUCT = default;  // C++0x
# endif

// g++ pre-4.6 does not support unrestricted unions, but we have no Config macro for that
# if (defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || BOOST_WORKAROUND(BOOST_GCC, < 40600)) && defined(BOOST_ENDIAN_FORCE_PODNESS)
#   define BOOST_ENDIAN_NO_CTORS
# endif

//----------------------------------  synopsis  ----------------------------------------//

namespace boost
{
namespace endian
{

  BOOST_SCOPED_ENUM_START(align)
  {no, yes
#   ifdef BOOST_ENDIAN_DEPRECATED_NAMES
      , unaligned = no, aligned = yes
#   endif
  }; BOOST_SCOPED_ENUM_END

  template <BOOST_SCOPED_ENUM(order) Order, class T, std::size_t n_bits,
    BOOST_SCOPED_ENUM(align) A = align::no>
      class endian_buffer;

  // aligned big endian signed integer buffers
  typedef endian_buffer<order::big, int8_t, 8, align::yes>       big_int8_buf_at;
  typedef endian_buffer<order::big, int16_t, 16, align::yes>     big_int16_buf_at;
  typedef endian_buffer<order::big, int32_t, 32, align::yes>     big_int32_buf_at;
  typedef endian_buffer<order::big, int64_t, 64, align::yes>     big_int64_buf_at;

  // aligned big endian unsigned integer buffers
  typedef endian_buffer<order::big, uint8_t, 8, align::yes>      big_uint8_buf_at;
  typedef endian_buffer<order::big, uint16_t, 16, align::yes>    big_uint16_buf_at;
  typedef endian_buffer<order::big, uint32_t, 32, align::yes>    big_uint32_buf_at;
  typedef endian_buffer<order::big, uint64_t, 64, align::yes>    big_uint64_buf_at;

  // aligned little endian signed integer buffers
  typedef endian_buffer<order::little, int8_t, 8, align::yes>    little_int8_buf_at;
  typedef endian_buffer<order::little, int16_t, 16, align::yes>  little_int16_buf_at;
  typedef endian_buffer<order::little, int32_t, 32, align::yes>  little_int32_buf_at;
  typedef endian_buffer<order::little, int64_t, 64, align::yes>  little_int64_buf_at;

  // aligned little endian unsigned integer buffers
  typedef endian_buffer<order::little, uint8_t, 8, align::yes>   little_uint8_buf_at;
  typedef endian_buffer<order::little, uint16_t, 16, align::yes> little_uint16_buf_at;
  typedef endian_buffer<order::little, uint32_t, 32, align::yes> little_uint32_buf_at;
  typedef endian_buffer<order::little, uint64_t, 64, align::yes> little_uint64_buf_at;

  // aligned floating point buffers
  typedef endian_buffer<order::big, float, 32, align::yes>       big_float32_buf_at;
  typedef endian_buffer<order::big, double, 64, align::yes>      big_float64_buf_at;
  typedef endian_buffer<order::little, float, 32, align::yes>    little_float32_buf_at;
  typedef endian_buffer<order::little, double, 64, align::yes>   little_float64_buf_at;

  // aligned native endian typedefs are not provided because
  // <cstdint> types are superior for this use case

  // unaligned big endian signed integer buffers
  typedef endian_buffer<order::big, int_least8_t, 8>        big_int8_buf_t;
  typedef endian_buffer<order::big, int_least16_t, 16>      big_int16_buf_t;
  typedef endian_buffer<order::big, int_least32_t, 24>      big_int24_buf_t;
  typedef endian_buffer<order::big, int_least32_t, 32>      big_int32_buf_t;
  typedef endian_buffer<order::big, int_least64_t, 40>      big_int40_buf_t;
  typedef endian_buffer<order::big, int_least64_t, 48>      big_int48_buf_t;
  typedef endian_buffer<order::big, int_least64_t, 56>      big_int56_buf_t;
  typedef endian_buffer<order::big, int_least64_t, 64>      big_int64_buf_t;

  // unaligned big endian unsigned integer buffers
  typedef endian_buffer<order::big, uint_least8_t, 8>       big_uint8_buf_t;
  typedef endian_buffer<order::big, uint_least16_t, 16>     big_uint16_buf_t;
  typedef endian_buffer<order::big, uint_least32_t, 24>     big_uint24_buf_t;
  typedef endian_buffer<order::big, uint_least32_t, 32>     big_uint32_buf_t;
  typedef endian_buffer<order::big, uint_least64_t, 40>     big_uint40_buf_t;
  typedef endian_buffer<order::big, uint_least64_t, 48>     big_uint48_buf_t;
  typedef endian_buffer<order::big, uint_least64_t, 56>     big_uint56_buf_t;
  typedef endian_buffer<order::big, uint_least64_t, 64>     big_uint64_buf_t;

  // unaligned little endian signed integer buffers
  typedef endian_buffer<order::little, int_least8_t, 8>     little_int8_buf_t;
  typedef endian_buffer<order::little, int_least16_t, 16>   little_int16_buf_t;
  typedef endian_buffer<order::little, int_least32_t, 24>   little_int24_buf_t;
  typedef endian_buffer<order::little, int_least32_t, 32>   little_int32_buf_t;
  typedef endian_buffer<order::little, int_least64_t, 40>   little_int40_buf_t;
  typedef endian_buffer<order::little, int_least64_t, 48>   little_int48_buf_t;
  typedef endian_buffer<order::little, int_least64_t, 56>   little_int56_buf_t;
  typedef endian_buffer<order::little, int_least64_t, 64>   little_int64_buf_t;

  // unaligned little endian unsigned integer buffers
  typedef endian_buffer<order::little, uint_least8_t, 8>    little_uint8_buf_t;
  typedef endian_buffer<order::little, uint_least16_t, 16>  little_uint16_buf_t;
  typedef endian_buffer<order::little, uint_least32_t, 24>  little_uint24_buf_t;
  typedef endian_buffer<order::little, uint_least32_t, 32>  little_uint32_buf_t;
  typedef endian_buffer<order::little, uint_least64_t, 40>  little_uint40_buf_t;
  typedef endian_buffer<order::little, uint_least64_t, 48>  little_uint48_buf_t;
  typedef endian_buffer<order::little, uint_least64_t, 56>  little_uint56_buf_t;
  typedef endian_buffer<order::little, uint_least64_t, 64>  little_uint64_buf_t;

  // unaligned native endian signed integer buffers
  typedef endian_buffer<order::native, int_least8_t, 8>     native_int8_buf_t;
  typedef endian_buffer<order::native, int_least16_t, 16>   native_int16_buf_t;
  typedef endian_buffer<order::native, int_least32_t, 24>   native_int24_buf_t;
  typedef endian_buffer<order::native, int_least32_t, 32>   native_int32_buf_t;
  typedef endian_buffer<order::native, int_least64_t, 40>   native_int40_buf_t;
  typedef endian_buffer<order::native, int_least64_t, 48>   native_int48_buf_t;
  typedef endian_buffer<order::native, int_least64_t, 56>   native_int56_buf_t;
  typedef endian_buffer<order::native, int_least64_t, 64>   native_int64_buf_t;

  // unaligned native endian unsigned integer buffers
  typedef endian_buffer<order::native, uint_least8_t, 8>    native_uint8_buf_t;
  typedef endian_buffer<order::native, uint_least16_t, 16>  native_uint16_buf_t;
  typedef endian_buffer<order::native, uint_least32_t, 24>  native_uint24_buf_t;
  typedef endian_buffer<order::native, uint_least32_t, 32>  native_uint32_buf_t;
  typedef endian_buffer<order::native, uint_least64_t, 40>  native_uint40_buf_t;
  typedef endian_buffer<order::native, uint_least64_t, 48>  native_uint48_buf_t;
  typedef endian_buffer<order::native, uint_least64_t, 56>  native_uint56_buf_t;
  typedef endian_buffer<order::native, uint_least64_t, 64>  native_uint64_buf_t;

  // unaligned floating point buffers
  typedef endian_buffer<order::big, float, 32, align::no>       big_float32_buf_t;
  typedef endian_buffer<order::big, double, 64, align::no>      big_float64_buf_t;
  typedef endian_buffer<order::little, float, 32, align::no>    little_float32_buf_t;
  typedef endian_buffer<order::little, double, 64, align::no>   little_float64_buf_t;
  typedef endian_buffer<order::native, float, 32, align::no>    native_float32_buf_t;
  typedef endian_buffer<order::native, double, 64, align::no>   native_float64_buf_t;

  // Stream inserter
  template <class charT, class traits, BOOST_SCOPED_ENUM(order) Order, class T,
    std::size_t n_bits, BOOST_SCOPED_ENUM(align) A>
  std::basic_ostream<charT, traits>&
    operator<<(std::basic_ostream<charT, traits>& os,
      const endian_buffer<Order, T, n_bits, A>& x)
  {
    return os << x.value();
  }

  // Stream extractor
  template <class charT, class traits, BOOST_SCOPED_ENUM(order) Order, class T,
    std::size_t n_bits, BOOST_SCOPED_ENUM(align) A>
  std::basic_istream<charT, traits>&
    operator>>(std::basic_istream<charT, traits>& is,
      endian_buffer<Order, T, n_bits, A>& x)
  {
    T i;
    if (is >> i)
      x = i;
    return is;
  }

//----------------------------------  end synopsis  ------------------------------------//

//  endian_buffer class template specializations  --------------------------------------//

//  Specializations that represent unaligned bytes.
//  Taking an integer type as a parameter provides a nice way to pass both
//  the size and signedness of the desired integer and get the appropriate
//  corresponding integer type for the interface.

// Q: Should endian_buffer supply "value_type operator value_type() const noexcept"?
// A: No. The rationale for endian_buffers is to prevent high-cost hidden
//    conversions. If an implicit conversion operator is supplied, hidden conversions
//    can occur.

//  unaligned endian_buffer specialization

template< BOOST_SCOPED_ENUM(order) Order, class T, std::size_t n_bits >
class endian_buffer<Order, T, n_bits, align::no>
{
private:

    BOOST_STATIC_ASSERT( (n_bits/8)*8 == n_bits );

    unsigned char value_[ n_bits / 8 ];

public:

    typedef T value_type;

#ifndef BOOST_ENDIAN_NO_CTORS

    endian_buffer() BOOST_ENDIAN_DEFAULT_CONSTRUCT

    explicit endian_buffer( T val ) BOOST_NOEXCEPT
    {
        boost::endian::endian_store<T, n_bits / 8, Order>( value_, val );
    }

#endif

    endian_buffer& operator=( T val ) BOOST_NOEXCEPT
    {
        boost::endian::endian_store<T, n_bits / 8, Order>( value_, val );
        return *this;
    }

    value_type value() const BOOST_NOEXCEPT
    {
        return boost::endian::endian_load<T, n_bits / 8, Order>( value_ );
    }

    unsigned char const * data() const BOOST_NOEXCEPT
    {
        return value_;
    }

    unsigned char * data() BOOST_NOEXCEPT
    {
        return value_;
    }
};

// aligned specializations; only n_bits == 16/32/64 supported

// aligned endian_buffer specialization

template< BOOST_SCOPED_ENUM(order) Order, class T, std::size_t n_bits >
class endian_buffer<Order, T, n_bits, align::yes>
{
private:

    BOOST_STATIC_ASSERT( (n_bits/8)*8 == n_bits );
    BOOST_STATIC_ASSERT( sizeof(T) == n_bits/8 );

    union
    {
        unsigned char value_[ n_bits / 8 ];
        T align_;
    };

public:

    typedef T value_type;

#ifndef BOOST_ENDIAN_NO_CTORS

    endian_buffer() BOOST_ENDIAN_DEFAULT_CONSTRUCT

    explicit endian_buffer( T val ) BOOST_NOEXCEPT
    {
        boost::endian::endian_store<T, n_bits / 8, Order>( value_, val );
    }

#endif

    endian_buffer& operator=( T val ) BOOST_NOEXCEPT
    {
        boost::endian::endian_store<T, n_bits / 8, Order>( value_, val );
        return *this;
    }

    value_type value() const BOOST_NOEXCEPT
    {
        return boost::endian::endian_load<T, n_bits / 8, Order>( value_ );
    }

    unsigned char const * data() const BOOST_NOEXCEPT
    {
        return value_;
    }

    unsigned char * data() BOOST_NOEXCEPT
    {
        return value_;
    }
};

// aligned native endian_buffer specialization

template< class T, std::size_t n_bits >
class endian_buffer<order::native, T, n_bits, align::yes>
{
private:

    BOOST_STATIC_ASSERT( (n_bits/8)*8 == n_bits );
    BOOST_STATIC_ASSERT( sizeof(T) == n_bits/8 );

    T value_;

public:

    typedef T value_type;

#ifndef BOOST_ENDIAN_NO_CTORS

    endian_buffer() BOOST_ENDIAN_DEFAULT_CONSTRUCT

    explicit endian_buffer( T val ) BOOST_NOEXCEPT: value_( val )
    {
    }

#endif

    endian_buffer& operator=( T val ) BOOST_NOEXCEPT
    {
        value_ = val;
        return *this;
    }

    value_type value() const BOOST_NOEXCEPT
    {
        return value_;
    }

    unsigned char const * data() const BOOST_NOEXCEPT
    {
        return reinterpret_cast< unsigned char const* >( &value_ );
    }

    unsigned char * data() BOOST_NOEXCEPT
    {
        return reinterpret_cast< unsigned char* >( &value_ );
    }
};

} // namespace endian
} // namespace boost

#if defined(__BORLANDC__) || defined( __CODEGEARC__)
# pragma pack(pop)
#endif

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif // BOOST_ENDIAN_BUFFERS_HPP

/* buffers.hpp
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
*/