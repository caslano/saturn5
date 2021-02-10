
#ifndef BOOST_MPL_REMOVE_HPP_INCLUDED
#define BOOST_MPL_REMOVE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Sequence
    , typename T
    , typename Inserter 
    >
struct remove_impl
    : remove_if_impl< Sequence, same_as<T>, Inserter >
{
};

template<
      typename Sequence
    , typename T
    , typename Inserter 
    >
struct reverse_remove_impl
    : reverse_remove_if_impl< Sequence, same_as<T>, Inserter >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, remove)

}}

#endif // BOOST_MPL_REMOVE_HPP_INCLUDED

/* remove.hpp
8P7bQ50I7iDHWSlag3ZM5+mIYEine5CyA98RshZpBGBLaUh2hTBHOpzboJhHAoWkWuo7zF+4/PuuUf4NtrLowLUZRGGx7dPcnKAUhqhQwdCU2lLdZY91zbatbCbsx8v1+FKSHEO9qKxsRGu5a27gOI9/BY+uV/t7bjY+O2labXWmqwlzloQ/2rd224Cd04xi2Gr2gH2jGQcfbql8DNmirfjuzcer64vp5YB9yDJsaHuP7w22LPZmFG42nxYOc71QuWi7cfDMNYpG+VEYHmY4fztgA/Yc9m/0WsOpNGREaaVWMTwS0NunN9FwS7A3kqvo/fU/Kjv3bVV+0pdOy7aZ/0VXEBAD37gi4Q+G45tf229QSwMECgAAAAgALWdKUrlqbp4qAgAAoAUAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxODdVVAUAAbZIJGDVVFFvmzAQfreU/3Dq1Jeq1MA6bUUkVdV1TaSsiRrWd9ccwQrByHZD8+93YNJMmraX7aUSAmx/vu/77s5OHVonhcUJS1VdaPpscN9qk9sJm2bZsn/B/V3GCl1Vuq20FE7pmqX8CEy538s+wArNDk1gVY4sNdhUe1rOhRM+HI8uIvgYRpCVygI9AlpUJtfg8NXBFq0Va2Rf
*/