
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
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
*/