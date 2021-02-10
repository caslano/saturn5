
#ifndef BOOST_MPL_AUX_PREPROCESSOR_PARTIAL_SPEC_PARAMS_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_PARTIAL_SPEC_PARAMS_HPP_INCLUDED

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

#include <boost/mpl/limits/arity.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/preprocessor/enum.hpp>
#include <boost/mpl/aux_/preprocessor/sub.hpp>
#include <boost/preprocessor/comma_if.hpp>

#define BOOST_MPL_PP_PARTIAL_SPEC_PARAMS(n, param, def) \
BOOST_MPL_PP_PARAMS(n, param) \
BOOST_PP_COMMA_IF(BOOST_MPL_PP_SUB(BOOST_MPL_LIMIT_METAFUNCTION_ARITY,n)) \
BOOST_MPL_PP_ENUM( \
      BOOST_MPL_PP_SUB(BOOST_MPL_LIMIT_METAFUNCTION_ARITY,n) \
    , def \
    ) \
/**/

#endif // BOOST_MPL_AUX_PREPROCESSOR_PARTIAL_SPEC_PARAMS_HPP_INCLUDED

/* partial_spec_params.hpp
sPR4wd3Glkk1YHdxPGlucHsTty9Fabc7trBZZjeZVdJpa5jgBx/B2zCn7BRmWK6x9CudIBMlFtmOvifSyTY075/34WcQwvjBY6MuWASpc0XEOW5lXmR4btBxggQHNeZvfnkZBkEQeuyPdBhBvMIfEFzBo11DGPQD6F9EF1dREMDt39hj19Y4NM4foVm6NILAYx4xthANS3gEQ5HfwbhUV1CldpUlMEfQS2NLTL54+K/68LlNdh1B2CGoFNXLN2vyXRp0uQve9UfTONeZrn3axlHNgkyqpp0GrBaDHPZLEEbm2MoHBKZLVA422qWwSTXJVEhF1AbkvLLZyiEcUnuajsiftwFAKJvn0iTtEUd60z6nJ2nNlzrPsRYc/BH4231lenfjWXw/iXo1xWQ8jQnwLZpYoHSrEmk82vkR/LBDdl2CTerPWOrFDmppQC4cliQ/Qj2lkMqK9EcDJ1QMd8LEurGlEBTVWWWzAaNBfd8sH8Lvy02Ft5WL4MjYY08krT9cElQEalVmvPd8M53djx89NlQKC9o+42cem9TJ+FRhQ4o3ej4gFv4w02usy/wBTNe5vTBwdP3TvZ8ykc//YxL8IJbgbwryw3/wFVBLAwQKAAAACAAtZ0pSWtO0e3ICAADKBQAAHgAJAGN1cmwt
*/