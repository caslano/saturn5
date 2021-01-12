
#ifndef BOOST_MPL_SET_HPP_INCLUDED
#define BOOST_MPL_SET_HPP_INCLUDED

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/limits/set.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_SET_HEADER \
    BOOST_PP_CAT(set, BOOST_MPL_LIMIT_SET_SIZE).hpp \
    /**/
#else
#   define AUX778076_SET_HEADER \
    BOOST_PP_CAT(set, BOOST_MPL_LIMIT_SET_SIZE)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/set/AUX778076_SET_HEADER)
#   undef AUX778076_SET_HEADER
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER set.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/set.hpp>

#   define AUX778076_SEQUENCE_NAME set
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_SET_SIZE
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_SET_HPP_INCLUDED

/* set.hpp
fhvGa0H1AMpEiEvudvOU78z4hfK82ExdxWGQ8fpdcsvz/qjzSfa8qeaNZMLsLj95fszXrnLT0DfAjPCuW4owyfZXWl76MpMWUhWXeU3xK/q5yDnuo84FYX1R6Q3pCnHN7hPpw5CO/uXyt0n8fIh3Yjhvny58IS9bdM2Mty5U8kT9AOqfs8vzA1nHVE58o3+jyoZ5Ugu43sh+D/G5UA+8uFC4NuSWUJ9YVpgfNtw+1Cd2YD12
*/