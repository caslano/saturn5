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