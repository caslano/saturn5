
#ifndef BOOST_MPL_AUX_NA_SPEC_HPP_INCLUDED
#define BOOST_MPL_AUX_NA_SPEC_HPP_INCLUDED

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
#   include <boost/mpl/lambda_fwd.hpp>
#   include <boost/mpl/int.hpp>
#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/arity.hpp>
#   include <boost/mpl/aux_/template_arity_fwd.hpp>
#endif

#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/preprocessor/enum.hpp>
#include <boost/mpl/aux_/preprocessor/def_params_tail.hpp>
#include <boost/mpl/aux_/lambda_arity_param.hpp>
#include <boost/mpl/aux_/config/dtp.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/config/ttp.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>
#include <boost/mpl/aux_/config/overload_resolution.hpp>


#define BOOST_MPL_AUX_NA_PARAMS(i) \
    BOOST_MPL_PP_ENUM(i, na) \
/**/

#if defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#   define BOOST_MPL_AUX_NA_SPEC_ARITY(i, name) \
namespace aux { \
template< BOOST_MPL_AUX_NTTP_DECL(int, N) > \
struct arity< \
          name< BOOST_MPL_AUX_NA_PARAMS(i) > \
        , N \
        > \
    : int_< BOOST_MPL_LIMIT_METAFUNCTION_ARITY > \
{ \
}; \
} \
/**/
#else
#   define BOOST_MPL_AUX_NA_SPEC_ARITY(i, name) /**/
#endif

#define BOOST_MPL_AUX_NA_SPEC_MAIN(i, name) \
template<> \
struct name< BOOST_MPL_AUX_NA_PARAMS(i) > \
{ \
    template< \
          BOOST_MPL_PP_PARAMS(i, typename T) \
        BOOST_MPL_PP_NESTED_DEF_PARAMS_TAIL(i, typename T, na) \
        > \
    struct apply \
        : name< BOOST_MPL_PP_PARAMS(i, T) > \
    { \
    }; \
}; \
/**/

#if defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   define BOOST_MPL_AUX_NA_SPEC_LAMBDA(i, name) \
template<> \
struct lambda< \
      name< BOOST_MPL_AUX_NA_PARAMS(i) > \
    , void_ \
    , true_ \
    > \
{ \
    typedef false_ is_le; \
    typedef name< BOOST_MPL_AUX_NA_PARAMS(i) > type; \
}; \
template<> \
struct lambda< \
      name< BOOST_MPL_AUX_NA_PARAMS(i) > \
    , void_ \
    , false_ \
    > \
{ \
    typedef false_ is_le; \
    typedef name< BOOST_MPL_AUX_NA_PARAMS(i) > type; \
}; \
/**/
#else
#   define BOOST_MPL_AUX_NA_SPEC_LAMBDA(i, name) \
template< typename Tag > \
struct lambda< \
      name< BOOST_MPL_AUX_NA_PARAMS(i) > \
    , Tag \
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(int_<-1>) \
    > \
{ \
    typedef false_ is_le; \
    typedef name< BOOST_MPL_AUX_NA_PARAMS(i) > result_; \
    typedef name< BOOST_MPL_AUX_NA_PARAMS(i) > type; \
}; \
/**/
#endif

#if defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING) \
    || defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT) \
        && defined(BOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION)
#   define BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, j, name) \
namespace aux { \
template< BOOST_MPL_PP_PARAMS(j, typename T) > \
struct template_arity< \
          name< BOOST_MPL_PP_PARAMS(j, T) > \
        > \
    : int_<j> \
{ \
}; \
\
template<> \
struct template_arity< \
          name< BOOST_MPL_PP_ENUM(i, na) > \
        > \
    : int_<-1> \
{ \
}; \
} \
/**/
#else
#   define BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, j, name) /**/
#endif

#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
#   define BOOST_MPL_AUX_NA_SPEC_ETI(i, name) \
template<> \
struct name< BOOST_MPL_PP_ENUM(i, int) > \
{ \
    typedef int type; \
    enum { value = 0 }; \
}; \
/**/
#else
#   define BOOST_MPL_AUX_NA_SPEC_ETI(i, name) /**/
#endif

#define BOOST_MPL_AUX_NA_PARAM(param) param = na

#define BOOST_MPL_AUX_NA_SPEC_NO_ETI(i, name) \
BOOST_MPL_AUX_NA_SPEC_MAIN(i, name) \
BOOST_MPL_AUX_NA_SPEC_LAMBDA(i, name) \
BOOST_MPL_AUX_NA_SPEC_ARITY(i, name) \
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, i, name) \
/**/

#define BOOST_MPL_AUX_NA_SPEC(i, name) \
BOOST_MPL_AUX_NA_SPEC_NO_ETI(i, name) \
BOOST_MPL_AUX_NA_SPEC_ETI(i, name) \
/**/

#define BOOST_MPL_AUX_NA_SPEC2(i, j, name) \
BOOST_MPL_AUX_NA_SPEC_MAIN(i, name) \
BOOST_MPL_AUX_NA_SPEC_ETI(i, name) \
BOOST_MPL_AUX_NA_SPEC_LAMBDA(i, name) \
BOOST_MPL_AUX_NA_SPEC_ARITY(i, name) \
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(i, j, name) \
/**/


#endif // BOOST_MPL_AUX_NA_SPEC_HPP_INCLUDED

/* na_spec.hpp
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
*/