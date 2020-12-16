
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "fold_impl.hpp" header
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 0,First,Last,State,ForwardOp >
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
struct fold_impl< 1,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
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
struct fold_impl< 2,First,Last,State,ForwardOp >
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 3,First,Last,State,ForwardOp >
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 4,First,Last,State,ForwardOp >
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

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< -1,First,Last,State,ForwardOp >
    : fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State, typename deref<First>::type>::type
        , ForwardOp
        >
{
};

template<
      typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< -1,Last,Last,State,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* fold_impl.hpp
f6Buv9/SOi24IaxOJc/ZGajS6vt/LPV0IKye2IepHzmni1wzc55ol7kzL08k0tYB87IAIUnmwSsr88JT8nAKhoE2Hv1eMbeq51g3IgpsV9pz325Iqzjb+dzY3rtPT8vJGZ+Gk/kZaUVpjnGMZRQ+/2UZ2XMx577q/mYq4Dbq6q3gEknoxrB8iq5Mz8nOzCuq2B7Q/hhrfh3PJ5rjO6KrHMsWmr2q1Iw8xxx/kYx5JiF7jn8lrpl5L681kfqRa/lFWZlTtewSo5Rd8yrKbl9Y2e23y878dhfblyP7ZmuZ629PfXrQpU/tvruxrl7z3u+y23I2v++u2P9iHHsYb2aJiZm6JFIv33ijWw/3WqXfj2SfXrfKrbcfW+XeC/grv59aP2wP6SSt4FL2i5kIRzfE95vt9iKnXFKNLLGv78PXhN5jVGQ+/2TSxd8buuVs3DxyD6IB7km8xZZz6i/YZzVrnKj7rG59WHqyRvAJ96D+AjaSsnLLYFQINv/TK+RoHuN6rp7z/INj/KnNPfkJU/NznfvviUHcm8/5op0X7V+MpwAPwLO57tvj3JNnvzBx5BZgSGLfsdsrx8iwZ8xsn1778U2Q0ZyT1d5M/VtZj97P8E1d7+U9xzZ0l3PXU7SAfs99nyaWlnPZbR7lnJmXHsvez7+zbJ3tNImbjrM5DyoEm0L2OqvdspuHNZS7Q4ztw8yB1oQ/r+Gzmcq1g52nXMf6ohghN1UyTp3MPEIODCG2Ti7Wa7q+pk4+vqHJO5+luJ8n73DqWraNYkf72ePxjGeX8xkPZS7j77AONW1sd5Q2loS2sfNUbWO1b3e0sch1bOX9h3B/G2lXa+z9hi+l7csY4NjzmXi7+5nQ6tvdz4TK+X07v89gfH8MWy8dYBuYR11VinACyjDpDrsNTJODWr9Anzqfx+VkTsvMsevYfXaLdcyzWwUVz/YP2c/2XX1u5WncX6fMcxBOhMzllNmMkYWFxZlTU802fyz7mWyf9nzA0T4rx0iOrYn4npdLGW0d5JKxVUuN/DDqhRDCKWjnq9faMhZm5mSmA8ZkXAx6IdY5jT3Ou+t6BWXqzXLrLnE1xP0qk+PwY2x1beav9e15XWeuRWudHm4fmLb87ox4z5Pr8aJq06vnSK8Iv8wIy9tOpjmXac6SckHexmma6NEZqUX54/NiaQsV5Sx7WePz7HI2+2PZeZXlXGSZ74jbfX4lm/2/NmTagSD9ebGRQ+/72d2fXTq5Kye1ddlujkZoITr5LpOPwskO5515xblVtJlEV15OQRyFky33OoNpNWRa9RFa4ksbj7SmpeUUo83FnV7YeQZXnTU/IzKvrWTPwpW+mSbFnC7aPvNpl2kp0zmc6ch9Z8ja0J0OjuOgSHNyqk3LmYd9HnloK/OssLiLc2Mvu9YsO2c6486MrKv2+LLanU5BcWFWzOmwrFx6DsrXbe/SI92zZK/ElS6bRxzto3UM7WN9a/3lz+zTPyCcLXMrTXs6lvHo06lphenVr3+Nfudznelm1KUOq1xDYW/EbZM9tU3YubTCGTqW/mTSh80xrmdOvFu/d+H3Wyu/2++mr/ZHf+fb+53sX8//mPe74/G/kx3Nzmevo+R6l+lFy+YubJzQ/S/lXx089Zm+8dvz9H6XPbo9Uu933OO3C+r9jn70d/G9/dRFty96w5FyvWXpXen3DzrvhJ5bv9i4/96ey3G+w6T73Ospn9+Tc/y+n69Z3fPtkx76GnM4c//GDy888cZx9x5+xRE7fI2+u3tL/LYH4rVt8LU5I8Yz+jy7fxD/CJl/66dtUO1vtgfry3XwNNEJYBvpn6DGw7P1PHO/23LHcxXf3V8MSr9dAjYCl4JnyXY=
*/