
#ifndef BOOST_MPL_AUX_ITER_FOLD_IF_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ITER_FOLD_IF_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
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
#   include <boost/mpl/identity.hpp>
#   include <boost/mpl/next.hpp>
#   include <boost/mpl/if.hpp>
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/aux_/value_wknd.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER iter_fold_if_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/unrolling.hpp>
#   include <boost/preprocessor/arithmetic/sub.hpp>
#   include <boost/preprocessor/repeat.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/dec.hpp>
#   include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename Iterator, typename State >
struct iter_fold_if_null_step
{
    typedef State state;
    typedef Iterator iterator;
};

template< bool >
struct iter_fold_if_step_impl
{
    template<
          typename Iterator
        , typename State
        , typename StateOp
        , typename IteratorOp
        >
    struct result_
    {
        typedef typename apply2<StateOp,State,Iterator>::type state;
        typedef typename IteratorOp::type iterator;
    };
};

template<>
struct iter_fold_if_step_impl<false>
{
    template<
          typename Iterator
        , typename State
        , typename StateOp
        , typename IteratorOp
        >
    struct result_
    {
        typedef State state;
        typedef Iterator iterator;
    };
};

// agurt, 25/jun/02: MSVC 6.5 workaround, had to get rid of inheritance 
// here and in 'iter_fold_if_backward_step', because sometimes it interfered 
// with the "early template instantiation bug" in _really_ ugly ways
template<
      typename Iterator
    , typename State
    , typename ForwardOp
    , typename Predicate
    >
struct iter_fold_if_forward_step
{
    typedef typename apply2<Predicate,State,Iterator>::type not_last;
    typedef typename iter_fold_if_step_impl<
          BOOST_MPL_AUX_MSVC_VALUE_WKND(not_last)::value
        >::template result_< Iterator,State,ForwardOp,mpl::next<Iterator> > impl_;

    typedef typename impl_::state state;
    typedef typename impl_::iterator iterator;
};

template<
      typename Iterator
    , typename State
    , typename BackwardOp
    , typename Predicate
    >
struct iter_fold_if_backward_step
{
    typedef typename apply2<Predicate,State,Iterator>::type not_last;
    typedef typename iter_fold_if_step_impl<
          BOOST_MPL_AUX_MSVC_VALUE_WKND(not_last)::value
        >::template result_< Iterator,State,BackwardOp,identity<Iterator> > impl_;

    typedef typename impl_::state state;
    typedef typename impl_::iterator iterator;
};


// local macros, #undef-ined at the end of the header

#   define AUX_ITER_FOLD_FORWARD_STEP(unused, i, unused2) \
    typedef iter_fold_if_forward_step< \
          typename BOOST_PP_CAT(forward_step,i)::iterator \
        , typename BOOST_PP_CAT(forward_step,i)::state \
        , ForwardOp \
        , ForwardPredicate \
        > BOOST_PP_CAT(forward_step, BOOST_PP_INC(i)); \
    /**/

#   define AUX_ITER_FOLD_BACKWARD_STEP_FUNC(i) \
    typedef iter_fold_if_backward_step< \
          typename BOOST_PP_CAT(forward_step,BOOST_PP_DEC(i))::iterator \
        , typename BOOST_PP_CAT(backward_step,i)::state \
        , BackwardOp \
        , BackwardPredicate \
        > BOOST_PP_CAT(backward_step,BOOST_PP_DEC(i)); \
    /**/

#   define AUX_ITER_FOLD_BACKWARD_STEP(unused, i, unused2) \
    AUX_ITER_FOLD_BACKWARD_STEP_FUNC( \
        BOOST_PP_SUB_D(1,BOOST_MPL_LIMIT_UNROLLING,i) \
        ) \
    /**/

#   define AUX_LAST_FORWARD_STEP \
    BOOST_PP_CAT(forward_step, BOOST_MPL_LIMIT_UNROLLING) \
    /**/

#   define AUX_LAST_BACKWARD_STEP \
    BOOST_PP_CAT(backward_step, BOOST_MPL_LIMIT_UNROLLING) \
    /**/

template<
      typename Iterator
    , typename State
    , typename ForwardOp
    , typename ForwardPredicate
    , typename BackwardOp
    , typename BackwardPredicate
    >
struct iter_fold_if_impl
{
 private:
    typedef iter_fold_if_null_step<Iterator,State> forward_step0;
    BOOST_PP_REPEAT(
          BOOST_MPL_LIMIT_UNROLLING
        , AUX_ITER_FOLD_FORWARD_STEP
        , unused
        )
    
    typedef typename if_<
          typename AUX_LAST_FORWARD_STEP::not_last
        , iter_fold_if_impl<
              typename AUX_LAST_FORWARD_STEP::iterator
            , typename AUX_LAST_FORWARD_STEP::state
            , ForwardOp
            , ForwardPredicate
            , BackwardOp
            , BackwardPredicate
            >
        , iter_fold_if_null_step<
              typename AUX_LAST_FORWARD_STEP::iterator
            , typename AUX_LAST_FORWARD_STEP::state
            >
        >::type AUX_LAST_BACKWARD_STEP;

