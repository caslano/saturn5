
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

#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/preprocessor.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
#   define AUX778076_INCLUDE_DIR typeof_based
#elif defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
   || defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)
#   define AUX778076_INCLUDE_DIR no_ctps
#else
#   define AUX778076_INCLUDE_DIR plain
#endif

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_HEADER \
    AUX778076_INCLUDE_DIR/BOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define AUX778076_HEADER \
    BOOST_PP_CAT(AUX778076_INCLUDE_DIR,/)##BOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif


#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/vector/aux_/preprocessed/AUX778076_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/vector/aux_/preprocessed/AUX778076_HEADER)
#endif

#   undef AUX778076_HEADER
#   undef AUX778076_INCLUDE_DIR

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
WQkTwjGjxKrtSE0I8ncHWWL8wJsS1oQprhY5wnsWPcf86pYc6lnTVIqdJZHH6xTLjMIqeT+QBhguF5H8zBF/a7tedw7dxHuY5DvG25N3+pkvw+ucMYocN22JqWOT55ZLQ9eRgExO1GPPBH+uV+aga00YiSdwPc/ev4Tm8rErJDk8YMf/MQQrSdOwcFOkfBGq9cvOB+8N9n/Om2lHvcrswJbrocoqmNOwGQnxdtzaB7wTcUG3pdJv9T/udV125wEuYVpefFHkzft/fQPN7UcRhE0N4B+CcT1dUzUzT3Wd5ma55G5YhPpPT+t/3+pABZJc0/ROqX4xMN305jbkcArnEzVhT5y6o4qGQcrWvcsEt6rz85OTJcOAUa2NyqoLSkLTfRmSW7TnIQlWbZ0B4ymqMI0gmANhcVbzVp20cGZOqHt5KOXwH3Bezzmq+97R+600sr5E17QV+ErWwjrHIAvif6+yWTnRHFaeTim+8O2dQMwtpTVIA9EplSB3+wS5lq4F8kSOL933ZJayzltPrIs2iOgvu+VWrzsLsWElmDb+FU9ygwOSCsFgaO2AEA==
*/