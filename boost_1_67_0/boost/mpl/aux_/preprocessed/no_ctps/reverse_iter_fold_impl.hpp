
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/reverse_iter_fold_impl.hpp" header
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
+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
*/