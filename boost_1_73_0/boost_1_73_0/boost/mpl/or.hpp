
#ifndef BOOST_MPL_OR_HPP_INCLUDED
#define BOOST_MPL_OR_HPP_INCLUDED

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
#   include <boost/mpl/aux_/config/msvc.hpp>

// agurt, 19/may/04: workaround a conflict with <iso646.h> header's 
// 'or' and 'and' macros, see http://tinyurl.com/3et69; 'defined(or)'
// has to be checked in a separate condition, otherwise GCC complains 
// about 'or' being an alternative token
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(or)
#   pragma push_macro("or")
#   undef or
#   define or(x)
#endif
#endif
#endif

#   define BOOST_MPL_PREPROCESSED_HEADER or.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(or)
#   pragma pop_macro("or")
#endif
#endif
#endif

#else

#   define AUX778076_OP_NAME or_
#   define AUX778076_OP_VALUE1 true
#   define AUX778076_OP_VALUE2 false
#   include <boost/mpl/aux_/logical_op.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_OR_HPP_INCLUDED

/* or.hpp
HjihazESOVHF6YcjRKVaYafYGSyQDm22mnJIDfH8mOkdppCti4IjjjSXya4OIqa+UmU6En4ChVnIP6oeXA3A38HJw3QeP87CEwc+m77G4JqHUu4Vk5zHo3wCRBkqWtfIa+4MEMljhPP2VJjiO9Y6a8BxB5URS0f5XplcWfhALKFvc0N9EW3aXAZgTDKJKUaCffafUeDgGk88GEsh7O888cZq+eMFdw8hWdeFPHmfvM4fpy+eGCcJVhw+laeemLmp2SlliQlpU4bwhFj540Jv0O06kscZokzzTp2Iw/5Rtj6sTMoRZ77+iJm+INlEVdgOB50J4Y5L+c5RsMzBjRRYlKlJrHRBf/9yAmdfTmw91vbbsjrMA2t2ZAofDRT6w5V/gUmqCRRBY9Y1mG0JtbbLQIiDvXvx69ukJ3t34+f5pHfe695Bb0duSwztNvQptTy+939QSwMECgAAAAgALWdKUo8RPvEqAgAAzAMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNzJVVAUAAbZIJGBtU1FP2zAQfo6l/odbJ16QWrewaaKklRAqAw1RRAPvrnMlHokd2VdK//3OSdqKbS+Jzvfd5++7O6eEgbQKOBOpsWvHvzfcbZ3Pw0zcZtlj84Gf80xo
*/