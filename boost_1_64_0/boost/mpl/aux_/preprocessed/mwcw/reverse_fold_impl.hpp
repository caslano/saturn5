
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
5Ba3uMUtbnHL+lraf/4/y9hzsls9/7+Hxv6LfrLG/pZJ/9A94BNYYZyfNLGvtQFTQKfbz4HXCidNbDg/uOF8ThbnLR+Cz/Ah5Dr4ELrNCvgQLOVm+BC0p5aD3YRgu2pI0z4EbAfqHN8xvO0kw7Ya3Cy7RQ52U4Pt0sHR2bX9Kd20N95DsvsAYvlTkor9di2b68yfUqe6vS9/ytuqW8LpqlvgM1L15E/xtmP9zLmtWbnTCk618zxQ1++QCzjOseoXug8Ts7xpW1DfL+4UuqeF+v6MhvZxn6hx7d82cw60Oa9X+8cE1X1I55D9V+Tr8hj3je3navYehi3wc5l1O1Dz4VepX79Wv9Ya/Vo4KXb9at0fw+mvLtTLOverVQ+o/jbvD723fg3BaM5PnRn5Xlrtz0vb/v6u8H685vuFwvu1nPxOzc99Ed6f5uTndPY3pvj9aa8u/WzynzMrMmeUvfTU+Td/+pqj30z+Lv1v0nM6LcTftaP8VvHQq2NbL6GFekkt1EttgV6qR/8X4EPS07yrRnqn6jhfxw8E2dEzHL7vYKer9F7R8Rs6fju0/foulZntCGOnVMeBeaBqx67SM+eB7qJ27ArjYSLcGe5m5onXdVc1Uf+LdXyJjr/W8Sx0MvDRFCPzkMWWLGl6nhl+P9Pn5/f3VX/dSb4+27/n7NvzyKe3MMR39wJi++zGGL66+UioPy4DMf1wB1rvlb+tItjHZvrXQn1rAZ+aDzH8aOF8aAGfWWUEH5lPvrBl9GUt4vknzhOPpCDjkFlIBVL1j+sbc4tb3LLuSwzG/1Oy9rWG/62L/Vtj8yndPf7fm91iEDd248NtGx9u7/Vw8ztEl68/3G+aB5EaRHHL0JilYpXh5sNHjk0uRzwHh53/rvijGXsM/p1Thiw8pPVz3OMRxRCJHZpxw9CYYbg4YbgYYfRxQTsm6Ba3uMUtbnGLW9ziFre4Zf0onZCC9h7/J6fn5mdmpedn79vqeQC7KHZ/YB/L1z6lwbKiaXauv2lGrr9kh3h73YxA7NqsY5OxQjNGnGTvCQy3hb2hFetLm+K3bdoNivfFG0aN2N+52KeeA/1xuR6ejq2K/VmpsbZQPjbr2GedMHIFZu/tj236Y37kSaDu9bkbrp0avE9AKRegDY32CfApPj5Abe8FX6eeCdPCtL1oSp4dhx3XwrbTFuXwR0735YCgvIqZUyYH2r9BJ+pXNMV//GBIW5OpZxJ136cDdq26Kr/dUt5XQCIFf6V5s22/Sv2nPIUBG3nYeJBzc6c39Ndi5dnz6bhSunR9oP8OVv/1VPz9au2xcLli2OWnNeq/iGs2vE3Ei9Vvukf8RpqMZys2HOg3xXqJNTXf9xY+duvsSwsf43TyRTXfN9Zc35KTj+pkf4y28uiub11/+T2Z7yauvXqPTb0PNN83pliinkd8BxCvGUtUbh/ruBP0ws4QPXLo6FmjZxB6/pwh8dCjNQrbwsGwJxwOk+FIeDgcBYdrLUIGPBpOgsfAPJgHz4cFcC4shNdCH7wHToXPwyJYC6fBP+F02J06FCuXx+lwb3gGPBzOgkOVy2OicnnkwQrresrdUQEXwIeUu+NVeDP8FC60rgNvhf8oh0cH2n873A7eBfeAd8Pe8B479tpBzyc9t+gvfx/3Vn/dr/56QP31EBwEH4PHKGfN8fAJ5UJ5Ep4Lq+E1ymFznXLY3AufVf88Bz9Q7ppV8AXlQHkJxitnTRJ8BR6m3DUnKGdNLnwDToFvwWL4LjwLvqf++gDeDD+E98OPYBX8WDlOauFz8BP4FvwUfgI/h6vgF3BD+uNLuBNcCXeH38JekDorB46eT3pueUNy4PTUnvq94I5wL3gA3Bs=
*/