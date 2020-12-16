
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
KuJCLkLWIh8jUev5P2QOshhZiWxCPkMi72ePX2QWshhZiWxAvkIiHuA+ZCKyAFmO3IY8jWx7wJmP5IQGHf9Pr2xoxv8ntQnz9rsWaax9rvrMFiBL3H3DX1r6zIjcsCUtPzezzv5q9/jo17nfd3x0jLFunrVvmG4LS58Fx+7V/C1r/mvZPN8+7l2yTl6wfRX2vmx/vm+nb6O+fRvB9lWUGn0V89rP3C/74UcKvzh35PFHdBnY1l9fRWj7HmaF6fnRcxXp0+Zoo2/vKBgF28EesL3a4vvAA2AnmAW7wQWwO+ztzBmv85vTmTMe3PdkIN+SofqObKhvyDkPOt9nTnCCE5zgBCc4YdeGBmj/Z2aFqP0/xNT+d/lp/1d8YWn/E3lw7f9xtu3/mrHqET5r6qn9z3Gute3PLB6n7e+0/YNp+2802v53L/vurDNHNS/dbc2+LT4fvnVAw7X9K77Y+bZ/Z5gFu8MFMNZp+zttf6ftH1Dbv9xp+zvBCU5wghOc4IQGCI2Rhbu0/Z+UllHgKkowXAA77wMYbvIBrNT6c5Mb0R6Bo+AF7jEAHxg+gNQJY6YlpaWOnjB2fEJayqTkMdVzFV1QYYd77WkuKPMP0clCgta5oJ5z6vP3rrVfODe3yDyPlQPjXPV10TqXU0SCdF1HOJN/POvUWPfew+/ArR4/QmyYdT+CNfIrFHFRtf5SzrmNyVrkKjpO+lfrugwXV+ncZTq3KNM4Z+i/SOcW6vg2jru5bUXacryW42U98bWw5kZakcu7B8Iq7RHgku7qPQJJT9EizfNdb7q3+r4yxXeU7lvJcbNY4jPuslunz7pW10WU9aqt9mWdNi0leWBY3XNTG7KMfcszpqY8LWl9TU6qhZrTnA33J+8qzGk9JoHkjktDX84x840iDGgfiSGfomNH+0jY5EWkb14o3aOw1lguReUZrT0oMnSsek0ds9bprLy0TPOcaOOeHNcCcsu7x8TFceRVZrZ37vylHLvmZSX47jFRcIxnfnh/T7rCuM+SlxdpXbmzeVe0g8ugOy/LPrXkpaqONzuNvMwN8D3hzteWX/yz8lXPFn7IbPfCV7X27mzL8Spd415mLm1Rpvs673Noqr/efT4vV5mY3x+q98Y1a0xl0lrvD+x024CpnnMX6V3hfYb0XimueTa8PtJVf6OPNNg5wP83H2nlVCPf7nvhz6YjXE8sC38y7pvr79sWOt+pvc8zeJ9q92nu87Nf7fv0U+sSr856vfctf1606IzQ+k4jd9c3h75FRnF8AH83htVzitrBWNgZ9oI9YG84CPaBo2FfmALj4BTYH86EA+ARMB5mwoFwIUyALjgIHgMT4VKYBE+Dg+EKOAReAfeD6+EwuAnuD5+DI+CrcCR8Cx4At8JR8Cs4Gv4Ex8A/4Fi4B4kdDyPgBBgLJ8LhcBKcBifD+XAKXAJT4RnwEHghnAqvgIfC9+BM+AWcBX+Cs+Hv8HDYjLycAzvBI+D+8Eg4BabBw2E6nA/nwjyYCVfCLLgGZsO1cD58EObAp+BC+AE8Cv4Bc2EjynERjIB5cG+YDztDF+wOj4YDYIHbHrgUjoIneOcQ6ftE3y2jfOYQnay5QKfAfvA03VeOVOi+hbtxn367Num+lfLFXwWj4LVwH3g9jIer4WB4A5wMb4TT4C3weHgbvADeAS+F98KH4H3wcbgevgPvh+/Ch+Bv8GH4O3wEtsOujXAAfBQOhI/DmfAJmAGfhNnwKaVr1m763dXvMeniGajZy+t5PScv6Tkp13PyCoyDr8Ph8A14GHwTpsG3YB58G14J34NlsAKugx/Al+GH8A24VfX7c7g7cX8BO8EvYTf4DewLv4XJ8DuYAn+A8+A=
*/