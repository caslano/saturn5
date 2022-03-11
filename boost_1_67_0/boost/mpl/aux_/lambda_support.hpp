
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

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))
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

#   if !defined(__BORLANDC__)
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
#   endif // __BORLANDC__

#endif // __EDG_VERSION__

#endif // BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#endif // BOOST_MPL_AUX_LAMBDA_SUPPORT_HPP_INCLUDED

/* lambda_support.hpp
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
*/