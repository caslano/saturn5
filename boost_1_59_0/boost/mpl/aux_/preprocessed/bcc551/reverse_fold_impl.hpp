
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