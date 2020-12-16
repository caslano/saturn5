
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
YrZN9/y65m275j15fNlaY88bJS3zxHc81qn302dvXHwSGjnnHMG/N13LM3wmseTLU+HhvL5xTq3qxl/ma2SdsN3xrKqjVKk2p6lwcC291PnG5Ruutr5qlw1XDT8KF1lQnrDa1GuIxVV6wNhmtnYpZfI3B7pb2e+XjR1YrJDiszg7KTJt4Z3TEQZzlqumv//Ja+/D5XZpEy+Y1N1b7NZ4PngjKb18+znNOO5jjxtVz94v+tlP1akNzmfLZZgZl+1WfKuq+VR9clmW62yV75uiRCQbdp312VVSsGKZwL2YmSaytI4X7Lw+t0u4+X70Fq3eXrHhX69ZY1+yPHbdlcY40Y0ZaSMfmO4u14czC4O/6Tc67R8Ub5F9O52y3MPrVaGN2w3G3v237/2qcaLqyvvbkx/nq7a9/ZV4r6/YTpkDc0QrPqVlOvZ1yq47UJgsK1eXvEL84av+c8sMfZy0T1fWvdj2/Nseg4gTZonrt109x/c3fnl0zsG84YeX+cvkP36f1plSD9o21Ox/wOVkgPzMNLV50ykvLg3M3rZARiFgX+N4nNXO1MK9b+d9P1VSs62lVvPq6RXXCwMsfCgRIfyG31wbn3b5nlnLuPYgal/+6yRho9PZI143umveXM0MO1KQ6q9xK69oremMuYZzdzbHxjTdoV8XXhwRiq9x3EVJC+kZos1/m8LZknK1qzFl/sxZRyeX3H/gUWqm6qvk3Liuciu9abGZ+eGQXzdtXj/zPE1y23AKrWLq0N5fGZkEex59t+/izqfzT3xmbd8f8JOW5/mYRMVnC7blJzcMJweuP/XY5XTFLPcxd5ENwd9Em5zfqsVn+1yPXHRA8G6YaTYiUvYbKmv5hVcbZ24Inzp4Lj3xQGv3xm0bUxNmZmZXfj0+Pmdeb3Rolsz2gpdpyZztt15LW2+7UH9oTtX5nHJH82HDSp/D+ZWFCdRFzw5oa3nr7jxju/3QM3bys45FrI+b9+9xecCo6d98daDo/MrXy0LfNRVof3Xsbz+4XFB87K7M7I1LeYffE6m/ePTQJMBj6snQmvFjuqcbzlQky88T3y3cfzWPsbtbXeLKlhM5irft6qYdz+Z9vXrd6cM5tUxfGbsVk0l3Vu1k0Z6kzvCUfzj9Onj11y09Ci9Pblwl8su6rNzgA9+m7b1+y951gDWxZeFJiBoQMViwoY4FF1SkWRAbUhQUAQUVawwkQBQSTAKCPhF7f/a1PsXeFRsiIqJYnx07FuzYK/a2PzdlZhJ88rZ9u9/uDT/n3nPO7e3Mzczk0ZbWmeXPf1/VZs77Tw0m+Md+ympbwzc+/C/Di/qPSZ26T3LOq865IsHm07NXJlfaPd1LpFqvGrPuUNzs8vdHVjq2vJ99UFF429WPc1q45JV5+NlhsteYgi87QwanB/U7MNJqY11h3S3VJ4hihV+/TLb//tH6ZFf5lv6DG3T7/Walw9M6NP3meDbvr2EvPuT3OHMvql/VedP8uvhbrkvfkzVmRn/fIecnt5o7yGP9ceppSI+hPv5dJ1p4Zqkv20Y1/+Vd8lB+y55Pgr47nV1xaND+vByzDhdiX+wMPjetc7lJ1RVUzw73V2RdeLDHJkWwws299/yokfTldjMq3nQb8UHlFnRy44DDkxLS1lB4NHjE3Lx4qveHSXs/LuV5Tf6+Wup1ix8xvsnVayp5rfnPbzqtUDTZIhTHSoZvjZp4/H7ek7pnDh57IRlqt+nVwdZjTmYE1Is6N/b+tvD213ef3ica5d7f4mM7n5cVj8QqBvl7hA7yO/CX3rWnPGriXm3nlIbZt+mK+X/dajfON/p+m7ELR/pWGBQ8x8k+fEfzsbR17aup02ObuNRpIqX6Oi8=
*/