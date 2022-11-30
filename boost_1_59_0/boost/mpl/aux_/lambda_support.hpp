
#ifndef BOOST_MPL_AUX_LAMBDA_SUPPORT_HPP_INCLUDED
#define BOOST_MPL_AUX_LAMBDA_SUPPORT_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) /**/
#   define BOOST_MPL_AUX_LAMBDA_SUPPORT(i,name,params) /**/

#else

#   include <boost/mpl/int_fwd.hpp>
#   include <boost/mpl/aux_/yes_no.hpp>
#   include <boost/mpl/aux_/na_fwd.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/config/msvc.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>

#   include <boost/preprocessor/tuple/to_list.hpp>
#   include <boost/preprocessor/list/for_each_i.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_ARG_TYPEDEF_FUNC(R,typedef_,i,param) \
    typedef_ param BOOST_PP_CAT(arg,BOOST_PP_INC(i)); \
    /**/

// agurt, 07/mar/03: restore an old revision for the sake of SGI MIPSpro C++
#if BOOST_WORKAROUND(__EDG_VERSION__, <= 238) 

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT(i, name, params) \
    typedef BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::int_<i> arity; \
    BOOST_PP_LIST_FOR_EACH_I_R( \
          1 \
        , BOOST_MPL_AUX_LAMBDA_SUPPORT_ARG_TYPEDEF_FUNC \
        , typedef \
        , BOOST_PP_TUPLE_TO_LIST(i,params) \
        ) \
    struct rebind \
    { \
        template< BOOST_MPL_PP_PARAMS(i,typename U) > struct apply \
            : name< BOOST_MPL_PP_PARAMS(i,U) > \
        { \
        }; \
    }; \
    /**/

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
    BOOST_MPL_AUX_LAMBDA_SUPPORT(i, name, params) \
    /**/

#elif BOOST_WORKAROUND(__EDG_VERSION__, <= 244) && !defined(BOOST_INTEL_CXX_VERSION)
// agurt, 18/jan/03: old EDG-based compilers actually enforce 11.4 para 9
// (in strict mode), so we have to provide an alternative to the 
// MSVC-optimized implementation

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
    typedef BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::int_<i> arity; \
    BOOST_PP_LIST_FOR_EACH_I_R( \
          1 \
        , BOOST_MPL_AUX_LAMBDA_SUPPORT_ARG_TYPEDEF_FUNC \
        , typedef \
        , BOOST_PP_TUPLE_TO_LIST(i,params) \
        ) \
    struct rebind; \
/**/

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT(i, name, params) \
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
}; \
template< BOOST_MPL_PP_PARAMS(i,typename T) > \
struct name<BOOST_MPL_PP_PARAMS(i,T)>::rebind \
{ \
    template< BOOST_MPL_PP_PARAMS(i,typename U) > struct apply \
        : name< BOOST_MPL_PP_PARAMS(i,U) > \
    { \
    }; \
/**/

#else // __EDG_VERSION__

namespace boost { namespace mpl { namespace aux {
template< typename T > struct has_rebind_tag;
}}}

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
    typedef BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::int_<i> arity; \
    BOOST_PP_LIST_FOR_EACH_I_R( \
          1 \
        , BOOST_MPL_AUX_LAMBDA_SUPPORT_ARG_TYPEDEF_FUNC \
        , typedef \
        , BOOST_PP_TUPLE_TO_LIST(i,params) \
        ) \
    friend class BOOST_PP_CAT(name,_rebind); \
    typedef BOOST_PP_CAT(name,_rebind) rebind; \
/**/

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x610))
#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_HAS_REBIND(i, name, params) \
template< BOOST_MPL_PP_PARAMS(i,typename T) > \
::boost::mpl::aux::yes_tag operator|( \
      ::boost::mpl::aux::has_rebind_tag<int> \
    , name<BOOST_MPL_PP_PARAMS(i,T)>* \
    ); \
::boost::mpl::aux::no_tag operator|( \
      ::boost::mpl::aux::has_rebind_tag<int> \
    , name< BOOST_MPL_PP_ENUM(i,::boost::mpl::na) >* \
    ); \
/**/
#elif !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_HAS_REBIND(i, name, params) \
template< BOOST_MPL_PP_PARAMS(i,typename T) > \
::boost::mpl::aux::yes_tag operator|( \
      ::boost::mpl::aux::has_rebind_tag<int> \
    , ::boost::mpl::aux::has_rebind_tag< name<BOOST_MPL_PP_PARAMS(i,T)> >* \
    ); \
/**/
#else
#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_HAS_REBIND(i, name, params) /**/
#endif

#   if !defined(BOOST_BORLANDC)
#   define BOOST_MPL_AUX_LAMBDA_SUPPORT(i, name, params) \
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
}; \
BOOST_MPL_AUX_LAMBDA_SUPPORT_HAS_REBIND(i, name, params) \
class BOOST_PP_CAT(name,_rebind) \
{ \
 public: \
    template< BOOST_MPL_PP_PARAMS(i,typename U) > struct apply \
        : name< BOOST_MPL_PP_PARAMS(i,U) > \
    { \
    }; \
/**/
#   else
#   define BOOST_MPL_AUX_LAMBDA_SUPPORT(i, name, params) \
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(i, name, params) \
}; \
BOOST_MPL_AUX_LAMBDA_SUPPORT_HAS_REBIND(i, name, params) \
class BOOST_PP_CAT(name,_rebind) \
{ \
 public: \
    template< BOOST_MPL_PP_PARAMS(i,typename U) > struct apply \
    { \
        typedef typename name< BOOST_MPL_PP_PARAMS(i,U) >::type type; \
    }; \
/**/
#   endif // BOOST_BORLANDC

#endif // __EDG_VERSION__

#endif // BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#endif // BOOST_MPL_AUX_LAMBDA_SUPPORT_HPP_INCLUDED

/* lambda_support.hpp
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
*/