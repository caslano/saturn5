
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