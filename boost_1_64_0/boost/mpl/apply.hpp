
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_APPLY_HPP_INCLUDED
#define BOOST_MPL_APPLY_HPP_INCLUDED

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
#   include <boost/mpl/apply_fwd.hpp>
#   include <boost/mpl/apply_wrap.hpp>
#   include <boost/mpl/placeholders.hpp>
#   include <boost/mpl/lambda.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER apply.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/default_params.hpp>
#   include <boost/mpl/aux_/preprocessor/partial_spec_params.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/config/lambda.hpp>
#   include <boost/mpl/aux_/config/dtp.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/eti.hpp>
#   include <boost/mpl/aux_/config/msvc.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>

#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

// local macros, #undef-ined at the end of the header
#   define AUX778076_APPLY_PARAMS(param) \
    BOOST_MPL_PP_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        ) \
    /**/

#   define AUX778076_APPLY_DEF_PARAMS(param, value) \
    BOOST_MPL_PP_DEFAULT_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    /**/

#   define AUX778076_APPLY_N_PARAMS(n, param) \
    BOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   define AUX778076_APPLY_N_COMMA_PARAMS(n, param) \
    BOOST_PP_COMMA_IF(n) \
    BOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   define AUX778076_APPLY_N_PARTIAL_SPEC_PARAMS(n, param, def) \
    BOOST_PP_COMMA_IF(n) \
    BOOST_MPL_PP_PARTIAL_SPEC_PARAMS(n, param, def) \
    /**/
    
#   define AUX778076_APPLY_N_SPEC_PARAMS(n, param) \
    BOOST_MPL_PP_ENUM(BOOST_PP_INC(n), param) \
    /**/


#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/apply.hpp>))
#include BOOST_PP_ITERATE()

#   if !defined(BOOST_MPL_CFG_NO_APPLY_TEMPLATE)
// real C++ version is already taken care of
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

namespace aux {
// apply_count_args
#define AUX778076_COUNT_ARGS_PREFIX apply
#define AUX778076_COUNT_ARGS_DEFAULT na
#define AUX778076_COUNT_ARGS_ARITY BOOST_MPL_LIMIT_METAFUNCTION_ARITY
#include <boost/mpl/aux_/count_args.hpp>
}


template<
      typename F, AUX778076_APPLY_DEF_PARAMS(typename T, na)
    >
struct apply
    : aux::apply_chooser< 
          aux::apply_count_args< AUX778076_APPLY_PARAMS(T) >::value
        >::template result_< F, AUX778076_APPLY_PARAMS(T) >::type
{
};

#   endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#   endif // BOOST_MPL_CFG_NO_APPLY_TEMPLATE

#   undef AUX778076_APPLY_N_SPEC_PARAMS
#   undef AUX778076_APPLY_N_PARTIAL_SPEC_PARAMS
#   undef AUX778076_APPLY_N_COMMA_PARAMS
#   undef AUX778076_APPLY_N_PARAMS
#   undef AUX778076_APPLY_DEF_PARAMS
#   undef AUX778076_APPLY_PARAMS

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_APPLY_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1

#   define i_ BOOST_PP_FRAME_ITERATION(1)

template<
      typename F AUX778076_APPLY_N_COMMA_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply,i_)
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    : BOOST_PP_CAT(apply_wrap,i_)< 
          typename lambda<F>::type
        AUX778076_APPLY_N_COMMA_PARAMS(i_, T)
        >
{
#else
{
    typedef typename BOOST_PP_CAT(apply_wrap,i_)< 
          typename lambda<F>::type
        AUX778076_APPLY_N_COMMA_PARAMS(i_, T)
        >::type type;
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          BOOST_PP_INC(i_)
        , BOOST_PP_CAT(apply,i_)
        , (F AUX778076_APPLY_N_COMMA_PARAMS(i_,T))
        )
};


#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
/// workaround for ETI bug
template<>
struct BOOST_PP_CAT(apply,i_)<AUX778076_APPLY_N_SPEC_PARAMS(i_, int)>
{
    typedef int type;
};
#endif

#   if !defined(BOOST_MPL_CFG_NO_APPLY_TEMPLATE)
#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#if i_ == BOOST_MPL_LIMIT_METAFUNCTION_ARITY
/// primary template (not a specialization!)
template<
      typename F AUX778076_APPLY_N_COMMA_PARAMS(i_, typename T)
    >
struct apply
    : BOOST_PP_CAT(apply,i_)< F AUX778076_APPLY_N_COMMA_PARAMS(i_, T) >
{
};
#else
template<
      typename F AUX778076_APPLY_N_COMMA_PARAMS(i_, typename T)
    >
struct apply< F AUX778076_APPLY_N_PARTIAL_SPEC_PARAMS(i_, T, na) >
    : BOOST_PP_CAT(apply,i_)< F AUX778076_APPLY_N_COMMA_PARAMS(i_, T) >
{
};
#endif

