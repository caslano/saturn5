
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#if !defined(BOOST_PP_IS_ITERATING)

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

#   include <boost/mpl/limits/unrolling.hpp>
#   include <boost/mpl/aux_/preprocessor/repeat.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>

#   include <boost/preprocessor/arithmetic/sub.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/dec.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

// local macros, #undef-ined at the end of the header

#   define AUX778076_ITER_FOLD_FORWARD_STEP(unused, n_, unused2) \
    typedef typename apply2< \
          ForwardOp \
        , BOOST_PP_CAT(fwd_state,n_) \
        , AUX778076_FOLD_IMPL_OP(BOOST_PP_CAT(iter,n_)) \
        >::type BOOST_PP_CAT(fwd_state,BOOST_PP_INC(n_)); \
    typedef typename mpl::next<BOOST_PP_CAT(iter,n_)>::type \
        BOOST_PP_CAT(iter,BOOST_PP_INC(n_)); \
    /**/

#   define AUX778076_ITER_FOLD_BACKWARD_STEP_FUNC(n_) \
    typedef typename apply2< \
          BackwardOp \
        , BOOST_PP_CAT(bkwd_state,n_) \
        , AUX778076_FOLD_IMPL_OP(BOOST_PP_CAT(iter,BOOST_PP_DEC(n_))) \
        >::type BOOST_PP_CAT(bkwd_state,BOOST_PP_DEC(n_)); \
    /**/

#   define AUX778076_ITER_FOLD_BACKWARD_STEP(unused, n_, j) \
    AUX778076_ITER_FOLD_BACKWARD_STEP_FUNC( \
          BOOST_PP_SUB_D(1,j,n_) \
        ) \
    /**/

#   define AUX778076_FIRST_BACKWARD_STATE_TYPEDEF(n_) \
    typedef typename nested_chunk::state BOOST_PP_CAT(bkwd_state,n_);
    /**/

#   define AUX778076_FOLD_IMPL_NAME \
    BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_impl) \
    /**/

#   define AUX778076_FOLD_CHUNK_NAME \
    BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_chunk) \
    /**/

namespace boost { namespace mpl { namespace aux {

/// forward declaration
template<
      BOOST_MPL_AUX_NTTP_DECL(long, N)
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME;

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_UNROLLING, <boost/mpl/aux_/reverse_fold_impl_body.hpp>))
#   include BOOST_PP_ITERATE()

// implementation for N that exceeds BOOST_MPL_LIMIT_UNROLLING
template<
      BOOST_MPL_AUX_NTTP_DECL(long, N)
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME
{
    typedef First iter0;
    typedef State fwd_state0;

    BOOST_MPL_PP_REPEAT(
          BOOST_MPL_LIMIT_UNROLLING
        , AUX778076_ITER_FOLD_FORWARD_STEP
        , unused
        )

    typedef AUX778076_FOLD_IMPL_NAME<
          ( (N - BOOST_MPL_LIMIT_UNROLLING) < 0 ? 0 : N - BOOST_MPL_LIMIT_UNROLLING )
        , BOOST_PP_CAT(iter,BOOST_MPL_LIMIT_UNROLLING)
        , Last
        , BOOST_PP_CAT(fwd_state,BOOST_MPL_LIMIT_UNROLLING)
        , BackwardOp
        , ForwardOp
        > nested_chunk;
        
    AUX778076_FIRST_BACKWARD_STATE_TYPEDEF(BOOST_MPL_LIMIT_UNROLLING)

    BOOST_MPL_PP_REPEAT(
          BOOST_MPL_LIMIT_UNROLLING
        , AUX778076_ITER_FOLD_BACKWARD_STEP
        , BOOST_MPL_LIMIT_UNROLLING
        )

    typedef bkwd_state0 state;
    typedef typename nested_chunk::iterator iterator;
};

// fallback implementation for sequences of unknown size
template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME<-1,First,Last,State,BackwardOp,ForwardOp>
{
    typedef AUX778076_FOLD_IMPL_NAME<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State,AUX778076_FOLD_IMPL_OP(First)>::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , AUX778076_FOLD_IMPL_OP(First)
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME<-1,Last,Last,State,BackwardOp,ForwardOp>
{
    typedef State state;
    typedef Last iterator;
};

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template< BOOST_MPL_AUX_NTTP_DECL(long, N) >
struct AUX778076_FOLD_CHUNK_NAME;

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_UNROLLING, <boost/mpl/aux_/reverse_fold_impl_body.hpp>))
#   include BOOST_PP_ITERATE()

