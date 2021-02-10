
#ifndef BOOST_MPL_VECTOR_C_HPP_INCLUDED
#define BOOST_MPL_VECTOR_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/limits/vector.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_VECTOR_C_HEADER \
    BOOST_PP_CAT(BOOST_PP_CAT(vector,BOOST_MPL_LIMIT_VECTOR_SIZE),_c).hpp \
    /**/
#else
#   define AUX778076_VECTOR_C_HEADER \
    BOOST_PP_CAT(BOOST_PP_CAT(vector,BOOST_MPL_LIMIT_VECTOR_SIZE),_c)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/vector/AUX778076_VECTOR_C_HEADER)
#   undef AUX778076_VECTOR_C_HEADER
#   include <climits>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER vector_c.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/vector.hpp>

#   define AUX778076_SEQUENCE_NAME vector_c
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_VECTOR_SIZE
#   define AUX778076_SEQUENCE_NAME_N(n) BOOST_PP_CAT(BOOST_PP_CAT(vector,n),_c)
#   define AUX778076_SEQUENCE_CONVERT_CN_TO(z,n,TARGET) TARGET(BOOST_PP_CAT(C,n))
#   define AUX778076_SEQUENCE_INTEGRAL_WRAPPER
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_VECTOR_C_HPP_INCLUDED

/* vector_c.hpp
Xg7iGeejaTEvH2fZqFedFS8lTyc3R+U0SRJfwTHJfx6KDOW/oq1Xe+j7A7kiP1iqEPqLCZV0sEDUcOYqQ2dMbMNZL9FaQ0aZJmd9DwH3bn/EpsZRBp+Kithf70J8++bZ3tvONnz0ev8yfyyeI3arFLZ++YJfRCz6JlXBT3X74NgNP/2G/wBQSwMECgAAAAgALWdKUn+3OmHoAQAAYgMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxOTlVVAUAAbZIJGC9U9tum0AQfV/J/zAich8ibxccNy0r4ipKXTttEls2zfsahouCdy1YO0VR/r0D+CK175VYYC575syZ3cBiZSNV4ZgFuU4MfV6wfjVlXI3ZLAwX7Qumk5ClhVmvc52yQJxTAtHtumAXsMJyjyWv8hhZUOK2qCkeK6s6JOF99GDoujD/yb4pixLCHQ7A9eHJ7CngueCN5MiXlDJ9DFkHJ6FhyKvWEIl6QfagyPFo4jzJMT6geFfwY6cbeEIZSs89okxClUpwhp47/MTj6DO/8kfXw5H/xWG3UYRby5dKp1hJWNdUid0ZbVFb/oA6tZmE68ajMbK50RKiwlR4ygnrLTb8fluR2U3Bvu+0rnmGiljVWNHDGE+M4SRTp0MgDrq0gt0V
*/