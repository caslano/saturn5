
#ifndef BOOST_MPL_AUX_PREPROCESSOR_REPEAT_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_REPEAT_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/preprocessor.hpp>

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_REPEAT(n,f,param) \
    BOOST_PP_CAT(BOOST_MPL_PP_REPEAT_,n)(f,param) \
    /**/
    
#   define BOOST_MPL_PP_REPEAT_0(f,p)
#   define BOOST_MPL_PP_REPEAT_1(f,p) f(0,0,p)
#   define BOOST_MPL_PP_REPEAT_2(f,p) f(0,0,p) f(0,1,p)
#   define BOOST_MPL_PP_REPEAT_3(f,p) f(0,0,p) f(0,1,p) f(0,2,p)
#   define BOOST_MPL_PP_REPEAT_4(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p)
#   define BOOST_MPL_PP_REPEAT_5(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p)
#   define BOOST_MPL_PP_REPEAT_6(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p) f(0,5,p)
#   define BOOST_MPL_PP_REPEAT_7(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p) f(0,5,p) f(0,6,p)
#   define BOOST_MPL_PP_REPEAT_8(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p) f(0,5,p) f(0,6,p) f(0,7,p)
#   define BOOST_MPL_PP_REPEAT_9(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p) f(0,5,p) f(0,6,p) f(0,7,p) f(0,8,p)
#   define BOOST_MPL_PP_REPEAT_10(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p) f(0,5,p) f(0,6,p) f(0,7,p) f(0,8,p) f(0,9,p)

#else 

#   include <boost/preprocessor/repeat.hpp>

#   define BOOST_MPL_PP_REPEAT(n,f,param) \
    BOOST_PP_REPEAT(n,f,param) \
    /**/

#endif 

#define BOOST_MPL_PP_REPEAT_IDENTITY_FUNC(unused1, unused2, x) x

#endif // BOOST_MPL_AUX_PREPROCESSOR_REPEAT_HPP_INCLUDED

/* repeat.hpp
PHpICf1b9aTAzNUGad7agUz4bofiNt03vDyjkcUaPG/g7wlD2mB7d5SZJXFQwR4p5fZYsmhiqQRVdVroasBo8j97zDfzuQXYeoFcoa2L4V1wwJ6I9/BiSqBiELWpeOf56uHxdnQfsAshcE7bB/wgYGPfTEjyK5Kj4fcOcR5eVHKB3gO/ALMzPLXU6UeOPh+NfkhGP1T6twipwt9DmPAddQl/45Pvru+fUEsDBAoAAAAIAC1nSlIc9uVnRQEAAC8CAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjY0VVQFAAG2SCRgbVLLbsIwELz7K1ZBHI17KByQm0tpRQ8VEaH0iIy9IRFJjGxDy993nfCoqp7snZ2dHU8iA/qglceUyaotLB17PH9ZZ3zK8tdVxjy6EzogFHSJes+kuDOk6IfYgA0g75jcVwaZdHioz0QwKqiUxS1E7gspLs1u6rmusA2XKd0VROm3pswX4UAD1xJkqxrsnYG2zqEOUFofoj/qir4NUtumUa1JGeexfThuGzOGYZ7P8+X6fTYGzrsXHV296ZduYs05Mf9pjAgGfoThR/6ynEJ0NRViOF/kq7dsGmWzxXIVz032ORO13YmiqnEyeRyF7/jymx8ZcYg2n5I/tOSWUwRj
*/