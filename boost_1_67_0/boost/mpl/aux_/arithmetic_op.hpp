
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