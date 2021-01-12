
#ifndef BOOST_MPL_BITOR_HPP_INCLUDED
#define BOOST_MPL_BITOR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2009
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

// agurt, 23/jan/10: workaround a conflict with <iso646.h> header's 
// macros, see http://tinyurl.com/ycwdxco; 'defined(bitor)'
// has to be checked in a separate condition, otherwise GCC complains 
// about 'bitor' being an alternative token
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitor)
#   pragma push_macro("bitor")
#   undef bitor
#   define bitor(x)
#endif
#endif
#endif

#define AUX778076_OP_NAME   bitor_
#define AUX778076_OP_PREFIX bitor
#define AUX778076_OP_TOKEN  |
#include <boost/mpl/aux_/arithmetic_op.hpp>

#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitor)
#   pragma pop_macro("bitor")
#endif
#endif
#endif

#endif // BOOST_MPL_BITOR_HPP_INCLUDED

/* bitor.hpp
JMzBZPweJ+LPmILW7ZV3GLGqdnul7Q5P/AB9MAMr426HfhjDZf5cF/0wHiKeLx7GR/EIBuJX2BKPYziewqH4NZoxB5/DszgPz+EizMUsvIjZmIcn8AdJT2Qhed9Q3j/0xwCCrb2fa5KO69gQb2ArvImd8Rb2wzs4F1nQ9JcVcD164kfohQewCF7EongVvfE2lpB+i8vgY1gWh2B5NGEFnIy+OA398H2uJ7XwI6yNe7AB7sWG
*/