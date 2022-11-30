
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/reverse_fold_impl.hpp" header
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
struct reverse_fold_impl;

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_fold_impl< 0,First,Last,State,BackwardOp,ForwardOp >
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
struct reverse_fold_impl< 1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    

    typedef fwd_state1 bkwd_state1;
    typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
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
struct reverse_fold_impl< 2,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    

    typedef fwd_state2 bkwd_state2;
    typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
    typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
    

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
struct reverse_fold_impl< 3,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    

    typedef fwd_state3 bkwd_state3;
    typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
    typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
    typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
    

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
struct reverse_fold_impl< 4,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp, fwd_state3, typename deref<iter3>::type >::type fwd_state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef fwd_state4 bkwd_state4;
    typedef typename apply2< BackwardOp, bkwd_state4, typename deref<iter3>::type >::type bkwd_state3;
    typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
    typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
    typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
    

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
struct reverse_fold_impl
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp, fwd_state3, typename deref<iter3>::type >::type fwd_state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef reverse_fold_impl<
          ( (N - 4) < 0 ? 0 : N - 4 )
        , iter4
        , Last
        , fwd_state4
        , BackwardOp
        , ForwardOp
        > nested_chunk;

    typedef typename nested_chunk::state bkwd_state4;
    typedef typename apply2< BackwardOp, bkwd_state4, typename deref<iter3>::type >::type bkwd_state3;
    typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
    typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
    typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
    

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
struct reverse_fold_impl< -1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef reverse_fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State, typename deref<First>::type>::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , typename deref<First>::type
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_fold_impl< -1,Last,Last,State,BackwardOp,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* reverse_fold_impl.hpp
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
*/