#   else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if !defined(BOOST_MPL_CFG_NO_APPLY_TEMPLATE)
namespace aux {

template<>
struct apply_chooser<i_>
{
    template<
          typename F, AUX778076_APPLY_PARAMS(typename T)
        >
    struct result_
    {
        typedef BOOST_PP_CAT(apply,i_)<
              F AUX778076_APPLY_N_COMMA_PARAMS(i_, T)
            > type;
    };
};

} // namespace aux
#endif

#   endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#   endif // BOOST_MPL_CFG_NO_APPLY_TEMPLATE

#   undef i_

#endif // BOOST_PP_ITERATION_DEPTH()
#endif // BOOST_PP_IS_ITERATING

/* apply.hpp
ceq2BZhZwMw5CFapWm8UMA2FGjwgrJzqXQnMJmC2HACrVK13PmALAVskrOwaPg2ARBLNOyl8nK33wDS0cGCaREV2JfcBsAyA5YqJo/W2ApMFjIcxdbzJSq/rgh54q5VTuQMh7aA7QbeCbgPdDLoFdCPoJtD1oBtAbwK9BXQt6I2gq0BzvUTYaN5bHS3j8Ohalo59XE7dOoSsAV0COgx6NegVoItALwO9HHQh6KWgF4JeBHou6AWgZ4Gew9KDbXQ8QWtZDsdmpzo6k2Oj0xGSBzoftB90LmgvaB/oLNAe0C7QGaBpjCKaxiiih0DHQWugB7kNBKoiwZrquhiH1/Wi2fRzbGUfQrpB94DuAr0DdDvoTtCtoNtAN4NuAd0Iugl0PegG0JtAb2HpobJIoKI6Wsvh0SqWTttb1kwNQspAV4BeC3od6DWgS0CHQa8GvQJ0EehloJeDLgS9FPRC0ItYenAHHTTRdfvQySw4LC+AZuYg5HzQM0EXgJ4OOg90Pmg/6FzQXtA+0FmgPaBdoDNAJ5JMc7eiA70InRTUDSVZJxr6SJxjKwcREgPdD7oXdB/obtA9oLtA7wDdDroTdCvoNtDNoFtAN4JuQo/DYZXc2Bit59joJvTBBsbUbUFILeiNoKtA14AuA10Bei3odaDXgC4BHQa9GvQK0EWglzGNMcF+nFXIsbQv5vwshZYWIWQu6AWgZ4GeA/p80DNBF4CeDjoPdD5oP+hc0F7QPtBZoHnMwUXdlJPVOIhyQUsJDOkZ0FVyP4cM7Wc6DloDPQg6BrofdC/oPtDdoHtAd4HeAboddCfoVtBtmERWoC6KYIjqUadlvTgtmwkVzYKKZiKTs+S07Joz+bSsLYePNmUEmWk5LZtlOS3r4dOyXj4twzgX3KEkdEPCHEiYCwlzIGGuSMiAhJYcPmRroaM2RBsS5lok7GAJ3SSBD3fpGrw2dW7bDgkeSPBCgof/gqYz3G+fwRKqckI1PA6FaiRaP8aNMkid5LaxhHaSwMe99D5Ai5LQCgkZkJAFCRmQkCUS5rIEOm1FG4WWrYe0GRZpWRZpLSytlaW10OFydbBKaawG0pKYrl1gQTQ3HNHYc/lcnrKcUEUkgMNlRCuNuSwaq2IJNSyhim7Zl4uhdSHIG+TEISeB6TDOf4mGnGKWQye86G0olbUnxS0yKYGSiR5PYtHnSbJ1BAiWKX1WQPIgJA9BMtPVREOfQ1O5hDty+IAeoyeilQ4ZpHRYxiWsIDkyxqOv60KQT8jphxwNcvohRxM5VSyH+ibGEOTTejDdb5GpmTLr1uglLNFLCK3g6fBb/XFTX2erj4YtdbhalbAPJYyhhExXEw0595/OJVwxgpER+VQH4wI1ZcYsdRjWS7haLyG0gifcLW9ouEjJ94NpLpj6Uc5c6Rlnnm64opzHWQn05LBHQA/5BQBpKJjxSsErdPFFEP/6Bq6HT3t9A5d5zN/jPOZvcxzzVzmP+cucx/w7nMf8LY5jfowTjpN+tGHHYT9q3XHeD7UIv8N1qTr6O/o7+jv6O/o7+vu3/9jfoQvffz8lPuJwd4Cd3OHxAEuk3ekBBiaH3wOO0x2uD1E+yHR4P+A83+EAgUMkhw8EFl8ONwis4+yeEFh0KAM/ffR5Pn1DghY5l54cH9E9bZF/S9R5iILTJ8phifIhCv60lYX2qL1+wzm5cpE96nd+wze5cqE96qeIEhfNBfaoRr/hoFw51x4VRZS4Xc6xR93gN9yTK2fZoz7uN7ySA82ZWBgGW8p3ushlJRI0nZJz/cZK8Ay/wyk51Dh1EpaBgaapmVgDBpunbafl0qndkaBwHtI5x8G5PhI0fZKfPsnhkxyqV+waFLs=
*/