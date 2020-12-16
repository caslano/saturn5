
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
4qTSWkv9u1zyfPJs432j1b/SbGOe2StxDtNesjJyCjEpNTNndo610EsfNMs5/fpYI3/OdlLTIcbo9iZ8Vvb+y5G8ZSFvkFZcjiFv9h829uucn8PWWV7tG9Yo+O465EktR9Em9diRL/38qO3i2N2Sh51SJysNecD4WbK9lpdlknPV6dlvV+Z9PVTW1lER9WWV2NQ474/j7wLKrzLLZ3pRLpsT5s/mUE0v8zpyTo28Sh7y0/O0JAw2O8okhral5l5qpbIn3nRps6dIm105x2Ar1TKrkHrpVZvdKs/38jBrs0+ZtNlHXXkz/EaHKG22GGxrc5Mpk3XkVQt3S66cwSvtP0q1uWs0u7JGUmmHW0obPiWCNjzT9Vs93LHncbOae2RKm5Nn8F9WYaF9Y8Ecui7Z6Tn53uxpWlff6fZ1dGNjhdHGuQWZWdpo0hmxK7SF7F0lda+71L1qo122Wy0nq9Crutd07n+m7oXx3XGpWw6DvKmTWv2r1MafWmAknxfne1//pD475kVa8yxSBxU/VosfZ0t7k4G8Fa3ZaPBjIaWbnutlO1N5Gn7spvlxpuf2NESZpyzG6X4zDrW0G7VJ8nar/GZUm+QtZ3Z+VoHtFvMuf/MtvuevZt8lwIe+y3Tpu0jXRf/7fq7duG2Sz82Sz3KLm3zam2Ovn9NGzPM9ry2VvOZles6nrSylrdSMTCWSWpbl0qJsRVpImb5NWiXz3OVxTpa3v//nFJxe/hzPN6Emz0DhXuSZZyItDa1odffmyGDztjexQJ9neQfAT7jnPXx9zZ/YrjtTfG+w8Wz56taURYHJGevaggIf9gb9urXxXPmhIeZnupcVnLkz3R1532diyz/5UGFii/14e+/tIO9uz7fvK/pjWxl9nxzJs1mBbn/WUeOGj9dc77XuiZFGvz/bypjXyYQLKDTocrrdl7JOjNT7vSzYvd8HhRptmUr8KKMtNrf7Uv4TIz37fWOo8RyO7hgTp9fP1r64PTfXo2417YjWxrx9dh7+0aXtdLHHtB35Kg/W+7fQZJ/dXmLDBhMbLuaDpYYNRYXZPut3+HU6ny3WAl3eM8NkQY2060uRP2l9YLtea6H9ftIOs5iVmz7b4/Oot+2b+ls8KycrN1PChUr5a8pcbbixb6fFk3qmy89RyU8/8WMf5F3ixll1+cnJJ3JOpvd9eN0zmpIfK2aq90l2G3P9pXr9uXPnzimiOqXn5NafDd/x+dhZ7tdSmM9Pcr+2w3x+mLv5ZL7Px/J17Yj5PC3f55P5ukakvtbiuFvLssRWLnc/svnFd/447+TikL2hXZv8MNbtmifztU1u19a4X6tkvtbK3Tw53+cdDrLNnxvW4I8rZgw7MLXZ/QW3/zrpI7fz+XxfIyVrXRiTce1VvLrGWherzKsrgk3hfBgDF8DOcCEcCBfBS+Fi156jMr7CF5KuuudoN1lj0h2Gwh6wPYyFfWBP2A/2gmNgbzgR9oF5sC+8GvaDxbC/6K3QRPQyjoJe+2/C46L3EtE7SPReKnoHS77i4SB4GYyHCXA8HAonwOFwFhwB18CRcAscBbfDy+GTcDR8AY6FL8Lx8DWYCD+FE+A/4ET4K0yCZ2FvstN/MuYBl5v4b4rkY6rkY5rkY7r4L0X8NwOOg6kwGabBuTAdLoYz4RKYIXo1hRWi937x33n8/Z3oXdDArnchDIWLYBe4GMbCYjgSLoEZcCm0whJ4NVwOy+AK+BhcCQ/Aa+G78Dr4BVwFG2j64TlwDTwProX94PUwDq6DSfAGOAmuh7PgjTAb3gTz4M1wDbwFXg9vhTfD2+E9cCPcAWnz8AN6Eft4AWmL/1vCYvHDe+L/98X/H4j/P4TR8GM4BB4=
*/