
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
1sO38Cb8DOvjd9hAtmtD/AMbYzXy3ATrYQQ2xluwKd7qOn7kuzqa/Bw/t8r2aS7HTwusii2xNrbCBtgau2Ab7IHtMBrbu64L8t0advm5LpyU9XkaK+MZWY9nsTX+il0wB414DuPwPKbhHzgNL+Ay/BOfwELSprcwvo1BuAODUcov3605RvyUP17ylYAVcDTWxTHYAJMxElMwCq04EW04H+3uvj34Lh1YXyHZMl2JPKY7z4jsYYG3vawz7d/xnIu7nWXg7Ssv9XmXPNpW/mPtKg3DixvCiA7EIMJOzCaWE1uJw8R5InQEbS6JSCKRmE2sIraOUG0rVVJJJZVUUkmlS09X5fd/fnG6XL//R3MjHVVNu4/Tq+ntVv3Xe7vj90/+/qTWT2d1z7/TUbQtJZkJ9OcDFnq8HyBK7t87E0FER6KddqPjeD6ga9+++m9rRpkTebEF9HvNGSxWKO86af91unnVrV6+us+C1hnnVbddP0kb36NS68y4ERHT2z91NqPz6M6N867DdtT9yHqV9b2P8Kz76S/34ndidRyEDXEwtsFh2BGH42wMHc33dMLzOf5FRDGfexeD3J/sJRrI/Yjn/UaY3E8s9b6HkPsD971BGpHl853fQvQfrb6Tq6SSSiqppJJKKqmkkkr/jXRV7v9NifFxyZf+/j/t/n2Ravsf8P37v+2Zryv9bJdq+6/a/qukkkoqqaSSSiqppJJKF7//j7/y9//azf8l3/svUff+6t5f3fure3+VVFJJJZVUUkkllVRS6W+lK/z7f4wWxrHW+Mvx/L9WB/C4R/9+o+T5/dry/H5N4hmtj6UPpb+cjkZTipH+8xLiaZqff19Lzv6HDtHY1zTSZuefrr58GNDHGenOx7MPovXkx5YwUh8OZXgD/6PIev9Dx/V8MC7C3S6gQ+G87oULXofgvw6k4HUF/us0Cl5XUNA6jYLWIfiv0yh4nY//Oo2864LmJGnj07asHjl+/ePfLvi5zJnTezteyLvuYmxJbfyzgycOOl70wRWTV1XI3vX03K0Fr9PIqw7K1beB7F+1/fRtUE7aU5THmlgBIwsHVkeyoxf3+sR5Iq825Il3aPUmBO4ijhO7GS7V212PktY7d13KcsZtJZx1KqFR/utVdkW561bGjy7ut37F1IfP4Aw0tCPf6K+uJayvs74F+3rXucxg3p71Li36sQyMxuU4A7cS/uphFo0uXqC6mFIDChsaE2EdWRYuIDYTBwhnHc15bZqBjroaC3rW15wZ6KfO5k5Hu/VIHEX4q8MpNch/PU4bbfygwOtz0ga763RWqXYvKqmkkkoqqaSSSv/JdFXu/7lB1h//vwz3/09wfx3h036/htz/VyM28XeL5/2/vvC/d+9f3vPe3/O+3+c+P0Puwzb69DMcXDh3/cRKpsl050/LnNbZcKolgPoJ6VvXuWxX/j6hI7k4+3hjQrK7v+6PGTcmIXmsRT4XKuOsjNDyvFnyvEnVTfyn6ybeStLX/2tBYxv+Xj8jq2HzP3/sdajIP183YZH9q0Y+dRPVsAI6P5d5kTqNSvK5a7EmXodRqk5D1WlcpjqNrZQ9W9VrqKSSSiqppJJK//N0Ve7/Ldbky/X7/1Me9/+D5P7fSJQmhhJbtPfnve+6v7bQa5+d0QG8H4t7a0zi5jnWwrDcW8+lE/bx6PnOoZT4eI93tsl7kuT9On3ImWWM93t9GNDT3ZLPccTr5DPLJ5/GeEvA+VzBeoi/hHzq5TR411cslXwOl3wOJp5ivlEfOPPJ2/ZikmyO3F6edZrPOnT11dgmSN61IHmzEfOZz26/eWNNFmCb6+uyAPnzXHdnsMNVaI/i/75dtVO53O1UziZp4w8=
*/