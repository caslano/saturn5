
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
#   include <boost/mpl/aux_/largest_int.hpp>
#   include <boost/mpl/aux_/value_wknd.hpp>
#endif

#if !defined(AUX778076_OP_PREFIX)
#   define AUX778076_OP_PREFIX AUX778076_OP_NAME
#endif

#include <boost/mpl/aux_/numeric_op.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER AUX778076_OP_PREFIX.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/aux_/config/workaround.hpp>
#   include <boost/preprocessor/cat.hpp>


namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
namespace aux {
template< typename T, T n1, T n2 >
struct BOOST_PP_CAT(AUX778076_OP_PREFIX,_wknd)
{
    BOOST_STATIC_CONSTANT(T, value = (n1 AUX778076_OP_TOKEN n2));
    typedef integral_c<T,value> type;
};
}
#endif

template<>
struct AUX778076_OP_IMPL_NAME<integral_c_tag,integral_c_tag>
{
    template< typename N1, typename N2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  AUX778076_OP_TOKEN BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
#else
        : aux::BOOST_PP_CAT(AUX778076_OP_PREFIX,_wknd)<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
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

/* arithmetic_op.hpp
unUMv17iXdZ8NzYiSuyH53ZSCi9Fba2wo5Y+tYDvBXq4iMh5BMjFeZcuxNLU4O3ZOp9e3iA51P6ykQxZPkSixCzQwa3IPmpJ9Y5ma3DOTwnsAcDkG3TeGvCSYFZE5Ong3KIVOcpMWUz2RYC5CFC+nQEOPnkhHTUiQT2UjXZSiU6RA1ho6uwKy/YGjQyvGR8jdgcDiupdGP5EpihVCmOexW53BDsgERf97LDDDMAw86/nNwR4oahYYQ55+1eoMRMr+9kZkrequnkyZvEAGcy3EPoK0xSean7RoLY6r9+OYDdHj0bExYRKACfLVQapsKd6ivtJvVaDOpdK3bTJUlehDzk9PdjsoavBLymv7YlzsSgZAC5Upm829Tacxo+HNrwgS2DagPUf7VcLlmWjwOsM0AOWc7hedDL2kbOBxSNXEeS3Czo2B/Y6I1fzWc+V6h2/aDx2GesYS0OBWejrvA2YWO4koEo9W2eF1ga5DjIie4/KmSuUYEZ/glFs0maAT3Xcc5FmhABlDzJbNmnYny9TFmfDYH92RmIb9+sXaZ84/HqqG/gBTzwx+M8Lcw==
*/