
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
1FXOHgfhYi0Uuui29ZxYhRbiX3fniYd8zG2dvEkVg2zFHW2+2HQ/1L8qdIEg6N493DTe5QDD2wBZ/v4AQ8dw2S3FSEPHseVWn+T/Kn+l8U7/Z82T/fITg4iKMblbxYTi8Y1F1vDMoQJzauIcKZw+WJbvmE+6dhEa2W/mIrj14coKEkLDDvuy7dQ43ZZge6nBG4My7BhhvfzCGxuX/0bc5Lm5xEvbcv8uAjmr0DHi8/JMSQI891oCy/ed394XPhlvEK9q4v5C3ZfoMnyr/Jd0OiytHxZMAa+9sgy+Jdi9b3gNrR+b/9WPa23YS/+XDq0qi5/9PPSBvnROrVXRXhnexv6LiAxozzFxEYHkdFHe3oSKbxK726yN9jtESisM3CWwjl8bFw8xK5CQ10TZIW/DAjeHJdxHRJ4ynviaWgG5bljp45cL2gGGT0hObL7hfKX6oBAi1RaD6UCci2dHiaJFU8YIKuFxA0WNq8qaYeBl59hYkbxOF1u1MbJnEWw3u4TrxtJ0jyubdFvvCFpRVU7sqbAYMBT+tQ0/4VQ2htaVgFmPTspdMPBbMxdhc0izcNP3L239vG++M+yWLwL825VAW47btDOURzTGS5j7IMr0Ms20N+uN7g/TkQCS7BrTbCrfJb5pox0tgYF7tkmWKNfiyoNPL9z4TFrxWo+SnpxYdwyyAydc2ChGodove/CY5ZAUYs0NkCgfP9rd4j6ZSLeXDzmmaWgMpqq6DlOjwgOQZ3fNqch9vYs26VZeh4M9G/YN2waddtluG9zabY1Di+3miV79IQYQw0p7+R6NBoVHRXP8BDCHC4jSSTKvbUgytauoqJ5Qw0MeOVarjhnehNssOE9QZc4izzRQr9mAkaFZrlP8UZ0nMsaDX66x5gjmYjv3UtW9qjCAC7zKEMKKHwJ2SnHznGzhUwxe5s5H6JpD6O1aUG9tly9EcSWs2j/5bc/s/7C7BIosmZdsj+T0IydunwTbypxztNOAzEBpKviqVYEFaqeAwLsVzcivYvVt74tOwIsaU0BUw9jB3fV3nzwDURdMb7YIj+e782qk4aUCQYqvpXjtLQVsisF/09dLPNln0wDuDn/SzTGtLzuZ5ifx3b3XcqThPtjfo09PmYXhzchHH1+idNTKLL3h8xJ0MygeeyxQdoIZlLW53mnMtw0HsAK2C/aD/aPSDfTI+l+UZ7aBKNO2N8+j9v2LJy16AXeAyX4zqIYMcTvz4ckfS0hrrR8ELKRaW9qRhkDqBJDSf2JX3t4Xq6MOxD4z70bZXgb7GRa8tWrQuuTr+ky1hNT5GZRzlvFZd+vfMPMcwl1xafP8KUFAD+kjkT0/1fLi4nZn+wt2t21uHnDsPcaFuA+VaF4btpJM2Eg7bUI9fQ6z+yopcEOXA92U+KsOB2iNbkAyeMw6pDVOMIelunixCZg9bV4vt96QGSsnaC5/aYgoPiP2/PQqu64jO+USNSSCAxlTzBaoB3VhO8uEOiAcXGtJXVzQkPp0hw9IR4r+c2oX0BmV2VzZw5/x1t5pX/eaYXzVdxviyLffufxzdp3z9cGk8/YV5Njx1qpkARuTYk3/4+lLDC9lnf7HEtErFkNNA7GmZ9oHByYU7TdpClEjseYrlmfmwX9StylwvEUTxdHz6JknmSNRhcgL/1hHOm4e2942Fj+h25PpSulNPUQWaxP+8y3rw6N9muVd4ceHBFR3J0/TO/Ih7fr741BW4HbN8pkA+JjjjII2//LNJ2Fi3hPq2nqgh49BcrRv9wGRQzek95u6QbjDVJveSEt3hXf3s0qGn/X9Fd7eu/ZhxuO3mNZ3DjDG6L+cKftvRSjxYAuIyrhM6jJvwu1dq+k6mzb/y3h/J8BKpsnTGjHuno56ARhdfuFc6lz8oQ7kYPwmqkC16ZSn3K6F6b2rIdhOjuWoFqq9DRVMf7aEwFmbp5APacgfOqzsbzGjbA8opOTn0Jdcteuu7vX9mRd5hXiTk/Oww1f7qcUNfBoi5mX0KvDdG+d1D365G+ad8rbGCOgCgQQm39sFpOx9Ydv/KOhdlAAnt2nTkR6m9F0EutrfBzW4v1eZmTM+IMf533+8cxB8TZp/X5nr2pRwVSyRXZc/jrjfjT7SvKb8yxH6LCV99tNlY5xn/Cz3zOwDSdpTiY3fp7AvaOk1h0MnsXMkBt0jjB8RYyD9blnMCuEkMKmrdev4KVr//bqeVEtLPd5zOJ6ynRPyXQBi8suSg+0YgzYzj9ciR9bhNjPeGiJuO9SoZQ64H3wDhPRGxyOYkTYViBCD5KmJZN4bQI/7QJP21cR3A5m73bHPECRTC9iIsTNrOVMk67mDjtfxTVM7HTEf3E0PrqVhug1scnu0Ry7be8HjZJe4eSAaMIeo46gzcblJxTIjuAVX6kKQjOmjHvVvDaIoZyvH7NYYqr19TOZ1Nx/wnvdJw9iX4KxG33Y6z/tO3+2XR6Sg1q7x5WPaEm/eEPKnlkZOG563QQ6X4brggsJdt6AAGzD+rAQ8dvCzUYxGgl+GHgvia/8wX5mL4KWr9qBMtK0May3sjx2eo0FsNOw6+TXVGweQN13mdSWhV3SK+9WevOq4p9sp/qBR+zHzruKoEz5L/Xr7ZEvBwMBtxrnbGz2szxNWfyuRU+PzxPY0R2dzEfQY/sdeRdyb3Lo89KswCztZAxXckK6cVN/vxQODhLY8FNaQtf87SY28fW4Sxe/bRA2DqUooK/orxNSk6P0b3DpVbh2J4P9+/BjeRVet7ev9H2kMdS5mzRxqr04ePaq25w9O8tPxdUpnvBFj5lFZ2eK0GXLnVNl0zHDZvMLGBea5NGylTmqMfpZofYwFiAJS1YM5/2RlKFNBQV1ShIDxvvpD4Pv39AQXC19CoWL+qFV79xXLNjCz6xlkYC7wNYmtnHOU0tHGW1zxGVLpi2h/ctTsPy68phAmdz4CNObIKOclN9AUifsXSIr1UmbhBE8BDHtCnB5TKOxVuGWsJr3EeQBH5k6FB52W3JAKFN3w7D6ooJkVYukWEL264FDc8FRf6N/F34M+F0ouUvTFUVNx5zCCtR4Q4Qy8V4T0D9kdCbiMuBM30TPaeD0MxHS3e9/7gacJO+q3t/s6v6ufAel4T6B1WfbcmgmFaJb20ds2u3wnAX78j19CvE3XkBibv6pj3WkePlNy5h4rRprBTGuheLdkBM/AR8BvSLsdrfJGOA9ggSVzXj4xtnkLeB5UrfyHmI7kPW2dkZnvt93PKAx3dJvhnf86Dgx6LoUBYh+dVE2KuF+X+6jfZNqlpXBfPQnIni4m8EFK6r9aL4N9r3NQ5SME1okknkgBNeDu/hLt72uxKS07HLH6wcewovynxgUmgZ2c3Tt9GqSfGahTDSMNFZ8mIExHPMGX2ohtmO8/ZEIOYwKCY8h7Q7cWIe+ADOo2/KuLH+5dN+Ubvx1Wu4iA0Um3Its8kgpUB80Qu77Iltsbco7E0KIo8lCPHdcTdndPwuLbom0PfXaOHJYy7aPd1RmZ57e66/TWyliCZgQ3yCzQKwwXxeQfEvgOLB0ZwwxuHNn++VEO72ytGfQ7zSYcYxdJNywU0msqGVwTrGPJ7lRjywLXeQvjf2a/ZqS+jB5Ddk+vQZ+OV1aEGJ95985fIvzd7rybslscGaNPLWakB6BPrN/ux3m8QFQ/KV+bow/3TLSiG9TfPBL5nWuGfUSfwk2Iv1MUWBMIZnoe5YS1fNDc3N1UiC6U53efoBJbRm9aOtL25hUFjNYEKFxDhlsFDxJ+g0ry5bOj2nklTAh9UXd5l2VHCXpUJhNf+PZeqRLdW+mVPwj/Qa4WKanvMe5/fnocq1Kfr9H+FrBcAWBed1dkmOkuKyxrPQS6/Wtx/fDfJhJDL2CdOuvA+oCC52emDme82hBYJFrf2pI1/WOwTYVfo1XGSNN4rXPS44CfUNC4GFBC9nMbFLuxJifh9qwDjFmXj9Qung5r7qEBjH5m0M+neNg3mL69uY35zHqfKVyqZeY+iJMajMvU36fiZB9LKQ1VT8JLWDo05vlgjJWQ3W34io/uui/tZy00BPrAnknvLVrlNxQ5tjGeIFhk4U5qLisspt3XYQ+vfLFw1HDk89UHOk+FIvl2k+wSvJ8HNOAiWcTMiSESlfJJ293HBzuoROD9RuQEHhaRHgAOSBhXx3F/g7NAz9R0JbZu0x4nkBBdS+FJ8nwSHzi/3bzB4/URIN6FkfGRFWHRf6T1ebV35aB0WTSf4v32gXlzO9h+itkUotdRl43pdm7ZH7pUsdLXa+lZMrvPedhvcUusFnCz2mnZ9vyYXF0Qw70uJVGetn3jwzvzxKlayElKXjFdPTazmskJ7DSQyGbjZTud5v9K8pz6x4Wh2anQPRxvEKqcz5xOz9K1o4VMd56R1NHS7gJo7m9LsS7FazsioU+vZtJYbW1o90iS++3NmJIlPy38QEm7HFXJobWJv2QyF3Fuhth+BlCrhF7OWaxdz7fOVbfDDLQ04evEwE/eEHBrrhZYlovYMfhg02797f/9s5V6cf+YnWmjmXQDCZhTfy6I71PpuD6pXQzIfFJG0tvfVBPa0sCY6y8faddo2zHjW6yQ7ajyualg1eM40Q5naVHTeaXfzUSqS7bvN70CLBG0+2jsUg9QkJEFRWiR1Y0FYr6MWFBglk0EfmMuZW+Mvfdxa4KcePYwDC+3pDOefLpNJ0tA1mrq0qY3s8XnDm4zljc8CWa9iawIl7TLsIcXGuMDMkllRZUqXM6gTWqvr6OjLdJChgJrLhV92sf1E+Xf33Hj+arMOY8z3IHdGPTd1dJ+d5zGpIugshwz2fnn9qoBjoFEZmM7IrcunE26itkaNxzA+cTn88y6RgG9Lv+HGw9gsbj//uW6YBOI9dqJ9UqgX+eXOayRAENuu8jlPH3LCPPCE0ncn5K4Lo1laa+u9FZF8/Wk12GwdJ9Z1Z+CBXj89E0Riy7HJdg2HSGiqOneL0dO69xjqRjhqghHo6lJ0DPhKQjfo9KIe8Ib2SdZ4dM19Tnf75Jq5Xnr8i4tRTQuUmu7c+QtxuhG/oAcGW7Ta+hcbrQvEcf9M3c3SzhLd83WxFcN+P2MWHLLf//ZuLWZfvhfyYe7bS39Z/Gz8UnA4tdX1NBzOrdR+jXb5XpR3GcL7mr23Ii/+aXWzj/meoGyOPRrlXv/n+XVQwb+HeaNFxuJ33yfhCO0Bf36yPUAsNeY5CeXwiv/BxgTvpElnCKX32PnQvVeXsirM9er6sdjh95rxOcuRIIMKVUneRlNum2iTbOz07Zz/JodnogfNTDqYLgOODNQC5CLPcqGTLEBkVcIDzM+cllycR6T/lx4qeCZED5of66mT0aiF0Xe6NGtoEABw7Z62I5cTNo6xHfZymJd2yctmQZSrcuaVyWKHwMQH4UQvBg7VUeWK5/Ez+4MF5fHjx732xKLQNZE4wpPTHrsIpX7lzSrr9KKG1413iKlzpYe3kUMpXFPEgmd3Zvk/Mx5jqp+mYJqrSrv1Y7K+X1s8i0KCsT0uVbFLZwzC8uxEy1MOyXv5DGnM1HvJ9mPwcvLMxi0GVNw8z8zxUEuAHWtbN/vH6epeTmO7luok6sZz7YJehBuU2zBm4+1tHPDy1s8zp9Bhu4ddil+WV3Dtfd9UzXb1Eag/7aQFIgI7c+GuBeL3YEH6bvPLCHPBB/elzyh/5TUwbq/D9bbji1LluA9ti0HVmLeHKr8ntd9Nnfc26B9vpYGBA4xb4DLGQjAFp2edye5j3k78OtAtlupFr9p32GEL7gW4hzfUvXY6WsX+BefT7nARhUOibI3zH3djwQ7IaDHdCv0q49UV88EbQX0I4R8ThhjFZbJS+9eUvfgzPqzeJXg1C72bpce7Y7Pd/Hj+2Tn62c4o0e3b6ibEdmF2rpJh+3LpfBHdN0qA3l7AZlvN1Bv163XU67RsAPlK73bDIbj6XGOoTEaD9vpe1W0Vaq3Zr+2U6KrMwqEuYSsDaiY/QJsU+y4mXXNTiG2Qm0opL506EFsYbT37hA5wLXqsd7q6EHwg4z2vHUhtgTe6AO//WV6djf+3ujoQuibd/buRJxDXwALekH6tDvPZ524eEO6EEssvoGz8umv3Xg/WxLmh5AVid5SwvZha0SMFogI3R+JRD/bXj8Xc/683fpaA1A4on0+654J2h1VcV3Hwlg3qsa73T9mLo9lW+tso5X3iA+Iul1txkC/2e/ulu34XO5aRKKffr/1wZF+p6EHJ/sKJ6EufB9c9qf4/j1fSfStdz84JOL6d+cuGM1emFe40tK3fGatXI7b4AyG8RW8c6dIjHJnfhofHlyNz6GGSOtDmX8QL1i7+eENFFGJBlj+ySXZKBZM+VdycUSvk6z0zn87Bfx5vv1cZnA4Bd8JCDE6BlBK3+akuqikXtiAxpvWTetlDlb5TOrnsyeb3uNGp750q/VyRhnSzFtmTbC+ANWbxqUGo+8FLtt/zlYpHAo+KIl4Q1/DBSJnHc9ExPlktjAI0tyeZvse6Xw0XEa8xN0lRvmUDroc9mbu5IW2UEfWu4//662KToP5wy5z7LulneLr//SmTg0FNM93KkR6+4CMASPPGCtPIj6tgy537Lvo0npHza0C7a3tpUPA50HeoW1IxsL/8ZjmFT7guwzNOyQI6ZwPOeQrP+ySS3m+7I9tgbQ72eq/I5y8U7eG2s05rMbL2cG84b6JifJ8GrUDr2H8GtgpaYfuRLLZ+9ak2nHIZn7ROIPqlG9f3zEoR7/x6p+H+XbK8jt+luus0O/ZTd3S0WDccY3mgzEwYNzx9EW/rsJy4JXrLNHvOSf1jnwMRHSFkL/+nL3gvqK3Ax/+xgn8jtbpOceh/PLdgECC7Tzssvm27voe7GCxAtTsfAZe+FIjQWX4CGVr3Nmdl5C5foaPajgfJ2EShnkh2k3FBbaASy18c35QfLN+vOW8jWNXfZfF5TzLfrQ5fF57A0/ecoD6Nd/IB0vfRB1QXF4Tivq+l2i1hGUCeB/9DEJIMSAJ3YDIrQYE0CbFjpfFXIJbjkzPuasv00tOO9Trh61rAILBS3dWEolBbVfeIg4CKyzemrROBmJ1J0uh65iu9XngZyMgM4+WUr+BHU+c7WJvv/JxpFVJQV4X0vOaCMjnkImHp/K4k5T0xl/+Kc7nUImb9tmurX3W6zawyya4GPjq8bx948M/0fXnGRL91ueXISQ/zEbJuFwGCl7zRqaxqp3UQa/kOP3j0XvCepgKjMUjW+z6g25b1iJ36AaNwH9gndvJKaOuvYdrazHkq3NWTHI54c+0xEpRVT1yN8ZrzRQVeTEyaKswfPjLswZ530f4rE8Otto9uz3sXO72kG/huTpTIZXz6t0Hqfm628kl/1ArjbecxJ5w6nK7xh3O4/vgXFzgiy3F7/2wBQHYJRM7be8Ed/eKpxvgAyz4H80BzsnDNSZCpucdsPXnBU8v4MPB7j+P/rDW/64eThPEFqz1z+8HbXDf48KoG5Ai7Qjycaa2UDCRje9XRQz2e92aFRTvF0cQVinqzct4YrcaW8CHi4E+2cgxjxXUq0+peGxONDottEiRMTvGPJoT7qmwd+zQy/gRPtA7Vp+P/X1WNWU2Zs6ajAU5Vh9z/6kn+plLPwKpg4h+V2VUnh+6K1xhqeaAZcxcGSdJBVpPGGte+cOXemPl9Fe7H8Di117CUPeF1rnbp8u92BvXIcutz5+rjpcBZ3Rd9h1fMkI9H1IBY+ublDlemiKx0DTuebsbaQk/s7cqu0+LXZYDN3696qnK9ceG22Ba5ixE5ZJqNXz1wxXrC46BNQjyX/3sfo1BmsiCfsnHB0b9Qofg0ylEQdeWI9NuV0IPFcaVhJ+0058YriePIwQFQSnPJtOfVbzS3ej4sLPdFO1DZu+YXL4HIHRW8wsAgGqiN7XJK2R2O3q+997nGvtzqyQCitfAYm/4fOcLxXhT2LcjOv62tsXp5ZCMa2hMongrOMKYTN+eLEmZH9+USfpsf5dx9tTCmzH/fhatw5Ktpb5k1wB1ZkybTbQlcjXL6XDJNe6fZkLInFa8ZR0LrvAG/hh++VR68FWKMr/B2giwqXIp7mLlOmzD8WUKFzxGQG6/NuUcmjfnqdlyq1O/516PKML01SPKb/ie8guWDYIBRMTxQrT0w4MfkN4LUmTceeWe9xbQJ9u5UWDeUKhAdeCk/Br0Ap8O/N50QcoV73m8JoIhqkA9iFEhqkRN9Wyq+SZig2ARqAar6VtVJuPsAST57bNo7Qnwx7gD+ySXyxiE+H3TZXpen6QCtzVodzy/pQO3DWh3HL8PVnK34efdHnW6BeqIk+WGo3HBS2pozLS6bRbrbIC6WrQ7d4+mZJm0VtAbSAxML8bW0GbPCXcbtMBal0LZUwfVn5zdiOKdmEtwrbxpL4zL/yX66/+M/5MYkH8O85aBOtXOcwvu62El+o27Rs9OyhLcC49LdK+B8n/26Sit5P6R7lKlalkfnyZUedcsv37fyVIsNtcAn+5W5Z7XK+aD3XL01M0Y2p7jcRJlHc5vaRc5IWkpxesroHbpdODwcn6XHqiXk+MrDvxOH4PsfW3l5hHskuh9fxlZBFkR27PqIcNU0esB7BHAIX6r81e1UcGk7ZOM2S5KFHnP+2/kKBmL3aI+/qtjxWdR73AVlJZWtcxJfSM40kj9m0VcQdU18VCKsWr0w9LI+Ozrc+9h6pYV/fAwcct+jRj+sjDMMnHM7UUnpTiVAe120qXOsG2Gy8caI1+XWsdNacn2C5rX499FjdXsBMe9CTbYM2+5Sqa3qBBeCDuQ3EcNXwDCt1IEAFqsBfdzcZwQfDuiSwwZlmAJnRA8Zv+K7YWK77/ZIkQidvo/gGDflJP3m9fj2/YbADLlRkP+hcRYAeoh2/m60w/03SLbuZ2a/o9ISfTsV74jAGMkek7/3E57QvFmv5T1Clyi3njsHRc75kn03EnhfZDW+A2vauB91PBCJE+zB/pukO0ANw++jGL8+jluYzygMhnQQZtkO45SMb3fQ/+deZ8D4Uspxm/edM/3HPW/JenDmBD82Lem9ztHouf2ookhZoqwAL/rBPUgpQaL97+QSyRi+xVGEIdvg3sz+pnujxx+2asxknEMWyRjfFf1HWpvNjQ8vwK5p/I/htwHKh9Jv3va+dfZB+kej8lnQjRPGfPX/ya/RYS/GSe/hXY=
*/