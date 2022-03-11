
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