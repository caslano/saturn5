
#ifndef BOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/config.hpp>

#if    !defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, < 0x582)

#   define BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC

#endif

// BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION is defined in <boost/config.hpp>

#endif // BOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED

/* ctps.hpp
OweQ+MH71e3rC/VDF9x5nh/PhPpVzh28YS8Ily/rF63GfOiPwB7AFazE1iuDSTx3ljXjFVw78dpwxmTLcwge+fSL5sXDrDgjD7xfZIELa47/7RhZyA5/MYZQClC4kDnleoju1SkHJz3kgSHaf64rU76qMgxG2Jzr5OjsYJtbgTaZGfzSHL/K7vko+hftPykdeVj0X7U/7b/V/rz/LtL+xpMMoiXi0VBHkYq/lIo3dGlmTl9HblDXkMoq6GxvQzna9p2c3zn7FWTYzIYlpuHHZysr6mqNEmYSQiS99xEtU1sWGjX5U9/obJBYeUqDkMKQMOMakgnkNJo79BUkRK1tfux2xxlV7swvqz/5Ffl27gO4Pc6E73KG/LJdPEwex2d0RC7Gy9inKxoiRg8m7PFZmRjMMKTLqNWGz/nrl+yrBJ5AMMmUrjdzHA5j8wKp2xNDHUi66BVI2siEyHaBiu+NajVNCs5kD18s2yLIAmWFwkYGV4r6TyrzzNtyRq/tcsAJEce2Ug+0emsacgYeL99vHfuNLUV2ksbM9QRv1LNkEMM3OrHVswKlqhguhyWgbL0BeDbct1l2CV78ssp77VTny4CpTtYabudTIcJikhkiSHp1kt0uWK+ymOylM7saDSABDiUcD4A+rmOcDB93e5x7CpCQQK/trVeQ7NXQ4A85nJTP/Ai51xNb616Cvte/7sEGATlsKfv33fwNtVYG
*/