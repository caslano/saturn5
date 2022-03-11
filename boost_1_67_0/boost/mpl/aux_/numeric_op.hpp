
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

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
#   include <boost/mpl/numeric_cast.hpp>
#   include <boost/mpl/apply_wrap.hpp>
#   include <boost/mpl/if.hpp>
#   include <boost/mpl/tag.hpp>
#   include <boost/mpl/aux_/numeric_cast_utils.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>
#   include <boost/mpl/aux_/msvc_eti_base.hpp>
#   include <boost/mpl/aux_/value_wknd.hpp>
#   include <boost/mpl/aux_/config/eti.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#endif

#include <boost/mpl/aux_/config/static_constant.hpp>

#if defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    || defined(BOOST_MPL_PREPROCESSING_MODE)

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/partial_spec_params.hpp>
#   include <boost/mpl/aux_/preprocessor/def_params_tail.hpp>
#   include <boost/mpl/aux_/preprocessor/repeat.hpp>
#   include <boost/mpl/aux_/preprocessor/ext_params.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/preprocessor/add.hpp>
#   include <boost/mpl/aux_/preprocessor/sub.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/eti.hpp>
#   include <boost/mpl/aux_/config/msvc.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>

#   include <boost/preprocessor/dec.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/cat.hpp>


#if !defined(AUX778076_OP_ARITY)
#   define AUX778076_OP_ARITY BOOST_MPL_LIMIT_METAFUNCTION_ARITY
#endif

#if !defined(AUX778076_OP_IMPL_NAME)
#   define AUX778076_OP_IMPL_NAME BOOST_PP_CAT(AUX778076_OP_PREFIX,_impl)
#endif

#if !defined(AUX778076_OP_TAG_NAME)
#   define AUX778076_OP_TAG_NAME BOOST_PP_CAT(AUX778076_OP_PREFIX,_tag)
#endif

namespace boost { namespace mpl {

template< 
      typename Tag1
    , typename Tag2
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_) = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value 
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_) = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value 
    >
struct AUX778076_OP_IMPL_NAME
    : if_c<
          ( tag1_ > tag2_ )
#else
    >
struct AUX778076_OP_IMPL_NAME
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )
#endif
        , aux::cast2nd_impl< AUX778076_OP_IMPL_NAME<Tag1,Tag1>,Tag1,Tag2 >
        , aux::cast1st_impl< AUX778076_OP_IMPL_NAME<Tag2,Tag2>,Tag1,Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct AUX778076_OP_IMPL_NAME<na,na>
{
    template< typename U1, typename U2 > struct apply 
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value = 0);
    };
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template< typename Tag > struct AUX778076_OP_IMPL_NAME<na,Tag>
{
    template< typename U1, typename U2 > struct apply 
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value = 0);
    };
};

template< typename Tag > struct AUX778076_OP_IMPL_NAME<Tag,na>
{
    template< typename U1, typename U2 > struct apply 
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value = 0);
    };
};
#else
template<> struct AUX778076_OP_IMPL_NAME<na,integral_c_tag>
{
    template< typename U1, typename U2 > struct apply 
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value = 0);
    };
};

template<> struct AUX778076_OP_IMPL_NAME<integral_c_tag,na>
{
    template< typename U1, typename U2 > struct apply 
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value = 0);
    };
};
#endif


#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && BOOST_WORKAROUND(BOOST_MSVC, >= 1300)
template< typename T > struct AUX778076_OP_TAG_NAME
    : tag<T,na>
{
};
#else
template< typename T > struct AUX778076_OP_TAG_NAME
{
    typedef typename T::tag type;
};
#endif


#if AUX778076_OP_ARITY != 2

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#   define AUX778076_OP_RIGHT_OPERAND(unused, i, N) , BOOST_PP_CAT(N, BOOST_MPL_PP_ADD(i, 2))>
#   define AUX778076_OP_N_CALLS(i, N) \
    BOOST_MPL_PP_REPEAT( BOOST_PP_DEC(i), BOOST_MPL_PP_REPEAT_IDENTITY_FUNC, AUX778076_OP_NAME< ) \
    N1 BOOST_MPL_PP_REPEAT( BOOST_MPL_PP_SUB(i, 1), AUX778076_OP_RIGHT_OPERAND, N ) \
