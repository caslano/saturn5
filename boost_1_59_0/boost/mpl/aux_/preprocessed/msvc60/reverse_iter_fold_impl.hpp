
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

template< long N >
struct reverse_iter_fold_chunk;

template<> struct reverse_iter_fold_chunk<0>
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct reverse_iter_fold_chunk<1>
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
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        

        typedef fwd_state1 bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        typedef bkwd_state0 state;
        typedef iter1 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct reverse_iter_fold_chunk<2>
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct reverse_iter_fold_chunk<3>
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct reverse_iter_fold_chunk<4>
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template< long N >
struct reverse_iter_fold_chunk
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
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_step;

template<
      typename Last
    , typename State
    >
struct reverse_iter_fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct reverse_iter_fold_chunk< -1 >
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
            , reverse_iter_fold_null_step< Last,State >
            , reverse_iter_fold_step< First,Last,State,BackwardOp,ForwardOp >
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_step
{
    typedef reverse_iter_fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
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
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl
    : reverse_iter_fold_chunk<N>
        ::template result_< First,Last,State,BackwardOp,ForwardOp >
{
};

}}}

/* reverse_iter_fold_impl.hpp
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
*/