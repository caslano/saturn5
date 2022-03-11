
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