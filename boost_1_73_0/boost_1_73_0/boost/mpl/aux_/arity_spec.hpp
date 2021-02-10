
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
d6v33+N+/TiNtUjpMdg5zbIqtFdbw0o7n9F6bLE8P7vfAVBLAwQKAAAACAAtZ0pSn6YKAtkDAAAvCAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwMDVVVAUAAbZIJGClVm1v2zYQ/i7A/+Gmzm1cxKYtO3asyi6KpG2yNUuQeO2AYRtoirKFSKRA0nX8Zb99d5Jsx2nXDRsQWNLp+Nxzz70okZPWCW7l1ItSlWi83MvNWpvYTr0r6XiWqnvvYja7KX/g/duZF7G9S8SqU94z7xncSfNZmrZNY+lFRhbZBh1i7jgoLZZS3E/8jbT+tIRivU4Pgm4Xrn/0zrmTIXyS8TFa4IeVwksvgN4gHIxDdHl/NfMq8BCIcNuWDyzh99I708pJ5dofpFq4ZQj9EZmUFC7VKgSRabt3mm0KSRgPji1dnu3s56kttE2rI0maScVzOaEfpHjyCsSSGyvdJFkptXkFuiDPiXWGq4X03pG1vZQ8DgEzxD+PcuIQyyxFojKGxOgcuIJSRSOtXhmBKjGSh2Ss5Sp1PMtS4lTpKMoHdKlynnpL5wo8sH2MEsndChGnHvHeFy1i+zcQUSr7ikKmBc/gl6sPZbLHT2hBxCr/SOg85yreJuwr3dYrV6zcMd6lSmSr
*/