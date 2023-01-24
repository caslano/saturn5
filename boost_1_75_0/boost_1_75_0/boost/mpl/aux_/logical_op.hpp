
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

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/aux_/nested_type_wknd.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>
#endif

#include <boost/mpl/limits/arity.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/preprocessor/ext_params.hpp>
#include <boost/mpl/aux_/preprocessor/def_params_tail.hpp>
#include <boost/mpl/aux_/preprocessor/enum.hpp>
#include <boost/mpl/aux_/preprocessor/sub.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

#   define AUX778076_PARAMS(param, sub) \
    BOOST_MPL_PP_PARAMS( \
          BOOST_MPL_PP_SUB(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, sub) \
        , param \
        ) \
    /**/

#   define AUX778076_SHIFTED_PARAMS(param, sub) \
    BOOST_MPL_PP_EXT_PARAMS( \
          2, BOOST_MPL_PP_SUB(BOOST_PP_INC(BOOST_MPL_LIMIT_METAFUNCTION_ARITY), sub) \
        , param \
        ) \
    /**/

#   define AUX778076_SPEC_PARAMS(param) \
    BOOST_MPL_PP_ENUM( \
          BOOST_PP_DEC(BOOST_MPL_LIMIT_METAFUNCTION_ARITY) \
        , param \
        ) \
    /**/

namespace aux {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< bool C_, AUX778076_PARAMS(typename T, 1) >
struct BOOST_PP_CAT(AUX778076_OP_NAME,impl)
    : BOOST_PP_CAT(AUX778076_OP_VALUE1,_)
{
};

template< AUX778076_PARAMS(typename T, 1) >
struct BOOST_PP_CAT(AUX778076_OP_NAME,impl)< AUX778076_OP_VALUE2,AUX778076_PARAMS(T, 1) >
    : BOOST_PP_CAT(AUX778076_OP_NAME,impl)<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , AUX778076_SHIFTED_PARAMS(T, 1)
        , BOOST_PP_CAT(AUX778076_OP_VALUE2,_)
        >
{
};

template<>
struct BOOST_PP_CAT(AUX778076_OP_NAME,impl)<
          AUX778076_OP_VALUE2
        , AUX778076_SPEC_PARAMS(BOOST_PP_CAT(AUX778076_OP_VALUE2,_))
        >
    : BOOST_PP_CAT(AUX778076_OP_VALUE2,_)
{
};

#else

template< bool C_ > struct BOOST_PP_CAT(AUX778076_OP_NAME,impl)
{
    template< AUX778076_PARAMS(typename T, 1) > struct result_
        : BOOST_PP_CAT(AUX778076_OP_VALUE1,_)
    {
    };
};

template<> struct BOOST_PP_CAT(AUX778076_OP_NAME,impl)<AUX778076_OP_VALUE2>
{
    template< AUX778076_PARAMS(typename T, 1) > struct result_
        : BOOST_PP_CAT(AUX778076_OP_NAME,impl)< 
              BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< AUX778076_SHIFTED_PARAMS(T,1),BOOST_PP_CAT(AUX778076_OP_VALUE2,_) >
    {
    };

#if BOOST_WORKAROUND(BOOST_MSVC, == 1300)
    template<> struct result_<AUX778076_SPEC_PARAMS(BOOST_PP_CAT(AUX778076_OP_VALUE2,_))>
        : BOOST_PP_CAT(AUX778076_OP_VALUE2,_)
    {
    };
};
#else
};

template<>
struct BOOST_PP_CAT(AUX778076_OP_NAME,impl)<AUX778076_OP_VALUE2>
    ::result_< AUX778076_SPEC_PARAMS(BOOST_PP_CAT(AUX778076_OP_VALUE2,_)) >
        : BOOST_PP_CAT(AUX778076_OP_VALUE2,_)
{
};
#endif // BOOST_MSVC == 1300

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    BOOST_MPL_PP_DEF_PARAMS_TAIL(2, typename T, BOOST_PP_CAT(AUX778076_OP_VALUE2,_))
    >
struct AUX778076_OP_NAME
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    : aux::BOOST_PP_CAT(AUX778076_OP_NAME,impl)<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , AUX778076_SHIFTED_PARAMS(T,0)
        >
#else
    : aux::BOOST_PP_CAT(AUX778076_OP_NAME,impl)< 
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        >::template result_< AUX778076_SHIFTED_PARAMS(T,0) >
#endif
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY
        , AUX778076_OP_NAME
        , (AUX778076_PARAMS(T, 0))
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , BOOST_MPL_LIMIT_METAFUNCTION_ARITY
    , AUX778076_OP_NAME
    )

}}

#undef AUX778076_SPEC_PARAMS
#undef AUX778076_SHIFTED_PARAMS
#undef AUX778076_PARAMS
#undef AUX778076_OP_NAME
#undef AUX778076_OP_VALUE1
#undef AUX778076_OP_VALUE2

/* logical_op.hpp
9Z25e+/fWZen6HvGiR2fTE/yR9j8JPRvYQGhBy8WAISzEIniCveRx9Ns415cfEFWd1P1XrxM+5wAtE/SoZ6y48Flw3oxenpBvJL6ym9KwnFy9h6KcLxjm94dajlid0JBrgsUs4q+JDYh7eOMnW0hh4WUnqyHuQu/7/1rvmzVXdQhJp2+FQNMsttPvvkF+oLrB+M3faE6kIuDRCRUxWVWfgX+C3S+pz+H0M52FxU6yLncYqUcVskVv887zcaB4+rmwh8eVkMjR9hhcjvvPAX4m+2F4C6PsBNdFW3IIqJOUGDL+z6FV34EeTXdUbeeCYC6aW5k3BvtebpP1X8tFWbdEVyEfT0sSlcU6CA2WjK8HhHvwOTqP8nLpN68bZ1zRf8e39Q07JimNBXBTP5SlTW65xjivBrrS1/BxhF38t4oEnXYY1fHc0c3YE7GDbMZs4yOuQ/Iq6KC01n+Ac1wJ/AGdIjvufr4H4h9c9y+hh+3klhAvJ7jWkRrlEeHyPJkmU04Rz+FpZ4FGIw6mhiubt/oloSqFEfFPU0XuZVuKc2UC+IDXZ2FWjVyTS5WEgap4eqFV9k1JshW9rHSgFtTCG8n++3j5lE3DBp3NH1/PKf+w0KTQtQp5+B8U22bWhAp+jiMYx2jstjmZ/DnAw4ChBPWQZaKvlwtOsVGHVeE15AOkJVI3A5dG9UfEdSy+NwGcSLT3A7/0ql+YrfVteQd
*/