
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