
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_INHERIT_HPP_INCLUDED
#define BOOST_MPL_INHERIT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
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
#   include <boost/mpl/empty_base.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER inherit.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/default_params.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/dtp.hpp>

#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/dec.hpp>
#   include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

// 'inherit<T1,T2,..,Tn>' metafunction; returns an unspecified class type
// produced by public derivation from all metafunction's parameters 
// (T1,T2,..,Tn), except the parameters of 'empty_base' class type; 
// regardless the position and number of 'empty_base' parameters in the 
// metafunction's argument list, derivation from them is always a no-op;
// for instance:
//      inherit<her>::type == her
//      inherit<her,my>::type == struct unspecified : her, my {};
//      inherit<empty_base,her>::type == her
//      inherit<empty_base,her,empty_base,empty_base>::type == her
//      inherit<her,empty_base,my>::type == struct unspecified : her, my {};
//      inherit<empty_base,empty_base>::type == empty_base

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< 
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    > 
struct inherit2
    : T1, T2
{
    typedef inherit2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1,T2))
};

template< typename T1 > 
struct inherit2<T1,empty_base>
{
    typedef T1 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (T1,empty_base))
};

template< typename T2 > 
struct inherit2<empty_base,T2>
{
    typedef T2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base,T2))
};

// needed to disambiguate the previous two in case when both 
// T1 and T2 == empty_base
template<> 
struct inherit2<empty_base,empty_base>
{
    typedef empty_base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base,empty_base))
};

#else

namespace aux {

template< bool C1, bool C2 >
struct inherit2_impl
{
    template< typename Derived, typename T1, typename T2 > struct result_ 
        : T1, T2
    {
        typedef Derived type_;
    };
};

template<>
struct inherit2_impl<false,true>
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T1
    {
        typedef T1 type_;
    };
};

template<>
struct inherit2_impl<true,false>
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T2 
    {
        typedef T2 type_;
    };
};

template<>
struct inherit2_impl<true,true>
{
    template< typename Derived, typename T1, typename T2 > struct result_
    {
        typedef T1 type_;
    };
};

} // namespace aux

template< 
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    > 
struct inherit2
    : aux::inherit2_impl<
          is_empty_base<T1>::value
        , is_empty_base<T2>::value
        >::template result_< inherit2<T1,T2>,T1,T2 >
{
    typedef typename inherit2::type_ type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1,T2))
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(3, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/inherit.hpp>))
#include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_INHERIT_HPP_INCLUDED

///// iteration

#else
#define n_ BOOST_PP_FRAME_ITERATION(1)

template<
      BOOST_MPL_PP_DEFAULT_PARAMS(n_, typename T, na)
    >
struct BOOST_PP_CAT(inherit,n_)
    : inherit2<
          typename BOOST_PP_CAT(inherit,BOOST_PP_DEC(n_))<
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(n_), T)
            >::type
        , BOOST_PP_CAT(T,n_)
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          n_
        , BOOST_PP_CAT(inherit,n_)
        , (BOOST_MPL_PP_PARAMS(n_, T))
        )
};

BOOST_MPL_AUX_NA_SPEC(n_, BOOST_PP_CAT(inherit,n_))

#if n_ == BOOST_MPL_LIMIT_METAFUNCTION_ARITY
/// primary template
template<
      BOOST_MPL_PP_DEFAULT_PARAMS(n_, typename T, empty_base)
    >
struct inherit
    : BOOST_PP_CAT(inherit,n_)<BOOST_MPL_PP_PARAMS(n_, T)>
{
};

// 'na' specialization
template<>
struct inherit< BOOST_MPL_PP_ENUM(5, na) >
{
    template<
#if !defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
          BOOST_MPL_PP_DEFAULT_PARAMS(n_, typename T, empty_base)
#else
          BOOST_MPL_PP_PARAMS(n_, typename T)
#endif
        >
    struct apply
        : inherit< BOOST_MPL_PP_PARAMS(n_, T) >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(n_, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(n_, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(n_, n_, inherit)
#endif

#undef n_
#endif // BOOST_PP_IS_ITERATING

/* inherit.hpp
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
*/