
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_ARG_HPP_INCLUDED
#define BOOST_MPL_ARG_HPP_INCLUDED

// Copyright Peter Dimov 2001-2002
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
#   include <boost/mpl/arg_fwd.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/na_assert.hpp>
#   include <boost/mpl/aux_/arity_spec.hpp>
#   include <boost/mpl/aux_/arg_typedef.hpp>
#endif

#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER arg.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/default_params.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/config/lambda.hpp>
#   include <boost/mpl/aux_/config/dtp.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>

#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

// local macro, #undef-ined at the end of the header
#if !defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#   define AUX778076_ARG_N_DEFAULT_PARAMS(param,value) \
    BOOST_MPL_PP_DEFAULT_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    /**/
#else
#   define AUX778076_ARG_N_DEFAULT_PARAMS(param,value) \
    BOOST_MPL_PP_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        ) \
    /**/
#endif

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/arg.hpp>))
#include BOOST_PP_ITERATE()


#   undef AUX778076_ARG_N_DEFAULT_PARAMS

BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(1,int,arg)

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_ARG_HPP_INCLUDED

///// iteration

#else
#define i_ BOOST_PP_FRAME_ITERATION(1)

#if i_ > 0

template<> struct arg<i_>
{
    BOOST_STATIC_CONSTANT(int, value = i_);
    typedef arg<BOOST_PP_INC(i_)> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          AUX778076_ARG_N_DEFAULT_PARAMS(typename U, na)
        >
    struct apply
    {
        typedef BOOST_PP_CAT(U,i_) type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

#else

template<> struct arg<-1>
{
    BOOST_STATIC_CONSTANT(int, value = -1);
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          AUX778076_ARG_N_DEFAULT_PARAMS(typename U, na)
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

#endif // i_ > 0

#undef i_
#endif // BOOST_PP_IS_ITERATING

/* arg.hpp
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
*/