/**/

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    BOOST_MPL_PP_DEF_PARAMS_TAIL(2, typename N, na)
    >
struct AUX778076_OP_NAME
    : AUX778076_OP_N_CALLS(AUX778076_OP_ARITY, N)
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          AUX778076_OP_ARITY
        , AUX778076_OP_NAME
        , ( BOOST_MPL_PP_PARAMS(AUX778076_OP_ARITY, N) )
        )
};

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,( BOOST_PP_DEC(AUX778076_OP_ARITY), 2, <boost/mpl/aux_/numeric_op.hpp> ))
#include BOOST_PP_ITERATE()

#   undef AUX778076_OP_N_CALLS
#   undef AUX778076_OP_RIGHT_OPERAND

#   else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

/// forward declaration
template< 
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct BOOST_PP_CAT(AUX778076_OP_NAME,2);

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    BOOST_MPL_PP_DEF_PARAMS_TAIL(2, typename N, na)
    >
struct AUX778076_OP_NAME
#if BOOST_WORKAROUND(BOOST_MSVC, == 1300)
    : aux::msvc_eti_base< typename if_<
#else
    : if_<
#endif
          is_na<N3>
        , BOOST_PP_CAT(AUX778076_OP_NAME,2)<N1,N2>
        , AUX778076_OP_NAME<
              BOOST_PP_CAT(AUX778076_OP_NAME,2)<N1,N2>
            , BOOST_MPL_PP_EXT_PARAMS(3, BOOST_PP_INC(AUX778076_OP_ARITY), N)
            >
        >::type
#if BOOST_WORKAROUND(BOOST_MSVC, == 1300)
    >
#endif
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          AUX778076_OP_ARITY
        , AUX778076_OP_NAME
        , ( BOOST_MPL_PP_PARAMS(AUX778076_OP_ARITY, N) )
        )
};

template< 
      typename N1
    , typename N2
    >
struct BOOST_PP_CAT(AUX778076_OP_NAME,2)

#endif

#else // AUX778076_OP_ARITY == 2

template< 
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct AUX778076_OP_NAME

#endif

#if !defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
    : AUX778076_OP_IMPL_NAME<
          typename AUX778076_OP_TAG_NAME<N1>::type
        , typename AUX778076_OP_TAG_NAME<N2>::type
        >::template apply<N1,N2>::type
#else
    : aux::msvc_eti_base< typename apply_wrap2<
          AUX778076_OP_IMPL_NAME<
              typename AUX778076_OP_TAG_NAME<N1>::type
            , typename AUX778076_OP_TAG_NAME<N2>::type
            >
        , N1
        , N2
        >::type >::type
#endif
{
#if AUX778076_OP_ARITY != 2

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          AUX778076_OP_ARITY
        , AUX778076_OP_NAME
        , ( BOOST_MPL_PP_PARTIAL_SPEC_PARAMS(2, N, na) )
        )
#   else
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, BOOST_PP_CAT(AUX778076_OP_NAME,2), (N1, N2))
#   endif

#else
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, AUX778076_OP_NAME, (N1, N2))
#endif
};

BOOST_MPL_AUX_NA_SPEC2(2, AUX778076_OP_ARITY, AUX778076_OP_NAME)

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1

#   define i_ BOOST_PP_FRAME_ITERATION(1)

template<
      BOOST_MPL_PP_PARAMS(i_, typename N)
    >
struct AUX778076_OP_NAME<BOOST_MPL_PP_PARTIAL_SPEC_PARAMS(i_, N, na)>
#if i_ != 2
    : AUX778076_OP_N_CALLS(i_, N)
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          AUX778076_OP_ARITY
        , AUX778076_OP_NAME
        , ( BOOST_MPL_PP_PARTIAL_SPEC_PARAMS(i_, N, na) )
        )
};
#endif

#   undef i_

#endif // BOOST_PP_ITERATION_DEPTH()
#endif // BOOST_PP_IS_ITERATING

/* numeric_op.hpp
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
*/