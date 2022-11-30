
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