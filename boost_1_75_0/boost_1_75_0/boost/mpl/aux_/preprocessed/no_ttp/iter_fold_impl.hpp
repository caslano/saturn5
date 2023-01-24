
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
aUPlWmFHfN7uypDnwrxWOaQtOMa2Gi/ExPIn0+YjXy9vmrrlxhFsiNfbLpMr3SE2lMvsO9ptSu3VYilbZQW5d8WEiBablPBKWenZT0oN72gZ+n2lZ5NpFdcevXfR244vNTBHdHe45+zFE2o+f2JL/0XPL/+DJaRnoT7j8LOUTC1AqBuvlFsF3p31rigxWr7sLxDO+OrogZcfk3HfNdOEFxu9juL7VH6oLLrCmuqvFOJgzQQWTBqNGCFuGqRqMJp4X4f1+kcaOqnZuGtszGPIY4iqz5uB0xFsrNOG/BD9Bn1eoqbzV8UyUx1yohqqhc5Ja+6qzdRln71w9t4U13zLOLmm14h/lvB1+oli0sDRFE+SDNQGH/L1INKOnFsyLNL+EtcwpOdhOoNCt5GJL7T3i6hMleu1anvA03iLFOGiCeeb6BMU3R9lOwYNKHU1JKoDAbKZJGvAuKjnpekVB6sN0ZFyPY43IVy0nOBE3/QJHT5wum/8hLtlfgWM0jbZfg8yUL2uqpgMRB6X549pUHMWk6jSAnpp2lXlBs+owKAC7Y/It5XiWZFK65i59J60l2yV4iF2Redo2WHRT+tyg0jxsE7hXp2f/t975NYJ17hTH3fl1plz/3Ksvv2p6JzEeLArDREVOcYO7nksHeHknu9c28HzwCQMm6wN4SHYCGL/cLwRfIHpdff7E3DzNOpDV4DsnO31XegTlVz2MZm9
*/