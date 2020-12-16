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
+5AoGqbcWxZQ3X7Izef0OLcfcrukN18ZjqN8HuNKPnu0dK8tj5/LbXb5nDiCfUSX3Kz2ZMa24hLz0I8LoV7Qbec8Yh06c1cs2gLkhKckC+VxTDrzWPZg9uM5Z16f89lNhSnzWZmkyyjTZRTWnZ9OHKUmM57PKF8t56sVFJ49nqi5LGPwpHCI5YwRPxvqRVckKiSaiuhKzu0oO5yAnvgtJJWdYjgZ1niFeoZPOIcnr8l3FmBGeHHSLfF5FfCnZW+JihRQsqUHat2ztwPF/IRqSCz17Hml7dHheCIVIPKAdslmrK7IIy/cN1xqFJ8Phn7ICtfzVPQ5fo9lRS9iaFdfQkNLQ0CTTNvpnlVBZ29bp3nK8fWRrdvRxVKtpckN0vXepJDzhLr25rd1VnW8ThaY2d8baWvbxZPPPZONAvfwVIEbz7dzbQFORu8NShsjrEhgRCLAGAZ4jACPSmbNh6ZbJWUSH1P95Aw8H3OKou5J3JBJVMn5AfNUzdJujEWOGhRPpV2JY8Vw0/6Iy3gyNvFXoyjLnjHep1/SfmkSFJMv1rUbWs4mMYd9kTpODx98XhQNnZ9BuwkYtRsh8htHIdrqJcTZC94JiSLtLaopO+2Ja3NHl2ZqqJ9LPZJmBBrsehx+SqnklEqZQpcnymeGutFqw6aHVYqfKJsHrThoQWjrNGcJkbNLtw1/MvsYXP6zEpB0Nmq8VMz7sNfF1oIAWAuCbTtOho83VnIRJCRCqZ23QUPwUXV6PCTnQWdiJJdp6aQRMHw3caVokmg0iIOJIXfJsn9rDd29V4UrR+YPravqeJqY/1s30CY8lXbG7pXTfViSzkmyhjpGYB0PQY9hCLoDQncGZWypEUNuXZ3GJghVehSr0kpaJZ7V+zBmZYgGT9zWFBojK/RzO/z8VfU5dQ7/EDj+vU8/y/35tRex539E8Ghv2KWtPIIs1wSpRYUe6xRE5Zbqt0fc1eBRwnIiPDeUGnKM0XIoHvYjv3tEBqZzE11505g+L5KfmsVtm8U69sSQi+Sml0k1sVXmD3H+kFRZWFb4xU6XueDSHBWQHH/moRhex0Imgtvb1Gd8A2uAhh2kSdpq2Glr5ltz2AHCv2Byu9hdm0CZ6boJL202VLeBN2DstZuK1dYzO/JhHtq9a8AdB3/mGu6CGhS2/HpD014byBng6sAs8mRTT1lfeUr7zJBFY0qzaExpxsYQnmIB8ZaCbgeuQ7Ca7oDY798aUPXEtk2UoDabujqYvxKmr7AXKt8LnBHu6gNelhYue+oYKA1xDpSGFH3oDanohFsZVuyBY2v9u+jl//Snn3/7pjRV1LJjii/Ws4ZknA8O+o370mx6BAa48/F/yGfngT9tXSefixbUnODK3vnUYn9huGwECwg/tePFedKonc18vvO85CTCc0KUT2MdlsequAs3xlc5hA6ukoRypNY9pTxflpI7V1fsEyIhHxI0QJiNW2S41ubqkuUFarGmZjS/aFCg4Ui2mEXlNn/L/kDJshuhlTx9eflKSz9PPvjmi42/odhmQlQ4thVW9cmy1Aw2ktNHCCX85aSTeVQ0UorgKlGLcpvvvB7cXAJcyK/7mmNjcG9qLeRR/c8HgDLdE9Y3UG1YoiNALg4akhacXk11szfRP3E5PgfSArl2Qgx242dMGMc3zLkyFEk2mzr35+uK+3k91Af+szwK8/RMFaqJzrGom4LvVhe3e9QbzV1e9UozSHnytYiwSo556kANv/f2sM9eyzYBAuKePVpufIDPh2Ijv5TKfgIYgh1kyOPKIk9Z2jzytv7AQGpMFOUixjJBQ9Y4wHwFvQdwiauWujhAW/MBmZgQW3dtsRiygdQNnH3LUQzJbng=
*/