// implementation for N that exceeds BOOST_MPL_LIMIT_UNROLLING
template< BOOST_MPL_AUX_NTTP_DECL(long, N) > 
struct AUX778076_FOLD_CHUNK_NAME
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        > 
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;

        BOOST_MPL_PP_REPEAT(
              BOOST_MPL_LIMIT_UNROLLING
            , AUX778076_ITER_FOLD_FORWARD_STEP
            , unused
            )

        typedef AUX778076_FOLD_IMPL_NAME<
              ( (N - BOOST_MPL_LIMIT_UNROLLING) < 0 ? 0 : N - BOOST_MPL_LIMIT_UNROLLING )
            , BOOST_PP_CAT(iter,BOOST_MPL_LIMIT_UNROLLING)
            , Last
            , BOOST_PP_CAT(fwd_state,BOOST_MPL_LIMIT_UNROLLING)
            , BackwardOp
            , ForwardOp
            > nested_chunk;
            
        AUX778076_FIRST_BACKWARD_STATE_TYPEDEF(BOOST_MPL_LIMIT_UNROLLING)

        BOOST_MPL_PP_REPEAT(
              BOOST_MPL_LIMIT_UNROLLING
            , AUX778076_ITER_FOLD_BACKWARD_STEP
            , BOOST_MPL_LIMIT_UNROLLING
            )

        typedef bkwd_state0 state;
        typedef typename nested_chunk::iterator iterator;
    };
};

// fallback implementation for sequences of unknown size
template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_step);

template<
      typename Last
    , typename State
    >
struct BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_null_step)
{
    typedef Last iterator;
    typedef State state;
};

template<> 
struct AUX778076_FOLD_CHUNK_NAME<-1>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        > 
    struct result_
    {
        typedef typename if_<
              typename is_same<First,Last>::type
            , BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_null_step)<Last,State>
            , BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_step)<First,Last,State,BackwardOp,ForwardOp>
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
    /// ETI workaround
    template<> struct result_<int,int,int,int,int>
    {
        typedef int state;
        typedef int iterator;
    };
#endif
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_step)
{
    typedef AUX778076_FOLD_CHUNK_NAME<-1>::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State,AUX778076_FOLD_IMPL_OP(First)>::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , AUX778076_FOLD_IMPL_OP(First)
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      BOOST_MPL_AUX_NTTP_DECL(long, N)
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME
    : AUX778076_FOLD_CHUNK_NAME<N>
        ::template result_<First,Last,State,BackwardOp,ForwardOp>
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}}

#   undef AUX778076_FIRST_BACKWARD_STATE_TYPEDEF
#   undef AUX778076_ITER_FOLD_BACKWARD_STEP
#   undef AUX778076_ITER_FOLD_BACKWARD_STEP_FUNC
#   undef AUX778076_ITER_FOLD_FORWARD_STEP

#undef AUX778076_FOLD_IMPL_OP
#undef AUX778076_FOLD_IMPL_NAME_PREFIX

///// iteration

#else

#   define n_ BOOST_PP_FRAME_ITERATION(1)

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct AUX778076_FOLD_IMPL_NAME<n_,First,Last,State,BackwardOp,ForwardOp>
{
    typedef First iter0;
    typedef State fwd_state0;

    BOOST_MPL_PP_REPEAT(
          n_
        , AUX778076_ITER_FOLD_FORWARD_STEP
        , unused
        )

    typedef BOOST_PP_CAT(fwd_state,n_) BOOST_PP_CAT(bkwd_state,n_);

    BOOST_MPL_PP_REPEAT(
          n_
        , AUX778076_ITER_FOLD_BACKWARD_STEP
        , n_
        )

    typedef bkwd_state0 state;
    typedef BOOST_PP_CAT(iter,n_) iterator;
};

#else

template<> struct AUX778076_FOLD_CHUNK_NAME<n_>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;

        BOOST_MPL_PP_REPEAT(
              n_
            , AUX778076_ITER_FOLD_FORWARD_STEP
            , unused
            )

        typedef BOOST_PP_CAT(fwd_state,n_) BOOST_PP_CAT(bkwd_state,n_);

        BOOST_MPL_PP_REPEAT(
              n_
            , AUX778076_ITER_FOLD_BACKWARD_STEP
            , n_
            )

        typedef bkwd_state0 state;
        typedef BOOST_PP_CAT(iter,n_) iterator;
    };

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
    /// ETI workaround
    template<> struct result_<int,int,int,int,int>
    {
        typedef int state;
        typedef int iterator;
    };
#endif
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#   undef n_

#endif // BOOST_PP_IS_ITERATING

/* reverse_fold_impl_body.hpp
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
*/