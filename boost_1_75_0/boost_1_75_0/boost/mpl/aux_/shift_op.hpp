
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
xGvK3zJZKh7os8Z+4v0jBrCyWml1Y+ILKxsZmdWyUwcdFdbWFLfuJRWtfEo9tFGT9xDQFAui5dIgyaEXJTabs8Qrm6dNnnm/4djsZXbKYZNMvfynqoz98umpyN8kzv8BchYn/ePbmBBztL2kpClTUwa/AwynzbObZ2CToukIAaa8OMdFSHg/v8hLgO+xOK8/OqI3MrJyfAxsa41UU3dLGpk4OAjB87C1QFpjgF5drfT1RS+1jGQa1EBtQX/KMVbK4WpG4jLt7CrWsmuqyc6lsEycI/5Vsn7i5w4jMpIMVtxgfMlvMVHq38OjsMkiV5vZrroQZMWCmOm/EeHmY4i4c6gbF8zqQp9sO6rkUCl7FUJeMzAIOfILMBpXojb9ElkIjPkCRQR1M9kSs1RKNSgpU2bqbH8XRSWObR2jXX1QuHLZOquJ2WiaX66U+aveGOuxYVZVRjkLjkTpWU0jR27ieomQMUbLMDVdBP3kcomyIG918QA32StQd7eaobS8w/py3vaPEblQBauJUU6S9yCG4z8LC9N3djhAY9TJGt8SmBL6k3cKI/uQnB9G+r7vrjbzt+X99cs3U9G4+sg7OvpbWXl6/5Rl5Wba31eTrZ9e0lNbM1Kdtqx1n1+406vsICNL5ufvMDQEhIeDHw8yzrUqigq5OGUN1LWsFGYPGPCkw/K/sbIhJ6aOjnHoJiugx//OEsxcF/lbz8RzJJfP
*/