//  boost/endian/arithmetic.hpp  -------------------------------------------------------//

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

#ifndef BOOST_ENDIAN_ARITHMETIC_HPP
#define BOOST_ENDIAN_ARITHMETIC_HPP

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable:4365)  // conversion ... signed/unsigned mismatch
#endif

#include <boost/endian/buffers.hpp>
#include <boost/core/scoped_enum.hpp>
#include <boost/static_assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>
#include <iosfwd>
#include <climits>

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

# ifndef BOOST_ENDIAN_EXPLICIT_CTORS
#   define BOOST_ENDIAN_EXPLICIT_OPT
# else
#   define BOOST_ENDIAN_EXPLICIT_OPT explicit
# endif

//----------------------------------  synopsis  ----------------------------------------//

namespace boost
{
namespace endian
{

  template <BOOST_SCOPED_ENUM(order) Order, class T, std::size_t n_bits,
    BOOST_SCOPED_ENUM(align) Align = align::no>
      class endian_arithmetic;

  // big endian signed integer aligned types
  typedef endian_arithmetic<order::big, int8_t, 8, align::yes>        big_int8_at;
  typedef endian_arithmetic<order::big, int16_t, 16, align::yes>      big_int16_at;
  typedef endian_arithmetic<order::big, int32_t, 32, align::yes>      big_int32_at;
  typedef endian_arithmetic<order::big, int64_t, 64, align::yes>      big_int64_at;

  // big endian unsigned integer aligned types
  typedef endian_arithmetic<order::big, uint8_t, 8, align::yes>       big_uint8_at;
  typedef endian_arithmetic<order::big, uint16_t, 16, align::yes>     big_uint16_at;
  typedef endian_arithmetic<order::big, uint32_t, 32, align::yes>     big_uint32_at;
  typedef endian_arithmetic<order::big, uint64_t, 64, align::yes>     big_uint64_at;

  // little endian signed integer aligned types
  typedef endian_arithmetic<order::little, int8_t, 8, align::yes>     little_int8_at;
  typedef endian_arithmetic<order::little, int16_t, 16, align::yes>   little_int16_at;
  typedef endian_arithmetic<order::little, int32_t, 32, align::yes>   little_int32_at;
  typedef endian_arithmetic<order::little, int64_t, 64, align::yes>   little_int64_at;

  // little endian unsigned integer aligned types
  typedef endian_arithmetic<order::little, uint8_t, 8, align::yes>    little_uint8_at;
  typedef endian_arithmetic<order::little, uint16_t, 16, align::yes>  little_uint16_at;
  typedef endian_arithmetic<order::little, uint32_t, 32, align::yes>  little_uint32_at;
  typedef endian_arithmetic<order::little, uint64_t, 64, align::yes>  little_uint64_at;

  // aligned floating point types
  typedef endian_arithmetic<order::big, float, 32, align::yes>        big_float32_at;
  typedef endian_arithmetic<order::big, double, 64, align::yes>       big_float64_at;
  typedef endian_arithmetic<order::little, float, 32, align::yes>     little_float32_at;
  typedef endian_arithmetic<order::little, double, 64, align::yes>    little_float64_at;

  // aligned native endian typedefs are not provided because
  // <cstdint> types are superior for this use case

  // big endian signed integer unaligned types
  typedef endian_arithmetic<order::big, int_least8_t, 8>        big_int8_t;
  typedef endian_arithmetic<order::big, int_least16_t, 16>      big_int16_t;
  typedef endian_arithmetic<order::big, int_least32_t, 24>      big_int24_t;
  typedef endian_arithmetic<order::big, int_least32_t, 32>      big_int32_t;
  typedef endian_arithmetic<order::big, int_least64_t, 40>      big_int40_t;
  typedef endian_arithmetic<order::big, int_least64_t, 48>      big_int48_t;
  typedef endian_arithmetic<order::big, int_least64_t, 56>      big_int56_t;
  typedef endian_arithmetic<order::big, int_least64_t, 64>      big_int64_t;

