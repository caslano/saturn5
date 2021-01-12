
#ifndef BOOST_MPL_AUX_STATIC_CAST_HPP_INCLUDED
#define BOOST_MPL_AUX_STATIC_CAST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
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

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561)) \
 || BOOST_WORKAROUND(__GNUC__, < 3) \
 || BOOST_WORKAROUND(__MWERKS__, <= 0x3001)
#   define BOOST_MPL_AUX_STATIC_CAST(T, expr) (T)(expr)
#else
#   define BOOST_MPL_AUX_STATIC_CAST(T, expr) static_cast<T>(expr)
#endif

#endif // BOOST_MPL_AUX_STATIC_CAST_HPP_INCLUDED

/* static_cast.hpp
yKoy4fnu8L7cRUKUxxv/Fsvj4ef3N9jTHxhbe1/5m5Q+cGh2ekP+JrZHQ72UFsaVRX7t0ZDv+y43/cI4/L2FisJpwleWn78qd5sM1Ru2qlCBx56Pq5sTt6u/FGdVo/Ht+j0hLS+EtMwTonNLuddjaUke8SfTUD7u/JB7XthZwOMsJ40Vw1jvV1lB9eAn5l2TN43Ds+v4GQVozxV7J74e37MuPr4jIb41Ib45Ib4hIT43IT5b
*/