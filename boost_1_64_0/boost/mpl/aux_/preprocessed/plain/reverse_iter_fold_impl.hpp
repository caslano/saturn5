
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
dinxOPJoO27kh232rb9U6wxp7X7s4vXBsVR5PEjqZLzX/sMtj3zSTs7Jy8ww3nWMjuf5mTnZAXy+Ia9o+xyivLnqVCl/z8nLMPM11ChzYkqEc4wYLOdyJaPez5pjxO9ct2NE+VjKLznWVX3eYpSv1jWPqfJbXJ5f8qlzVvmN/9Ajv8pm4HXUXz7dPvMrnh6RrjEWqqgfdGfimfCRJR59/khOc3wACfx7hrfx5Ddpn/20zz7aZ/ghxz7Nz3iuHQfxvcbb/lKiylecoDIfQ8rvyPOu/RlV29hpMhcGTs5Afu9kf65z3qwPD0SybfbV1ljJ3LbH2BG2Y+M6P9Yfcp0f1mv8wSjPfs1LyGPJIWsf40Q+72fOzpzFl5rEOTmZs9Lzg+3fvEh9ja37ntPIs2/xUtYr87PvYPs5L6qgn/MgRzk08iyHwbwu/GNLLLbLPEUQcAxnKQbrtSkt2jP/17NefAX7zC3MnxNMue/qqbxb3ktzC/Lc4jjqJY5E4pjgO47yQxBEHGf5OgbW+tDY8xgs53W5tjgW5FAZuHIZgZRXCeNQBB7LMsuxGKV9n2jsWQYrWG+1/30bRRFUf/dlvspC7RTjffZz/+P6s/tqB7ki2nj+4GVp193X6NhfjkTO/Mf2lS+2D77d4anqz+69/eIf18/91vrm9ifcnnTkoaweqzuWvPX5j9ee6av/+2/fn32N2S6z1oN/u/nWzVcsXTc6M2FLZMxCX+MVnLp2qMH2cw+2nW55P2rdZ9T9x2m2ftSZ6leZhZE4H2MwG5tiDnbEXOyGF2IPzMPxWIATsRDPwYU4ExfhQlyMi3GJZd6JIsVzufHY1s/zo8rEg4ewHR7G/vhPHItHMRW/wEvwS7wUj6Gzn6fu7W0iTbP18/xG2/8WW+N32BtP4kj8Gc/Dygy1n4PV8FqsjtdjTfwKJ4Tpvh120X6q41DtJ0Xtb1OxNs7EaJyFcZiGHTAdO+FslU8xKVfbLdF2I/FJbbe34u+LkdgP47G/8jEQE3GQ8nMWTsUEPB8HYwYOwfmYiItwKC7DJLwSh+FNOALvxFF4L47GR3EMvoDj8DWcgDtxoo5DbpjusWG+8lEb05SPh9X/+FGMxMcwHouwN27GBHwCh+OTOA7/gpPxKZyOT2MObkG1i9Y9MfKi/VrbRZ/Oeub7KNbGcGyDDbATRmAiRmp7y0m52t5iba8uFmh7n+r8OYqR+BnG4xfYA7/CgXgcE/FrHIff4GT8FpPxBKbjd5iL32Mh/oDl9U33pHCGl/pWSeVZReVZVeV5GvbAGjgQa+E0rI06X3RviG16OV+mqL5NxUichvF4LvbAGTgQz8dheAGOx2ScjCmo+HVPhzrqJf5oHZfGOi5NdFxisD02xV54BvbHZqh5X3R/hrxpu9Z5X87TeTgDa+D5+JX6PaTodZxD5uu6G9cM/Xb3jspzD0bg37El7sN2+C52xgMq34M4Dt/HKfgBTsUP8QL8CFPwMGbgJ5iJn+Kl+C+8Aj/Hq7AM1+NXeDsewy34NT6PJ/AV/A7fw+/xQwyjvI9BJfwOK+NPWBUbkLdqGIOnYRxWx3ZYE7thbeyDdXA81sXz8HRMwfq4EBvgUozCyzEar8PGuB5jsAib4lZshtsxDvdic/wYWyExhZ2JtbA9tsCO2AM7YS/sonrEAdM9GPPeDMeNfZjnV/nypM7Hv2AEPo0xuAXb4zMYj89iT3weh+ELOAZfxIn4EqbgX3E2vozLcBtehq/hRnwDt+IOfAF3YjHuwoNYgu/jbizFPXgC9+L3uB/ra1yLhvgeRmMpxuOHOAQ/wqH4Meo6p/szlIeX69wklcNkjMUp2ALPwTY4FTviNOf1RfdacLQ=
*/