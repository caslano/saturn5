
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if !defined(BOOST_PP_IS_ITERATING)

///// header body

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/static_constant.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>

#   include <boost/preprocessor/arithmetic/sub.hpp>
#   include <boost/preprocessor/tuple/elem.hpp>
#   include <boost/preprocessor/enum_params_with_a_default.hpp>
#   include <boost/preprocessor/enum_params.hpp>
#   include <boost/preprocessor/enum.hpp>
#   include <boost/preprocessor/repeat.hpp>
#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/iterate.hpp>

#if defined(BOOST_MPL_PREPROCESSING_MODE)
#   undef LONG_MAX
#endif

namespace boost { namespace mpl {

#if !defined(AUX778076_SEQUENCE_BASE_NAME)
#   define AUX778076_SEQUENCE_BASE_NAME AUX778076_SEQUENCE_NAME
#endif

#if !defined(AUX778076_SEQUENCE_INTEGRAL_WRAPPER)

#   define AUX778076_SEQUENCE_PARAM_NAME T
#   define AUX778076_SEQUENCE_TEMPLATE_PARAM typename T
#   define AUX778076_SEQUENCE_DEFAULT na

#   define AUX778076_SEQUENCE_NAME_N(n) \
    BOOST_PP_CAT(AUX778076_SEQUENCE_BASE_NAME,n) \
    /**/

#   define AUX778076_SEQUENCE_PARAMS() \
    BOOST_PP_ENUM_PARAMS( \
          AUX778076_SEQUENCE_LIMIT \
        , AUX778076_SEQUENCE_TEMPLATE_PARAM \
        ) \
    /**/

#   define AUX778076_SEQUENCE_ARGS() \
    BOOST_PP_ENUM_PARAMS( \
          AUX778076_SEQUENCE_LIMIT \
        , T \
        ) \
    /**/

#   define AUX778076_SEQUENCE_DEFAULT_PARAMS() \
     BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT( \
          AUX778076_SEQUENCE_LIMIT \
        , AUX778076_SEQUENCE_TEMPLATE_PARAM \
        , AUX778076_SEQUENCE_DEFAULT \
        ) \
    /**/

#   define AUX778076_SEQUENCE_N_PARAMS(n) \
    BOOST_PP_ENUM_PARAMS(n, AUX778076_SEQUENCE_TEMPLATE_PARAM) \
    /**/

#   define AUX778076_SEQUENCE_N_ARGS(n) \
    BOOST_PP_ENUM_PARAMS(n, T) \
    /**/

#   define AUX778076_SEQUENCE_N_PARTIAL_SPEC_ARGS(n) \
    BOOST_PP_ENUM_PARAMS(n, T) \
    BOOST_PP_COMMA_IF(n) \
    BOOST_PP_ENUM( \
          BOOST_PP_SUB_D(1,AUX778076_SEQUENCE_LIMIT,n) \
        , BOOST_PP_TUPLE_ELEM_3_2 \
        , AUX778076_SEQUENCE_DEFAULT \
        ) \
    /**/

#else // AUX778076_SEQUENCE_INTEGRAL_WRAPPER

#   define AUX778076_SEQUENCE_PARAM_NAME C
#   define AUX778076_SEQUENCE_TEMPLATE_PARAM BOOST_MPL_AUX_NTTP_DECL(long, C)
#   define AUX778076_SEQUENCE_DEFAULT LONG_MAX

#   define AUX778076_SEQUENCE_PARAMS() \
    typename T, BOOST_PP_ENUM_PARAMS( \
          AUX778076_SEQUENCE_LIMIT \
        , AUX778076_SEQUENCE_TEMPLATE_PARAM \
        ) \
    /**/

#   define AUX778076_SEQUENCE_ARGS() \
    T, BOOST_PP_ENUM_PARAMS( \
          AUX778076_SEQUENCE_LIMIT \
        , C \
        ) \
    /**/

#   define AUX778076_SEQUENCE_DEFAULT_PARAMS() \
    typename T, \
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT( \
          AUX778076_SEQUENCE_LIMIT \
        , AUX778076_SEQUENCE_TEMPLATE_PARAM \
        , AUX778076_SEQUENCE_DEFAULT \
        ) \
    /**/

#   define AUX778076_SEQUENCE_N_PARAMS(n) \
    typename T BOOST_PP_COMMA_IF(n) \
    BOOST_PP_ENUM_PARAMS(n, AUX778076_SEQUENCE_TEMPLATE_PARAM) \
    /**/

#   if !defined(AUX778076_SEQUENCE_CONVERT_CN_TO)
#       define AUX778076_SEQUENCE_CONVERT_CN_TO(z,n,TARGET) BOOST_PP_CAT(C,n)
#   endif

#   define AUX778076_SEQUENCE_N_ARGS(n) \
    T BOOST_PP_COMMA_IF(n) \
    BOOST_PP_ENUM(n,AUX778076_SEQUENCE_CONVERT_CN_TO,T) \
    /**/

#   define AUX778076_SEQUENCE_N_PARTIAL_SPEC_ARGS(n) \
    T, BOOST_PP_ENUM_PARAMS(n, C) \
    BOOST_PP_COMMA_IF(n) \
    BOOST_PP_ENUM( \
          BOOST_PP_SUB_D(1,AUX778076_SEQUENCE_LIMIT,n) \
        , BOOST_PP_TUPLE_ELEM_3_2 \
        , AUX778076_SEQUENCE_DEFAULT \
        ) \
    /**/

#endif // AUX778076_SEQUENCE_INTEGRAL_WRAPPER


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
// forward declaration
template<
      AUX778076_SEQUENCE_DEFAULT_PARAMS()
    >
struct AUX778076_SEQUENCE_NAME;
#else
namespace aux {
template< BOOST_MPL_AUX_NTTP_DECL(int, N) > 
struct BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_chooser);
}
#endif

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, AUX778076_SEQUENCE_LIMIT, <boost/mpl/aux_/sequence_wrapper.hpp>))
#include BOOST_PP_ITERATE()

