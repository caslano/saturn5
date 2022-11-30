
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