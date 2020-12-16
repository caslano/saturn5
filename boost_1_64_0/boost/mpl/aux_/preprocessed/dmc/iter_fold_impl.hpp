
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 0,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef state0 state;
    typedef iter0 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 1,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    

    typedef state1 state;
    typedef iter1 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 2,First,Last,State,ForwardOp >
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 3,First,Last,State,ForwardOp >
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 4,First,Last,State,ForwardOp >
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

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< -1,First,Last,State,ForwardOp >
    : iter_fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , ForwardOp
        >
{
};

template<
      typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< -1,Last,Last,State,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* iter_fold_impl.hpp
EV4L34UJ8CgcCj+G18Hfw2HwJBwOz8kadu1ae730oyNgFLwRXgJHwa4wCfaCo+FgOAYOh2PhSJgMp8CbYDYcB+fB8fBOmALvghPgSjgRboY/l371ZvgonAR3wlvhfpgu/WsGrIJT4IcwC34Bp8FaOBOegzmwGccgD0ZA196m6B/JmJKMNXGcnMc4XI7TSVnDXQMjZQ18DPwr7Cxr4XvLWvh4WQv/E1kL/3NZCz9L1sLPhd/CRbImfrmsib9H1sRvlTXxT8ua+Ofhj/DzVRgK34Nh8DA8H34AL4CnYBM5XhfBphBxHq+LYTxsBofCFnAUjIDJsBXMgJFyXNrABTDKfb1n3EnuyxTX+9VSP2tkjftaGAs3wS7wYdgHlsma961wENwGp8HtMBc+CYvgU3A+3Anvhk/DB+Ez8BFYDvfA5+Cb8Hn4CXwRnq9dh2E0fBleDSvgGLgb/gy+AnPhq3AW3AMXwtfgYvg6XA7fgBtgpWYfvgkfhm/BcrgXvgL3wbfg2/Bd+Ev4HnwXHoUH4KfQ+c4ceAhq7fA92AJWQX2vhzzPzFfcx+VLPRdJ+5sDO8DbYDd4OxwA58Ib4B3wFjgPOuB8eDu8070nSMaLOGZiz7gn6IjY+0CO62/gJfAY7As/lOP5ERwIfyt2j8PR8GM4Dv5O/KiGU+CncAH8DK6CJ+Aa+AdXvxki4z6wQvxqCdeJXzeLX5NgJ3gr7AHTYC+YDq+FGXAonAxT4RQ5HzNhJsyCOXAqLIDTpb3NgPfCmfBhmCPnYR7cBTmXZY+djP/IuFCqxx67GNlj1wF2hZfAnrAj7AvjYHndHgyfey8i17OeHMlESpGdSCVyHDmLxFeQ5v5QS8y+Pvym3Jdxf2i99makome3P6OY/225PzRo+zRU+zPKyd+4R+Pg/aFB36dhH9cPm/eH+rVHI3IDx2RDaEB7Nc5VoFvrf6y/lA0N36fh2BDq116NUtKFT6AeobcYgEc2hDZoz8bZDaFB3beRnhQa8N6N+sQEjJ5IXW0MNe3fGLwxNKC4gJNIX4JsQ/YjNUjEJto3kow4kHVIOXIQqUGaPBAa0hMZjmQjS5DtyH7kNNJ1M/9DspEtyEEkZAvHEElHliO7kONIkwf5HUlFSpAypBKpRkIeCg2JQxIeatwT0vhp/DR+Gj+Nn8ZP46fx0/hp/DR+Gj+Nn8bP9/n5Ifb/ZxUXZuVpAQAauP+/s7yjL7Wzvl8/MTUlccz4kWPHyPZ/fe9/uSKN7PzX3+fXtKX7fX6FNnv2S9bJvk5TRoHtLd/b2X5v+QnF+wde0eLDquxqm7D9sOtaA/i5Ys9+imLP/niUylX2fO4hsNiz7MM+aPPeQofKXoD72td5qdc+ij37r1KvVUq7rP70w64x/z2h1n2dr5N/LfnLvk6zDT/yd9XjngD2dbr8SVK8r69SW+u63saf8f77s7ht4P4cDLPu9XyLL8nrXXst618/n/ux1zTpfKv9vXwp0e3Xvz6ua2Nv/7RzTVLgaw/Vaxjt1orarXW1W4tqt4bUbi2t3drewNec2q2x7dFO+33111O/i7lqfczYyCvmbts9+gu7NaF2a4Ht1+rqaznW6WtDmBszr6mINq5tlHRtFelijWtmvKRrb1xTaWsXGtfWSLrWPvKrlXQdvaZD1tunizGumZF0MT7yK7FLJ/mtO0+bjGdOAGFuw/+5QsM84QDT3KBlXpA5QdN8oHEeUOb9/JvzC5FYbDLHx/weviBJyDbrXB7zeOb5uxR93s40ZyfzdPr8nNd5uXTEOg/nnnuLlTk28/ya/dxabYLdXJr9PNpxxDBvJnNm1vmy8qGGOTL7+THbubByyPyXXzHLPOe8BiPMbxk=
*/