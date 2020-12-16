
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
Fnq3m9brY1PeA6rvL7XdyrXdDmJPPGTebpXE8w/F86Hi+Vjx7Fc8n5m3WyXleFTleEzleBy9203rNbNJ/26tt0H1thEb4z3YFO81xVNWSTy3KJ5bFc8axXOb4rndFE/YN4Hj+a3iWa54ViielYrnWlM80ZXE84Di2aJ4HlQ8DymeEm88hEriWad47lA8dyqeuxTPelM8KZXEc73iuUHxrFY8Nyqem0zPJChWPK0Uj/mZBA7FM0/x5GMTLNDxUohn4nzzMw4qiW+G4rtM8SUrvhTFN1PxpZniK6skvrGK7yLFF6/4xim+CYovwRcffZeB41ui+K5QfMWK70rFd5XiW2aKL66S+GYpvizFl634Ziu+HMU31xSfo5L4EhXfFMU3VfFNU3wXK75LTMfxesXXyOY4bqbv1Sh9jzfX9+Umwg6tt1vrNcF1Wq+llm+F7bENdsG2GIvt9D3cAcdjR5xmpIs52BmvwLPwKuyKK/AcvAW74x3YE5/AXvgKxuDr2AdLfe+A4DpH/YHqJyS/xMV1BBrTffq9uBkj8X79XnwQB+FDOAxLcAw+rN+Jj+F0fBzn4lb8HT6FL+PT+AY+g3/DHfguPod78QXcjy9iHfLyMkbgTmyGr2JrfE3XT7vwbHwDe+Fb+n34V0zB3Xgr7sE78B28C9/De3Cvfi++jw/hB/gE/hO34ie4B/fjPvwUP8bP8AAewIP4JdalHr/CNliO0fi197pWfZDYwGa/aq79tAXWwzPNv5+0Xmub9RpovYbYEhtpvf6EHVqvidYLx+5ar6vWO0fpdcMI7O5Jl+XLtH6x9o+ORrraPw6zXAs8ot8vP+B5eBRnYI0a7mc61cQbsTauwzp4P9bF57EefoQN8AA2wsMYgWeQVmNsi03wAozEUdgCE/BMzMKW6MA2eB22w5uwE67FzvgonoV/wq74Op6DB7Ab1qKc3bEr9sBu2AtHYgxmYW+cjX0xD/vjPByAevaW+upIQ/VufvbWRJ0/JmF9nIzNMRGjcQp2xiSdHy42XVfEKd41Nr+Hz9P55Xxsgf2xJw7AITgIEzEWZ+NgLMYL8Xc43NuOov44GGrTjnKz0rkFI/F2bIm/x/NxLQ7GdTgF78BL8E4sxLvwOlyPG/FuvBc34qu4Seep+7AMN+NneL/y9wD+iFuwMXl7GJvjIxiNj2J3fBx74hM4ELfhYHxK8awOUx8YvqT6bITLVM5klTNF5ZypcqZhL0zHfpiB8ZiJaTgLf4NZeA1mq5yz8UGco/NzDj6Dufgc5qHeHaQ+Ks61ypf53UHzla8FyleR6n2R6n0xjsPf4FRcgsl4BWZhsa4jl+IyvErbYxnejtfgWvyttssK3Iwrvded6vvBi22uO9fqe+NObIN3YSdcj+fg3fqe2ICTcSNOwXt0nowmlCv+uoTRhGoE7xgV33Lqd+EcUelyBC3X7DjLxQW5XMpxltvO+SB2gP3zopL4vMVl4ZU8Z+rX+Swp/+dIBff8KOPZUa2DeH6U+dlR9s+NOv4zo07n86L+w965wEVVpQF8VDTfISKQkoLa5gMVzVc+EhXfJqOQ4qMAeQjKY2SGQiPDsk0TzczK3dRos9KyojKzcos2SysrLCtLKyota91ijd3czWr/d+abmXvn3oEZtPY199fX33u553zf+c65d+6955zvDL2Kc5FSZCuyHzmBtE4JMsUiZiQbWYnsQKqQWiQilThTSBJSjGxC9iDVSFBakKk7MhHJRsqQbcgBpAYJnU/8KWQeUopUIIeQ00hkepApDslANiC7kaNILRKcEWSKQcyIBSlDtiEHkBNIcCb5IqlICVKOVCLHkKCsQKyrwBbYAltgC2yBLbAFtsAW2AI=
*/