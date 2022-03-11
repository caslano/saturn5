
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