
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