
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