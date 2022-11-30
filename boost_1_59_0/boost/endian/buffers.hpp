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

#if defined(BOOST_BORLANDC) || defined(BOOST_CODEGEARC)
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
#ifdef BOOST_ENDIAN_NO_CTORS
public:
#endif

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

#if defined(BOOST_BORLANDC) || defined(BOOST_CODEGEARC)
# pragma pack(pop)
#endif

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif // BOOST_ENDIAN_BUFFERS_HPP

/* buffers.hpp
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
*/