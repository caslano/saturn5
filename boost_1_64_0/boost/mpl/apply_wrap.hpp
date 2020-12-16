
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
jSSweUCzvdQ99rke2z8yWUJTTqiZ23uoGdHGKSKDxnrNu0skqFeQp0PC+ZDAdDVotv9AwpacUH0ksIXeRUK0IeF8kZDyFeQmpaVmSMiHhAJIyIeEAtHS8ZDQkBNqjAQaIqFGRBtaKrBoqYklNLOEJrIQ0DvxSkI9JORCQh4k5EJCnkj4fgZL2JgT2hQJSJvNtUjIs0jYwhLqWQJ6R7BBaakREnyQ4IcEHyT4RUtBSOjP4TfIpZ/7LFryW7TUwBIaWQJGl+BGJWHTa7ttDKSzhJqcUC33lFDt2G4bG1nCJpawkWx5h99aI+mvt7XWKAm1kLAAEhZCwgJIWCgSzoKEihz2v6ggLwxEGxIWWiTUsIRallBDBkT6GoDSUtWYjgTQ0s/SDLPqM2ksrC+HP5PQRx9LANJQ2FyLwipYWNWpHUc6gCxLe30DiHmo3uc8VO92HKo3OQ/VG5yH6v3OQ/Uu57vzW5zvzm90vjtf43x3vuLoQfrR39Hf0d/r/xn20HMPDL9ue2jN4dhDe5320CqnPbTnTbCH7jDtoX00P7HFs1bZQzHN9pr20CqK5TG0J6U9tMqwh/aMbQ/daNhDu8ewh/5t/7DDHrpjlGlvOzDKHmrBBGoE8CAAyh4qAKeJpxIYZQ8Fxm7+KwJA2UOtgCoBXAyAsodaAT0COB0AZQ8FwG7McgOg7KECcJr2Xto3bLWHAuO0hz4OjNUe2jdKaXXAKHsoMHallQCg7KFWwCbd/guAsocCYNfYuwFQ9lAroEK3/wKg7KEA2DU2tHfYag8FwGkP3QGMsocKxqm0RmCUPdQqqFsAdwJgtYfW2LVxDQBWe2jtqCY0HxhlDwXGrpDTAFD2UADsTcgFgLKHAmBXyO8Tww57aK29CT0FgLKHpngH5+sAWO2hNXZVrAPAag/dNKqky4BR9lBg7CW9EABlDwXAXvUnAqDsoQDYS/rKP4et9lAAnJapncAoe2iK1+WaAVD2UADshb0LAKs9tNdekM8CkNoeqmrt0n8OH449dCpgyh6a2sI78urwmPZQVagXgbHaQ3vthXoCAKs9tGqUPfSrwFjtoRWjMnwDMMoeKhhnhj8CjLKHAmPP7bkAKHsoAPbcegCw2kN7RuVEe2XYag8FxpmTTmBS20NVZuqBsdpDe+yZufWV4UPaQz8BTGp7qBJ0ITCp7aFKVg4wqe2his/L8eEx7aGKzy+ASW0PVZgH4sNvkT2UP/f3xuyh7P/x5tlDO8kd443ZQ/k1kDfPHsruM2/MHhojo+qbZw/l107emD2ULXBvnj20gb5j+cbsoWLDGkoPDpG3Fzk1KXcvLZ2tNoM5QbiIBQfJPSqdPaO6ctjw0xnhz+21pQfJm6qd3xiQlyUDiXR8zTQnCD81doeIpZNZhaxegX71McqW9GAL+QPwixxBvMgRaEpnI0ZzTrBZLPJkAUvnL2g25gQalQ1sS3pwCxnx2MYYhI0xMKR7DMVf2yXphaFhm6/bWC5JTo83hxPY2E5VpRBgem2ldKoa2y3MrdzCZkJACgOuDwI6c0Jd3EFD1EE5WnzYxLcQbmwp3MKsPns0ckNACvvtD14etr9aUzfdIoBBY3nxdeoq6oKAfAhIYb5dAgGWV0vq8i0qKrCoqJMFdLEAlDTQogtohYBcCEhhvf3734btNu66XIuAPIuAFhbQygKk7bXpKmqHAB8EpDDe1kKAxQGzzmdRkd+iojYW0M4CpEs06QKaIcADASlst+dBgMXCXeexCPBaBDSxgGYSgLHksJvpM399vc20QRfQCAELICCF5fY6CLCcAtQtsAhYaBHQwAIaWQBKGtiiq6geAuZAQArDrYcE6IbbSUTanDDr5li0Ndc=
*/