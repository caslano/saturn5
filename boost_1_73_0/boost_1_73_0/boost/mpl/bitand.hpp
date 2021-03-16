
#ifndef BOOST_MPL_BITAND_HPP_INCLUDED
#define BOOST_MPL_BITAND_HPP_INCLUDED

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
// macros, see http://tinyurl.com/ycwdxco; 'defined(bitand)'
// has to be checked in a separate condition, otherwise GCC complains 
// about 'bitand' being an alternative token
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitand)
#   pragma push_macro("bitand")
#   undef bitand
#   define bitand(x)
#endif
#endif
#endif

#define AUX778076_OP_NAME   bitand_
#define AUX778076_OP_PREFIX bitand
#define AUX778076_OP_TOKEN  &
#include <boost/mpl/aux_/arithmetic_op.hpp>

#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitand)
#   pragma pop_macro("bitand")
#endif
#endif
#endif

#endif // BOOST_MPL_BITAND_HPP_INCLUDED

/* bitand.hpp
LAMvA2eAl4OngtcGxZtLLXgBWBcUm/96sBVcA94GNoB3go0gLe3cROmDa8GD4HUg6WtbQNJcXU/pO7y8skvNqjaQvqIEWOHwAnIu+bDoAleBN4K1DluUuI3gRrDd4UXQXPJf5VI+wM2UD/BmcDvYGxQvK1vB58EkuN9hrzjua+Bt4Jvg7eDPwDvAP4IDYCGe550gLQ19FxgB7wHxbNQ3Qdxj9S0Q946877i4N+rbIC3B9x0QeVD3gohbbQcfAu8=
*/