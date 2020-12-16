/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   is_ostream.hpp
 * \author Andrey Semashev
 * \date   05.07.2015
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html. In this file
 *         internal configuration macros are defined.
 */

#ifndef BOOST_LOG_DETAIL_IS_OSTREAM_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_IS_OSTREAM_HPP_INCLUDED_

#include <iosfwd>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/has_left_shift.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/formatting_ostream_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T >
struct is_ostream
{
    static BOOST_CONSTEXPR_OR_CONST bool value = is_base_of< std::ios_base, T >::value && has_left_shift< T, int >::value;
};

template< typename CharT, typename TraitsT, typename AllocatorT >
struct is_ostream< basic_formatting_ostream< CharT, TraitsT, AllocatorT > >
{
    static BOOST_CONSTEXPR_OR_CONST bool value = true;
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_IS_OSTREAM_HPP_INCLUDED_

/* is_ostream.hpp
O/wtjIW/c9gjNqn+FMO3r/vr8R8Mu8Ahet8ZChPhcNgPjtTjcT4cB0fBCfAC+BE42m6nztdhmqGdD2l998C+8CsOvZyBofsnVvsnTvsn3nG9z1e9kYbzZbvu79N6Hd4BM+Dn4AD4WXiebt/NDvdu7xqWX0nLn2R1mz4l/z3+JKNygnxKnjNfkqbvg5v9R4bnO/IoNHw73OQ78pz5jfxv9Rd5rnxFvsA5dBSJur2rJw3JRpYi1chO5AByCDmOdKnv6hmGTEPykS3ILqQJOYKcQmI/je/JT0fsNCMhEiIhEiIhEiIhEiIhEv6fwjmx/8dq5mzY/ydh/9/Mw9BtfX3PMSi3nDp4PGL3v8rhFzDDa/tzk9BJ7Tyb+1prdVdR/wULZntOv4bmXN8s6mCv0dv8AfVpsct1+xFxf//VvL6Jrr1Wv9FlS2Veq9f8xjXyOHhU0jub7Z77tm99NPBbo13gRreNlNptuNa5ZQ37D331Od44tw+ZkbpQXojIu77ah540Qx/i1qGoqLjIY+hLyyagm+gtNvUtZbavb8kfsm8TYCdJH2/oW5eurt1Sd4fuREkfYH9P8qOy3dGRv/JjThvPvpI+rc31+dgP4bglp9nHTbav0O1Bme5z4VhU0Lkg6+F11nF0u1EJOV63SP7OZhumM3g/xVf37WmWHYX7m7jT1A58OokxcCr0jcGmPlJ3xwAM7xxu6tO+cab5Q9oDNkv6aO943/igiTG2ziDHmHOXs8kX6fhur7y/n+pLP278bmoC/Inu5yL9buqNUsa68jIy9dTvN78meUZ4W78DjWmM7iMJjpB9HPIk2ftYsbp4xVpMIaowpvPY9X9LyhnIvnJl+3X9NnILHEGjz0M2IU+l83w9g7UFTR+bjK6Offpag/kbyn9ItWyDz/xcSHV+0z6wTYytR2RfrAmPc39Hd3ZX2yeHhAzkOcZWvv8eUbTa4Q4sXBsYdANsMSsN48qVT8dhgeFaZcpXYbDjNOVbJ/kSHPkSJJ9zHLq/0Z/iyJsSkPdGf5l55Ja8aY68aZLXbaPULwyb+7beGaHvbDuYGHscFKjtqD0uZDvB2qbNlCntoG2ub9imwRslTtrgusac0HFAsoQEvT422uNA/HCFbdPXGNAX1yWH3xeB73mN0jpu6Rbw/qHWsd6uI1WsDq9+9e2cWzjq5Oq3ZjUe+4SXvEJ/nVqSpU7Om4rx+pkCvSnk5UtoU7zm+wplma+b+u37TqKf6021r2n2bnlJQ3ZtX//+KGX9zL/Nf++LbmrI6+lfJH+JtxvpNWotEq/3wntFty/naJTjml2+Vtqm+0uR6+jlrBmmEKfXZIdtunUPOSX7WeWd7Y125HPb6SfAP0m+Mu8iL/t0lLfWsc9npF6f4Ro3O6id+i1puY5/mR0/HMt5Ar+Tzno9CUuS/df6kgx/2ka2GyHXdijC9R2G8Z38UPf54ynua/E7/D/5HNi0mW2e2m/T5rnDS/wDLZ99fcojb3/r7pWXvPj8Kzc9999j02a2XTt7NmrttUU7WzZnts2U/paJNqyhZ+ta+ETYCU5y2DK0qF6swZahn+qla/586zcEKNT8XZGFmn+g2hRkwnQ4GA6EQ+FlcBicCofDq+AIuAyOhB+F5zttLNKM9XLbRmn+E/Y8U+bLkr8vchSxbABi4E54PrwLTodPwSvg03A2vAcugF/UejXAQvgluA7eB2vg/XAjfADeDB+E2+AeuAN+Bd4HH4b74CPwoNrqvAK/Cd+Fj8GO+t3eTvBbMAnug6NgE8yC34WT4FNwKnzatp3Q+QccYDjuz2o/PQcz4PMO27NG1Us02JYcUr2XYS/4U5gAX3Ho16t+T4P+D1X/R1De74E=
*/