  // big endian unsigned integer unaligned types
  typedef endian_arithmetic<order::big, uint_least8_t, 8>       big_uint8_t;
  typedef endian_arithmetic<order::big, uint_least16_t, 16>     big_uint16_t;
  typedef endian_arithmetic<order::big, uint_least32_t, 24>     big_uint24_t;
  typedef endian_arithmetic<order::big, uint_least32_t, 32>     big_uint32_t;
  typedef endian_arithmetic<order::big, uint_least64_t, 40>     big_uint40_t;
  typedef endian_arithmetic<order::big, uint_least64_t, 48>     big_uint48_t;
  typedef endian_arithmetic<order::big, uint_least64_t, 56>     big_uint56_t;
  typedef endian_arithmetic<order::big, uint_least64_t, 64>     big_uint64_t;

  // little endian signed integer unaligned types
  typedef endian_arithmetic<order::little, int_least8_t, 8>     little_int8_t;
  typedef endian_arithmetic<order::little, int_least16_t, 16>   little_int16_t;
  typedef endian_arithmetic<order::little, int_least32_t, 24>   little_int24_t;
  typedef endian_arithmetic<order::little, int_least32_t, 32>   little_int32_t;
  typedef endian_arithmetic<order::little, int_least64_t, 40>   little_int40_t;
  typedef endian_arithmetic<order::little, int_least64_t, 48>   little_int48_t;
  typedef endian_arithmetic<order::little, int_least64_t, 56>   little_int56_t;
  typedef endian_arithmetic<order::little, int_least64_t, 64>   little_int64_t;

  // little endian unsigned integer unaligned types
  typedef endian_arithmetic<order::little, uint_least8_t, 8>    little_uint8_t;
  typedef endian_arithmetic<order::little, uint_least16_t, 16>  little_uint16_t;
  typedef endian_arithmetic<order::little, uint_least32_t, 24>  little_uint24_t;
  typedef endian_arithmetic<order::little, uint_least32_t, 32>  little_uint32_t;
  typedef endian_arithmetic<order::little, uint_least64_t, 40>  little_uint40_t;
  typedef endian_arithmetic<order::little, uint_least64_t, 48>  little_uint48_t;
  typedef endian_arithmetic<order::little, uint_least64_t, 56>  little_uint56_t;
  typedef endian_arithmetic<order::little, uint_least64_t, 64>  little_uint64_t;

  // native endian signed integer unaligned types
  typedef endian_arithmetic<order::native, int_least8_t, 8>     native_int8_t;
  typedef endian_arithmetic<order::native, int_least16_t, 16>   native_int16_t;
  typedef endian_arithmetic<order::native, int_least32_t, 24>   native_int24_t;
  typedef endian_arithmetic<order::native, int_least32_t, 32>   native_int32_t;
  typedef endian_arithmetic<order::native, int_least64_t, 40>   native_int40_t;
  typedef endian_arithmetic<order::native, int_least64_t, 48>   native_int48_t;
  typedef endian_arithmetic<order::native, int_least64_t, 56>   native_int56_t;
  typedef endian_arithmetic<order::native, int_least64_t, 64>   native_int64_t;

  // native endian unsigned integer unaligned types
  typedef endian_arithmetic<order::native, uint_least8_t, 8>    native_uint8_t;
  typedef endian_arithmetic<order::native, uint_least16_t, 16>  native_uint16_t;
  typedef endian_arithmetic<order::native, uint_least32_t, 24>  native_uint24_t;
  typedef endian_arithmetic<order::native, uint_least32_t, 32>  native_uint32_t;
  typedef endian_arithmetic<order::native, uint_least64_t, 40>  native_uint40_t;
  typedef endian_arithmetic<order::native, uint_least64_t, 48>  native_uint48_t;
  typedef endian_arithmetic<order::native, uint_least64_t, 56>  native_uint56_t;
  typedef endian_arithmetic<order::native, uint_least64_t, 64>  native_uint64_t;

  // unaligned floating point types
  typedef endian_arithmetic<order::big, float, 32, align::no>        big_float32_t;
  typedef endian_arithmetic<order::big, double, 64, align::no>       big_float64_t;
  typedef endian_arithmetic<order::little, float, 32, align::no>     little_float32_t;
  typedef endian_arithmetic<order::little, double, 64, align::no>    little_float64_t;
  typedef endian_arithmetic<order::native, float, 32, align::no>     native_float32_t;
  typedef endian_arithmetic<order::native, double, 64, align::no>    native_float64_t;

//----------------------------------  end synopsis  ------------------------------------//

template <BOOST_SCOPED_ENUM(order) Order, class T, std::size_t n_bits,
    BOOST_SCOPED_ENUM(align) Align>
class endian_arithmetic
{
private:

