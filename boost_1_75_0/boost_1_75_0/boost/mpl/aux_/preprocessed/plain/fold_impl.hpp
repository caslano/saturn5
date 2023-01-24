
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
JTAeStA4KYuirDYC8pUZCHEZY6WIdHT7wvqInR6ZoOOugEXofuo5aCal3wjZQls/EAblftZPfq1Yo/2GzwSH/oyhJfCEzUdgO00pMdVdt8AhRZiCKCoXojIXyTTff8Q1N+/Gl3CUKiU3hya2rZLLPrXU0cLu7Oa02x3u18WCzZK3MTjV/XU2G14VlKIS3Sj15ZhPCxwfrpDVL3GsfMdvsKbOAu+z7JyIMi1teyVIRnZC7sk1t8gb6PuFLJ6cx/1dXFypk+jIiHhY2zElpcrPPlqoSMBh5PndRsF61/q0d34LOYrAVG1JdTeJ87b17xidZh/cxrhBgfHWbdM+UFU5O7LVjRbz9tz8PKUyfXihWWcyyaiBuLL8YtV2toqvdsv2jcSZaN+22zztCVVk3GARe9Gc6fikT7pcvf63OTxhh/4DWlyt1QXr34GBogkqzVAeMx3Betwmo04PX1vL9cy0uD99A3dmjq29Lqt8dnojod/4jHFdgaWyO9iLIGyck/lf1pvpNuLrY/xmszIUQgaaHq7Vo+pZg6UatqxR4pqa7yi6N367vGR5fbl3X8CllhcYen0fYcb1FCOOPdtxoFFu11XEWahcBPBuzRvrDY77vgtviD5oOsyY2PiF5ddFP0si4ST/2dMX+WkqrzwlLq68VxbkBMXx8sjJUIT4TTUgAT3JJkstcqYFK0Xq3IZNdzomQQvHpBzunNm9iVGk
*/