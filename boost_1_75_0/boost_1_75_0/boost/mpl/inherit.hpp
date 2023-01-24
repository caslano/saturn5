
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
/DEmdjlguscva8HvUcxSJ7hn7KNrqauRHEKi+mvb0iokjp8w11yEzACy883wh8TjYHLTfEBXynbTp8kMwZQPMk1dyQIbrRboEyPP2Uqz74Hb2Nmxt+QZUVqZNPG3y9KNjFWqgb2lnvJuYRiuy23uJW6c5b9U1QRBOstOlS2eoBbipnnTfIHcA5KASWKBH62vmmJtpj7wup6IuSUDt+66YY7eyxsvsQdao4OgBYcPxfScgHqu2yjF+i4DcJZQweoaa89+RU/vSnDGwW9A2thrqOJ1teD9elpPmZBHnrVObZkvlz1KvHmJU5MO8GOteQOLXX10j6mQ+4aRUP2CrxBMX/ONW8T7jd5+K7IEyvtepvcqU2/nNaPi3MbZF/bt615WuvR2X7fHW+eJDIp2Jxxn8Hif42c5N9DZph6u9789leXAul1CB8UbyZkFUYzBtt1tG15AR8AUSmq3Uau3IjlZAVnj6NmVNi+sNAUvB6ymbelaVgG1eiCS+8OIbVFTAJ/qbO7u0NFyJuijs7oL5mKepCDwt803dDU08TC8q9dbGjQ9v90z96/g1FIt5EuIoHnyNIzMqFTcMJHS6gk5oiXSwr7F82PsiULKRbx+4dkN0MVlhta/YZHt6nCmH/tluWh7/PGDPkDFTZ194TPXwv7Jx4su53STlO3xt6syQZ/iLvs2p7oZFi+yUE9mP3Pge0Oy8Opmguxmz22pw25B
*/