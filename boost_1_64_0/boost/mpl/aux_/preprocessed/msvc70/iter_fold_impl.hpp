
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
hx0r+lW2MrafpY+Rfmf2Htv+NN5jXXYc0lo/3t6k3Z+Gep7+u2x7g3fZiPNlXoaMV5uRm7V7Uik7KyfHarO7p1SXOiaJWwJbA/JL8vFaC1XWZyzOzy1V112cpuwfd4rfvbU2VmJFtHFugTInWvqo9z6XUpfZUpeZyArqkniBUpeSnLz8edbMnDJ78cyZWk2c9YjwU497ycNrvrvM1eZrt+jsreOPsgbpLBRVdUyO1vfJW7R7RtExO6s0P8f5eCsqLsoJKr7s4+7esQmNYazzmaY8I/SxKNFtnJm9Jbbbg9yGXpYLlbVe86w5c5wqBdD26OMTS9FY9MsutfjGT2Vq429raVvs6KiD69t0C6UPcK3jdGs17oJryUAX91ApdZoqdZqE3KHVKUGpU7FtobNK/vtBTTaWehrWS9YbVfX30rO8rbOQBnXQE9aDq9DTpupZUsByyHTXgOLBwpvn9pX+ql9PVXSmPmGeeKxIn/58wqA/76eOOT73XGQ7fX9eje6VfT26U+cya6ld6dH++7NP/wmoL7tj7ESnTWLPjXANOlUrOmGHzNJ5OTxyPWNArB+bFl6kH8ti1TWKRcej0Q47u8e3KgNblvJ+kZXrWYv2HepZijaSxrOGcdbFXnEnlTFOpU5Kn/4auYe6RfZ371Gr2DmwfbM/7a+v1w2MpfTT0kDGkaZe96LdvV9zazQuVu51Lb290KZlIc8/2fu0vVOhRtKHtPIfoPzEi117kiaNGJGSnp6ZnJI+YuKYtIwxE8ZrrcZuqAUFFv97lDqed1LWFsry3f/0ecpKq6ksW1lpXgDluPrsLp+9ULW2ttlLvPacje6gr3MVetg8eqSP76u9KKWMyHBX1r8OahkbO+jr+rC2oZphGbZimyOa2X8ZrnrKM9u9nvkAStVymFlWRD/23le4S0e9Lseo7wZjXTB48Hq47M27g9hb9p79L66vbBzbE3xsTG2t0/z/th5zba27XGeYdv6bxaXZP+365A99dn1f75NHvig0W3f53KyjnGCROROwC5LoM0f7GZnj/CyMg89DZzqZpwCGGaR7QeY0vwgvhVuVdGmSLtog3UNS3gbYGj6spLNJuliDdI9JusdhB7hJSbehhvLWSbr7pbz1SrpKSRdjkO4mSXczbAtXqnt01pDudkl3h6RbpaSLjTdPt0bS3S3p7lXtKemiDNItk3TXwxbwBtWe8ebtbpd0ZdLu81V7xpu3+7XS7ouk3ctVu8Sbt0O+lDdb2mGOGvvQw7zdiyRdsbS7TUmX2MO8vFxJZ5XyZirpZvQwb4d0Za/UtlDdK3VVDemmSjp3TJ3az2pIN13SZUq6LNWePczbfbykmyDtnqbas6d5uydKuiRp9xGqPXuat/tIafdR0u5jVLv0NG+Hi6W8S6QdBijpKnqat/tgZe/ZDnCIGpNYQ3kJkq6vlNdPHc96mbdDe0nXQdohVt0j1zQdlHRdJV13tZ/VkK6npOsl6fqo9uxl3u7Rkq6NtHtb1Z69zNv9I0n3V2n3j1V79jJv90+l3Y9Jux9X7dLbvB3el/I+kHY4pI5nvc3b/U+S7oi0+4dKuqU1lHdA0r0r5b2njme9zdthl6SrlHb4jZLuQA3p9ki6NyTdm2o/62Oe7m1Jt0/S7Vft2ce83XdIupel3XdCV0xymqTbiiT6xCSvlBiwW2EUvA22g7fDOPgr6OhzsB+8EybC1bAA3gXL4Rp4I7wb3gzvgQ/AtfA5eB/cDNe5Y/7kmxqcLXqpMX8Pil4PiV4bRK9HYA/4KOwFN8Jh8DGYBB+Hk+EmmAOfhDPhU9DdbheY2z9OYtI6w7awK3TaUb5jgbcM7HiJ6JsEO8PhcBBMhikwBaY=
*/