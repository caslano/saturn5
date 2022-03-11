
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/reverse_iter_fold_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

/// forward declaration

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl;

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 0,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef fwd_state0 bkwd_state0;
    typedef bkwd_state0 state;
    typedef iter0 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    

    typedef fwd_state1 bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    typedef bkwd_state0 state;
    typedef iter1 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 2,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    

    typedef fwd_state2 bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef iter2 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 3,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    

    typedef fwd_state3 bkwd_state3;
    typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef iter3 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 4,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp,fwd_state3,iter3 >::type fwd_state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef fwd_state4 bkwd_state4;
    typedef typename apply2< BackwardOp,bkwd_state4,iter3 >::type bkwd_state3;
    typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef iter4 iterator;
};

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp,fwd_state3,iter3 >::type fwd_state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef reverse_iter_fold_impl<
          ( (N - 4) < 0 ? 0 : N - 4 )
        , iter4
        , Last
        , fwd_state4
        , BackwardOp
        , ForwardOp
        > nested_chunk;

    typedef typename nested_chunk::state bkwd_state4;
    typedef typename apply2< BackwardOp,bkwd_state4,iter3 >::type bkwd_state3;
    typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef typename nested_chunk::iterator iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< -1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef reverse_iter_fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , First
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< -1,Last,Last,State,BackwardOp,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* reverse_iter_fold_impl.hpp
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
*/