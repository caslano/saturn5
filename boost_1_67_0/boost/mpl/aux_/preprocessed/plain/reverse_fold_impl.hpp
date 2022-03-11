
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