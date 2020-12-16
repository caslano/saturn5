
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/reverse_fold_impl.hpp" header
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
struct reverse_fold_impl;

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_fold_impl< 0,First,Last,State,BackwardOp,ForwardOp >
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
struct reverse_fold_impl< 1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    

    typedef fwd_state1 bkwd_state1;
    typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
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
struct reverse_fold_impl< 2,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    

    typedef fwd_state2 bkwd_state2;
    typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
    typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
    

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
struct reverse_fold_impl< 3,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    

    typedef fwd_state3 bkwd_state3;
    typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
    typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
    typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
    

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
struct reverse_fold_impl< 4,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp, fwd_state3, typename deref<iter3>::type >::type fwd_state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef fwd_state4 bkwd_state4;
    typedef typename apply2< BackwardOp, bkwd_state4, typename deref<iter3>::type >::type bkwd_state3;
    typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
    typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
    typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
    

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
struct reverse_fold_impl
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp, fwd_state3, typename deref<iter3>::type >::type fwd_state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef reverse_fold_impl<
          ( (N - 4) < 0 ? 0 : N - 4 )
        , iter4
        , Last
        , fwd_state4
        , BackwardOp
        , ForwardOp
        > nested_chunk;

    typedef typename nested_chunk::state bkwd_state4;
    typedef typename apply2< BackwardOp, bkwd_state4, typename deref<iter3>::type >::type bkwd_state3;
    typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
    typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
    typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
    

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
struct reverse_fold_impl< -1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef reverse_fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State, typename deref<First>::type>::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , typename deref<First>::type
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_fold_impl< -1,Last,Last,State,BackwardOp,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* reverse_fold_impl.hpp
vtN5+87m6/ua+V2tB8nSt+0P7df2e/Zp+yX92Sx92fz2Y9P3JL4jefRdC6rfmp8+a377qzm/1wT4fcZ337Rf3ifN1h/tN+mLZuuH9qu+c+j7htfvGnzPsPc789vnzPj+ED4y9B0gtISW0BJaQktoCS3/P8vv8/0/e8Gp+P5vfH9fGBnmbKs3Td/fLybVVbuMaOP7/2vONshJ2QvSs4g2bShjaqn5fwBtkKvVn/2as0212j56nx/1OO1iyZ6zfaba/rrNV1yqOC9XnJeS9rBe0Ws+5rLWlPjBzP3vaw5oaxxb1HZhkxkHKo6U7d7j4LgFEUcdcx/HjW2pDJ8r/3erMeN6m48fdD7uZT5e73zc03x8ufNxj4Dy5eiP0EPt97vod5xOpMZGO9LXfeQrwzFN+C+ft36YrV1/icp0JymGfef62jeT52oi918/Z73m9T/dOmc9G7XOV5+bZtT4MGffkmqNeC6ngDrs6kcRi885nzcaTLva/6/pyX7nGeu65/u4gs5XvnNITcn38jcqyrf7/PERQeTbPP6as5loXG2kXf1tnHOVRxFhwfzc5Jx8Vz5uJh9mCLZ8rKymcZlUdxI1F374Dl/5KCAbsygmIyPB1x37PPj2ch1zmqtvTV3lr5lRnyqIR9XJGNwv6PrkKNdVEZrzW+X6Jx5rvnPVJ2udc5XrjZSrEYIjH+OUj1i1mZ+hfEwjNTeuzTv95iPfbGRMVQnsuuOlfFX3OcHZiCtPq2KoK/n5hbp+O8+R/Owcr/mxXjt3Kj/TlJ/JpJbkZ7Wv/OQbWSGCX5AHa38AtmCt65pj20u9tsU7TW9wA1Wv+5Pe7sX/3vQZr66Jv7xOT2TPxhbs/at2KpZaisV4uIwGehN8xWJegoKPw7rPNP2k068yxwt7YWujHf+b1v5W8cl5jh0bxyqg61K1+nN3Wfpb8XjFLt99gKzt3RmRU9dq92MbYTu2p+tabe1bGOvlWheHXciteYnXtbwVduQ581I+mXIcmWY+35bnE6zPq/yOWj7DeNYp1+cclTHbqlK/hAymUL7T+fsRozy17zL19UhflJtsnQveelwmqI3/CF5UF4fimcZ7dYlbPzjLceEqqX5j4X6Oy4jd7sclZbf/vllch63XOZ1nGpdT+S/z/Jyn8nCVT3ndd6+De5TXeF0zOpLakteS3dY+cvHulT8/8OuFfXxoxejWdylBnQdHK4bhpHbGdfhtM4bU9HxGsU11HK/A96367HbN6VhXYwnq2LbGdGLMLd8Xodo+j2dmZxaYQ7yW7zfaz/Ed9I79eHqWwZ+NMpjl6u81P9w4vgU6TpY+czquu1ifO3uUu84HrZOjvipHeOz2uU/lOuP08uAyuK40wnPR+Cxd9o4jr14//+iTvepzpcD6Xhl5r7vX/zXGrU7+5F4WJ3msPofl32fY9qN8UE41PgHruarWc1/PhakPaKF5edR5rm2ZFYdK4Hj9cT1fqMpkLa+CeuWZe59MNMISNMtrb4XlpW8g6gcbRHmt3BdceZ10lpfKQvleqHyrTFWG7vldqPz6KtcwW7lay2WpLmod9T7VVvVowru+yqXAVY0CPG8SDgReFg2s1/F55Ap1Lql8rOdJ+bnVQOeJ9f3f8/OUyrC8XNm2ezms5P/GclDXjn2qH+EHKygHqkcw5fDMe4GXgy3P+m7hWS5HbOVQZsmztRxuMT47Uyd8lcMQx3WFYI2lhcrhDNxLjLnvV1QOXEiD6FutPHp9D9TnE32W02d/23tiA+u1NE3fF+3H2zbufULD8kC+1PvQZ6QOvA+VfmDpB7wgOTU/uytfyvPo4hJI33fvn5uJi2OapmPofs0/aaunxueZFDbWkfh68rg=
*/