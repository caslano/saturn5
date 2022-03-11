
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