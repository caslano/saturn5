
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/compiler.hpp>
#include <boost/mpl/aux_/config/preprocessor.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_PREPROCESSED_HEADER \
    BOOST_MPL_CFG_COMPILER_DIR/BOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define AUX778076_PREPROCESSED_HEADER \
    BOOST_PP_CAT(BOOST_MPL_CFG_COMPILER_DIR,/)##BOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif

#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/aux_/preprocessed/AUX778076_PREPROCESSED_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/aux_/preprocessed/AUX778076_PREPROCESSED_HEADER)
#endif

#   undef AUX778076_PREPROCESSED_HEADER

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
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
*/