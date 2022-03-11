
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