
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
cjb0/W1ZbNm3imtiykrOx3KtGkJ+xUrb14K/p6rtldXvyC6mFtIcV1U5roexrew40/4mpUTGhHe8h/7Byn4kJuu/9zZlHm8DI7cs410l8S6XeBdLvDXi9Xg9/4J4HdzNK7tKvC6E4cSbZ46XH+4jMxInxZb6t/tUG300s6zPXxLncKlT/XAkcdolmOLMiIwyvTotKVbeZ5d9j8exdb/wDEJqSrq0LZJGqQuzpM91VGRUutpHfqY6T9t79bugud6ZurtnWB4nWR7mRNUllJfzUyjzCsaZ9inL1MdfjhXTkHj30CZIf37SoB4bluMP1pB5Mv6gPHsgfbs7mje4RfpAPoNKumqMLyFd4fGxybFpidGSvoB7PI7vNa3VDM8eZKnfS2Sad8ZRU+QaqFiW6ci08dkD+W7pqK/jZmfjeYVqxucSCPJ8A9MyTpd8L5C6In1UzPXX1IlZ+hlPZ/ki4mxTjniT9PfV7ZVlowz9jAtl/Anb4ymVPH6R7fGpSh6Hyva4Uvc+/pLt8bJKHpfJ9nhcJY9/ZXucq3sfz8r2uFslj09lexytex8Xq6RxrtzGK/OLIq7/+sD9Bz5MSFzyW8boXY+Yx6HysZPnlHAwIZ9/2KN6TdaiKuOPYCtsjG1wALbFq5hlJ88JyfND+QTluEqS9Tuw3EPoia3QCwPQG2OwE2ajLy7Frvh37IbvYHc8jf54BXvgfcTRU+L3t5NnczBY0l8BPSX+CvaM14IV0QkrYUesjIPwfryKEYQC2U5f2c79GCLbuV6efMAbWBtvYl0sxuZ4C9uhHdvzhvuwO5bDnlhe4nGxk+di8EGJ5z50lHiU8ULUckmV5VrYKJf3WK48vo+18QNshnmo5st6Wb+vjXz5XMaVOSvrfYH++CX2xHzZTqidPHMCCbKdyhgk2znH0CXV8BusgxewPX6LvfAiBuF3GInfYzT+gOo4VItk+06EfKtxqA7Lfh7BOvgOquWVK+vNsFFezzuQLtyEdXAztscXsBduwSD8G0biizgJt2IWbsOr6HSfPG8hz2EQj6kMHdBUvyUf3bERemAX7Igj0RPT0QsXojduxE64H33wDPpiEXZGZxkvaDL2w3cwAB/ivNUf4zEQ92AQViKDBmIiDsJ3cTC2syftuBCH4nochtsxBA/gcPwHjsBzOBILMRQrsL+jsA6Oxhb4MPpgmJTDqvvkeQV5joH8MZXpfMmftHKkGx/F1jgTu+IsHIiPYyTm4DSchwtwAT6Hi3EHLsFPcClewGV4EVfiDVyDSpmsRTdch/74LPbE9TgCn8c43IhzcRM+g5txDb6AufginsSteB634QV8Ca/hdqyijEOE7fEV7IY70R93YQjuxRh8FXPwNVyFr+MzuA9fwrfwTdyPX+MBvIpvYyEexsrk71F0wmPoh8cxCN/FQfg+xuIHaDp+K8izF/JMhlI+W5Tjl/l8TOPsVcNq2AiroxvWQH+siUOwFkZhbUxHR5yND+JyrIOb8SHcg054FOviZ1gPv8P6eA2d8QHS0gCdsSG6YSPsjS4Yio0xCZvgJGyK2eiKc7EZLsPmuA5b4BZsiTuwFe7D1ngE2+CH2BbPYDv8FtvjVeyAN9ENG5Lv7tgdPTACO+Jj6InPoRceRG/8FjvhAzI+Xwf0xWHYGTOwC65CP3wVu+JZ7IbF2B2bcPz5Y1/sgROwJy7GXrgLe+Mn2Ad/xb7oRJn2Q18MwNHYH6dhID6LA/AgBuF5HIgVKnLewOY4GAMxGMfjEFyIQzEXh+FJDMEiHI7OlTh/YFcciZEYijNxFD6Po/EQPozfYBhWpCEZgy1wLAZgOCZiBM7FSNyKUXgCo7EAY7AmJ/xY9MI4HIHxOAM=
*/