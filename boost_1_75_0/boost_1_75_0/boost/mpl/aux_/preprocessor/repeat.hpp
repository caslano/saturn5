
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
pYoGLQm+muE6+TA17V8ibsUyB8E9UtpnEW/VKnjwkbP94kP2inzniKG7hJTYJnkCYNfxnW867dA58IWzXSlda6VVv5WUQYs5PDDmfA2rSqqW2K5xxx/5u+GV2S+kdHmM1Pr7N26v+2n51jy6rI4+rJErG1HMaaibRTdXA/WLURczY6iVBWDEl3+h7Cxj4gCyOF6OAleguBZr0eJWXBaX4u7ubovL4hR3KO7u7m7Ftbi767L47llOkrvc5T5MJjOTzKeXvPye/N+b4sGjUlK95zKoWDlihXYWOiKoxoticOvTiZXdiqqvVbiE/sL7cot2sRfJQlfTNDRnQV/4sCDs5+BwbZMt8tz9KeiJmflRnfIFb5S1s5nKi4R5DmqAUBkPRHwm+gH6nW5IeuCxWTpybWr6pLG75jw6LdSdv38P8cdFqK9Muv3j4H7nJurgpcgu8M2mcAJVD+Gafb5X+GMY8vYvnO13pAvXNlhMcy9Ur5KkUHcsH4UgKcKy/CSvZ2XoQmDF6VBZgqqVtVE5Q9PXLT8BbfuOdPVCape0dWYFhRxRtPmQ9V23Tnpa2ZogEp+fBRlxe7YiGeG6PgASoReS64jvT34Czonf93klj+XbZea74v1SYuYy4hCachX4OPIN8Lsi5Y0kHj2ZbW8/PlO/0fiiuNz6XreK8IBfiH36c5dYdKJxSNFjCS0G9prSHFe5M8aD2Xduej1wT5F9
*/