
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "reverse_fold_impl.hpp" header
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