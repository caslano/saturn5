
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/fold_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

/// forward declaration

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl;

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 0,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef state0 state;
    typedef iter0 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 1,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    

    typedef state1 state;
    typedef iter1 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 2,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, state1, typename deref<iter1>::type >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    

    typedef state2 state;
    typedef iter2 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 3,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, state1, typename deref<iter1>::type >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp, state2, typename deref<iter2>::type >::type state3;
    typedef typename mpl::next<iter2>::type iter3;
    

    typedef state3 state;
    typedef iter3 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 4,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, state1, typename deref<iter1>::type >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp, state2, typename deref<iter2>::type >::type state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp, state3, typename deref<iter3>::type >::type state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef state4 state;
    typedef iter4 iterator;
};

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl
{
    typedef fold_impl<
          4
        , First
        , Last
        , State
        , ForwardOp
        > chunk_;

    typedef fold_impl<
          ( (N - 4) < 0 ? 0 : N - 4 )
        , typename chunk_::iterator
        , Last
        , typename chunk_::state
        , ForwardOp
        > res_;

    typedef typename res_::state state;
    typedef typename res_::iterator iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< -1,First,Last,State,ForwardOp >
    : fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State, typename deref<First>::type>::type
        , ForwardOp
        >
{
};

template<
      typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< -1,Last,Last,State,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* fold_impl.hpp
a9EZR0Et7EMllbB9mQZmP47mRSf2h2jCrizpc06+8znTe1r1Qmp4IcpyFutKu6gI2UBdR4TRr67JyEUqIho0gzTfKSjxVWoB7TMXWMI4RjaZr1mlGZyiT3RymnN4bSPudJTDe3ftdjMa/Bc/aW4t6pYiWPQLZYNnpbEfwzlTcAZScdDKgbBYaNJXYP4w+1koyxAAZumZO7CfjmW1N2q1M3R20zsx2SNmebK07Fp6BD4nfU2i/d6uRKqhi9FE1E/9XODvNbWNchRiH2VKvLIxR6ZocZxRexlwyUzvK2g5yDc0bFxzK3aKFNG5Gydo7OrLbhiyR25dkOa1KdB2JCq3W2jTQQBru654p+oT1RU9+SB3qVfX0dCbFTsUmlpsKN2MqX1pEwMaVtIzYR6lllhrfFGa21JFuxEithxcRJDBlw6lSvnQfFLrSkYbPRNbMHPjqA/zB3zje1WJ55P8ajq9nMkRXhdy+0IAfinaKIlIxnCujYguZakf1i04Mea9mIS/rAJ7OzpNuWx7IJSAsuJcUsEzloC64vz8A5IAO5GQweboa6viQHeCLg31zBn1jCziivBtHy/DmMWxLkXMNEQi7F48KgEdGF9N0DMB3h7+5JbEeIAuUteaiHsUoGPUoT78HFqXIfQP2Eou4Atvmvtox/g9sHk5PeC2Pj86JaVgeQxWRLp1VxI88m9b77PyMFNo6fmi+CwggHQ3b0O0
*/