
#ifndef BOOST_MPL_AUX_CONFIG_PREPROCESSOR_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_PREPROCESSOR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
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

#if !defined(BOOST_MPL_CFG_BROKEN_PP_MACRO_EXPANSION) \
    && (   BOOST_WORKAROUND(__MWERKS__, <= 0x3003) \
        || BOOST_WORKAROUND(__BORLANDC__, < 0x582) \
        || BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(502)) \
        )

#   define BOOST_MPL_CFG_BROKEN_PP_MACRO_EXPANSION

#endif

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)
#   define BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES
#endif

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING) \
    && BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))
#   define BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING
#endif


#endif // BOOST_MPL_AUX_CONFIG_PREPROCESSOR_HPP_INCLUDED

/* preprocessor.hpp
5Ou+DpYUMxx7HKNahOyy6PjrwwGZdjLAb3pPLXgtEZ77eq4bXvPu/JIC7OWDe+snqKnvj5kgjEGJ0S/ymXCa5LstlTkxUVrESlKyQMAA5I+2nuNV2lLNwuEV/zcLt7qmNAD7X4GLm5jtkDWTW7EMcnuQNUQQgQ5nu/zzRsiZLjRHQkH2lWltru1ETaqsaDTsyiZFmP17XaENN8LrmaC/mWn9aUUPXyuHT9QL0ssrbXcyKEZufbe2xPmbf66Cx9i/9myfck9F6bRpxN7VZ6drFG415cVNUS4v+rVGRp0NlBxCEeI/+eNWosuf2GdjpdP3tm5sFGBo74IJw+TeinXtTsOlX8cwmKwLFbq6Qevai45KN7eXbXBGY6lOH0kLUJkg9SurY1K8q94OsL0H72CN9+fnwVEwsjVkOBK4Iz0AYiSxAlYa5P4tlz1stJsyq9lT5HixSqNzkHioTK0IdJ9+Yxn+4WDpC9/iRBd+ICPkUWR3At8Uu2fAy8Xv6oI0Lb5Zxc5WuLjDZ8XA46ggJeZOwRG1qjBLo32ZTzewChKPyNmUt7tF75BE/tJq4Q==
*/