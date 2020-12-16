
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
ui1tpONoE22mLXQ8nUAn0la6HZ1EJ9MptI2206l0e9pBO2kXnUan0x3oDDqT7kh3ojvTXeiuNEN3o1naTXtojuZpL+2j/bRAd6ezaJEO0EFaokN0D1qmHq3QYTqbzqFz6Tw6n+5J96J7033ovnQ/uj89gB5ID6IH00PoofQwejg9gh5Jj6JH02PosfQ4ejw9gZ5IT6In01PoqfQ0ejo9g55Jz6Jn03PoufQ8ej69gF5IL6IX00vopfQyejm9gl5Jr6JX02votfQ6ej29gd5Ib6I301vorfQ2eju9g95J76J303vovfQ+ej99gD5IH6IP00foo/Qx+jh9gj5Jn6JP02fos/Q5+jx9gb5IX6Iv01foq/Q1+jp9g75J36Jv03fou/Q9+j79gH5IP6If00/op/Qz+jn9gn5Jv6Jf02/ot/Q7+j39gf5If6I/01/or/Q3+jv9g/5J/6J/03/ov3jItxBbmC3CFmUa05nBTGYxmzmMMMoYc9libHG2BFuSLcWWZsuwZdlybHm2AluRrcRWZquwVdlq7D9sdbYGW5OtxdZm67B12XpsfbYB25BtxDZmm7ARrJ41sJFsFBvNxrBN2Vi2GducbcG2ZFuxrdk2bFvWyMaxJtbMWth4NoFNZK1sOzaJTWZTWBtrZ1PZ9qyDdbIuNo1NZzuwGWwm25HtxHZmu7BdWYbtxrKsm/WwHMuzXtbH+lmB7c5msSIbYIOsxIbYHqzMPFZhw2w2m8PmsnlsPtuT7cX2Zvuwfdl+bH92ADuQHcQOZoewQ9lh7HB2BDuSHcWOZsewY9lx7Hh2AjuRncROZqewU9lp7HR2BjuTncXOZuewc9l57Hx2AbuQXcQuZpewS9ll7HJ2BbuSXcWuZtewa9l17Hp2A7uR3cRuZrewW9lt7HZ2B7uT3cXuZvewe9l97H72AHuQPcQeZo+wR9lj7HH2BHuSPcWeZs+wZ9lz7Hn2AnuRvcReZq+wV9lr7HX2BnuTvcXeZu+wd9l77H32AfuQfcQ+Zp+wT9ln7HP2BfuSfcW+Zt+wb9l37Hv2A/uR/cR+Zr+wX9lv7Hf2B/uT/cX+Zv+wf/GIdyF3YXcRd1FXc3XXcE3Xcm3XcYlLXea67mLu4u4S7pLuUu7S7jLusu5y7vLuCu6K7kruyu4q7qruau5/3NXdNdw13bXctd113HXd9dz13Q3cDd2N3I3dTdwRbr3b4I50R7mj3THupu5YdzN3c3cLd0t3K3drdxt3W7fRHec2uc1uizveneBOdFvd7dxJ7mR3itvmtrtT3e3dDrfT7XKnudPdHdwZ7kx3R3cnd2d3F3dXN+Pu5mbdbrfHzbl5t9ftc/vdgru7O8stugPuoFtyh9w93LLruRV32J3tznHnuvPc+e6e7l7u3u4+7r7ufu7+7gHuge5B7sHuIe6h7mHu4e4R7pHuUe7R7jHuse5x7vHuCe6J7knuye4p7qnuae7p7hnume5Z7tnuOe657nnu+e4F7oXuRe7F7iXupe5l7uXuFe6V7lXu1e417rXude717g3uje5N7s3uLe6t7m3u7e4d7p3uXe7d7j3uve597v3uA+6D7kPuw+4j7qPuY+7j7hPuk+5T7tNusdDdU543VClNac5tnCsW6xqbmlo6OzPNLZ1NHa1Tu1rb2zK95Xw+DS9U0tDB/Jy6xpbOTHchU+jLZ/KDVflVqKe7R6R7u+sbxiqQDIg5cnmezvd0J3nJtFJ5Sa2sNFQplAa9atrLVyLRmVn5eRGG/CI2PDinnB2KSU50tubayx3ZQVTrGywJwFICCRNV6fxgpdBbyJeb+kuFnrCYiqO0iqpCPLW8Jxf1wlJt9ZnGtpngBulxrV2Zzq4=
*/