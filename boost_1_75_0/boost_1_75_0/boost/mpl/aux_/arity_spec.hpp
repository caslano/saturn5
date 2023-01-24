
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
Zfq6ktNAyac9S0uETkbKk0i2gYCqQO9DMuCe3HOrV2gV1QX39N1moxeuYkvZCu9hzl/S7YAOEiLhAkguKkUOs6drHu1RSta8S0alf2FoyMhYd/yw0BUhWiuCzsafm/CtBdUItS76wbdIQEHJ1ZyKgJEeCpDeSf58byCwaZ7n8jzfyyoaErVBT5IAvK6Ncrr7w9eaxzzcD0ejrd+3bLxR0k+cTbPBKs34dDHWmYw8jX3YKDeZNq/wyS8C2MAu2skuwz9TISoUOCBDBHKGQIA92QPz3u6/VXhzWVPN+FmGcbWQsmm2o5kl3564gu5O7XmVWzPc6Sdbly/b4tvVZWI58BiVPf0bMRgh5rG63x5cmXhViwoN5Krwow2RxRbNS6oLTmxYC9OGMpaK0TgTkIk3XGWAixY8EKPWqdXIuLDWWRMN9MfHD7PKp5ITiZP5RnM4cjqbFZFv7MBeaviQbuJv/mbHA2+TD9frsUDfhzUI8qXUBlU7p9XDfZ7DW/2mn6lWZNoswFhTc5sZwOVE5tUfqensNV7Pr5+yWcnWP1GXJqjGismHupNQBrNRD+g1Ee5UHu7cYsamcK6VHXK7R23f6ql1gnBnoTMBfwAlGS1EavfgU9c3UzdIvviZNfnshY6EAdHx05hq9vmRh8WHT/L7P5Fu/AEdcFHlVpkjTt/sXHG8h8wsMFplnbUI6H6CxnuP+oh8Slu/SXqe8jOa
*/