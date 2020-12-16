
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
jqTNRAupt2iMxJbYBFthK2yLffFiqb92OAQvwQTsgBnYERdjJ7wDu2AhdsVHsTs+gT1wL8biG9gLD2JvPIT98Aheip9jHJ7Cy1D5PPXHMByE0TgY++AQ7IfDcASOwNE4Gq/BMZiFV2IejsPbMAkfwfG4ByficzjZPXaqPHeU55HxurFT98jn6O8Yic9jE3wBW+FL2A9fxnjci0PxFbwCX8VpuA/T8TXMxtcxF/fjTXgAb8E3cQW+hXfjQdyAh/BFfAdfxXfxNSzFN/EDfB+PYDl+iBGU5yOsix+7xk61yDNFbCzlraMctwSLzBPXAB/Ei3EtxuI6KU8hjsW/4SR8CGfjw7gYH8XluAk34uO4FTfjLtyKB/AJPI7bUNnfOzEcd0k+oy3y7A/rEBoS5FypLn097yMy+V579vfx3M2/+GL8fF+ivC+qgvfZzvK+Ppr3rXCne/b3FbnLe/b3FfsZ31E/82fZ5t/7oreZp9tC8754s/jkfeoF8aMwS/RHgfV5+Kv1dzjfvg7n2s+hNLaK330d9q4JPef+DoH2dTgRW+W/0t9hyEdhF6zPQ8zPF77Pw/Cfq/1X+j1MpF7OKHHgGsJewklCxMdhlj6EaYRlhCJCCeEMIfoo49cS0gjLCUWEEkI5IeJYmKUTYTghjVBAKCQ8SzhKCP2EvxMSCQ7CKsKzhOOE0E/5GyGRYPs02AcjuASX4PL/vfxZ7f9p3aF0ADiv9v9K2/3YKIu7LXFDuQ9tRKhCaCDtvMrWhmn79quNPZRS0DHf1e6rwnY4/vRhN/4NIfDfmgL9DSHQ35qMf7O6cH3bA/0t6K/Wh924j/kf37f9Z/W3ppA13WK3jT+WXnL1g90/viZtX+C/iZ29D7t8HuRzou/DHiV9wRtgKDbUzPldF5tiA2yGE6tYArpX+l/tH36u90z+3i+d673S/1vf8At9j/TfuD86M5jXgvciwSW4BJfgElyCS3D5E5c/6f4/K3P6+ff/V/r3P8ANSqTav9/VId/ZXc/qyMhNk/79vTTj/9GWROa8l751hFo0kom419O3Li0/25Y8PTPX4kd/RlefmNW6/ofhmB2hzvHt7sOxVnkPHd7cfbB0ffrTJU/TCRHkKVGfp3Rbhf0Oz5afRyM9c46fMegfqeR3ukH+lkn+Okv+LiHUJX8lnvyprc3Ptb5M6se9z+ZVkXZPkn4OIVLZZyu9xmRQmitPt+ZV3PfWJA/uvioz8nLzbfIaq7r+K566ozujI9/u6WOnxJ2nTlPs7J+ynHpzkPeOvD50paZ/ikFZteXtJJ0DL5Py9iXUp7yFuvJKd95zrnNXeSUeNc8LyW970o9W2ktq8lxulmddP/6xkudRhAbkucw7zzJpxrkfJ/7sI6UcMSGkTWjDeqP7Ki6H61jfIv3/Z0s5sgmNKMe0+9zlUB8g+jvWh3kZpC+yuwxIfq1ZmTnSX879mczM8Rx3SlxZBp+RNOmnP1TyPZDQRKl/Xb6d5zX/+3Kandem24zzLX3RtHUsZfGcb7T13VT61s+QfKcSminnvvu9830hzn3ppnnWn/9M69szLoLku648a44gNFfOiZ58qwMiyFXJeUEKYLyIB0hX2Ua/n9tLBfSQdLsRopX9rEs3R6mAAPq2rtcfo1KPGSl28iD9b1eRhlKXDb3ztFvyFCd56kfYwntiVql5Gu11UQ0gT4+bX1PV/FglP1t1+ZkS5ns9bUUdFejzw0EVyOf48Qt4TS2VPDaXOmtKaN1T2fGSR7mo+jPOi88+lP3V4AHj/TWxunHaMfq01RE4zj39Ybr0+0n6faSvfJG0J99MaKucYyV93QU92WrQZz7Ej33k7/XC2f8UQzzX71qaMSM=
*/