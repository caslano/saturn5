
#ifndef BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !defined(BOOST_MPL_CFG_USE_OPERATORS_OVERLOADING) \
    && ( BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || BOOST_WORKAROUND(__EDG_VERSION__, <= 245) \
        || BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, <= 0x0295) \
        || BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(600)) \
        || BOOST_WORKAROUND(__NVCC__, BOOST_TESTED_AT(1)) \
        )

#   define BOOST_MPL_CFG_USE_OPERATORS_OVERLOADING

#endif

#endif // BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED

/* operators.hpp
HmBGbqIt5Ph1XNm090D2u7181sWtc1A9LaHUWCY8CiEfLBEvH/RecJ1zB/yfkFg+ISmf5LPGYcyaOPngtImRjwcQQVM+pqXzKPSwTSgP3CYSTZrHeHiiBiA6FiGAuNlSCxDbPt+QA3pJXA6Y4usgjntJ4pKIILd5LyaaetM1sThq+8a8EPym/YGLFG2XA8otd+tnDNcNXXj5NkOteQUBEJ43onFCGOxDzdjF1HZ2JgToZDL+BX/rKTVD4qrgr84=
*/