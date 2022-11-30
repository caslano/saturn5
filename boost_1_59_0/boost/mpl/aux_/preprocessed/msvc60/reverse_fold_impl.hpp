
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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
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
*/