    BOOST_PP_REPEAT(
          BOOST_MPL_LIMIT_UNROLLING
        , AUX_ITER_FOLD_BACKWARD_STEP
        , unused
        )

 public:
    typedef typename backward_step0::state state;
    typedef typename AUX_LAST_BACKWARD_STEP::iterator iterator;
};

#   undef AUX_LAST_BACKWARD_STEP
#   undef AUX_LAST_FORWARD_STEP
#   undef AUX_ITER_FOLD_BACKWARD_STEP
#   undef AUX_ITER_FOLD_BACKWARD_STEP_FUNC
#   undef AUX_ITER_FOLD_FORWARD_STEP

}}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_ITER_FOLD_IF_IMPL_HPP_INCLUDED

/* iter_fold_if_impl.hpp
wJLgDkHkA7AwDrsVY+nKgQ1E+TE4Bo9HHpEPisfgdDQeDM7EYWVEDgAL4fBePH5ZRCYoDwZfBbhHCa4MjR+DK3FYBuxDHCZBTT5B+TG4CccT4a8FxWPwVzwtKsCEEgwWAlgCh4UBVsRhCsDDAUaV8QAeDbAQDv+7jK2Hh1uP62DjjuJgZYDAvTrg4O43qceFtUZfB3ssrIeLPaFnaQFfUgEsChP4liVRPOA4sAcEAuvgy7UOAssi4ENdDtbP3WWyA7zsu3EwGA7Np81YxPbyQr/04Xq+207yRCyHPtnFxwVWufj9KK8n4HxtOFReHMC+4wwRy6H6Org5+DpM5fid0GXWGE7yUFa0LKjIXOwAw4E5YXwcvPxA4QGiR2GwvgSHqZ6IdXOxc/FFywhlAMvxg8ymeNt4EvAwXDAHD/LrhR09vCf1uDa+A1mjxxZ+uXd4YdSzBAfWyexcXMB1dpiKpOHm4gMRgrGD2QMw4M9XgMDYu3gPMC3+7QBI77oyDRlPZ4BNBXg5WGRMXQL+rQCfAFsElgn+6+BWgq0H+x5sO1iknyN9Gun7bmCZYCk3wIKLjKM7wCqC3wD82uA2gd8U3OHg19Q1NGX9lf7i4GGHlJ3O1UzQdsyNwfoE3d7Bx87bxdPXw7sn7FRfB293G7S/eTtgrgWy6kM3NLTC2y8nll7aGKte2JgLHgswtGF7Bw+uhoj2M6h8Z652hvdFzM8JbzQeCY9MO8zoMMbCFAN3k+n+sBFEnwk+lM7G/eBD91tiuP1oXOBF4rK1sad7O9j5efu4eLhD8T19ncU4ckPXHSLjOG9DOEVzbEyIGbghlpq6sAEVEWMJWg90+DUGhwBGAC0yLozeQ8OnojDdCUdXIJFZGqxMACMkgBszJGNYpfT6OQMe+DWTCP7QqOn2fpM8Z0JuwKDb6GB0wRoY4GG4BkXUzzcgmvkTCIhUtPEJjQ5hYP0tIJZ3F1EXMbYOTi7udE0W6hHrxTu42/Niod9FBKELh7EhYxFY12jsOAwP8BhTYw481tAIhcPjoaeOMTY01B1vzDX/wvjQvDBNYvG6jmQEIQsE+qm6yOqlCYgDDB+NmyIJmUKWL3Unw2wUiGZ0KLEm1qPssJcXXV+YVpn1vurow9wQpne9u54w341nx8NqtuVQTRZn4jiUwwAvAgyYRVoOBXioOedNyXKoLhhNFgTS5HRhX2TODv/QJnz0kYzRsdR6JrvcvLqo6cWAmDmYvvnnyhqeMzqyNmo5tEeEkBG+cicGxbFg1VHXAe8DZvTgIFboOGOMj4fXPpLFjGdFslERBrHZQYyIWMD3yiAMNN36pgcx8ee9N/+hccmhMdAUQ3TxV1gwmDR0E0MZoZFMdi+Om4kB2nUsXWwXHhsTYpmJID5unp5MzObNG9SGYNkBOy424Ed9umwgWWqyMCydK/wAZQiMvQbxMPAwPdN4/haH4Div2f20d04dC2j3AjnAsNEyCo4PKWn/fQilCugryHKzPqzLRcZJikEPw00vtqf9DnS8iefRiwBfAGeVeMBjFrIrwfvgRjDcEcGrOaKzBpaF7qWGxQSFs8CNi0cx4GJv+aOx1R2YOOBrwACh1T/QvCCbtVxZGUSCOUqZMq1NhETzlCDRcsFWgqVLkmiBNBKNIEOinQDLqQeIZ0DlDo7EtvU4aQnSPYXtZF0r2F6ALkC3sOR4Ec29P9HpQNKKgzffP9GvQDbmmKBC+CfpoGGSIIxgc+QevKPIEziyooA9ATgdCwKNiL8/TQU/CaeLgD0Nfv54YEGJALuxqKx7tm4HlL/QZCafzAXq280QG0BcYX31Mg0GkocwfB/3T+oCNin/uC4gjIC6AJn/dVNUgdU=
*/