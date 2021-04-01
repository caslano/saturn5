
#ifndef BOOST_MPL_AUX_NA_ASSERT_HPP_INCLUDED
#define BOOST_MPL_AUX_NA_ASSERT_HPP_INCLUDED

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

#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !BOOST_WORKAROUND(_MSC_FULL_VER, <= 140050601)    \
    && !BOOST_WORKAROUND(__EDG_VERSION__, <= 243)
#   include <boost/mpl/assert.hpp>
#   define BOOST_MPL_AUX_ASSERT_NOT_NA(x) \
    BOOST_MPL_ASSERT_NOT((boost::mpl::is_na<type>)) \
/**/
#else
#   include <boost/static_assert.hpp>
#   define BOOST_MPL_AUX_ASSERT_NOT_NA(x) \
    BOOST_STATIC_ASSERT(!boost::mpl::is_na<x>::value) \
/**/
#endif

#endif // BOOST_MPL_AUX_NA_ASSERT_HPP_INCLUDED

/* na_assert.hpp
IorT6yJF6y71QzSWY22o/j0AZnw8cxqZywA7x93eZ7kRzigguATQbohliN5APD9Hbm3oJF8LmDQNGCLqPeGXVdKraZE7WvLVFA7ZMACqUa/G7YtuZjxbpeuvXZcS8bczNB54xhGltT7fl4JahKL57BUO2i/Qeo4JPIcY6FAhDxJo3Lemt5P9BIisUVf7ahkXk+X2fEZqw/hBCUlCmWF4lDmczHliVwNIvZuWf9TNt6/2Px56CHspyqW7MTgz1OJwm2a7dtktw/XCrjHJeAcxfaX+Y5ANdX8vcpxf/+ZNc4Z2mFWTTd+SB80R617j5uTbdL9muAjJd87UIkqukzM2AEwStS5Wrz8oLIzDswYz9DwADaTjMNzUKYHscQO6nGEtvet1bJ+r3brMngWGRc9Tj2JHes6wZlyZfJ6Z8SmFgjWlI14kHMOFS507w2s2XzMzvqmB4gt6/RhaAY4v9RnE4YUcT0Z7OBENiuDjdWwR38fhMOmE151kkUV65qRzFOknBzZk045iYEBJDXWRRo6TY2XX2QET9dk8MdCyZZUs45YmFRIjNaCRzSBFsg==
*/