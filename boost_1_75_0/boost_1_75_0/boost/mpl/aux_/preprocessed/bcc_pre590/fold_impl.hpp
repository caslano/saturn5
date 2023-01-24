
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
Ej60msJHJEpH2y52/hpmcm/sNm1fd9o1bbguTIsDWPWmVltV/AvtBZtNTyo7GNYeHm65Cv5cMfizMvVFTkzbG8KbVegjuuaOPT1mF8uyB7P95t/HdwxZCjgDuIs7WkzVoN6w6ZgXK544yLLTXUO0m2oUYbea19UP5ESWtwFxgGs3GI0d29204f3hh/pk23nw8BKNHtVetkqGHoTZOBaByK7/smZJsGsF8O1hBZO4xlQHlG7QUOz3NqUlVCY69pVTeM6jnTbStKxef+ntlXkUsj7/tM38GHj6yzZa/xOI6/Qd7uN6bRMNhQXVY2II56051fahSE7EzvhnC2Zu7cwTZZUyPpRMKaOSx2Q8Jnk8EtF29LP0xYuijJJg1DEZIY7jiZze8ToBKJsq4nw2nxK2TednrFm4fSOnRWprWCa28M3W4wfJrmFFnH5dbWXfYVMmizg/78p839agoGYGDRu5Ba6JH3ZMk6jNqGIO2N8lkP8aNuXAsR6xjzbLsnL5QLscV/n0iCE4hFPMkNBQnIQg9c+gsmZcBdYQrN8VQac+IFgcki7upn4z3DE4KD1y2yxsNyJMEOOBF1Wv7mgV4ZH7Gsv+7ewiv1Gg7OIxB0UkoiQ68VMy7rU/j2IPpcQopmTd7erIFkKYOSp1+aqtlnSZAe6POVSHoJMOyilfdqhFo3ZdX36mtvU38eo/GdOMjzOPM4kqbeoYDzs2km8N
*/