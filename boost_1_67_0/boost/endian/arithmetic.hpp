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
class endian_arithmetic:
    public endian_buffer<Order, T, n_bits, Align>
{
private:

    typedef endian_buffer<Order, T, n_bits, Align> inherited;

public:

    typedef T value_type;

#ifndef BOOST_ENDIAN_NO_CTORS

    endian_arithmetic() BOOST_ENDIAN_DEFAULT_CONSTRUCT

    BOOST_ENDIAN_EXPLICIT_OPT endian_arithmetic( T val ) BOOST_NOEXCEPT: inherited( val )
    {
    }

#endif

    endian_arithmetic& operator=( T val ) BOOST_NOEXCEPT
    {
        inherited::operator=( val );
        return *this;
    }

    operator value_type() const BOOST_NOEXCEPT
    {
        return this->value();
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

#if defined(__BORLANDC__) || defined( __CODEGEARC__)
# pragma pack(pop)
#endif

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif // BOOST_ENDIAN_ARITHMETIC_HPP

/* arithmetic.hpp
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
*/