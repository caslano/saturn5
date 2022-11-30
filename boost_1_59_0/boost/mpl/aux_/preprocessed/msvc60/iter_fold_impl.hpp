
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

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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