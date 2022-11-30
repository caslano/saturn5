
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

template< int N >
struct iter_fold_chunk;

template<> struct iter_fold_chunk<0>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef state0 state;
        typedef iter0 iterator;
    };
};

template<> struct iter_fold_chunk<1>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        

        typedef state1 state;
        typedef iter1 iterator;
    };
};

template<> struct iter_fold_chunk<2>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
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
};

template<> struct iter_fold_chunk<3>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
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
};

template<> struct iter_fold_chunk<4>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
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
};

template< int N >
struct iter_fold_chunk
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
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
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_step;

template<
      typename Last
    , typename State
    >
struct iter_fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct iter_fold_chunk< -1 >
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef typename if_<
              typename is_same< First,Last >::type
            , iter_fold_null_step< Last,State >
            , iter_fold_step< First,Last,State,ForwardOp >
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_step
{
    typedef iter_fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , ForwardOp
        > chunk_;

    typedef typename chunk_::state state;
    typedef typename chunk_::iterator iterator;
};

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl
    : iter_fold_chunk<N>
        ::template result_< First,Last,State,ForwardOp >
{
};

}}}

/* iter_fold_impl.hpp
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
*/