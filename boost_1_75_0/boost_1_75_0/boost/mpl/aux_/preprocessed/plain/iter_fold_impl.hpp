
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/iter_fold_impl.hpp" header
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
struct iter_fold_impl;

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 0,First,Last,State,ForwardOp >
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
struct iter_fold_impl< 1,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
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
struct iter_fold_impl< 2,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
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
struct iter_fold_impl< 3,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,state2,iter2 >::type state3;
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
struct iter_fold_impl< 4,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,state2,iter2 >::type state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp,state3,iter3 >::type state4;
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
struct iter_fold_impl
{
    typedef iter_fold_impl<
          4
        , First
        , Last
        , State
        , ForwardOp
        > chunk_;

    typedef iter_fold_impl<
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
struct iter_fold_impl< -1,First,Last,State,ForwardOp >
    : iter_fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , ForwardOp
        >
{
};

template<
      typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< -1,Last,Last,State,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* iter_fold_impl.hpp
djgJgttxUvktrl9TFbDbECgWHHIqMTX/ZA+j0SRg2INdpyvQ64MfAh7j5SBI3DH6sWRDNJ0Paan/xHIlE9JaCp0860H5JqtSRMAjTF6QASsiMfqZ8Pdqfl6d/q9QGx6i/QWhHOpFDe2IK4L69j4l3+g/6BUB1D6h/D+8ID8sJOdk2cleHQXDiGXqcPF18z/K0V/lvb1n+3SWLGzFweH0iseWA4rTCXRzerKFPASN/LFXJipk71a6f0z7jODZQh692ly7i2mZ92oJGH3GXOihWsqYDbg+QHnJdUIU+4IqSkxCbI8gsBix++uuA6Ohdy8On+BWyrEBvx6v3dXjEIrdFpQVwrze53dVt5/tA353dL5ntBQP6Na+8nOtf178a//ZNgWBDPXflEWIBpiuRdqW5AY0xAJgmyAmZ+NJRddieA++DhpYaefNVxAp5GMb9BoeQPxPnfYE0iRaNhoYHazsOsmGyorM+ro9UD7Qo7eotyHosLQ7Bc94VYI58BBZGxmCwvNKmzGD05T5aCE+b13m2V68kfTodTOK8Fe2KWmE78sfMb/epTIoNtnq76663G3OW5NWp8Op3G1sdHOUDzl4x3Xjv0pJcZpgFyW8FCfcPpYdRFRclUdTY6xd/aexd+hYDTWAFapYvYMNnbmIUy4cKUEsYbKGmPPoSqM+DnE/Ks5CfXFD4JfwDfTXfR9oCc8cWx7NUIbf5BtcpmwY
*/