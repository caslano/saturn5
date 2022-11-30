
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
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
*/