
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

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
#   include <boost/mpl/integral_c.hpp>
#   include <boost/mpl/aux_/value_wknd.hpp>
#endif

#if !defined(AUX778076_OP_PREFIX)
#   define AUX778076_OP_PREFIX AUX778076_OP_NAME
#endif

#define AUX778076_OP_ARITY 2

#include <boost/mpl/aux_/numeric_op.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER AUX778076_OP_PREFIX.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/aux_/config/integral.hpp>
#   include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct BOOST_PP_CAT(AUX778076_OP_PREFIX,_wknd)
{
    BOOST_STATIC_CONSTANT(T, value = (n AUX778076_OP_TOKEN s));
    typedef integral_c<T,value> type;
};
}
#endif

template<>
struct AUX778076_OP_IMPL_NAME<integral_c_tag,integral_c_tag>
{
    template< typename N, typename S > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  AUX778076_OP_TOKEN BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
#else
        : aux::BOOST_PP_CAT(AUX778076_OP_PREFIX,_wknd)<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type
#endif
    {
    };
};

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#undef AUX778076_OP_TAG_NAME
#undef AUX778076_OP_IMPL_NAME
#undef AUX778076_OP_ARITY
#undef AUX778076_OP_PREFIX
#undef AUX778076_OP_NAME
#undef AUX778076_OP_TOKEN

/* shift_op.hpp
fYC/LiAqR6ReXxhSi448oIazrjaOWPYB6yk6Z1WbefHGGWmajPnVhqjgcMVH7N4nCV+FOmJ/yEJ880pCEpC0Rz5+Xm7z1fppxG6kxJZ+vuAXIzYK4g9TUn7ScPrn/gNQSwMECgAAAAgALWdKUmONxl6sAQAA6gIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDM4VVQFAAG2SCRgdZLBbtswDIbvegoiQeDt4CjtDt06I5csWAtsaxAbuysyHQt1JE+iE+TtRylush4Gw7YEfvzFn2JBGEirgEtRGNs4/r3i+eR8HZbiqao2ZfrC93UlNuufoNGTaYxWhKKQN7SQl2wxFVMo0R/R58HUDHnsu3MExkUiVp1BSyOh04aRBhUNHlmuLH/EtzfWGrvn5FuoCEl9KVqiPryd1TmtutYF1jzOezxwyhsHhVUHHN3AyTu7h2glimPdDzt2AbuBwJt9S7D6xRnykgKFdoeDsvVS5LlW0TzMyu3q2/NWxk2Q6xq71eC7rXPExFwzkefvpN8n/KdeSG4epbwGHmep4M3LtpL3i0+f2dG1mCmsbeB2ALWK4IQZL/2QegXOwlUDdqjVEHBEdIv6NTLUIqR4tCmK3mMKLUWPvoMcYdJ7YwmyiqcDPP4Z
*/