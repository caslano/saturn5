
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