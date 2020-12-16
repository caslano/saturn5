
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "fold_impl.hpp" header
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
rNb8qEP6Rr/OR4f9KPB1nuxbS4SfHQaZ5wrwpn2TQs4bZQ42f5Pi9l8Yv5kRd/nIOddWW1PmdDtqGrz8opGTrVrZdsXU0XWQ0m6xNhUZdVB3gP0K7MZ+Y8ceWD/LIfzl6m5s5Wvv8Zdb6eozU1O136t2f4fL19e/VjvXNgqJn7u1bgf3KftkE/m0HrrynlK+ep9GTeZDzwu1ibujfeQ4NKobM8fMjeRhxKYwTyO3Sx5zuCaofIaO4FXUkl8i2sBfjumSQk5FGF27TqwRZMk5KP/uNO7X6l0r6q6eNYGh9Zk86DuKGZ95iKZfqS/tLFbOz6Yu27f9CxqjrL3No8/PiA3z/MwQL3u3Guc0rquMc6tGzs00/MAuWxqeWxVcaaTRe9X+52eng2PTrQ+fYaKxiXb979frOF9daQEWzge3SJgmy04Tjduv+vfMt2ye8ISJuZFfrfs0GO0Ov7NPj+MLOvzh+ZKGo+1PkdMhmZvVO0N9/g4DTlCdvxgmApzHBw98LhDs8OvzrOyfDC8D/bxRrUu8itQTegWlfKwqqPk+G6RC91h7usSlzsDUyNeTBF9yfmjXLRcmnTZ4Lbe4QNIo1KZdcxK5bI3aI6RV2UnqWOtnhCbnM4MZtck3ODSa5YD/RpCreV9yNY8kV/N+5GoeUa7m0eVq/pfkGkGm+S0h/0sUdKV/aROKA+5ncHAl70DmLcwd9WKZpESyA5y72DxVaaHF1VK++SNmsj5vaC7bLCo5i913f3MkGqeVUsphOUCsATssK+T5NY7R8/KO7zNPOsOYk4/Qr9P+Un57TL+GAkyflzf90pjLLL8aPZe1+NS9e53yUxyFiFgkPg3hqXHb0JRnaE/DgeaOZrFlxpA8SmUtf6uP+LeAa9UbFeH2jefFWj2H0M9yfuyouNr9VHkfVb+fmZQ1dM8wyLncT8XbKv1ifSjUw6/tkRa6QANU2h5pQHJuoULNtNV2ST90XCw3r3lMm9f8KtwArsID3YHeAX9HeLsFHmcGWcQDkPbulo5e4rILSeX+OTPIIp5bNiLKsYEbwJKmrY2VIgmAXvjUtL9EMC3HFGD1VO590k5a3BVDcG0sxdkd+jUfkOfy1FIcMLb7A+H2A59TNfPNqP6DXR+j3/DvaiXJH3p5umeXkwSfdndolieyizhokPgXFe1//t10aZS1YLMa7+N08HXbxHfqdPe/rieGDe3G803bxDqq8TuBW4D9viGcF6673pgXttFu+BbkXTGhe+xbJUyD7wCvIN5ivdIEfwJ4wwqjjONuUMd4X/Kr/3tR8mg5IrzX5E1gvVuiwmu4N+h4lO36/LeX881Rxvw3/kbFer1bl/9MNCJuNN0Hlfj6OWXmjcYcuttEo+DGf898cF9/YqnZUeIostXYXc4KR5G8Qyi/gaXOHU8a8HXq51MhxIbw15KYtvUGeRu7ekz+6mOnnZwx9oY6+3X9qmttFeG+KiZrfqE9nL1DW85qPdyMdNY4iuwyh/W1+fh4hcw8Wr/uHsGSiue2lxx4nCGe8XrR4VvEEJrc4StuSEcuj0VIVaVJxZ+2SbYGhsP8hOelzF3VF63LZ8M5h4x8clyu9UFSUWnmTDCt/1VrKhfdZZtTpwKNkNamDhwfDKEndA90diaG4HbJpiL41HcqkrlEy/Xhc/kMfJgF2ceYKx7crljLdWvH19xk9NU9242/h9bfpljvdcn7atocYruYVxjXRyy3hmFj5ZrIeGDa/TftnnmMDu9I7V6gCgvH003Gb9Nm094mz7dn7TtPWm+Psm68Izwnahh7aP3GjFV5fmHhvvs1bY+y7rpZ10/WO25Rc8I11MdS96NHAT/2OsXqulXNU/XUqS/NCuE=
*/