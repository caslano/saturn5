
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
UVsgR++NM+bQEf+hpytwX0pihL9Ps3Auc5A35aL2VvWv8PderxikAHE4C/3hxc7GW0XF/Mw24i99c3XxdvFs+penx1MfMUuhYzkH6VwuHOvAn7oc4/cfRoFNJMNh6E0b6vd5VOAdecx+/8B8p0UoLTHEMpUZqKqKURlv+3VGX8m3SIe+EJtFqFXLqo8unx9wzmoi7x6I9wdb4F3fc06E+za6gF9GV3+A++F7MBTE7g0H31a0TmB7x7RmeLNpI1hkiJGE9GCF4b8pBncgG2tVBJg5Ha7q1+jD+s3+I1K7cOSt+XPSGinnUjICCeZGVKjP8A7kESOc94TDMA2Z6jr4KeFQmszKRnqYA7as7I7wM4AIPGsbmoDsMYhVh1+ZgRqdybLYKpaA1e4GDpqIrhD4eCLCTAJD2wHd0w6JzDnrhR2CFa/gxDpjnNnOZ5j9Im45eBTD3Hewm+Px9sJ+HyNwfxiS4BT/inSlDTpQwuGJvsHmsv7Yl+1EOupSfyDTbLs/eEQqfi8rgP0X8tfMZQv0XLgGw8UOdIUdgUsr4Ll38LoAiz73dSW+38/U3lUrIa1dDVWxC503TAj8zhZRDhlTCrrTM6y6QP757mBvhLc88P1KpH8uFwNbY5BE7FUZXPWV2lfost2KHrU/IYkZaMXbgbfVl6ECP/fPZaS/ZkuRYKyj5dhidLOW1jvpYcYhuF1toP9tURnewg8yBPnNBOszeJYM2LEa3elVoavLw6/43eeS+B4MM0grdTyuXBi69QmrDWY8Ax2dz4z9fDC41yCwhFx07X4ELF39Z/bOP76reY/jJ4apyapVq1YNS3G7dX7/+H7POd9hWCSj6YZksa4hGQ2LyrhhSJa63SEZN+wSDcmwm2ERut0hLHZZDNPtZugmV9e9z+/7rLjcHx731+Nxf/hDj/u42s75nM/7/X79+pwTfzF+YpAbXpW4gd1Tw52vFd01XdboVrD+M/gHx+gHWSYu6zD3aNylu/w3/FHhZMlLpIuOv9TnXwXp4kFOh1edAAo71xrFifLX7f4grLucJ+BAv3TfdF/1PvH2Fy/u6VgYXwr/7A3+vIK0ylHh9eFCEFRj2CvRP3Eyk+AV9MAP4Xzpiir7eSBuj6HeACOaxiTpZX1uv+Xu4/3C6/RaULPmB6vlGSil6VL359rdgo5wC711G1xtZ/jN077ZiRx0l+j625NPoSZd+pEdHEePqQieDH6BDv1ZkE3dh7jXp6IPXEwf3Z+/fUBiNOj9RNT7kkQNT/1R8M02OX+ULjh1bzVUj6Avz0M3+in57za0o0O10VouXmAFKYHXmSB7MUMG6YZ+sX6ZPg9PpkXfrFP5Rr4x31hoLBMEuIc5Bs++iOptAe1vRJU5HMVlvrPQqSELV48m9pbzvjOGvjrDvdnd6A7Al7gZ3PqllxXT8Z2Wxp4nGTgw7sXPjo/F03uMjtqXPjojuDNYD9YuYO49m/TtGtNF4z5LfQz1d6Q2RtvJFaboqeiNofELMsFbUV+vpfZPdZY6z6Kx9cUDKUVZXetdTf1PBsM/jDd1rtRltAe3qaP1PP0W/TLu5j7yc29+w2+71XwYbPWu+TxZngSzAx3LG4oqdhae7QF+X2Zh9GzGxYvIFfUSzWs9SaHp+BbrZa/3Em/hKPy58Th0s+zr7DX0ppfRDH9L5mMIClbMudxZ4AxBU0igzpR5P/bu9R7jmk9Hn1XUXsInt9rj4g9IbrhXtJcN/lUQ/X8PaKtJ76LiFUX/exRJmAeMZL4v+m+fiQ2IK1W9lGzpQ/nwwWTua6l9Jr/3OPSr+aLXRX93iDU0dhenBpS66F5G6aO8qvhBwQXB6kBp7KWMFL5err9lDUb7/CU=
*/