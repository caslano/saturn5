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
atAnDA0q0RpUJhp0IX1nCXyHAByHEwf4b6u4QXWU8Rt6g/K1BpVxvdSg22ymBrmpQdfYjKjjKI4LKAD5kaKeDrHwm9BKxNQ1EepZgswwVauybSVBYTMVA8t4RdyaGmjWvu5i/dP5SzGfbAY+6xGJ+0WLH8bP0n925xqlDr/6q5EyUOe50HtQxU/Ct3CsZL40pSqttaoD+aGqHRG8tRd+FBXqBTA0xF0kVi/bPELWNYrqEsFJw1uRfSj36Gsg9wvE2t/hL7+00zr3aedD7l9S7mevL5G5f2XIXcC5O9og95WUezPnXkm5DzPnTnwz3iuCRNq4GTMNWYdw1mibDBL5/BaVtSJN1huh1g+YPqqtjma9fD3Ltnol28JkZ8fpsUg+NpXRVLFYvnd61RWrIq5gNU0fTfjkF2QheQcTfGyWDqvAoW7xVg0CQD4EXBIedsoHiDuDtRuiWR6cj75lvFgR6e/565S/6q4bpb8qWUnQNTBAG6jwFKaOyIBIFIQTsNAjg3J1yjBM7fBXRUWKdecnO3FqSAVrUg5sMXjhSvfqlT4jKoWvY5ymMFcXkXWvlhGX/vmDOEZc2nQojDCEH6t4bF2rFX7uXlOmx2MLSWspR/eKLV0sIg9BLYGKJ7FXwoa4r5HQGDante1ANa+Yxry3k6gPJsww+rstQCn/kB1qXRshGeMPJc3Xd2IlHIdOfj8o8cjxziio63QZb2uOna7/tast78reTuUTFzoZvl1yFcLwUEllq7i+HvIuqOLPfKnikS9VQHAxqrZcVVtq1warnoBrNkrgPouYbZRlnsryFEpNonCowEfQaQq6RXy4U6v75SskaD0rzMm7OEMnE4IXiHkuBCND+J4ggMLAOozK4DM8kfNrlHPvh0qpKuxTVH63J5bXVUw3qPPHqL5Q/F4QY9SyE4S+tlzUkSiitE9CmjFO2Mm3xD+CccKIP6ziVW1cRfzB0oI9YDniEvM2ismgIcJtNFYLJiMlJA7HoWEWX0nOtP2KjyzXf9S2dpfyIVhVPO60Mhv6z927mD47BmasEkgDm2IhmLXg7bP09vZKaRPIajdXX/9dIz7KwQ2n3gPrD7cDIE+c9X6sP9zXWK4/Kkij3HO35fpjbktybVGm1hZlcm1x3bm4tjiRmn/93Wptcd/G7NcWadcTl7b1sZ6wuTA6JT7Z8elYfMoTK4g/oIJba71k+LJBEZ+UsjIIEjYe3my5Mpi5jLDhVdjwathomamA3c2Yhj+ptZ9GtV6yWdPavzrVchlhrbW7+qO1l2XU2st0rb2MtfaqbSatvUzT2ssGnNZebRWa+3MriXZoC2oCTkxRMQLFr/4MN7AvxA3sWbiBXYnZD5svNrB9pHYfexfRcSR2y/1CLRUR3sMcU56k0SkX6YG95Ufq6COt4iOzjB+5p1F85Dc0GVE1PiZLqZYv+5n6tvv+pFoe3YoUTguJo5qTanmUc7+xlRRoc+6as6Ra/ue3SmTWbkPWPM76yBVSLT+Sa70lTdYDZ7JanrN/x8H+LKeWU6+KG2P/85k+oZ9/XDwSi5fI53bBofPFemwJDdvuO3HYLsBhu4CH7Z1LcdgS06iY5Pp60udJCamDJ5IyAcVVYg5s6xFllNrOMf4DqLbPd/Rnssp2vhUxYz97pdJH3VezPorqN7sF4UNYPQToQW4q6yrrXqztCcADUr9QLRcNo01eis17j5T/d4zEeTMBf2KngAUFs9ix6PrLJKvErpNP4dhV8ikgo5+7QppYC6DHzzF5MA5Om1oK3gradRAa8zqOlVwUVDzZcVY+fODfNVRZhGQiFH6F5Lo8sQQKKRbZK4pQdZ9rk8php52kYIDMkF+bKtM32Slk8X4=
*/