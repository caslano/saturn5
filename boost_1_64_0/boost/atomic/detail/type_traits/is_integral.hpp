/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_integral.hpp
 *
 * This header defines \c is_integral type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_INTEGRAL_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_INTEGRAL_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
// Some versions of libstdc++ don't consider __int128 an integral type. Use Boost.TypeTraits because of that.
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
#include <type_traits>
#else
#include <boost/type_traits/is_integral.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
using std::is_integral;
#else
using boost::is_integral;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_INTEGRAL_HPP_INCLUDED_

/* is_integral.hpp
KK9M+TUqc4zInEl8mcSXRWZbqX7epfLnnpE8i9xjVcuJhH5jacapJy/vUbz+8oQn9pzkWai8MXiREj8h0sW6XvWmvMjWKdjMde9IvuOUV9QmlwNLv4LzNsfsRuboLZnOd2xNN2d17Z6VOjecY+bIFGZhMzLOmnZkds3ISM2GDd01z3LdU2RMbqXs9zOd+1TTM777lOYZmOXcp5r2eMetHfL1urOznO/3mpqzUnt5eZsmXyP5plK/1DWD+eyxy0DPukHyDuFcF87NI864lvZ8xA7EP0m+3mbdFX9co9eYcb3EjGvb/nXsmfuksW/JGw3Y/3M1iH1yTuxTzjXF8qLa/W7utZ5aSatt/fapcbTxe21jtrbK3lK1ZHFt3bJ6mTuwpYZWjkPtfFZxs4WKasavyk4Te97eW/KtMPdaV3quqxxaJcXIuAzO0wBjdelyy4xDkyfonn4G6TMl/UQZMyNi75MqG2nXH2uB+mNtEN272qt9kA3SRtJoo86T/Ux+0y45X2jOa1u0jBGeudzdP5f1Mr995Ugl2C8XNrv6px47qb5Y+0g5vWtFH6SYfnFk0tptc662ea3UiTI8a/08le6uQrJ8G0cbvuf/1rK2oZVpSbXCvrdUue4J18vND3Tvof2UShco7yVH67UroF6qM/08KqxuKktJ9nzRj/I3EsbI99I9+AhJ5zrhvbS/f6+pt0efW3P89V5j/4YIqbf2dVidVS4HjRrujvJ2nLQCaU8LbaniYmMPQXt6xvJ4Ymw4q7fuf6q83I2EK+SFo7t9DdH6uoZqHHRX85Ff6DqbqU3ljjD86CMkfhbjOtPwo6+Scz3CvjvRMgaYdecAiV9pc2lFZpqsM2VaNuuQ4tb6Wkfxr3NPuLKodV13GfgBuAxck0P7ihLzBUs9Pb5gvWs4/3ckXt7z1t5+ztci9NvyaAxv9LT5kEZPd/FaF/p9YiLTed7gQvV56a1fU56/fueSd39g/YSaFlY/ZOLy0kjvPC9tYQI+O6dpmw4EtOlS5LN3h/KJqz+G7pcz6Zt1SwJ1c/ODn+rjv+YnuGZJ6DWFsqjfWfh0iZzRJb/ZfJxF0jvPWeR6Pl1yjUDO4sR8f7tusvmuu92cRaPADutvgqO//GBebXR34rza6O7Oj48wHvKNfUP4p7s7wD/d3Q7/9CD6siP805p+IfzT3R3kn+6OO85J7/w4T5R/mvTNa3zzhvBVw/iwYTzWjvvyDea9hvNV5wjv9QfHDdozbc3K0t7ZG+/Ky/tL6n/PvvvBvNrDvx//e23+deX3dZNyY7Ndfy9y/X1O29+yHoaaIf5wx7r+nqZ/X2ihf9ffpfzdjCxma03Vv3/O38rt0vdU8p6MNBe3S32hDgH/CY5TX6jHgRngWWA35TJlgV8BeyinKRvcA+aBj4N9QL2evrvhfZL3euo7dgT4B3CGcvpOAd8GTwffAWuU0xcFD4CNyuH7uHL6rgD/anzP6jsK/a3d7PE9+7LuLf5z8Cjw12AJuA88BvwVeLyedziP+7S8Si3PzXncrNy/W8Gx4G1a3t1azh3gPOWsLXD5Wt1rnu3K83gpt599D9Vyz1WO3XngeLACnAMuAxeBteDF4EXKba5XbvPF4NfARvAOcJVymdeBu8HrwWeVk7cX/Bi4D1wN2pW5CewK3gx2B28Bi8FPgMeAl4OzwU+BZ4BN/L8E/DS4ArxS29fsPFMDN2n7bD3dru27z+XDeZpy8paAe8EK8EVwDbgd/AL4MHgz+G2wGdwJ7lCO5SMaf1Tjb2m+v4G7QWzW2gMeAT4OTgOfBCvBZ8FrwRe03uucZxf6zKbZ4xv7KPLZOArsDo4Gs5Qb3gMco/Y1FuwHjlMuaAk=
*/