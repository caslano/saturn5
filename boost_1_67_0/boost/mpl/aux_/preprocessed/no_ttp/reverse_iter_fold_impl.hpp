
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