
#ifndef BOOST_MPL_AUX_ARITY_SPEC_HPP_INCLUDED
#define BOOST_MPL_AUX_ARITY_SPEC_HPP_INCLUDED

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

#include <boost/mpl/int.hpp>
#include <boost/mpl/limits/arity.hpp>
#include <boost/mpl/aux_/config/dtp.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/arity.hpp>
#include <boost/mpl/aux_/template_arity_fwd.hpp>
#include <boost/mpl/aux_/config/ttp.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

#if defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#   define BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(i,type,name) \
namespace aux { \
template< BOOST_MPL_AUX_NTTP_DECL(int, N), BOOST_MPL_PP_PARAMS(i,type T) > \
struct arity< \
      name< BOOST_MPL_PP_PARAMS(i,T) > \
    , N \
    > \
{ \
    BOOST_STATIC_CONSTANT(int \
        , value = BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        ); \
}; \
} \
/**/
#else
#   define BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(i,type,name) /**/
#endif

#   define BOOST_MPL_AUX_ARITY_SPEC(i,name) \
    BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(i,typename,name) \
/**/


#if defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING) \
    && !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   define BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(i, name) \
namespace aux { \
template< BOOST_MPL_PP_PARAMS(i,typename T) > \
struct template_arity< name<BOOST_MPL_PP_PARAMS(i,T)> > \
    : int_<i> \
{ \
}; \
} \
/**/
#else
#   define BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(i, name) /**/
#endif


#endif // BOOST_MPL_AUX_ARITY_SPEC_HPP_INCLUDED

/* arity_spec.hpp
uvQo8k2k8ujpbX4V7e5LI6IjfkvvVaFOD+CRw5m/KpN76A7PrK0rlbjJdMlgZ1d8aAxmdiSCg0ex7qCauXVWMJfj50EHu24+Ef60F7bB9aa5LFJUgUPdRi5XDi/7U1YUEMRPHRkksF6cd/DJ7Go4CV5hjAxMsseFtpmI6Ad3sR/mKwyqGXbmHI9THkkU5ocYEu/4AEyRS+s3JfjiDNmQP9U5LqfMs09tf7DAyH4OA7DATBn/cL6Lz+RUe7DOJoMhZ+c+odwq7/hf88H3oayoGgq4dicceGkOMNVP7mtkIXvqfInMsutP/N9QYPCwxLP/sadbJDuamuTkMeoSOtwyntqwOLayx76kGwOSpp9rv2qSZtauaTO/Ir4u35FOdhIZmHqJ3EYh4NCgOBldf9uZAcK04NCRvyB9HeNqrasW3QRq91X72B2zqos9aplkuuIAOtuzwBA61bl++JisjyyIkQ2VYKMSBoOmIfTHuT9pp7FgyIxiJvrEzX8+ALggFV76ECOCkv5vbBCH2dSjB8p5EhJSXnH8Wg5ZVyxamgLri5VpvmNFrIWbCoHGgg==
*/