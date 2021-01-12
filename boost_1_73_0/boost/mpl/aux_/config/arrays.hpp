
#ifndef BOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && ( BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        )

#   define BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES

#endif

#endif // BOOST_MPL_AUX_CONFIG_ARRAYS_HPP_INCLUDED

/* arrays.hpp
RAjjkA+N1TNr46YnjclZ54pdsfvqqtjs47bQz3v3LjctPSncj9wdxiQOy2Tuyl5/9vjEYdstc0IF8/iinOO/QWgLpYdzcjXxcO9/n/detuXTNqoZllMOxS0nPYsqiFuqhvhq8eZZ25aePvT81LH9h48Y3t8zM0mpoV/F578cHG1Pm/zq/uy6Kaedlq62ymmfWu7XrOVaZadtd1w7yzRloJIyUDo6Foap1bK/a02evEb2WOsO
*/