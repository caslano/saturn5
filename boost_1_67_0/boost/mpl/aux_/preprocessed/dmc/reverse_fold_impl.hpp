
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