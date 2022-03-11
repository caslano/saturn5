
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