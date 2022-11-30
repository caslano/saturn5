
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