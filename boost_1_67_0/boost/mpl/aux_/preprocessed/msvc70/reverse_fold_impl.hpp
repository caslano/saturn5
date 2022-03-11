
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