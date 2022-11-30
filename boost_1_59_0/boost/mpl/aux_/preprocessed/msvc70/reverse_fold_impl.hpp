
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