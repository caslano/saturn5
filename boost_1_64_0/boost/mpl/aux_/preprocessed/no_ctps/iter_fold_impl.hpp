
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
BnM0BzQK3qs5oWfhLvAzzQ11wIhc2AeOgVvBsXAsHAf3heNhDdwVHgt3gxfCPHgjnACfgLvDN+Ee8AeYDztRt4lwXbgXTIMF8DY6AvNAbX77sb3zP5fP/nPmgBrmxJ8Haqxftbmgy+e2Ph+UPm/V5oTSj/1/zQu151uJf8TcUPD7iH/w3FBg4R8/P5TI3NCyecTOIl2PZa1gZMqx7vyQm/7c9Fc9/5dWV6/y87/1bb9Caw2jTOsZWI+bPGKGVqipCa4BOJW/52xh+zvrNtRUBZeOCs4hrEjjEm5bA3AXZHVjDZjmjNAz7cSJhcHP5K0sDZNq2n621nMUN/14zy3xngfijbPjjZuTHx87Pw/EG3/He76K9xwV7/kt3vNYvOeu+M+T+wWfKxrfmZp3WMra1501dssBM9YMpMR97tK4X8dUxzq/Q/S4v1rj5Vq4IZwBt4KHwuHwcDhKzwWbWHrO5N2HM9t+j8kcL5m+MnOMxPhIY6OoMZH8YI4+MMexjscY46TsiX4kD1nqMIZ5GDHHLgXyYw1HNE5hjNL2uGQq4jQWyUL65qBX4w1zjKHxRdS4oiXH9DE5jyHMsYPGDeaYwT5WMMcJGhfEHwc0wAzodM+33+/Ne/1gxLivR+7pBWe69243uclNbvqdvTuBj+HsAzi+ESF1BiFucZUqEhG3EsRZIsQRR0WODSHHNocmdcXRFkWjVB1RtKp1VLUodWtRLa201dJWK9QRdTSto6i27292/7tmN7OyUfpeO58+/ZrN7jzPPPPM7Ow8/3nGOTkn5+ScnNN/3vRP/f6PSou/L7//jR2u9VXP9mfB4XExkcowubXk74W1/i4DwCrLCPehT3JnIX6jyx9V41ObnyPgrizD8ncZI5lMUuUawh/ldJY+5yzpF5/pSp+zGO3J62WM1xAsmSQnmsbg9OY9dvucyR90AeWVz5qe6d/X0/jvOj2D/Px08lopy2tNWplfu1nO8lpL82ub7rzWzPyaz53XmphfK3LnNbpqKAevpZc1v9b8rmM/U3vSF86ySDHyd09U+sYNMl9RxrWMNs5LX7kPn09ONfb3Z0usvhLsHxNOj78+itddy7SlEIeo4xn8bban1Avvv8r7DSw/OY6nQMiYh+rxF7PkHoPnSCVJU0hxlD+ggnq7mLYsZTCNlKpcS3IgNsA0LqisHztAfLLUibymHhtzNHmGR0mdqMbKLGuqEzTGD8TqZLlVUWIKlKoz1sER1v+Qq6kuQ5Tya9Qh6241NmlbWYGicm3LzXxvjNX6y30h9xAvoh579aLkdUDqei9pDOXSeVnlxcD2lvou8H0oyvwNdZuhXgLIN4eUqtSTl7QN1X0fymiiMi6pVZxIPzftutFVtCqv0hTvqV7M+QQUkfG/JB7lMKZSfg/rfJRrjMZ8xhUgH3N7k/owzuew3tHMcywzzk9l/pXG/N2QZqyvUFa0KmV6mc91r0QZVM/7r6VsM+PIuFwxTTKthxIfMlHeF8lylXmfyqZ5A/PqNpAt6zqUPxr7bHEs71lWxWpdk/5uGyiBabLONvdHWe8TvKbeH3rKGP2HpI0ekOciDK9mLJ/VF4YjxwB1jJjtvVl7Ja92kldrGft5eHVVXqZLy3famgNjYZdV5ZnMp6Ns2ltD97zPQylOvutN+ZKH6TDH8dLhdm2gQEmST2PJ56rk4yXbuhyOp86zLPncadMeDuShbsNXzftuSpzVvhybkGA5HvryoVzSdOZDatw5Huby3jJkmCR1dUO+I+L0iSNk37QaK3ykjMNfRuqrNGkHbcLX2zxGb+/gzkEhIT3DQvr17R7UNf+xwq3H513Hshif1/p76aG84yIHEpQQbCdPy5DIDuQ=
*/