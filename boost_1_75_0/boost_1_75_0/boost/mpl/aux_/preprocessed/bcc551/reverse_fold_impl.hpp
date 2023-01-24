
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

template< long N >
struct reverse_fold_chunk;

template<> struct reverse_fold_chunk<0>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef fwd_state0 bkwd_state0;
        typedef bkwd_state0 state;
        typedef iter0 iterator;
    };
};

template<> struct reverse_fold_chunk<1>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
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
};

template<> struct reverse_fold_chunk<2>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
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
};

template<> struct reverse_fold_chunk<3>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
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
};

template<> struct reverse_fold_chunk<4>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
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
};

template< long N >
struct reverse_fold_chunk
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
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
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_fold_step;

template<
      typename Last
    , typename State
    >
struct reverse_fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct reverse_fold_chunk< -1 >
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef typename if_<
              typename is_same< First,Last >::type
            , reverse_fold_null_step< Last,State >
            , reverse_fold_step< First,Last,State,BackwardOp,ForwardOp >
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_fold_step
{
    typedef reverse_fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
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
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_fold_impl
    : reverse_fold_chunk<N>
        ::template result_< First,Last,State,BackwardOp,ForwardOp >
{
};

}}}

/* reverse_fold_impl.hpp
LVMuLMbortkxD5Gu7tVLxa/d7ul9wg3Q2oUrJ+h40Um9owz+WAtGDXfBXULfPv0wwGmS9AxBzSzc24/pQuefLOUfzg0VL1Bbc8t3QfY6cr5eGK3SNDsErGB7+WdPXYrhDQE4PimO1D4kPkH53i42B++egRUG9sKa/AsvA52nKV9eNhxOQHpl75cbfBGU9+3HglJ/JbtnzumVwbtD3LMaJXd/ewxXyjvSnNPX83HN2C4JzXhXcc3ocvHN2Ns7/fape9KrKAZUdAgCldvwFOlVxnaJQwM4ioq7fX2K5lw7nFXwo/WDW/nwpIPLV87kqiMgeuBZY2P0GarX73C1T9/x6FUDN1NXzSMlvm95u5poIrAXAlF+90lJwS99cll2gaEvSt1Vw9YJfCmwLeDw86a/B/NbYFKdlzF8MrV5eOK6DDGgZTFRtQ9PbJjtiJ9Zc0v/C9qdbf2mblI0yYF3JcboINfjjdJo8rnS6MKk8jXeCyuTR0FEoocB2vVT6i1UpPC+I2y5d4RLJ2P3cRr08ifO7jKozSYB4DjO4X1pC8Xf4lKsuLeU4lLcvbikuFuhWHEJHty1uAd3lwZ3Cy6BQIDkbO7mPtzMzdzM83zYnf24X347O/89jghCHnBv+MCP4zf84LXdN1O1mz7wSThqG9ANR/htPm6XbqL2SQJLnP1MnjUbiOKbJpeXBuAVbre1vyZ/oyh8w8/pPa5dJoRj
*/