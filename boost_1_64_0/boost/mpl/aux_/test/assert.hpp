
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
9ZAG84J7KMFg/M8niafgXU3NMqHxvSD2Quvqt5j5cHlvCRrFLjzmJ2qMw/C68GVwW48T2HQiq1Ds33X55jH0OmlFUtcft3WC7fQzz4g3i18/cfxsnDQwBP4Ni6rGR9AyFTZfxjrNyQIRQYSnLfIiJtYwZ/ZHpxs8rmwZZwubaNSeOnHnuy8Ur+B0WyNY4YV4Vxp6B3P1zK4omgQkc75+vrM/36XXmWeaHjTV33K/DYOgbGwHn0eLnvuNFjh6/R8t0sPPpeBdHlozG+bxZLr1ZN75pMMrC0cq5WMevbW7tkC2VGOl5i44UYruv2VYKunm23PghRzd5BH2Ofy8XNF6WozeyT3LGGDX52v6eRt33uooT8WmaNF1vNnOd9UHd+onVAA6kJrB/xAfUmo4E0Frsxi9yvNMOp9AsaBKPFb0IFjpsLKT+2+ddmKXw5146PWaJrSEP6jt1IN0OstXzm24bsguDkbHp6EB1LUK+M90HrFmphq+I5L5cjZYTROE/3jVkUmupHXM7Z5fglcG7F6Nz1iqy3L9u8dw7HvdeQ/OdTSQCZ24DAZ178QBLg==
*/