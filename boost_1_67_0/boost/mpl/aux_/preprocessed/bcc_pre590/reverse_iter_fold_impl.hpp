
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "reverse_iter_fold_impl.hpp" header
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
struct reverse_iter_fold_impl;

template< long N >
struct reverse_iter_fold_chunk;

template<> struct reverse_iter_fold_chunk<0>
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

template<> struct reverse_iter_fold_chunk<1>
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
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        

        typedef fwd_state1 bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        typedef bkwd_state0 state;
        typedef iter1 iterator;
    };
};

template<> struct reverse_iter_fold_chunk<2>
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
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        

        typedef fwd_state2 bkwd_state2;
        typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter2 iterator;
    };
};

template<> struct reverse_iter_fold_chunk<3>
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
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        

        typedef fwd_state3 bkwd_state3;
        typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
        typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter3 iterator;
    };
};

template<> struct reverse_iter_fold_chunk<4>
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
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp,fwd_state3,iter3 >::type fwd_state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef fwd_state4 bkwd_state4;
        typedef typename apply2< BackwardOp,bkwd_state4,iter3 >::type bkwd_state3;
        typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
        typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter4 iterator;
    };
};

template< long N >
struct reverse_iter_fold_chunk
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
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp,fwd_state3,iter3 >::type fwd_state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef reverse_iter_fold_impl<
              ( (N - 4) < 0 ? 0 : N - 4 )
            , iter4
            , Last
            , fwd_state4
            , BackwardOp
            , ForwardOp
            > nested_chunk;

        typedef typename nested_chunk::state bkwd_state4;
        typedef typename apply2< BackwardOp,bkwd_state4,iter3 >::type bkwd_state3;
        typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
        typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        

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
struct reverse_iter_fold_step;

template<
      typename Last
    , typename State
    >
struct reverse_iter_fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct reverse_iter_fold_chunk< -1 >
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
            , reverse_iter_fold_null_step< Last,State >
            , reverse_iter_fold_step< First,Last,State,BackwardOp,ForwardOp >
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
struct reverse_iter_fold_step
{
    typedef reverse_iter_fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , First
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
struct reverse_iter_fold_impl
    : reverse_iter_fold_chunk<N>
        ::template result_< First,Last,State,BackwardOp,ForwardOp >
{
};

}}}

/* reverse_iter_fold_impl.hpp
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
*/