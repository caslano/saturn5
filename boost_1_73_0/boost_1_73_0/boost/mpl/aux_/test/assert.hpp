
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
TZQotv+lwKMyRo9WeoevlAyNvcOiKzygHzwnpXONh9+XY3BaK5AW9iV3voDWIsjaOuQ56AJORWvUKWEBNidKbl68THx/XxJgNa98KG7xW+tfDxoe2gujK6hkhWACi+BKbbjYplC1yknfRPsuYEJXFa/zXlZK6cnCJ+hmnZ4Eq9er24z24x5w/vb4Rl2aPqKRxQGCE8ALhwZciZ3TUHILG8QaRrbUbkTYrsMGK5yRTcONJ7H0S/zo8YnHP5J49nlCH8eEg3qajW7rnJvDxdNkT0J7Tr9Hg07WGO20CJ6HbwyCLXAfx4gstHUp/GFeRC6FwMYvTehkiNR7rL+6MvUxPfs9Z90GhZG00KaKg6+v4J8Eh2D+3aZh1rW0jbayz/svg0IqLkaFRJWPAt/l66c4AyujgzmMPuwyHX5ZPwFQSwMECgAAAAgALWdKUh3ZJowQAgAAvQQAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NzFVVAUAAbZIJGDNVNFu0zAUfbeUf7hqNU2qCG6nCdTgVRobohOUVlvECwLJdW6IVScOttMSvh476RYEGuORPCS58bnnHp+chDm0TnCLC8JklWt/2WF70CazC7JM0013gs36LiWrm9UbwuiwzmjfQsZkDHdo
*/