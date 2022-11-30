
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