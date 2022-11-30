#ifndef BOOST_ENDIAN_DETAIL_ENDIAN_LOAD_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_ENDIAN_LOAD_HPP_INCLUDED

// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/endian/detail/endian_reverse.hpp>
#include <boost/endian/detail/order.hpp>
#include <boost/endian/detail/integral_by_size.hpp>
#include <boost/endian/detail/is_trivially_copyable.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/static_assert.hpp>
#include <cstddef>
#include <cstring>

namespace boost
{
namespace endian
{

namespace detail
{

template<class T, std::size_t N1, BOOST_SCOPED_ENUM(order) O1, std::size_t N2, BOOST_SCOPED_ENUM(order) O2> struct endian_load_impl
{
};

} // namespace detail

// Requires:
//
//    sizeof(T) must be 1, 2, 4, or 8
//    1 <= N <= sizeof(T)
//    T is TriviallyCopyable
//    if N < sizeof(T), T is integral or enum

template<class T, std::size_t N, BOOST_SCOPED_ENUM(order) Order>
inline T endian_load( unsigned char const * p ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT( sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8 );
    BOOST_STATIC_ASSERT( N >= 1 && N <= sizeof(T) );

    return detail::endian_load_impl<T, sizeof(T), order::native, N, Order>()( p );
}

namespace detail
{

// same endianness, same size

template<class T, std::size_t N, BOOST_SCOPED_ENUM(order) O> struct endian_load_impl<T, N, O, N, O>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_trivially_copyable<T>::value );

        T t;
        std::memcpy( &t, p, N );
        return t;
    }
};

// same size, reverse endianness

template<class T, std::size_t N, BOOST_SCOPED_ENUM(order) O1, BOOST_SCOPED_ENUM(order) O2> struct endian_load_impl<T, N, O1, N, O2>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_trivially_copyable<T>::value );

        typename integral_by_size<N>::type tmp;
        std::memcpy( &tmp, p, N );

        endian_reverse_inplace( tmp );

        T t;
        std::memcpy( &t, &tmp, N );
        return t;
    }
};

// expanding load 1 -> 2

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 2, Order, 1, order::little>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 2 ];

        tmp[0] = p[0];
        tmp[1] = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;

        return boost::endian::endian_load<T, 2, order::little>( tmp );
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 2, Order, 1, order::big>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 2 ];

        tmp[0] = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;
        tmp[1] = p[0];

        return boost::endian::endian_load<T, 2, order::big>( tmp );
    }
};

// expanding load 1 -> 4

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 4, Order, 1, order::little>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;

        tmp[0] = p[0];
        tmp[1] = fill;
        tmp[2] = fill;
        tmp[3] = fill;

        return boost::endian::endian_load<T, 4, order::little>( tmp );
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 4, Order, 1, order::big>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;

        tmp[0] = fill;
        tmp[1] = fill;
        tmp[2] = fill;
        tmp[3] = p[0];

        return boost::endian::endian_load<T, 4, order::big>( tmp );
    }
};

// expanding load 2 -> 4

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 4, Order, 2, order::little>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[1] & 0x80 )? 0xFF: 0x00;

        tmp[0] = p[0];
        tmp[1] = p[1];
        tmp[2] = fill;
        tmp[3] = fill;

        return boost::endian::endian_load<T, 4, order::little>( tmp );
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 4, Order, 2, order::big>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;

        tmp[0] = fill;
        tmp[1] = fill;
        tmp[2] = p[0];
        tmp[3] = p[1];

        return boost::endian::endian_load<T, 4, order::big>( tmp );
    }
};

// expanding load 3 -> 4

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 4, Order, 3, order::little>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];

        tmp[0] = p[0];
        tmp[1] = p[1];
        tmp[2] = p[2];
        tmp[3] = boost::is_signed<T>::value && ( p[2] & 0x80 )? 0xFF: 0x00;

        return boost::endian::endian_load<T, 4, order::little>( tmp );
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 4, Order, 3, order::big>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];

        tmp[0] = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;
        tmp[1] = p[0];
        tmp[2] = p[1];
        tmp[3] = p[2];

        return boost::endian::endian_load<T, 4, order::big>( tmp );
    }
};

// expanding load 1 -> 8

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 1, order::little>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;

        tmp[0] = p[0];

        tmp[1] = fill;
        tmp[2] = fill;
        tmp[3] = fill;
        tmp[4] = fill;
        tmp[5] = fill;
        tmp[6] = fill;
        tmp[7] = fill;

        return boost::endian::endian_load<T, 8, order::little>( tmp );
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 1, order::big>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;

        tmp[0] = fill;
        tmp[1] = fill;
        tmp[2] = fill;
        tmp[3] = fill;
        tmp[4] = fill;
        tmp[5] = fill;
        tmp[6] = fill;

        tmp[7] = p[0];

        return boost::endian::endian_load<T, 8, order::big>( tmp );
    }
};

