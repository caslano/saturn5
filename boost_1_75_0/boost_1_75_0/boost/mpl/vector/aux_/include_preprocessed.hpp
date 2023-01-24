
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
cccddsyRWPeF/KHH+EFuvvZrqIHZZK3++3yE44U8+zcr0kfCHdUXKdOl9rjyr1446BPZpc5PGVFGrCXkX8ayUSs0hoLVeOv0CJZYvc6FBW8ReGsvDqmXHh0P7DHP6eKqbSD+IkiBwjQccFl1Eg3Nmgi/oOUZYIEupdIj9gdTmGiVzuHsMZVimD9yeQCB0sq3J7W7xt+Ozw4TtuK50fNNFe9FWVDqzQqZfdMYLh2nDA5ZdHh4FvJ3q7Hyz737h3lDYzlVrgcrbhSqnXV51hXxi6iC8CMfodUMlmzFzfgEtYIvFquF6HaQgkKj6pNaYngO/2yzDmlFaXiQgBvNBDqBn3zqf1Ktmy9AxAZWMnvlZ/2PuHmJzddLqh5JsGqv5EJvOD9xTukhcb7QUQuvjXRrckhX1RG8H9L5/jD9FjltYaaXPAos4iRIG9BJWbH0/QYd35Hu56/h6281LmCQswi4UpnQD6lH0Kk0SCdIw4GSBxiqnBzI0UTahNK4hpSqWq4hdZfFfSeeNnLzV/w63DvQMh5l+SdcQlDISonIyqBP8OJPsiNAEsZXSr6yOU3pbRtByHvOVxU+VLHWuzPpyPtj+Y0pasBqUg5/rn89oAmqtpCMqO/mhq3c4A3Gx+9l6lL7O5l3F628w1th5yfmu4xNxvzQOtfxw1OMBcozBsX6XAcZmnZnz4EwlKDXL27mOSkBrPXNqkXovh+gOfdi
*/