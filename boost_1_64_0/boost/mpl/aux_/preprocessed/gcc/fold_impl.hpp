
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
l/anLdqH7yOMM85Prn2+Wm7GAmMXDv5+Lft9uML9UbX9v/tyWS5uuGdcx7CLk4ePmZQ8YnzipIuTyQPDWnJyjju2w3ycrK/tP2YmnzQSbNOo2j1fDptxM93r+I9VcbKcwz49DZ0J/t14KRXGzcS1Cjxu5gGbvMxn/dUB8lJYkFXlfLjOyfrOczjzrdu3rn/6RaxXYpt+1e9/c9iP3bHUQYlNHi5nvdKKeRg9dPLoZE516cGnf0mF9M9XHZjT71TPf/9bzHrltumziwdR/iZK/0rSS+OHJ79tLfVeUs+/zEtIM2KEXZraBavwXNZLKuyDeZXsgzH17es/xj4v7IJVz0dl9V9ik/5S4/i3S7+K76ksDmL/i2ngn/4TbcnnCPPYNb0ns4r7X1Yra/p8R/mX3yb950h/tSX9E3tP5/a2x7//9FSNnUusY3x+3a7YK87+V86WNzbGT2hx5c6/Bh5TZz9Grupj7U7VmLpf29g5+zF+v74xdYHGvD3gGmu3uDgxs2zO/rndRzWM6Z3guPDUjbXTmDquw31j6pIqjKm7UGPqhmNtHIGsx3s3dX2t6+4kQhdjOeMDjT1qoLFGbTTW6Fy8C2M11mgY3o2jcSOm4n04CzejA+/HhfgALsItWIwP4j34EG7HEvwcH8ED+KjG2D2G1cnT41gLn8AIfBJb4VbspDFGsRpjdCH+GS/BpzEFn8FZuAMd+Cxehc/hH/F5jQl7QWOUXsTn8WV8F3fiJ/gKfo679N7C17EevqF6jQvT9TmO0vaoif20PZZre6zAVrgSe2ns2Ahc5dk+hDLF01fx1MLhiucKxVPMf03xSmyJS/EcvErxLsPeeDVqf9E1Ncepzf6yUPFejlG4yDtWS9fGuF3rmcdqjdH+MhYjMV7lG4+dMEH7zyQchJNxHCbiZJyCs3EaXokX42/xElyH0/FOnIGPYwpuxVRffelals9s6usG5e8mlet3qqebsT/egqPwVpyBaxTv2TV0varrWOLlGkz3cGgMaHPcg+3xPeyG76u8H6i8ZTpePsSL8J84ET/CS/BjzMRPMB/3YxF+qvr4DK/Dz3ENfoG34wGNUf0Sn8ByfBW/xg/xIO7Hb/EbPIw1KcwRjUU9ijPwGC7An/BG/Dfep/e3PojVcSfWwN0Yjp9gTaxJnZyBDbEW9sDaGIt1cAjWxdFYDydhA0zHhpiJjdCBEXg5NsUrsQOuwi74GnbF1/EcjKzBsYG9sB/2xv54Pg7AS3EgzsBBmIGxuAIH47UYh7/HoXgXjsSHcRSW4mh8B8fgD3gRhoezf2MUJmA0TsQ+OBUH4TQchUmYiRdjHl6C1+N0XIsz8HG8DJ/GZCzFFPwUU/EgzsTDmI41OaFkYCRmYm+chRdiFk7HbMzE2ZiFc3A25uAinIsr0YHr0IkbsRAfwvm4HRfg33EJvoPFuA+X4pd4FX6Dy5B9jTGuuh7XdXqSsW1xmY7DdB2Hs7ALZul4ycahOBsTcQ4m4Vycibk4F/NwPjpwGc7T8ZCPa9GJG7BQYz9ZVmMvdc2u78m4Cvf3rzItl6DlGh9nOYeWa3ac5VYHuVxJkMuVVrLctebnGfiVw365iBHBxRcT5HIJQS7nGBF4LOxAc/1VvhzHX+VjZlvU5Xm8hF0TwjV+NvC42QMsYzd2NmXr6Rk/69z63zeGNjyBOhpjP5Z2A+XZSggfW/m42tKtwY2tPbq18vG1Z287vWNsk7ZVfZxtzjbfWNtl2058vO1t2058zG1KfI1Kx922SAg/6bG3m8Yef/xtzFbS3uYbhxvJvhL+VMDxuIzFJS7yFk/IIiwnbCLsJJQRjhBaTwwP60eYTigmbCLsIpQTIieFh/UnpBA=
*/