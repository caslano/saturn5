
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
gaIfacyFmjstC1g17LbOSHcheF3+Z7aTXDUI3KKtPtlYxg+Im7K0pdk9nUkBZpaX/5kD5L5ahnlab32asYqfEc9kTasF2PccdzPOUiGlUoCvkSBak7XXXtMXGVv5RRFk4j82LqRoGHTN086LieZb4CINrQT4Ij2sdCiUP9oXwX/qO52xb7biiq19LoLfwRBBzoJvDqYNsL+/An52MCrzn/karF8cHMgfrUX2QJyme+4W31sqpBAMU0lrMN9zdBUbCh3yu37EeB+rWQ2M6TNzjGXZIXBNF7g9sO7516hFrpLP1TdoaxYBPzdTH2405E/4LvGeTEBVuGStwzNaruL96Nd9XAPDIjJQrU8f0a0sVWullzHOYkZGCAk++a35npVo18Qp3+S+hT2Ba/g6LgKabRkdyBhYaw5msAMvA1aaLSeYLwFDv7MXOX3cWO+Or2FwDQy7yNtqe1oCqmiZNlq3jBB4YRniFVnTvI69O8FuBSZxxl2M/ZL/+UEkVi1Av6Xvs67YM78Ap97gTUQImO5Cc4BV275rb4ba7oC9U8hfz8rkElmnjqIWlO5h7X29D05GHv9CTIRXo1wo5HPqi1Yy1r+QUg7/HExGaJdRGW7pL0SwLIrYtLASGTg3tCPtRgPzX9j/3i10J91DE/SX9R76dnHanI76FOJWQzUa6CqjCmM+AjgzQl2k7gR7rkzb0on0MzqTvWCva2l4UtVYYQyRrcBVf7BjncCcF1aiMEzU5mhLtSfaed5RKGmF/XuaDS3cgc3kqXKDrOJ1wvkq7N/3OuOyoWTn31+S+pmazzHw/zCcDdzrUXwnhlukprqBP+NC4F8uFFYCQw11ONAvnN4DY0rWg1FN7pm2lWy1BYOban8Ml/ayrTgVnBrAtKwAz8orrNTB8Jzs1X/W6xjvGZvBS2bwr8FzE8BBfjNLAB8U/IT4z96BzAN+9zYqiWqitvBEnGgtPhX/rM8zoCszA88eGeKv7e/qeDqDZoCn7oEj8zn81lz4atusA9YvYAGRdrRt2W3s+64SHeLrpvusptZFG699rG03fjRCeST4RnVenzcxhznJzq/uHl/LhPhzkA4/bhUqwYbAPTYOUSIxtIZ/87Ja0FQS8q9/6h+0eh5c+sckRxJPQ9WyvcZenNcSDCnBP4N4RgwV6XRjppEGPZvxN/eQC1s0EcedXCdQe6Lchm4bNzFwzVEh/r6ZSr+ggSzic22knAY1cAJebwEz3GZ2S1tJCfHx5R19qX4YO/ApXMB2chzUXAAocU0M0TrXB+jT9HT9S302OPNu2c0ajBqcan9gZ9qfw2M/DG7/q53nnzE8F4bK4Goa3aSXNE/Dm7xntrSGWV9ap627VhRUwEx4nJvA1evhjIX4/tDH2LPN9T56qp5s7DZQtXiICBPRorn4WTwRT+Uweyr88w/cpe5yX1nFBLyc3flr0lAdjJ04hD3UXmixugl/+iYPBdKGmr+aGpjU3sBcHMX8YzipSr134NkuhPj7nNCT4GVdjPeNAvyuaGUqeflztsRcD3+7pFXPamE9BBoPtTfgrGlAqwp4ylBluF9HjpA2bApbzHbA6XvMGHbGR9qPUNCRuqrH6+/oa/R7el045v2NqVirs9CoLfhEOCJb+Gl+nzcCH/0QbPRmgOuAb72NPAOOiM+gJ5uLoEcem0pkqO87lNDqA+X7YOct0rZrJ3AFpvfVJ+hp0ICHwCmLG3WMflAOQWC/lHeC3pnN14OvFxJ1RBfxGtj6CrEbc/kCecLL4HBKdKi/TjPASLbAB7mnlqQUiDEdOvs0vUdDWG3WhL3K3mZL4R89ZQoJVQbj8y3gFi3gm/kpfo83FB3EInEUaFtMxsIffks=
*/