
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
K5vC5WsKXt8bn9devqDTTM0NqyYBvRLigxLdWg8IauC6fICta7u5t9/m8uY06urEX3Y0OXlhW8G8oIH7Pn/qYLX5fULRnEgH5em67bJ96xxpvnHX+d0fm7zPaS6oFbVLFdhu5eyevDn1d41al3cmaveWQUPcq1Rvl5vlPDIn1f11WZuvi7tH5M48/1vYgw9JoZ0vZdiul3ydX9Rn2OPfQno7nglb1GtzRODDxFrNOiV/SJFVSRr9pqhn/qw3zis8W8xYcC6v+t30rOBPHeq99Gy3ZV9ObsDBMP/tLWd0jzu/bdzY088q5udPn3g0acXrh7Vuze2qHDpz5ZSu8yo429z58v3G3n35T9bOS5G22P1h8rBalQ48oGwaWu162LRM2pn11tZO8+5bLCx8qjk3YY7tHK/G1qPvJni8cNz25caNVttuLrrZNNfSwiGuRraneeq4ih4N955pdW7ny6TAnV+fLRUMWF61fLRLBb++N/dO9Xr2W6TLw6dHC+fN6FCrRoGqgltKfHevcnM/nRrZPyI2e6O0nucGiwu8Hb+fK+Rvqd07ZMUYl+FPb6yrNMBtw9eH3spqFzp9Hlp/ZiX3C4vmnt4s75wRfqXfX3uefTMmav7nyMDyGVVTO/errbz1NSDj0K8HFaqHvb8kDpf6DJiwcM7FqYPMrOiYd+LrrVdS5Qe83hqxxfXS1GTLaaI4/+DzewUFCxwaF1kumFUUuzjkRvJSv/GzypZLPhHW7IWmzbbvTj1OCjvnnfpLsm2/ek9W3cl71dZ9+M4a1ROCvFoPGt+i8Ga13x60ePKXEe+2Hs94m9nyVNQh822iyQdG7K99+0PNU2WFR+KGhroNdOzrf/NC2bNHpE2P5GTtqHC2XfMZM+K8al0cVjE8qNH+vIyGS3cfqCq1W90p8P7lD4NGt2q/+tS8xNVVl4yfNN/3gfjoiFzLzHLXNq5MKFtncf1RI5qNc7m8zK6hqij7Q8YX8djXB4pi5217+9cvLy2+BlT+ltYuNvjO40qLg+xeV32tVDdYYX9o57Ik/7N2HyofbT5xtOTQAsXwx18U536JmdiySrmOoa+qPL+Z/Zetj3p1XNUldeGx920fZD6dHcuLuvFkjE3Vgude63YOyvwaP2Lmq4pmd+mlB680bBPV+nZGhzUvQp0nDm1z5nW6l9R12clVVU8IfGumTR9579X9Wl3GXS8ozIzLP+FlsWXkqeH9HvZ+17fDxWndztD2F1adXuV8LunzkwnNr5867xbSZvywXV9etEqcWPbwgx0p94syogOTdxw7vGJpSoVfnsxoPTeocWWrebu9bUc+d9pXuWX9Fb+XvdFkTkGryWMaHsp98mbT7ndVe99IbP5CKYl6fe+E34GBo3vM3Fix40BZwyk7V43Kb3bPc8TDcam/Prr9aHLYl5nnX/Q7X+7G3F5+17bfv+zO46l6Z920Uld2kfYLSp41N9OpbfCYSkppl7wG8fP+OuzWjOEHPtar12/4XzMmnuvm0cihwLJ75rJfikY/i7DeLOsz4rFCRdWc7expPSw2n5LcsOxi1qnu5rSCfoOkuc+WrnvwpP6UvMLTqS0LU/eskfY0dx0vajXjydHfyxQ6VuzdfXKTMeYFMTXl+17fq7Shoq3vxOEr3t2q4ZfvEZTwKqCJLY56t52KGje2QouKn9z7vFna2qvciIUt25mPs5K0X99lxJVBYy2nrq/b1N3ferVdwqPd56qU7drQzqrz2ATLMdOXhp3rQ1eoszdy1RiL/A/Os14JcgIVmdLujRZWaFBYJ2Xz9mBe9PPHY1dsn7707dTH1P/d/93/3f/d/93/3b/QJZsREDdpla1oJkD9gcvZKRRRpXA=
*/