    typedef endian_buffer<Order, T, n_bits, Align> buffer_type;

#ifdef BOOST_ENDIAN_NO_CTORS
public:
#else
private:
#endif

    buffer_type buf_;

public:

    typedef T value_type;

#ifndef BOOST_ENDIAN_NO_CTORS

    endian_arithmetic() BOOST_ENDIAN_DEFAULT_CONSTRUCT

    BOOST_ENDIAN_EXPLICIT_OPT endian_arithmetic( T val ) BOOST_NOEXCEPT: buf_( val )
    {
    }

#endif

    endian_arithmetic& operator=( T val ) BOOST_NOEXCEPT
    {
        buf_ = val;
        return *this;
    }

    value_type value() const BOOST_NOEXCEPT
    {
        return buf_.value();
    }

    unsigned char const * data() const BOOST_NOEXCEPT
    {
        return buf_.data();
    }

    unsigned char * data() BOOST_NOEXCEPT
    {
        return buf_.data();
    }

    operator value_type() const BOOST_NOEXCEPT
    {
        return this->value();
    }

    operator buffer_type& () BOOST_NOEXCEPT
    {
        return buf_;
    }

    operator buffer_type const& () BOOST_NOEXCEPT
    {
        return buf_;
    }

    // operators

    T operator+() const BOOST_NOEXCEPT
    {
        return this->value();
    }

    endian_arithmetic& operator+=( T y ) BOOST_NOEXCEPT
    {
        *this = static_cast<T>( this->value() + y );
        return *this;
    }

    endian_arithmetic& operator-=( T y ) BOOST_NOEXCEPT
    {
        *this = static_cast<T>( this->value() - y );
        return *this;
    }

    endian_arithmetic& operator*=( T y ) BOOST_NOEXCEPT
    {
        *this = static_cast<T>( this->value() * y );
        return *this;
    }

    endian_arithmetic& operator/=( T y ) BOOST_NOEXCEPT
    {
        *this = static_cast<T>( this->value() / y );
        return *this;
    }

    endian_arithmetic& operator%=( T y ) BOOST_NOEXCEPT
    {
        *this = static_cast<T>( this->value() % y );
        return *this;
    }

    endian_arithmetic& operator&=( T y ) BOOST_NOEXCEPT
    {
        *this = static_cast<T>( this->value() & y );
        return *this;
    }

    endian_arithmetic& operator|=( T y ) BOOST_NOEXCEPT
    {
        *this = static_cast<T>( this->value() | y );
        return *this;
    }

    endian_arithmetic& operator^=( T y ) BOOST_NOEXCEPT
    {
        *this = static_cast<T>( this->value() ^ y );
        return *this;
    }

    endian_arithmetic& operator<<=( T y ) BOOST_NOEXCEPT
    {
        *this = static_cast<T>( this->value() << y );
        return *this;
    }

    endian_arithmetic& operator>>=( T y ) BOOST_NOEXCEPT
    {
        *this = static_cast<T>( this->value() >> y );
        return *this;
    }

    endian_arithmetic& operator++() BOOST_NOEXCEPT
    {
        *this += 1;
        return *this;
    }

    endian_arithmetic& operator--() BOOST_NOEXCEPT
    {
        *this -= 1;
        return *this;
    }

    endian_arithmetic operator++(int) BOOST_NOEXCEPT
    {
        endian_arithmetic tmp( *this );
        *this += 1;
        return tmp;
    }

    endian_arithmetic operator--(int) BOOST_NOEXCEPT
    {
        endian_arithmetic tmp( *this );
        *this -= 1;
        return tmp;
    }

    template<class Ch, class Tr>
    friend std::basic_ostream<Ch, Tr>&
    operator<<( std::basic_ostream<Ch, Tr>& os, endian_arithmetic const& x )
    {
        return os << x.value();
    }

    template<class Ch, class Tr>
    friend std::basic_istream<Ch, Tr>&
    operator>>( std::basic_istream<Ch, Tr>& is, endian_arithmetic& x )
    {
        T i;

        if( is >> i )
        {
            x = i;
        }

        return is;
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

#endif // BOOST_ENDIAN_ARITHMETIC_HPP

/* arithmetic.hpp
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
*/