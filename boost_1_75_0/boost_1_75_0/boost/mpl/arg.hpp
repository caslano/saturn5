
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
4RqSmtczKy8Vc3rhigG9lbX147/G9MxskeYMlFu5GTE67XxTssuWX2fo+Rzn/lCFLaMqsiCpWtiidIq84xurrn/7ma+ZmVfP2pX6daaKUdTe7qOHLoaD64o/vf1lt/1k+2b74Ub74xrwnrVHw6h7h9p/Wu4bst8wbCtLkVvOMubtG969h/WGBq42/zOm1/Ij7EaiyVUTW4rg+hLBR92VEKXnNHh+Grpc0K++tziorLJLh+2EKopTYVNP/OqnR8VvwIohUiG1WTXGhD70QU/Tb3YTgNX5rLdI5ATSuGKB6MZxZnvF8kW0XNJIC1jaW3VodaCH3OOnLpLlTeU/GegBW295C090FTu/K8OgsJe946Q8h0/+XHcT02ICprD0N7tQJ6tGOip1wqrELKo/c2CeMIKpdp4+88gz0cT8ektapsTqA/uEqV9/wDneTKwKhEihm4+crzjsStnjhr8ZKPd2oH9STpmIR4NHKcNWlren/F9xg3fOh8A5gG3fm4Ycu0TVvUTx2vLjnToJbO0TAtQXAsaovVQQovxexv5NcNlt8qGywRvMZCJqjrdMKKGDI8oSYjQZls+s05A39WTPAbIXoxxFQVjccTC8m/GROso6WTM09akcBkXBlx9WVMNp5Qs5ER+AMjoRUXFze3IDnlztmjPXlu1VT09Xa/VLT0seavhEgFLN8iMs4dh74QgdazPPwgKWJcvpnDjZ0sp9
*/