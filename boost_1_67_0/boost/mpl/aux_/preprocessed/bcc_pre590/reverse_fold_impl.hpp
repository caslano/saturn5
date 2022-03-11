
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