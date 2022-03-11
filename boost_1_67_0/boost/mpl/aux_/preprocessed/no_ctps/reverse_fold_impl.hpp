
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/reverse_fold_impl.hpp" header
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
struct reverse_fold_impl;

template< long N >
struct reverse_fold_chunk;

template<> struct reverse_fold_chunk<0>
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

template<> struct reverse_fold_chunk<1>
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
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        

        typedef fwd_state1 bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        typedef bkwd_state0 state;
        typedef iter1 iterator;
    };
};

template<> struct reverse_fold_chunk<2>
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
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        

        typedef fwd_state2 bkwd_state2;
        typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter2 iterator;
    };
};

template<> struct reverse_fold_chunk<3>
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
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        

        typedef fwd_state3 bkwd_state3;
        typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
        typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter3 iterator;
    };
};

template<> struct reverse_fold_chunk<4>
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
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp, fwd_state3, typename deref<iter3>::type >::type fwd_state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef fwd_state4 bkwd_state4;
        typedef typename apply2< BackwardOp, bkwd_state4, typename deref<iter3>::type >::type bkwd_state3;
        typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
        typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter4 iterator;
    };
};

template< long N >
struct reverse_fold_chunk
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
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp, fwd_state3, typename deref<iter3>::type >::type fwd_state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef reverse_fold_impl<
              ( (N - 4) < 0 ? 0 : N - 4 )
            , iter4
            , Last
            , fwd_state4
            , BackwardOp
            , ForwardOp
            > nested_chunk;

        typedef typename nested_chunk::state bkwd_state4;
        typedef typename apply2< BackwardOp, bkwd_state4, typename deref<iter3>::type >::type bkwd_state3;
        typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
        typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        

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
struct reverse_fold_step;

template<
      typename Last
    , typename State
    >
struct reverse_fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct reverse_fold_chunk< -1 >
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
            , reverse_fold_null_step< Last,State >
            , reverse_fold_step< First,Last,State,BackwardOp,ForwardOp >
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
struct reverse_fold_step
{
    typedef reverse_fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State, typename deref<First>::type>::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , typename deref<First>::type
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
struct reverse_fold_impl
    : reverse_fold_chunk<N>
        ::template result_< First,Last,State,BackwardOp,ForwardOp >
{
};

}}}

