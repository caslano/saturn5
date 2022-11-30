
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