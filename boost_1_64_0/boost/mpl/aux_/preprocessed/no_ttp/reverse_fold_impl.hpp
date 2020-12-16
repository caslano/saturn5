
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
fllp/TaLkjYEd0kalm2o7BO29qHmpOx6tPMgLZf7hXqfPC/pr5DtsoTQV9kvbOnnmAxZScnWtL3dSFvz95mq7UJRA/Qr8d/eT0Rd2zpo9wfhqr+JW9cfxGpLOR/66d6X331j0bUVrU7p+zX7dlLd21h0WGRpq9Fi/Qtz2hs/u/Oxgg8uJn233nU/EdptU25t/xFBOrkOAz3B5zbXdfWtnOrqAySer0a8O+Vd8t6oxxZofU49XOLNVPLl9Jx6mtR5Z2JrNKEfZmEImnE45uB9uBhTcSnm4DLcjCvwYVyNT+Ba6XdgPb6OG/Ay5uIfcCN+g5vwbvK1GTthHvbHfAzDLTgNt9rLQa6vWGeNcmgv5dABvdBfyiFSJ9dK0Evi3YFhEu/PUu5foBdWoh6/xPb4F+yBX0k+YglBsrxQWV4zjJLlnZHlvSDLe1GW95Is76ws72Xsh6/gEDynaqOzVpbfUZavbqPjJ8tvh97YHn2xA3ZAf3t5yTUJcTTK66Asp0jiP2qPx/WE63K+KvHKZP0+VbcJknh3a8QLlngh2AIHS7zejeT3Pzwu+2lXy/aTa0yZfxh2wXuxF4ZhGI7AMRiOk3AUxuJoTMAxuBgjMB/HYiFG4j68H4/jRCzGKDyLk/B9nIwfYTRexan4KU7DSpyOf8UYvIs8z8C2OBMDcRYOwDgcgQ/gTDRgLCbgcpyPO9CI+zAJD2EKHsFU2/4n1yOYpLH/PSXlVYy++FPsiz/DYHwaR+IzOBaflXJ6TtXGp0iWP1uWr27j841sx79jK7wu6XyH/vhP7Ic6jr8QuA2HY2OcgE1wGjbFWdhMjtM9OrmuwAOSrg8WSLq/kHTfxC5YIsfR25LeL3E4XsQx+C5OwPcwFi/Jev4KF+AHuBgv4xr8GDfiFfwhfoL7sVS9f0v+Wmjs360lf3q8E9uoz1sSz18j3l6Jtw/b4371eT/O9fdFGznf+WIrbIvWNjDhEq+1xFO3gSmX9P6I3vgZtsTPVds/XuIv0tj+nWX/6oG+2BM7Yy8cgH1wBPbF8RiI0dgfZ+MATMF7MB2D1OUk6QZorO/jku/j2AmfUJeTtKW8SyOej5RTS/TGVqrvhXCJt0Lje2G7rOcPsD/uxIH4ED6AD+MS/CHuJ4ELhe69d9Hal8KxWvtT+H76Ugit2Z9Cg/Wj4Nx/guu+E9zrN8Fvusb7LLT7TWiwPhP+W/tKaKh+EsoLvTjgvHQBhFBCLMFMKCScJFwiVBKa7fTSdSdEEOIJKwlFhLOEK4RrBP0u2pQRInd52pR5Bs/gGTyDZ2iw+n9qU26+/t+X+v8hwVwDdVB+07LUTNInz0q9/2uqfgH8Gzk9wy71nqXTrfddp5D36dOj3Ljnq76ffEaW21mW25HQX7lnbV2u+hFKN5Yt93Tt/VbL/eRHutrqpaTOQ1VPxD31ZjGkx7ScYMd6oN1SD1+ok37wJX8BMRr546E7ozGJyxj32wbULZ/2/rZJyeF+ddbi6vUYrVoPZXyrjGd2dSx3H6lfbyvl3obQV9me1vWSxxLr+uyqukwrY+z1FOo+uv2louQFqaM9jUqZhk+1pK0q0Bu/W0Kpn708zVo/W/9yVcrx/a72vs8r1f2aS7mndaNeJjODydIPufR1rlTVtFf1HZ+YkpS4kEqI7Jw0RqXf9+o86hYHO/bRXSFl0UO2QzdCEPOYqvd/Dkj7U8j1qU9R14FmWetApTwSZFxvLR8Z95PxdBn3RykbS1kEMG4pC4MyxXHbxkidfjtZn7ayX521rY/lCeJ61dlZ6roknVMu0imypUMy5vqlYV2X61JXP0v6rZyOShrRky1p1HiOuPsN9tPIaKf91GkfrFTtg50YL5M=
*/