
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
gX1jIFlE5TU5G5XyLRfkKsigAdItzasXnTudM/Ui4smuLGc8XNxv1rVf7SYzJhkHrcdUxkepjt7XJIp3EQ5VMR3IBI8P+oidHDzaWsi3Hkrz0JhtYFA9hCQpCcRLfERLbZreQaXlriAm0mhT+IZhmWrilp7GtUD+jq44yug+V1zE1MiCJPL4LcGNQvk8zOc9dIlI/Vsp+v3mHU2U2cavLFsM68zGlM8D5WRsuNwMajZS3yo0MJfyCq3X0IyI56enT4vT64y8aMjn1Sc6tOPaxUi+L1qvFKRpafoKpfnDYdViznlvp471sB2hvlTaSl7gl3KVXXWb94amDmPzUgwtuzWF8wG1vRbhn8ssLCp/5ouSL8SqhmZjt4bhqjfGTMEsOJNx75LXQVgxf0kaASwN4qTeOwHkHkeg3WR+NwXtklurp2gPE721WzOXUqai45JxBVD6ZqTkMICi59+epgqEKOIryy6Pbn7wkIKIgD7jAHX0bSWBg2xnT/CdN8zT+skHowRnuJzew/VjbQxfzmzUqiSESYxvPJHMJT8+McAde95B+zmK0A+92FHoM6RtE88Zq1h4CvgtJtc9tD1CVZhiqDpNQ3GlyQkQoQepKJ0jN54XSyCTt0YqX2r7aLDfEH00rZKurvTVHJtZ6Kvf7PxR9B0b+6zs3viOaD2Nsjsqp3FOdwd/5nDii99lHH+9WdnLXnd0NI3HtVtCB/ra
*/