// real C++ version is already taken care of
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

namespace aux {
// ???_count_args
#define AUX778076_COUNT_ARGS_PREFIX         AUX778076_SEQUENCE_NAME
#define AUX778076_COUNT_ARGS_DEFAULT        AUX778076_SEQUENCE_DEFAULT
#define AUX778076_COUNT_ARGS_PARAM_NAME     AUX778076_SEQUENCE_PARAM_NAME
#define AUX778076_COUNT_ARGS_TEMPLATE_PARAM AUX778076_SEQUENCE_TEMPLATE_PARAM
#define AUX778076_COUNT_ARGS_ARITY          AUX778076_SEQUENCE_LIMIT
#define AUX778076_COUNT_ARGS_USE_STANDARD_PP_PRIMITIVES
#include <boost/mpl/aux_/count_args.hpp>

template<
      AUX778076_SEQUENCE_PARAMS()
    >
struct BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_impl)
{
    typedef aux::BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_count_args)<
          BOOST_PP_ENUM_PARAMS(AUX778076_SEQUENCE_LIMIT, AUX778076_SEQUENCE_PARAM_NAME)
        > arg_num_;
    
    typedef typename aux::BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_chooser)< arg_num_::value >
        ::template result_< AUX778076_SEQUENCE_ARGS() >::type type;
};

} // namespace aux

template<
      AUX778076_SEQUENCE_DEFAULT_PARAMS()
    >
struct AUX778076_SEQUENCE_NAME
    : aux::BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_impl)<
          AUX778076_SEQUENCE_ARGS()
        >::type
{
    typedef typename aux::BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_impl)<
          AUX778076_SEQUENCE_ARGS()
        >::type type;
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#   undef AUX778076_SEQUENCE_N_PARTIAL_SPEC_ARGS
#   undef AUX778076_SEQUENCE_N_ARGS
#   undef AUX778076_SEQUENCE_CONVERT_CN_TO
#   undef AUX778076_SEQUENCE_N_PARAMS
#   undef AUX778076_SEQUENCE_DEFAULT_PARAMS
#   undef AUX778076_SEQUENCE_ARGS
#   undef AUX778076_SEQUENCE_PARAMS
#   undef AUX778076_SEQUENCE_NAME_N
#   undef AUX778076_SEQUENCE_DEFAULT
#   undef AUX778076_SEQUENCE_TEMPLATE_PARAM
#   undef AUX778076_SEQUENCE_PARAM_NAME
#   undef AUX778076_SEQUENCE_LIMIT
#   undef AUX778076_SEQUENCE_BASE_NAME
#   undef AUX778076_SEQUENCE_NAME
#   undef AUX778076_SEQUENCE_INTEGRAL_WRAPPER

}}

///// iteration

#else
#define i_ BOOST_PP_FRAME_ITERATION(1)

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#if i_ == AUX778076_SEQUENCE_LIMIT

/// primary template (not a specialization!)
template<
      AUX778076_SEQUENCE_N_PARAMS(i_)
    >
struct AUX778076_SEQUENCE_NAME
    : AUX778076_SEQUENCE_NAME_N(i_)< AUX778076_SEQUENCE_N_ARGS(i_) >
{
    typedef typename AUX778076_SEQUENCE_NAME_N(i_)< AUX778076_SEQUENCE_N_ARGS(i_) >::type type;
};

#else

template<
      AUX778076_SEQUENCE_N_PARAMS(i_)
    >
struct AUX778076_SEQUENCE_NAME< AUX778076_SEQUENCE_N_PARTIAL_SPEC_ARGS(i_) >
    : AUX778076_SEQUENCE_NAME_N(i_)< AUX778076_SEQUENCE_N_ARGS(i_) >
{
#if i_ > 0 || defined(AUX778076_SEQUENCE_INTEGRAL_WRAPPER)
    typedef typename AUX778076_SEQUENCE_NAME_N(i_)< AUX778076_SEQUENCE_N_ARGS(i_) >::type type;
#else
    typedef AUX778076_SEQUENCE_NAME_N(i_)< AUX778076_SEQUENCE_N_ARGS(i_) >::type type;
#endif
};

#endif // i_ == AUX778076_SEQUENCE_LIMIT

#   else

namespace aux {

template<>
struct BOOST_PP_CAT(AUX778076_SEQUENCE_NAME,_chooser)<i_>
{
    template<
          AUX778076_SEQUENCE_PARAMS()
        >
    struct result_
    {
#if i_ > 0 || defined(AUX778076_SEQUENCE_INTEGRAL_WRAPPER)
        typedef typename AUX778076_SEQUENCE_NAME_N(i_)<
              AUX778076_SEQUENCE_N_ARGS(i_)
            >::type type;
#else
        typedef AUX778076_SEQUENCE_NAME_N(i_)<
              AUX778076_SEQUENCE_N_ARGS(i_)
            >::type type;
#endif
    };
};

} // namespace aux

#   endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#undef i_
#endif // BOOST_PP_IS_ITERATING

/* sequence_wrapper.hpp
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
*/