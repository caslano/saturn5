
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
MmsQJ9r4uM1TNdavNUSMWwBey0UKqi/Bi9sdjB1xuxXUFDs+j4onv/piS4sgpdkZvr9V2i/3Z0Bm6P5zVhP0ND1hgrkNfBxU22mIf6qUr37KJ9/r1g3Q5S0AohCOG76siuTeIHi7XXYQzb9nmRF/G4yPoH2R1fqvieF/BDsb91/2oq7OLva2bCKuLi72dv8AO4m1Q3qv41ntjmbGBi39WSiMViGjJzz/LvxS6SpCBEbb0/eRtjh3AWTzrcbkqvMb48meyNKUMH53rMKyMI0F/q9XM++wElWyXUIU0qbSko0+TecA8tmfVQ3o8hMbmr3c1xm04wiGv5KnbtrdtDze3Ljd3tzYnQEPYvxSX4b493afcWqm6D8FKKrsKMX7G7/zKEHOe3MGyVNhJM98YPPJmerHwBpbluOJoWe2HJN9O/Rm6C3TmwIqNWo58dQQh7S8cbnZsBY+9Jfhq3t5L6owHmQzB2Gk4TeRJvaontPMX4mts55gySUy0X467C0AS7znvWd1+2CQSa/WvBl2BibvR6zA1Da9G84ZGIbVe1gqxl0VxQCNH90n45uM8P1WbKM06kPO8XmuW1ttc/sbOe+RtOJ37yWsA+YGxHYohb4Gsvg5P6JKll5mWE9dYFP4YXef9N1x2VO43WfO24IHmuzecRb9Cnqiw/jFKOv76DlfMzhoXkcUpyivJkCnUTCMqHAO9sp8xn3kMU/w2Uz2
*/