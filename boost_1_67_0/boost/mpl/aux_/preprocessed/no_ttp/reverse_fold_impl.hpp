
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