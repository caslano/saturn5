
#ifndef BOOST_MPL_MAP_AUX_EMPTY_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_EMPTY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::map_tag >
{
    template< typename Map > struct apply
        : not_< typename Map::size >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_EMPTY_IMPL_HPP_INCLUDED

/* empty_impl.hpp
20gSnX77pWln2VMux+/+9yNhBrXJhEaPsKLeS3t84/VHqlx7JFr5CQlKFAo4XgwJNqHPQxJsUx6vNuF6G6acMNoPMNpmkBEZQYrqjGqqixwJU3gsrw3QFY4IygJr0xGZu1hEuzmPFJU42oG/K7BaVNhKQWsClSjKnbzA3T+le8vSFgaWyaoSdd7GLSgdv8Upj5LFuMlJ4g2H6QlOdslCY6bQwPQTJl3883w+sQa3CFt2kk7/A1Wxv0IujACxN6jAHBCaB4WD0LBDrGGoD9IMCTs71kYclTQyk6VH/NlsDoGf+C/RMuJfg6bxAMv4NXp3QtAKuf4j9Equ8dSA8ZYPrFQfyehtD+0/9hdQSwMECgAAAAgALWdKUmL3Tp8uAQAA5AEAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4MTJVVAUAAbZIJGBVkVFrwjAQx98DfodDkW0PEnV7GBIKXVe2gq6djWN7jO2JZW0jSXT67ZemnWVPuRy/+9+PhBnUJhMaPcKKeift8Y2XH6ly7ZFo5SckKFEo4Hg25DlchjwkwSbl8Wodvm/ClBNG+wFG2wwyIiNIUZ1QTXSRI2EKD+WlAbrCEUFZYG06InMXi2g355GiEgc78HcFVosKWyloTaASRbmV
*/