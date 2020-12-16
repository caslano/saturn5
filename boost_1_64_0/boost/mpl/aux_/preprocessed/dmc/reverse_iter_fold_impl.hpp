
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/reverse_iter_fold_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

/// forward declaration

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl;

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 0,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef fwd_state0 bkwd_state0;
    typedef bkwd_state0 state;
    typedef iter0 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    

    typedef fwd_state1 bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    typedef bkwd_state0 state;
    typedef iter1 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 2,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    

    typedef fwd_state2 bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef iter2 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 3,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    

    typedef fwd_state3 bkwd_state3;
    typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef iter3 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 4,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp,fwd_state3,iter3 >::type fwd_state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef fwd_state4 bkwd_state4;
    typedef typename apply2< BackwardOp,bkwd_state4,iter3 >::type bkwd_state3;
    typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef iter4 iterator;
};

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp,fwd_state3,iter3 >::type fwd_state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef reverse_iter_fold_impl<
          ( (N - 4) < 0 ? 0 : N - 4 )
        , iter4
        , Last
        , fwd_state4
        , BackwardOp
        , ForwardOp
        > nested_chunk;

    typedef typename nested_chunk::state bkwd_state4;
    typedef typename apply2< BackwardOp,bkwd_state4,iter3 >::type bkwd_state3;
    typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef typename nested_chunk::iterator iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< -1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef reverse_iter_fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , First
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< -1,Last,Last,State,BackwardOp,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* reverse_iter_fold_impl.hpp
sauzi6a90VRP6i1zg6h9U8Ztb13KXEiI5HOzFvo+k9W12P8xcrxrrl2O9JRnqlLPqniQejq1VOup9j0FmW7ESn6dpdQtxKaukzXPveU8L7Kt6sDyZD5Z22ciccpq9XOd9LJ/vnJIaa9aST3UfaXsN/NRUJrvCfP2K/l+0x6XHJaG++s42z6dcvdVzq1W+u/KM+Q3NTzKrh89uLf8nlLq+RbhA+VcbG2qp/mOvVPYffeR3Bdq21+1b8edQL83DRa3K5bvQjkGWbdu3hl34njmqmuHWEDXpgb0lXFYuTmqgw3wKGX2bGMtsxxapnKnlPJ59f2u550M+iDSpc93ZvzcGMv+ytTc37vIM+1Z2m0hy6XZHKu7DO7xl0ta2V6muLUSx7N0NS5V4qJjw6ZFhZjbvm2yXUnLpjUvl2Epb0jcDEseq2U51qculyLLzYoLmRouy2206UepKc/io1yIU7KQ5RL0/RKmYzSM482/r7muXT2sx2hiMd+h+2R/95b74Z6EY8r+bm/d37HhPIoswb2w5Tgt6jlgcj/zwhHSfoWh6TrKmpc8lyx9n6/1+kMeVhg+Lym6n6dAv91N17ezOqjXt/pzxNtckOVyXqcQ/tGAeE9TPZRpJeS7q+Ttb1Hvfuqfken75CQPw3kDpd7cl8hzEE/jPuhtPvI7ANknFfEkdXHoaKqL/JjG3ItlaYPd79N/m92xyGdGct6TH+WIYc3W817iwojU/LZe99xSzhf5ai1yW+TZtOVXNdfNLtLW678DpI9Q86zK4Hf56vFkfq9cysm2XdhRxgGz3bb9ZYxX2bYz8JRynHTSbFspwh/ps7W99nIq4hrE2ebZa13N9nXRPFPmHjpIkqrXZEbXOgWyPPGW5XXnSboMlvq61H89nqb+7l309bdch3o+QN2LP47k3Qn9NpJxGuT6VCqk1MfNdrtJenf5LQFrVOOu2hyL9Ym7JHGTw3XPJg2fsZ3XXPcbHpO6uaZlndayynEp8Zrj9ZZuHAmOaYPraaWseRIv6dX/aHp/iuN2I/uO/zlc6GL9Hsmx3t/pnkny8ord90ryQAfTvxxpI7MJZ5TvlW7qvje1Kez9El+PG+37MO2+1+1T2fcGY3vU1e/PIq9pNf3wurr5DzIXbqjUTflYgbJ4d7fUTbZmCZ4fyXcmx6e+DXO0qa+Twf13oU27dk/eM2G+aPXXB0r7FGsqF227Tft0SerRX777vaUeabb1CIor0W88SlIX/feZfrtmDZbnA9JenMePG5hfoqc809S7grCYEvdhlHfW3NfI58ma7xO5dg/RnqfG9wH6PsnpmuNkiWkd1vbiunW9ZKXf5kf8zIWsLn0WVSx9vT1lnkfTK0iRJb4OcuH79nov0/7VvttR/HtStv18lFz3zITKmp4LDOZY8DPfTw8kD5Dtpu9zl/5B7pHUawzT57a9LddP+j745UP4P2kTqsuY2LlKHzzLsw00P2Y132o8yHejXR+h1M/yLDyuiPO+QP9ulKkern2kD9vm/PEaai7Ah1KPw4TaLJPfx7YecZxBD14H2+NRrg31+9Du/VB9WXdJWSvLuV6RUFYpa19TWZmBj04SXvCYXMrfc0n7ozvPw22euTQbZv+buzdc+L9+lrmwfIeMCQwKGDlkRGBp5+nbJPM1avPbKPlp597a4kJKo/yUSbdKMRfdJuP5IXX5O/vb1/dnCuOt5j944IiBo338g0b4DB+o1Ljk+Xd3tp8bdLW/fX3/yYdg4/yUGpdq/jXyNKqzrgyOw/k/g/kYk/r9+fMxSp7M22Bf73Msl1ZEnqXd1+RpVG9936NBvS+SLqufbp43hikr3X4+38D+uE4eYV/fSyyXZ5+XTLM=
*/