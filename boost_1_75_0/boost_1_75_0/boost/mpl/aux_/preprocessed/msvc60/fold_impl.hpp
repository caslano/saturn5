
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/fold_impl.hpp" header
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
struct fold_impl;

template< int N >
struct fold_chunk;

template<> struct fold_chunk<0>
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

template<> struct fold_chunk<1>
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
        typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
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

template<> struct fold_chunk<2>
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
        typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, state1, typename deref<iter1>::type >::type state2;
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

template<> struct fold_chunk<3>
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
        typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, state1, typename deref<iter1>::type >::type state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, state2, typename deref<iter2>::type >::type state3;
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

template<> struct fold_chunk<4>
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
        typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, state1, typename deref<iter1>::type >::type state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, state2, typename deref<iter2>::type >::type state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp, state3, typename deref<iter3>::type >::type state4;
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
struct fold_chunk
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef fold_impl<
              4
            , First
            , Last
            , State
            , ForwardOp
            > chunk_;

        typedef fold_impl<
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
struct fold_step;

template<
      typename Last
    , typename State
    >
struct fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct fold_chunk< -1 >
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
            , fold_null_step< Last,State >
            , fold_step< First,Last,State,ForwardOp >
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
struct fold_step
{
    typedef fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State, typename deref<First>::type>::type
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
struct fold_impl
    : fold_chunk<N>
        ::template result_< First,Last,State,ForwardOp >
{
};

}}}

/* fold_impl.hpp
EIWKHtyK3azewHpIbf7xcK+y39sFeaPppGUnjhDJ4tYnNcrIMX3fVXf3Vbf++PSmFQ44hgzLmEgOpy4f/Vv79uAd8ISb45lavbvCDd7DetODj7taXiffaF07n/Pb7cKr3JTO57EeoYDKG+sy5C4VFs9Mn139PWzu38M7wW3Tx2KEv8315Pn27fWin6qH2JZcRuuC6tJBRtWFevNfRbpRpRyWFMmjHbkcguldSB83FQ2a064KHK4Fl4/8YugeP1Mov7O66NmMWha+X5VzYjubICsAFgZcc3xc/HRBk5c4UzLE/f4b32+7yM+/dlSid30zixJnS3EgytKg7xrt6puU0fAG0UMogvHJUhAupmaR8IWHOZtO7LdfoaWoO6/M8BW3LGtB0EYfqx3K/rWCeUQIGIKeWmJU4uITOSORYTSo00B8SXIaCpmyZvSvx56vW/CWnZf+80rlmeGN5K3zOqnJfUF6XzcAQxdKAHl18MHIdijZEdch9w+hKKOXrM0T/aYUk70z5d9WDFT62rYzNgHBEJELlJkt/J6QDYQSqQcmk3ZcrFYPlL8yvhE3py3bq3onJAZvHLKdsKFfgL0lF78FYr6SPiOIYM8ESgcmNLbNE54ipQZEtSu9YEPwn6WfmfzjoFFQYp48CBsR5vbt5WNlMWG4fcYJ7bMgQL/UaY7v1OjU4pngTS8f+Mxkv4BatVR4qXvdga0qJgFDNeiL
*/