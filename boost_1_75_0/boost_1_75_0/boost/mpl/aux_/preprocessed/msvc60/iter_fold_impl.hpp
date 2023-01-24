
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/iter_fold_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

/// forward declaration

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl;

template< int N >
struct iter_fold_chunk;

template<> struct iter_fold_chunk<0>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef state0 state;
        typedef iter0 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct iter_fold_chunk<1>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        

        typedef state1 state;
        typedef iter1 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct iter_fold_chunk<2>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
        typedef typename mpl::next<iter1>::type iter2;
        

        typedef state2 state;
        typedef iter2 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct iter_fold_chunk<3>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp,state2,iter2 >::type state3;
        typedef typename mpl::next<iter2>::type iter3;
        

        typedef state3 state;
        typedef iter3 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct iter_fold_chunk<4>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp,state2,iter2 >::type state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp,state3,iter3 >::type state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef state4 state;
        typedef iter4 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template< int N >
struct iter_fold_chunk
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef iter_fold_impl<
              4
            , First
            , Last
            , State
            , ForwardOp
            > chunk_;

        typedef iter_fold_impl<
              ( (N - 4) < 0 ? 0 : N - 4 )
            , typename chunk_::iterator
            , Last
            , typename chunk_::state
            , ForwardOp
            > res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_step;

template<
      typename Last
    , typename State
    >
struct iter_fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct iter_fold_chunk< -1 >
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef typename if_<
              typename is_same< First,Last >::type
            , iter_fold_null_step< Last,State >
            , iter_fold_step< First,Last,State,ForwardOp >
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_step
{
    typedef iter_fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , ForwardOp
        > chunk_;

    typedef typename chunk_::state state;
    typedef typename chunk_::iterator iterator;
};

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl
    : iter_fold_chunk<N>
        ::template result_< First,Last,State,ForwardOp >
{
};

}}}

/* iter_fold_impl.hpp
y+jG9ndmwLzTN4I7Uw0H/CVDIXLHD5eke873OTk6TJIw9BIZvTLxF/KniuG2mxJTSZhCmAetkBtzd6NMTR5eZfzrmIs6NlyRyrM9Z/3Lec1vALf4jwFKpbRAjKv18jXHMNeJh06Nl5cgvKB17VWME0QhODuU2r6r6uG7d+JVpZOGlGua+W2oh8gPAUWFxmWPEfAKwbCb+r0SFZAVrpmknzKKVM7ZOZl27e+fAeru5TgdfRSiQqoipbdR0UJcst4JedovlhR9Sn2stz4TL4CqW6C2DT+zbnIyUKyWR5e3yCTPcZT7KNOd0Z1x4sI1YmLdZq/RiDv11M06EPz+IkSG4p4sxUcjm+wrGbynaPUiPPaKuMBFcRFX5OP+b0ffFzpS8RrMTD7leMZu2pMez/DcYuOFUPaghVi3t3tBLizF62Ppk4OA+yDwu7c/8rwg2XVLU8e8vg+ULOI1X3WJVh2qs9fd12QO8zXpMmAYRL+pmFkQWLDGMsLGK//I8D26W5hLO/N2Ys62mfimwr7biD0FxUQcJbz5gvTcpTXqgipXt6lrRebIsV7D5z0Dt0HWQDdvwF1P/pjjbcXxvqZ/rmaS5/7Oj+ivZ25C+5qIJAzgR/7JuHrJ0dh6+g1tCbzUl/NxZ72JyqZhBz2E+VWdpd8CerRn5uuJPnP4QldWht9TnJPb2NEPTSYX/3BV1QpVIrT1H2ouu7FlRj+U6Dg/
*/