
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
68m/QgncLwaaYJRfXtvGMicimfM0rF5abXlLrcchWuaCojIJ6mHJsAx3xjNVvw8szKrKMDVhFlVbyqzLomF3xVu95G6WgNIYCucn4LiWCAjwQ+ZHnFJYbK7PjQ8fs5IjZ4e5+SQeBeLlirTXHATKEZmLgfzL4You1KeoW5m8rnSgTudMr9KuyqLpO7dFiw/ZiTdpJSLu85F+Y2O+xPj71bQXlUNnP/w9L0h/wOOlJa0Dg+rm/CYf221+zW68Ad48D1OYPyO301GfNuvA+yE7Vm5bF4AluE+ufsXTH/n+eqNBs3AxFAnw9uwn0BR2//gPpAN+Pjb7Gna6mLpcQ8yfOslvutu1HjojJmlQXqsGEmDDISH5p2eiXLz9z39HOi83uOSEATwP97e5shTa143OuFBNm7P+MCEO9cQCnjywb63n6DlH6SHuH3+IAlL8m5DEj5LXpjeBLQEqfqFBLYf2hxpgzJW/PPgf/H79FsWb352hfi3kI3mHSkYl04P93vdXWN2jDv9l9GZBtQDdnzaFw+sCp5WmfVVLTc8+IpzaSAVzGnASquACb9oBxId0QEL84+jf/TKn2JXChx1AwEhk5Uk0eHB1TvuUXa92eHpaWSmVDmsDAn2PkF8w0Vvhk0Uu98weub4u3LPZRjndA/6u8ynT+Y9y/1PnjP/16rnI38caVuZfnaz+M8mm6yHp1VjPqKTz1TBw4MryHUs9
*/