// expanding load 2 -> 8

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 2, order::little>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[1] & 0x80 )? 0xFF: 0x00;

        tmp[0] = p[0];
        tmp[1] = p[1];

        tmp[2] = fill;
        tmp[3] = fill;
        tmp[4] = fill;
        tmp[5] = fill;
        tmp[6] = fill;
        tmp[7] = fill;

        return boost::endian::endian_load<T, 8, order::little>( tmp );
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 2, order::big>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;

        tmp[0] = fill;
        tmp[1] = fill;
        tmp[2] = fill;
        tmp[3] = fill;
        tmp[4] = fill;
        tmp[5] = fill;

        tmp[6] = p[0];
        tmp[7] = p[1];

        return boost::endian::endian_load<T, 8, order::big>( tmp );
    }
};

// expanding load 3 -> 8

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 3, order::little>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[2] & 0x80 )? 0xFF: 0x00;

        tmp[0] = p[0];
        tmp[1] = p[1];
        tmp[2] = p[2];

        tmp[3] = fill;
        tmp[4] = fill;
        tmp[5] = fill;
        tmp[6] = fill;
        tmp[7] = fill;

        return boost::endian::endian_load<T, 8, order::little>( tmp );
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 3, order::big>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;

        tmp[0] = fill;
        tmp[1] = fill;
        tmp[2] = fill;
        tmp[3] = fill;
        tmp[4] = fill;

        tmp[5] = p[0];
        tmp[6] = p[1];
        tmp[7] = p[2];

        return boost::endian::endian_load<T, 8, order::big>( tmp );
    }
};

// expanding load 4 -> 8

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 4, order::little>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[3] & 0x80 )? 0xFF: 0x00;

        tmp[0] = p[0];
        tmp[1] = p[1];
        tmp[2] = p[2];
        tmp[3] = p[3];

        tmp[4] = fill;
        tmp[5] = fill;
        tmp[6] = fill;
        tmp[7] = fill;

        return boost::endian::endian_load<T, 8, order::little>( tmp );
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 4, order::big>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;

        tmp[0] = fill;
        tmp[1] = fill;
        tmp[2] = fill;
        tmp[3] = fill;

        tmp[4] = p[0];
        tmp[5] = p[1];
        tmp[6] = p[2];
        tmp[7] = p[3];

        return boost::endian::endian_load<T, 8, order::big>( tmp );
    }
};

// expanding load 5 -> 8

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 5, order::little>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[4] & 0x80 )? 0xFF: 0x00;

        tmp[0] = p[0];
        tmp[1] = p[1];
        tmp[2] = p[2];
        tmp[3] = p[3];
        tmp[4] = p[4];

        tmp[5] = fill;
        tmp[6] = fill;
        tmp[7] = fill;

        return boost::endian::endian_load<T, 8, order::little>( tmp );
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 5, order::big>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;

        tmp[0] = fill;
        tmp[1] = fill;
        tmp[2] = fill;

        tmp[3] = p[0];
        tmp[4] = p[1];
        tmp[5] = p[2];
        tmp[6] = p[3];
        tmp[7] = p[4];

        return boost::endian::endian_load<T, 8, order::big>( tmp );
    }
};

// expanding load 6 -> 8

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 6, order::little>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[5] & 0x80 )? 0xFF: 0x00;

        tmp[0] = p[0];
        tmp[1] = p[1];
        tmp[2] = p[2];
        tmp[3] = p[3];
        tmp[4] = p[4];
        tmp[5] = p[5];

        tmp[6] = fill;
        tmp[7] = fill;

        return boost::endian::endian_load<T, 8, order::little>( tmp );
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 6, order::big>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;

        tmp[0] = fill;
        tmp[1] = fill;

        tmp[2] = p[0];
        tmp[3] = p[1];
        tmp[4] = p[2];
        tmp[5] = p[3];
        tmp[6] = p[4];
        tmp[7] = p[5];

        return boost::endian::endian_load<T, 8, order::big>( tmp );
    }
};

// expanding load 7 -> 8

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 7, order::little>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[6] & 0x80 )? 0xFF: 0x00;

        tmp[0] = p[0];
        tmp[1] = p[1];
        tmp[2] = p[2];
        tmp[3] = p[3];
        tmp[4] = p[4];
        tmp[5] = p[5];
        tmp[6] = p[6];

        tmp[7] = fill;

        return boost::endian::endian_load<T, 8, order::little>( tmp );
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_load_impl<T, 8, Order, 7, order::big>
{
    inline T operator()( unsigned char const * p ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];

        unsigned char fill = boost::is_signed<T>::value && ( p[0] & 0x80 )? 0xFF: 0x00;

        tmp[0] = fill;

        tmp[1] = p[0];
        tmp[2] = p[1];
        tmp[3] = p[2];
        tmp[4] = p[3];
        tmp[5] = p[4];
        tmp[6] = p[5];
        tmp[7] = p[6];

        return boost::endian::endian_load<T, 8, order::big>( tmp );
    }
};

} // namespace detail

} // namespace endian
} // namespace boost

#endif  // BOOST_ENDIAN_DETAIL_ENDIAN_LOAD_HPP_INCLUDED

/* endian_load.hpp
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
*/