
#ifndef BOOST_MPL_AUX_CONFIG_ADL_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_ADL_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/intel.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// agurt, 25/apr/04: technically, the ADL workaround is only needed for GCC,
// but putting everything expect public, user-specializable metafunctions into
// a separate global namespace has a nice side effect of reducing the length 
// of template instantiation symbols, so we apply the workaround on all 
// platforms that can handle it

#if !defined(BOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE) \
    && (   BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840)) \
        || BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3202)) \
        || BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, BOOST_TESTED_AT(810)) \
        )

#   define BOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE

#endif

#endif // BOOST_MPL_AUX_CONFIG_ADL_HPP_INCLUDED

/* adl.hpp
/1v3sjaHNPQJ58UTQhrG/ZR4b3F08p+91v+9NFwfnfzCu3aq8WVmHSOJaRiYm4bSf2L/Faz/1v36neH+fMI5pFgY/3tTWefr4M++L3PXP++vvOPAZ+7/x87Xd5SIHz/1loT4TQnxyQnxiQnxCQnxSxPiGQnxignx0iWK/O4zTbuifHUzL+eY3xLqTtkQus3MG56Z2GPeYWOjW+HhnLc7fmzoQ6Plw7TsMdT7y9vom8J47j7T
*/