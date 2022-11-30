#ifndef BOOST_ENDIAN_DETAIL_ENDIAN_STORE_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_ENDIAN_STORE_HPP_INCLUDED

// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/endian/detail/endian_reverse.hpp>
#include <boost/endian/detail/order.hpp>
#include <boost/endian/detail/integral_by_size.hpp>
#include <boost/endian/detail/is_trivially_copyable.hpp>
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

template<class T, std::size_t N1, BOOST_SCOPED_ENUM(order) O1, std::size_t N2, BOOST_SCOPED_ENUM(order) O2> struct endian_store_impl
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
inline void endian_store( unsigned char * p, T const & v ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT( sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8 );
    BOOST_STATIC_ASSERT( N >= 1 && N <= sizeof(T) );

    return detail::endian_store_impl<T, sizeof(T), order::native, N, Order>()( p, v );
}

namespace detail
{

// same endianness, same size

template<class T, std::size_t N, BOOST_SCOPED_ENUM(order) O> struct endian_store_impl<T, N, O, N, O>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_trivially_copyable<T>::value );

        std::memcpy( p, &v, N );
    }
};

// same size, reverse endianness

template<class T, std::size_t N, BOOST_SCOPED_ENUM(order) O1, BOOST_SCOPED_ENUM(order) O2> struct endian_store_impl<T, N, O1, N, O2>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_trivially_copyable<T>::value );

        typename integral_by_size<N>::type tmp;
        std::memcpy( &tmp, &v, N );

        endian_reverse_inplace( tmp );

        std::memcpy( p, &tmp, N );
    }
};

// truncating store 2 -> 1

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 2, Order, 1, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 2 ];
        boost::endian::endian_store<T, 2, order::little>( tmp, v );

        p[0] = tmp[0];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 2, Order, 1, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 2 ];
        boost::endian::endian_store<T, 2, order::big>( tmp, v );

        p[0] = tmp[1];
    }
};

// truncating store 4 -> 1

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 4, Order, 1, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];
        boost::endian::endian_store<T, 4, order::little>( tmp, v );

        p[0] = tmp[0];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 4, Order, 1, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];
        boost::endian::endian_store<T, 4, order::big>( tmp, v );

        p[0] = tmp[3];
    }
};

// truncating store 4 -> 2

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 4, Order, 2, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];
        boost::endian::endian_store<T, 4, order::little>( tmp, v );

        p[0] = tmp[0];
        p[1] = tmp[1];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 4, Order, 2, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];
        boost::endian::endian_store<T, 4, order::big>( tmp, v );

        p[0] = tmp[2];
        p[1] = tmp[3];
    }
};

// truncating store 4 -> 3

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 4, Order, 3, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];
        boost::endian::endian_store<T, 4, order::little>( tmp, v );

        p[0] = tmp[0];
        p[1] = tmp[1];
        p[2] = tmp[2];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 4, Order, 3, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 4 ];
        boost::endian::endian_store<T, 4, order::big>( tmp, v );

        p[0] = tmp[1];
        p[1] = tmp[2];
        p[2] = tmp[3];
    }
};

// truncating store 8 -> 1

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 1, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::little>( tmp, v );

        p[0] = tmp[0];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 1, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::big>( tmp, v );

        p[0] = tmp[7];
    }
};

// truncating store 8 -> 2

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 2, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::little>( tmp, v );

        p[0] = tmp[0];
        p[1] = tmp[1];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 2, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::big>( tmp, v );

        p[0] = tmp[6];
        p[1] = tmp[7];
    }
};

// truncating store 8 -> 3

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 3, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::little>( tmp, v );

        p[0] = tmp[0];
        p[1] = tmp[1];
        p[2] = tmp[2];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 3, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::big>( tmp, v );

        p[0] = tmp[5];
        p[1] = tmp[6];
        p[2] = tmp[7];
    }
};

// truncating store 8 -> 4

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 4, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::little>( tmp, v );

        p[0] = tmp[0];
        p[1] = tmp[1];
        p[2] = tmp[2];
        p[3] = tmp[3];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 4, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::big>( tmp, v );

        p[0] = tmp[4];
        p[1] = tmp[5];
        p[2] = tmp[6];
        p[3] = tmp[7];
    }
};

// truncating store 8 -> 5

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 5, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::little>( tmp, v );

        p[0] = tmp[0];
        p[1] = tmp[1];
        p[2] = tmp[2];
        p[3] = tmp[3];
        p[4] = tmp[4];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 5, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::big>( tmp, v );

        p[0] = tmp[3];
        p[1] = tmp[4];
        p[2] = tmp[5];
        p[3] = tmp[6];
        p[4] = tmp[7];
    }
};

// truncating store 8 -> 6

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 6, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::little>( tmp, v );

        p[0] = tmp[0];
        p[1] = tmp[1];
        p[2] = tmp[2];
        p[3] = tmp[3];
        p[4] = tmp[4];
        p[5] = tmp[5];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 6, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::big>( tmp, v );

        p[0] = tmp[2];
        p[1] = tmp[3];
        p[2] = tmp[4];
        p[3] = tmp[5];
        p[4] = tmp[6];
        p[5] = tmp[7];
    }
};

// truncating store 8 -> 7

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 7, order::little>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::little>( tmp, v );

        p[0] = tmp[0];
        p[1] = tmp[1];
        p[2] = tmp[2];
        p[3] = tmp[3];
        p[4] = tmp[4];
        p[5] = tmp[5];
        p[6] = tmp[6];
    }
};

template<class T, BOOST_SCOPED_ENUM(order) Order> struct endian_store_impl<T, 8, Order, 7, order::big>
{
    inline void operator()( unsigned char * p, T const & v ) const BOOST_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( is_integral<T>::value || is_enum<T>::value );

        unsigned char tmp[ 8 ];
        boost::endian::endian_store<T, 8, order::big>( tmp, v );

        p[0] = tmp[1];
        p[1] = tmp[2];
        p[2] = tmp[3];
        p[3] = tmp[4];
        p[4] = tmp[5];
        p[5] = tmp[6];
        p[6] = tmp[7];
    }
};

} // namespace detail

} // namespace endian
} // namespace boost

#endif  // BOOST_ENDIAN_DETAIL_ENDIAN_STORE_HPP_INCLUDED

/* endian_store.hpp
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
*/