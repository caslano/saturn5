
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