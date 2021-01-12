
#ifndef BOOST_MPL_AUX_TEST_ASSERT_HPP_INCLUDED
#define BOOST_MPL_AUX_TEST_ASSERT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/cat.hpp>

#define MPL_ASSERT(pred)                BOOST_MPL_ASSERT(pred)
#define MPL_ASSERT_NOT(pred)            BOOST_MPL_ASSERT_NOT(pred)
#define MPL_ASSERT_MSG(c, msg, types)   BOOST_MPL_ASSERT_MSG(c, msg, types)
#define MPL_ASSERT_RELATION(x, rel, y)  BOOST_MPL_ASSERT_RELATION(x, rel, y)

#define MPL_ASSERT_INSTANTIATION(x) \
    enum { BOOST_PP_CAT(instantiation_test, __LINE__) = sizeof( x ) } \
/**/

#endif // BOOST_MPL_AUX_TEST_ASSERT_HPP_INCLUDED

/* assert.hpp
aINO6ALjs2iEoRAHVsiGPCgGNyyCemiEDugGw/fQB4MhBiyQCplQBC6oge3QAu3fQyf0wHkw1aOzHp1QAtWwth5t9WiDsxCxEZuBdSOaNqIH3Bux2Ub0QOtGtGzEVhvR8hw6IBUynzN8/vf53+d/n/99/vf53+d/n/99/vf53+d/n/99/vd/9neL4drIXmyLXjXye57CmZXzXYXFM2YXOmbOdLo9l/Zbdly+f6bD5Zo789L+
*/