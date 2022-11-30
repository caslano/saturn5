
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_AUX_LAMBDA_NO_CTPS_HPP_INCLUDED
#define BOOST_MPL_AUX_LAMBDA_NO_CTPS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
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
#   include <boost/mpl/bind_fwd.hpp>
#   include <boost/mpl/protect.hpp>
#   include <boost/mpl/is_placeholder.hpp>
#   include <boost/mpl/if.hpp>
#   include <boost/mpl/identity.hpp>
#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>
#   include <boost/mpl/aux_/template_arity.hpp>
#   include <boost/mpl/aux_/value_wknd.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if    !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER lambda_no_ctps.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/default_params.hpp>
#   include <boost/mpl/aux_/preprocessor/repeat.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/config/msvc.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>

#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

#   define AUX778076_LAMBDA_PARAMS(i_, param) \
    BOOST_MPL_PP_PARAMS(i_, param) \
    /**/

namespace aux {

#define n_ BOOST_MPL_LIMIT_METAFUNCTION_ARITY
template<
      BOOST_MPL_PP_DEFAULT_PARAMS(n_,bool C,false)
    >
struct lambda_or
    : true_
{
};

template<>
struct lambda_or< BOOST_MPL_PP_ENUM(n_,false) >
    : false_
{
};
#undef n_

template< typename Arity > struct lambda_impl
{
    template< typename T, typename Tag, typename Protect > struct result_
    {
        typedef T type;
        typedef is_placeholder<T> is_le;
    };
};

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(1, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/aux_/lambda_no_ctps.hpp>))
#include BOOST_PP_ITERATE()

} // namespace aux

template<
      typename T
    , typename Tag
    , typename Protect
    >
struct lambda
{
    /// Metafunction forwarding confuses MSVC 6.x
    typedef typename aux::template_arity<T>::type arity_;
    typedef typename aux::lambda_impl<arity_>
        ::template result_< T,Tag,Protect > l_;

    typedef typename l_::type type;
    typedef typename l_::is_le is_le;
    
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3, lambda, (T, Tag, Protect))
};

BOOST_MPL_AUX_NA_SPEC2(1, 3, lambda)

template<
      typename T
    >
struct is_lambda_expression
    : lambda<T>::is_le
{
};

#   undef AUX778076_LAMBDA_PARAMS

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_LAMBDA_NO_CTPS_HPP_INCLUDED

///// iteration, depth == 1

#else

#define i_ BOOST_PP_FRAME_ITERATION(1)

#   define AUX778076_LAMBDA_TYPEDEF(unused, i_, F) \
    typedef lambda< \
          typename F::BOOST_PP_CAT(arg,BOOST_PP_INC(i_)) \
        , Tag \
        , false_ \
        > BOOST_PP_CAT(l,BOOST_PP_INC(i_)); \
    /**/

#   define AUX778076_IS_LE_TYPEDEF(unused, i_, unused2) \
    typedef typename BOOST_PP_CAT(l,BOOST_PP_INC(i_))::is_le \
        BOOST_PP_CAT(is_le,BOOST_PP_INC(i_)); \
    /**/

#   define AUX778076_IS_LAMBDA_EXPR(unused, i_, unused2) \
    BOOST_PP_COMMA_IF(i_) \
    BOOST_MPL_AUX_MSVC_VALUE_WKND(BOOST_PP_CAT(is_le,BOOST_PP_INC(i_)))::value \
    /**/

#   define AUX778076_LAMBDA_RESULT(unused, i_, unused2) \
    , typename BOOST_PP_CAT(l,BOOST_PP_INC(i_))::type \
    /**/

template<> struct lambda_impl< int_<i_> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        BOOST_MPL_PP_REPEAT(i_, AUX778076_LAMBDA_TYPEDEF, F)
        BOOST_MPL_PP_REPEAT(i_, AUX778076_IS_LE_TYPEDEF, unused)

        typedef aux::lambda_or<
              BOOST_MPL_PP_REPEAT(i_, AUX778076_IS_LAMBDA_EXPR, unused)
            > is_le;

        typedef BOOST_PP_CAT(bind,i_)<
              typename F::rebind
            BOOST_MPL_PP_REPEAT(i_, AUX778076_LAMBDA_RESULT, unused)
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;
    
        typedef typename type_::type type;
    };
};

#   undef AUX778076_LAMBDA_RESULT
#   undef AUX778076_IS_LAMBDA_EXPR
#   undef AUX778076_IS_LE_TYPEDEF
#   undef AUX778076_LAMBDA_TYPEDEF

#undef i_

#endif // BOOST_PP_IS_ITERATING

/* lambda_no_ctps.hpp
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
*/