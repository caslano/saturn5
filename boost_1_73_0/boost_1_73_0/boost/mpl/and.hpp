
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
UEsDBAoAAAAIAC1nSlKIqaxdowIAANAFAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTUwOVVUBQABtkgkYNVUbWvbMBD+Lsh/ODJKocyxnabbYjxDSUvf1ia0ZmyMfVDtcyxqS8GSk+bf72Q5aSlsMNiXBWLL0t1zd89zp9igNhnXmLBYyELR6wm3G9XkOmGXabroHnBxnrrFbH53dz7rP1aNet6y7mlaKbFisf/iHfsOkL2DB2zW2Hha5MjiBlfVlo51t5nVecIyRd6ZEUp6tZLCqIa8X53HvYFLyQ9HIYyDAG7FsjRbKIREEDJHzAfMhYrAlAiPyLWhFTeA3GiQvO0cskqgNHrABhRmD83inBv+JsT8BvRGZ5XSOGBn3GAEaYvvIZjCnVqTSRhAOIkm04iML27TVwkQsZ6rwS/4E7l/oWy8W5WLQmDe44THcN1KG4pwxlEY7HHOU76MYDgOg/GJl2cfvePp5MN4Mv00dHm7ZLucsxKzp3/PzX9BRIk8xwYqlEtTgtAw6n8RjCcnb451qdoqp9p3x47Gnr/Y71uTOnbW0dB3rONk37IJK41ZdQ/PjcCuWRPyNEpVNo+NpdYoaLUVQBtKBFQBh1nbVIcstmYJq8RjeBJMCcB9xwWJ0TZI
*/