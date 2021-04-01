
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
JV+M1yQyIapdk5qgbU+3W2T5ZptAkActhOFZhPUWH+cjnMeCOqNkK9kJPkbpwx3r8VCsQup2MpWLWE2UTA0uYTSO7w7b5I9fuT8NTcje/vVYhpWjhGdZTraeI4i0CyiCLEwkWx4M8YT6iFr25JRne/8FF8hT0ed7sVBc3zyVo8mCsoSU4LYhOrObtqAeMhGuZmIqB+fQ95aW6qAeH1zZvXKYPs+P6iwuSYUxOEyTuMJhB+PSdxE6UBPOtvIIgiwF+iuk8dDzygn/jBzB+yq1k+HBsnzp6u+rbvJaDTEneYwz+gf4acJtusJ1TNUM4XP2TNGVTvx/WDczqfRPt7kIWIJMRHPwvL/iGvj1JzbdR2FoUzFQDibA95pCpluCqxwCQt2DPi2RYKXgG4IaWczwNo06umpfCVGeEc0SaSgwjxEDmU5uOjxM2OZJUSFNtUSIOTn9Z2ny7XDkyqoXy8XPvUk5XEZeCbz0f2nC/NVA4+0v9QRnhhrXpe1nFS/CF+UL0ViJPt7WS8ebRIKF8h17ZWV+Q8Wf2OPSGOAlXxzGmFB50v8OB12XQ+ol4w==
*/