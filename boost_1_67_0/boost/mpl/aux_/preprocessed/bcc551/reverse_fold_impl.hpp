
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