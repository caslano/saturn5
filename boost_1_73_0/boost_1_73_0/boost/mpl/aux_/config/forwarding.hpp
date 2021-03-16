
#ifndef BOOST_MPL_AUX_CONFIG_FORWARDING_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_FORWARDING_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
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

#if    !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))

#   define BOOST_MPL_CFG_NO_NESTED_FORWARDING

#endif

#endif // BOOST_MPL_AUX_CONFIG_FORWARDING_HPP_INCLUDED

/* forwarding.hpp
Wz0es0RDS5HgwMxYDnhjOPAPLVa0BZHGTZJIlxOCId7opOkxvNgi63XRlULBmEKPmIUalUJ1MYXmxrVgZqTRrZmcqmDhPDFqKniXYMR4I/VOWQgzSjmXAT8wBt/qseGd2u1i3GA1wSakb2fhu0Vxu5xrU9TBnJZgSmxh5l3sHQazIfEWpoi0hZk3BobkaJIhKzkHJU8s7UUKQyLIukijR5MjoI0y+AVXLelYnqsWoUGIGTRNiWte48LTPiwplTQ=
*/