/* reverse_fold_impl.hpp
U+F+VOIm0uBItF/hgGCcx7KB/dntvA5zW51WNzJtq5nBko6f1ShPxDhVEVI3jHNGzRFzHvyIOap94c/ght4IPC9PGMrfBD+o1NuyzqCnbs29xZY/7YA2mM8o7cW2S2xaQUoYLpDOeLOQPscOlFwfGZHvfK1JFOVirZIJ5v3Oyxeeps8V++/doSfpL+/XXBWncMMpcBLZbNEnEEBpore7so5TigPMptAXsynHtlPevP2/5J80Y1t+ho8W5XJy1Ygo+VSKh18ea8X3rUwcxTfEf67oRtY+3eQo5d9hzT/gFiLNytvkr6rzVmqN5wCjeVTxAstx3N6SWfVOR1Im0udSD1GIohDbdvTjtTxTVIaVV/MhE+3a4wxxQ6tnCXWWtZe2j1knhycSjNlWp+KU218uKSvKm8VwjrmTrlaraVddA70NF/6R+800g9mKo9N/NCYdmJQZIPNz6JYJwjq3a7N5Xj/BjS40YqvB/6+RoLIn0kAJtpuMLQtF+y/e/yYi8v991Kocyl/BL0ygSkBUclYE9d0y8Efy/9fpp/qvIQmFEP5N9Auz1vC/L4bvdkPdLxWYeTTLHMNPwL8NULmAeX54znnWoFbDZB3stHt32og4myMchqvfA2PJC3YGDn0yMTU/B6mXl3PeAV7qZHFmgovQRqz+1jEgsIB7qvJL5u2bp7iS6oam7LMgVA4yhRSVXEIyXIuWPhUedvIddAh/DCxf+2dqeNKUF4jKWtQQA2ZyUPyxCvi/iMj1wGdBldZlrF/LbwbOiO05YMFSgpd3AyZk2JgOc2axpI9W2tFgqnhwHCcJexuDoasYWs6h7UpCcjKIaAarCB7Fq3S327CSQldWwKCTjCDWCthWspd3LzcPFsFXMmLq0KuPFm44rOBtJM0fmv989LbC301Xh2ArcxVrXTW20QfZlbuJw5aIw4THzfvwngd4KsncDaOYVP08scGwlTn1uq/1+YNYioKQtPC2jA8zBXHqSWcRlv7cxFbmn3KUbDcYxVwDcVkudLw20yC0RNtsW+qAm0HZBxrjKhP39ucfk4e5JGrZ7cUsnslc7NkNlhlUYrdxWzeJZmx3sfg1O5Z5JO65MFsJGnZ0ug8/3dMDLJSO1mpnCRWYyrhAL6V8uRg58qDolZUYTUncz0qJu07itCL9g4wEZyrk1x2+1CxU0yIydw+j8KqjwqNC5Xa3g+yiFofF7rB1C/q2AWZb/45EiruASkj6OPeXCZwLb+Iv0FSAwlFWG/IvC/erwtqIcYWnKqebAqqbdHwOcKP3MYlV0xY7mds6RVkR2D3kc6cdT1AY39/VADIfBI6fb0csZmSM9JZylaVKXDf1xzimMRyjZwa1ligaNLYaJFgVcHIVUNe+1/NUqL9ZuL7c+K+vpB3aG7H80xGj02+j0uf3LG19FYz4MBY/M0Jv2rZhzV1h3jID0NT+tefD5kGSk5QWXKjhmVod7GRrPS/8bRv8p8EmX7aW9/agD9XdlVHpZG+1TO7Blr7y+A6GUny/Ci4TJsgnmkBY8KMB/8k8FTMhbeFOufrwJCYdd/vgpetYsOwmhyISN1VHVxo59LDTiE8960fKvb49aofL1uvE3xiTmhrIKxdi4RYLJ1swNQkg3jrN7OtBRbzq6nFi//4CtoVJGS9CgNA/GyhjGv88F4R6WE6wlqbY3/dQTkd+Ylxnp2j2vLrhagJhORMgt9bhPy6lh5vx+91sr5W99WKu3twVtke/NFXfsYq0XrixK2d1BtCVnHmhGKhYn20fvA9PacqF63uZbQHqYdL7hx3SKER9ai8Kjpvs3AF2znC+xz5FKfVUgGKa24ddmq8Zar6RjLjaiTh6kW7CgVa1iXtGJ6/aE5f4I1lZOk0qL73ktU90ZR6uX/Ulz0SfuE9e+mEoWZwZM8moXUn/SL7Qzw4ThFeQll/sEsASvuKf4rfil+Kn4ofiuxRNM+rWEmdJx0tqeWJpYnFjUWNBZ87nx+fL5yPmreal5qnmoefP58bjBeM54xnjKffw7S3C/nwt7Cyz9CyK0TeCZrsiMDzJeu+U4MPA+uUo1DD9tC3qmYBxTwOnitgxxrzWHcxY3t8bQiJ8YU/00NuCX4lGv9E8qLcOrJf2qi91H7p0osYKGHEBuqoWHVamxZ/iCWWlsVXnjCJ5bPa35X60Llum1p8l78NsmkmSugMzN9RInbfEJrPQzxfAz0prB0BeU3d0fmRCB1hTIFyW8ZG89zjV0WWiwt0VWKdXwyTKxtd0/KKuALOy7HUcMRxRHBEcYRwhGkEa+XXmfsmq67pmSoXvs0vuMwnj08roU0hqp8Jy4xsd9XjbhMtGeN+xHsD4tteLBOypTp9W1UlTfmW8LnhqoXi8/u29wRx2taJ2/TW0fPneem5xhbWG3NGnl6mC5KXF3fP+u+8GOLWzOVspKvX71gy4osFHtE4KKOIKTxbvWdaacFMad5p3XmXVca1mk1u0slyrzjpcjp9PRlUQvESqQAfXUHglCJyHK17PyZLJz0y09s5xs85wFZEaVo5Y003bLyHdK7zKGVqAasXfkvx1K77VGDfd2ru4qsNxko+pawffx8o31bWJF+Ro9m/OhNwxodGNeVjFX5Xlpe59Z0niJ6VigKE839jBhM/1fJyR78Q/oHXH+0T2OM62pLVWlA4oTS8YlrsdoH/JtiMvu2vVa8nZe9OCi9sKayocZHO9YxDG3/P207VYBuTG4esMwBj0BWd4J5m5OXJwOZZV+WhatfSetpYjn/PoKtrdSLf2d0v6dnGqLq+W7WZx4Z/Xz4kqv+nKhKswREgRwzjlP+gUopRxnKkbYL7D7bnX758z5TbMs89bKpUDNHJPKkZRr6hYHJwkbGxWdfVbHx6qmTSNMVtc2V4BrbLSzcXqzqByXW86oY8xDdNTGyevzq1tog+Fq49lp56ND+hiJLppC17onx0j4Z+t3uFmFen1zErHXRtr7z3hVGaw79Euj2mLSlubDOUD8U/Jxu+69iBra697AZ6iuYmYJUQUu1ZjBe2YesukxbrS15XEwesbpKYxRxphzQnPNu0ODmmoaHsQe9sPKwJqP53xc5vfIUy2fDiimg6rWaIZRWcH24fQun+qd5op0v6/c3eE8tgKKCL4/bLgiAqICn7fbTPCKcw8USoaoh8/ARExQugV2PflktBQfgKEONT/m6n7PkWFECb5b5zHr0zkub1eoMGawT9C6/t8reSuf936/Pl8Lbf5FHiVv754YiIy7TRPQtZU72ZiGz8xSeZwn6HzgBNpFmE3frns5KZ6JsuWHxEToE29o7hMCGUpryibg0pCx+aXh1pICTXnr5gpgNom/+PrzIoxf2T6tXGTa/qW8wlcAUYVut0usmsp/7onhq8d6H0xt7sh9dxttwsNffP3HFn3GcM2iKtcAbAbNGNlW/8Sg/UxVEA730vFp/B+QBWHfdjLlpFzbRvtCXncaOPSWb3gYAHuCw3OYYSaZoj+mhvVYB9kfOM2odVGdx1FLc4nj8pt4YdrtiOMLk0uCKRC5iQOoDtP2mkrs1ev/DI1bSFzfSk6I2qwhW5D6yjXjj2KoWwoSlq5PIA+GN1KYUhQypNKgbru0/lrNqKnY1xJ5KgCinnWXlDYPClKFh8qCnTlxMY5pjaVoIQ1RsZuxrg47VJHTsnjQSfVGefdkIg1cJ38OBkqZFWvgR6ep8Z/pNiZXndfYiWgkZug5f+h94j+77Hwb5/ZfYdEWN483eavZd4ia8ey4N8ILsur/kzFXCmW97tMxc0Te180l3vFJYA1nybTrNXrY6ulmJw7vUrgrMRUxIMwW3D1eW/hcOmVXodzhOS0k4yn5uY/xlOLxdl054YzM5k5vk4zkbGvmvqnEY0ZPNTNf7JUQJe8wo/pJWGp15wlG0QZYFx94zOeyvHc3s+moCuA4OMFUlYyd5vbTblKttzEvUAy8FehncDBr5N2uLkrnlV3av8QVOjR4Xb+iWrk3MVCeUtnYvL2i5Hn7NzHC3KA8z+7P4f0fEPViZ5FNorDzSI5z8Ip8MIxKmHzJQNGzu79+f3CUzfKIcXzBll7hbcocsXupMXuctdcB37NvoE1rxk1hWFT0TMr/KRrTyekefi5NMznEINtgtRIijRQuUuB0iqEikLizuS/OVHvtKFtroIYo29EVvO0piVTSgJLXmcOMOPuxo3bpIv0FvLzTMcp6gptQ1MPuue2/3y68A38+ez2e+onBSNt5Bs/RAMrKt1G7rFesDiXxqzenVWh3M4BdIEGhDmSjVWVyrrosAG3ZFdd7qedq5TCQcmXhKvm2ZSd2t7lBN8v6rqIlfV+lYJn+PPa2Ql6a0sPWMXGvLd4ldmAvbWk8m2MDHrNcuRkKx9mQ4rhJeGYCH5Ij1xF2q2E91JWjVJajZb9qoxujLhfyQ9mAqAXX85f4HUli7hn0Lyk4t9QfxyufCRl7gNagBPAR1Y5WLRdsBCelrPDIUArud1TmetadI5SznkRz8Uz4hMvY2uCgY1W4lFZNVkFCb5qYw5vBPMyhcXSVLdkXqbPesvR2qz2eGlSgiWt41khGW7j/NFCsLGS7e2yxMFIlskm/SiKUcY/C7FUD3DZt+d8Kz83qzRdSdp3XcsJ0ntTwq1WaZuQqCZTCbQiJbsaZMf92VMcBRyn+Z1A5ol/Byd9Z2pInYA3sCgZJq6PLDxuzp4YP7zos63WEok7LWEXTVmZ63DMZSZzI16ojqH+D72f51Y7nPWZyWfKDqF9XWJsVgkPPJwaM5OagA/MpPMGyMooINfRk/uX5H0tBz+2i+fAdRyPMGa0AfrbevBSXddafpiD7O48m4Lnqldop8MjEBB6oWXeLtt8LzxuT9K/jLCqQN1P9gG2/poZs2lsylbw9bMX8xJAifG/qKlTrZUhgZ61SUSEgIgI8fs7Ihq3X7C212gJiwj//l985IafIfvl91/UpET4fuC/YIrwf0/+N4MG9d+JstfzBoDsfj+Ljabhxmb+C3oUcPTRcjz14MJ4S0z/gFRfBwhAjHzLt47lzcbVvFBxL+qusabVbU3j/Rh8Li3vhqvfNkt+cR/gxUubrgzT48x6SHtL1Gjie/Orz1RKfatrJZv+uDyGkPMQaJ6yO9l7p5lrDn1O8GHt8PFsvu6/5ebV8fVq+nK/BLofbl/DWhhJO61yxwa/Yrk4SHv+qu6ChLfzmc0auJ24PKaY4SvumdYd9X1lXvFqB9mwo8l41Iv0aJ3YmiTj/aih4X3bfE6e3KgeKpBrRsoSuD7p0MivLxQ5HiHJwQJxFpS+0bgxspb2znkBYjn7BLSjwqXIUDgVu+sAtL4iqhmDrF0B3SAHLqQjyyvKb8pMYSHLuWavDJrinwmPjzH557GO2H+ClvTKLqJldxU4rQozzq9yKGY5XqJledq9F/SgTANkRXzlzjzeq8aLXs5I2og+W5NWtWBta39NkGp8rhFsFtRjHt89pzVEzUtY0yZPklhMA9fQ1Xw3vT7jofTjujJTdm+M3nizn9fNZ5dvHHHUiZcAkFOvjs9WVSmtKS+tdLv33RbXkeYZPsPcMU5C2UMbNBkae+lfHXyFAlXAwwYgicF7q9zIr6wwYEwivZ7EUfsiEuGlB+rG79PGlBVTy9h0QGAxC5Xp+XLxWTMYRdPxokbwzDvSvZf9M4y3ziQvoNDb1fEWWNOcNS3dqaTa8dpqiHYKmADeeXrrdE6/bOlJXDs1sT0/yqLdAc+J3+z0bBN8AGf6Z4my3e+lvb4HXYuodved3bYYnBePpIsj4a1n9++HU91GJA8sTHHr2+A+J58TDncKn/VJP0DDCu6HszTU1HlGrNo/veW2wW7npaTTsAoEdYlidIh5vXRpM82+7q+6KatTz/1qqNZznrd4FtHfixszO29b7/ymo76uWz860BvwAbSfAKoTmm6SdkMwn8ZjbGUPYKa1qsk7JIfyxvJptV1xUPY712td9W87jCqMe6jXHi67Zar1zpNj7JZu75SKbrvm16fO+Go3MbkukryuvvvBDuCnBVfl9hnwOiTqa+bThw6AKx88XSmXPbSnRx9gXpW6STZN0DW03xEJ545Z9GpnLcx7zOu91XqfGWlUpSadxDs57RE9TUFspDo5Qjf0sJTdidHwvHpM1Xo9HWV4VW+55gymPhloh6CH38X1PLj4SmXl0k3jpfSS/nFtHtqF68WiT/Wqu/SI3VvtIag3ALv9N6r6R7PkLl/zNdNSmtEN9LjdOintzwgIXxgEs780PcjyIKxqNvbJniWrFiF2nSBGGIaQNyCpvQ59SLc/MAi43+VOO4YlYpi2sq72k9wynSWHWmU18Sh1H94p3FivlYvRT/WGgOfAeqkHO1uHcsOcr26mr+6DnLcHtTAg+qtY2QMdAXzsnx/NYv3PWsPAOG3eD55MHu5P5ld3dvfbK/yR6v7SYbxPVyQMzDAv9g+3rSKNDDs/uVp0daqDcsy9EhfZux6pVP1ekn78fsx+5P0ld3d9h26nA/eMjYgHhvDoPx2SJ4rhB9I7EgMxO8EeNRk3a7y1mO7SGBfZZhLlpp+oV3/B9IKkWYQuGqaY7mgO84T28OljeH7C5OLhEF8oEov+TPkrIljtj8bxIpiax3/xQ/cHMQQ6NaKl/dN4qa8wGc+UOwBwhJBz6BiebxXNpCV7jstZ7CA4vvoRZ//7d+HUDlZO12Tg2PAqSk7dSg1u3j2zsjN0R+vRVA1alpZspUAhhzerdDqMJUw6NnlC6+BSzjt3IULQEmGiQJxAxK4OLjndrLbLnIa8uj/dRbeARFgwJULdv9Q/txkkxga2BLQeMbFBCcobNzYmf+UUMnPYOZTMTIVug+oVZAfXryjUJwgmSGzF1+A8vs6LrXiXtMOPiOE4MJHq6LHbiWx/UfnFxPrISC+2qUPfV6KZaar9HAvf8IFUMWjMSHofRUGiMFYQz43lex1VCtKzsMc9mPyDn420FwsdGNYDQQgH+aPBpISyWV0iG2wtjsXIY5Ha4ZpdNUK8KxdWSKVF5CQALNLpX7ujXxo6JzxGZOMm5ykHAaLHz4eM6g08H6o6WWjUNerSuuA9h5BtNY77G4yzCgVBEmWVkuL0QCnzEnkeF3WGoJNARn/iAFIoHfcIZxAU+RJvmFwkSTFm2Sit9PPNykghV3n/oZgBN/4894K6EOHd9mSi20AMuRfZDgWKnXbQOx577j0XuNDDHeuBee4OCsZhiV/AKsZpHDMy9/UkkKkS4XltNTz1xdDs3i+02NQlGq4BF3mKGTI2HWY4pG0BP+VWvVNO9nNfO4ejqAZs8cTA96frn1P1fr1ho1jHSz6GuHW6kbzWmtP2czBFIG8zHT+u/oh0kS70JoRhY5OJBjz7n2sSd/y0cHgDSHQEVyxPZg99ZR0ps004sWE4XBJEgLRzVOzighjXTQ0vJm1+LDxGxrqSfbB2Wlp6AaEyNcJuQF2RwZv4X/y3kYqD3FT/Us82wx8ScZHfyrqDC7Dm7cQ1hS7vhA3Auoz87H0PPcckxundD23vLae2Z9ozkh1p72kM1cP889CTFUqXRnzREyQ+t7jnfRpxNUkF+oTmn0bhgrRHyBo2+q9+kEG7jLFhSj8x9tdTeEIorOrOJbnNX0mUL6w7ZSLGfJIuZI92Liu7+80R/PZWwd1JiGKIePwd75bgsgFcQdkMJT96+J5yB3ugq6dKOfUdjDbSdtYY4XG7Tx1ADMKf2F73h1Ysv3zJ63Po+L8bIxs78Wmh0YjgYSniHaY03EuEFAPFg+nQqy/aG2EIalIlAg/QtrjMpwZIsZmo3P6+bLiG/Kwt6njb3ymjiUf2Z5FmjLm6ws2Q1EeKUaBz4Rnh1Gw6HKTKBslESom/DMomcGW46OIgq2rU6b6wPLWOOMDr4kANaf8Qxvupb8U37O9WpmmwyPQpxrVSylEQta8QVwkq7hahundDpAUWIM4PKO6QFcBlDMjNhK56/QSEiCP34eSOrQoQi0NHJxbSQhi4RdJmgETGWQaeN380VOHxHV5Vh+Xs9FZE0CHzETIEgt8r9ekMZihFuSGDDmktBex36f3xpdgGSI8I9aGbAbpcEzuapjJI2tOyxwdz2CL5Rx+CUf0oclwLIBKpp2KFsPe9Y+h6s6uJyUZyBQSG1m4D6d0mxeu/PEK5mWKPvBg1CVLnxryaZMoQxRM4Lvj/NmDZdSySsaGadLZQZidMxVlaO2ITZ4do+iaPoYppsEyR1AkNm5EdzNgmjvaVFr402POuEjSDXUIsaLC2k+aALZiQibtDw4T9USbGQtRnTOHUBfEeoq5IL1VzhGd92EtlTCsItRozjkfLJk8gzKcgv4oFhnFqE20QHgcIcR1gg3EJJB9zMWes0nToHkdOyR2vBbIbOxhAqSk2J0uu15BFBtIIb6M64CDF0gtl3CwQbo0FGCVwn0bag4uQc6iHOagdTuDCNMcpBy4HMve/1JV6HE5jDqUwj7O2yCwdfWw4ZuT87SA21Tr4o814g3tnSlYGweVFhhd/iXgJUGndJpmsAisVmKA1sfQQTe2LVCxKKOzJoIlF+50gYeuyU9rDZVhDVKyAPLpAfFQzE5YEqWROJ26Xi+hew7RH8ydAv4LIAMpcch/icn28B4DZB+eVMr47OwrqmHm+RrahTa42uoFvp2wwdS33csuLd/RqAOchLnkjiSnFCNdhzFIVqSJjihO/uW87GV3GL3t6Xm4a/akq4ASXMmgEBx1zyPjMfvwyMK9xXvtHJEeJh9zCQ+rxX0t5+7YwPJSdTCleA0fzSe/8b6OoErzfpsni8LYUmrFizSrwfSKYfZAIe3WwxmM7ZB3kkIEEXFfkgn+I8Yxk081QIQL/RsERfX9ciYPAWSieHEmyDIY509loYsgi3vLe1FD2umuqH58iPuhvDZQITQS+ItT1KxiSNqT1+RgntFjoeSdlfLqhSDlocouECk4RXlkmIATBqM/pZTgSHLpw5Mm4HkOoyRyW6dypDmfaG6vs/rYzpSujtEbSunS4FlOMGh/VUvWnNcFXIkm1vQnEKxeSfrSA+jAm03XXQLqnMSgmzYWWpN+s6Y2A0y9i8G42D04bdTG9YdxQWDbTKcVLtO0vMQ2xlWz6co1wQHXTrILQKWq1dHXxxeIQ5b7uo0q2Oqvf0LbKeYHkCOaTgagX5irte3e60WaMWwNeBqLmZfDsmmpLp2s=
*/