
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_APPLY_WRAP_HPP_INCLUDED
#define BOOST_MPL_APPLY_WRAP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
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
#   include <boost/mpl/aux_/arity.hpp>
#   include <boost/mpl/aux_/has_apply.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/msvc_never_true.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER apply_wrap.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/preprocessor/add.hpp>
#   include <boost/mpl/aux_/config/bcc.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/dtp.hpp>
#   include <boost/mpl/aux_/config/eti.hpp>
#   include <boost/mpl/aux_/config/msvc.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>

#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/logical/and.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/iterate.hpp>


namespace boost { namespace mpl {

// local macros, #undef-ined at the end of the header
#   define AUX778076_APPLY_WRAP_PARAMS(n, param) \
    BOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   define AUX778076_APPLY_WRAP_SPEC_PARAMS(n, param) \
    BOOST_MPL_PP_ENUM(BOOST_PP_INC(n), param) \
    /**/


#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/apply_wrap.hpp>))
#include BOOST_PP_ITERATE()


#   undef AUX778076_APPLY_WRAP_SPEC_PARAMS
#   undef AUX778076_APPLY_WRAP_PARAMS

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_APPLY_WRAP_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1

#   define i_ BOOST_PP_FRAME_ITERATION(1)

#   if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
// MSVC version

#define AUX778076_MSVC_DTW_NAME BOOST_PP_CAT(msvc_apply,i_)
#define AUX778076_MSVC_DTW_ORIGINAL_NAME apply
#define AUX778076_MSVC_DTW_ARITY i_
#include <boost/mpl/aux_/msvc_dtw.hpp>

template<
      typename F BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply_wrap,i_)
{
    // Metafunction forwarding confuses vc6
    typedef typename BOOST_PP_CAT(msvc_apply,i_)<F>::template result_<
          AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >::type type;
};

#   elif defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
// MWCW/Borland version

template<
      int N, typename F BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply_wrap_impl,i_);

#define BOOST_PP_ITERATION_PARAMS_2 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY - i_, <boost/mpl/apply_wrap.hpp>))
#include BOOST_PP_ITERATE()

template<
      typename F BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply_wrap,i_)
    : BOOST_PP_CAT(apply_wrap_impl,i_)<
          ::boost::mpl::aux::arity<F,i_>::value
        , F
        BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >::type
{
};

#   else
// ISO98 C++, with minor concession to vc7

template<
      typename F BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
#if i_ == 0
    , typename has_apply_ = typename aux::has_apply<F>::type
#endif
    >
struct BOOST_PP_CAT(apply_wrap,i_)
// metafunction forwarding confuses MSVC 7.0
#if !BOOST_WORKAROUND(BOOST_MSVC, == 1300)
    : F::template apply< AUX778076_APPLY_WRAP_PARAMS(i_, T) >
{
#else
{    
    typedef typename F::template apply<
         AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >::type type;
#endif
};

#if i_ == 0 && !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template< typename F >
struct BOOST_PP_CAT(apply_wrap,i_)<F,true_>
    : F::apply
{
};
#endif

#   endif // workarounds

#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
/// workaround for ETI bug
template<>
struct BOOST_PP_CAT(apply_wrap,i_)<AUX778076_APPLY_WRAP_SPEC_PARAMS(i_, int)>
{
    typedef int type;
};
#endif

#   undef i_

///// iteration, depth == 2

#elif BOOST_PP_ITERATION_DEPTH() == 2

#   define j_ BOOST_PP_FRAME_ITERATION(2)

#if i_ == 0 && j_ == 0 \
    && defined(BOOST_MPL_CFG_BCC590_WORKAROUNDS) \
    && !defined(BOOST_MPL_CFG_NO_HAS_APPLY)

template< typename F, bool F_has_apply >
struct apply_wrap_impl0_bcb {
    typedef typename F::template apply< na > type;
};

template< typename F >
struct apply_wrap_impl0_bcb< F, true > {
    typedef typename F::apply type;
};

template<
      typename F BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply_wrap_impl,i_)<
          BOOST_MPL_PP_ADD(i_, j_)
        , F
        BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >
{
    typedef apply_wrap_impl0_bcb< F, aux::has_apply< F >::value >::type type;
};
#else

template<
      typename F BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply_wrap_impl,i_)<
          BOOST_MPL_PP_ADD(i_, j_)
        , F
        BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >
{
    typedef typename F::template apply<
          AUX778076_APPLY_WRAP_PARAMS(i_, T)
#if i_ == 0 && j_ == 0
/// since the defaults are "lost", we have to pass *something* even for nullary
/// metafunction classes
        na
#else
        BOOST_PP_COMMA_IF(BOOST_PP_AND(i_, j_)) BOOST_MPL_PP_ENUM(j_, na)
#endif
        > type;
};

#endif

#   undef j_

#endif // BOOST_PP_ITERATION_DEPTH()
#endif // BOOST_PP_IS_ITERATING

/* apply_wrap.hpp
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
*/