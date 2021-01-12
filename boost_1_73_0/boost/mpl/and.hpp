
#ifndef BOOST_MPL_AND_HPP_INCLUDED
#define BOOST_MPL_AND_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/aux_/nested_type_wknd.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>

// agurt, 19/may/04: workaround a conflict with <iso646.h> header's 
// 'or' and 'and' macros, see http://tinyurl.com/3et69; 'defined(and)'
// has to be checked in a separate condition, otherwise GCC complains 
// about 'and' being an alternative token
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(and) 
#   pragma push_macro("and")
#   undef and
#   define and(x)
#endif
#endif
#endif

#   define BOOST_MPL_PREPROCESSED_HEADER and.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(and) 
#   pragma pop_macro("and")
#endif
#endif
#endif

#else

#   define AUX778076_OP_NAME and_
#   define AUX778076_OP_VALUE1 false
#   define AUX778076_OP_VALUE2 true
#   include <boost/mpl/aux_/logical_op.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AND_HPP_INCLUDED

/* and.hpp
7udJflKLsls9x/lJkA1eIvvGJ8Q3AbzeQ7Mt0m2S9avbR9z7OWEyJ5pcFZFuyZL8asvgOWZYQEV5DjoRROyRfTf2fjV/mZQyPV7Z0mzX5LRSn+N5vetXux/Mlfw2JioQdYh/KJ+1nmp+U812myV5RKljVl0xnzIelLIQdm3PcTpvci4gV7bncFd99dR+tjhUlmH80LIcswzqxn0s3iF56yx5a02cYd5iTd5sZnuOVbuDXGU+
*/