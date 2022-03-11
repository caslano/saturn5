
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "iter_fold_impl.hpp" header
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
LjohrNJri+M1PrRRw2+MGjtFjlaRWm34FJBYMZh9ToRs9PfvdCKtdoitTaoodQl5z1aGga/ZKCGE/a14lcOys7FPnNPusFRD6ujemW2u63XEeAXL0LTywf9O3mz8oCzd3LBr/LiHP/UtBWLL4/+0bI5inRQj0mFByDXXjdjF9gcdyQSz3R28tmr3oW6rO36x2dqZut7s8OFtu917IT9/rczTeNRX/BCS3EYQuvzSUkCkisegxDTzMA5zA4CKL5uH5JPXmV5vfS4oaPqq2bJ7pZjZGmWboodw9De7p1DsL95QOkQHLDmjWrxPoxda7ftxOkdANFrYrZSrttLXPbZ1KzPrcySNAC0xTKZ9bowoX14YHH+VCeBiVqjCFacfbgz1hAWBXM+BNQQpDUCGsgh6u5Hnl8RR3JtLRieo3rozo6z2j0kpjHzUHhyDVYFkHyv0saPckcU1paCtagi7fqqssWYK+4k9QloAb9n1SRUsAcRm4rr+XoS0f5Y6axDEUsvh7HTzbKELxTBaua7Sos1qvK7alFnJvjzM6XjfAdPF/rEssHQQ7roXhzIx3aJ8q3GI/xqaDKXwd3qKWWhC6V+/D93XUG3hGWu6CpIKpSl5XNPw6pw9k0DVP1/nPcoEFlf3pdKmfWHLhZlF981qb1U8FJ7deLQzVq4dMcxdnOWtd99rSuH9gOGIkoghT0FTMAkSsppsSA5QbDa6Lkmv8D1Fz+A+ODHJFSJB6QlcDbtD+XD65Der63U9v1IJBVwk0jeKk0sY8codFQ49K6nwye+bp99s2kp3/I6Rnc4EDC5R32rgXXjj6d/Bm93221vMMl3B8avqYZnUnSBtXtZgG/vYTvkB4M2X6fvPeOGyYIgPy7KzrTgWGSpN4EVuoVI3GKhgrqCrAvRXj/+3DJMva+ZuPbSwT2SBNPGtKYY/tZeZUPYYTWyylOekFk7oeWMlvZLe9kpZdMJwCifqysNvRLhlNBWDnkTozCIKhtsl2J/aQIGYrSFTqQ5sNjtz+pIoFxSbzBjS38V1hnxBChlKi/Y/4dySmC7z6GU5on2lYzOVG4FjdmXfIBP2Isec5NWXrtnbOn9lAGFHdJQhp6rilj0Ym2BNg1Uu/qz9UX7/crp0SO4NuFIpyxEYEsEqerXL01bVtTUtwBCkGrNneYKbUdzJ44rthkYNJdxLo44fEr322VP44PmS7z7JZovblMyZk1/U64x/8X6WRL3HLA5QN7J+/lJ7L5Ws35YyipmuhYhd6/NvHGWOcSqVrIwtpSJtHjTZlECyR5lz03iGLSyxrFmct9zKM6gzkn0Xm4RKw1WsuJYy2qdZ8fUH+a2PcixLczD73HsPzwiHVo6GSZsomxXb5e5orhB2U8fbNxuk3jY3M8Mw+zYOHm4YaYvmEPr9zf8utrt7L+jPCL89+e6Nw5cuU84XImwUrVgKKUe/oYcHDcvpvWjnKEE+dQbwpLxM+vPSKQIlLEs3nWPIPWkGfLl06v1KRu1GriLQiQGTOAwwFKsuRpFvg2loxL6ZNgRhkH+6qjhhvvLRvld7k2foaVd6fxUq8DJnPxUSTW7vBQkOk5GGDTu5gVPqc+E2kO59yk6b7miJSqi2Dem/u7WSkV+erKxOXxFfui8BWvvC5sxGn3M41DBkPtfNM42LKlr3anuXnr2Sz3Nnk9Pkh9otDCJMuSRvqTLTKUx3BY8+5Su/l3j4ooIZuyXS2tgZNbQ69PiQr2prh7nxEY3S3pJYPjxO1i/HwkOOXUyltPxdyYtJT/f4BSHEyo7VE16eFLd8ulk2hUcuFa74pMVLaPSV6BbviWO7i5aTNQOyT1U9nJcGVxypNY9KAiSYJWqrBA8Eyg5L0ruUngASLO3TyZb1+06dxICVe5cVDYD8Q0mcjPircsNUPrlMl6FXTJIyMIF0JIufuZTYJrF6ATUpBqGa96kf7VGy5F8y2LiwJDLD6728aFg1M9r8RBIuruUQtixz3yJ5BKMgbK7spCnj5MVADFu+vCUO9z01FbJI5XuFaXWzc1Nd/7sUPuO6pE21SwN2MdldfHQgwhRvaV+1sICPmNWRYNUn/ziXVZeHxyt+ksTFUFXW1yxYhcUtnBGdHTfCPZA4rjdP8c3YsHtJyQRbsuORYRD18cnx6ta8vYe6YfxXNRbCXAkEInF5eylVIPaIVJRc1Irhc/GBaCgmexnA/Gi64LWKhA4CBlFv7b/qzmV5AqqK2KhVWSO1ZNn1tJOtZk2HAH2dOn8BtLkHZaLxbTXN3whtpmpVN5fG3DNDnatqIAIPXb4K6llXcGCB3K5m2bgMNye3wVl0Kh2NqMGbBMb+JaJVkZtlSGb6UJ+kDjMfxYOECqIbesGCCgfYP9g0EmOI2C1CHwJHldtauBh/1inUZ8oa4uhgyNJAlcCmCpYFlZIAQtsnt9YSYVMSKpdRLpF4JrOHigcL/+IQaJ8whbJfUlQ800DLJ/WjeqY1knA2pCSz/5m/0VGVKbw/dOBLTv2d1Fk0O10A8/U2wuSaMMaIsDqxVC3pu45jtSYxPcBsaAL+haZ/vTLbWBUDZ33Y60k90B9LytK+fsyAUrpR4lTcWt/CcumtlyHiB2CdHSrzjGhh/up9Ye4ey4f90I1MV10NROsFYhlU/Glf2EyjLv7mnZp0915NSXT+rv3f6k9vG0rt5xMVQlPl8PKeAq+NgXwSQdjQDy1CcVep/QL9PBaY1jqRrTRM0a9bOKqqQ9w0x+tHQZnITb7QrTkAYdiVkDLZJtisswwQQ8EugiVbyWLFlvCtJXqedAmW4b7fIDomZ3v3diHZTSQyoLT2aPuD+ceHoO+EqPHE8TISaLR5V6nH4RO/0SkU9w0XlppRGVca6l3TpAgC67bAWqBYhHKFcIQ5aA9DocW/T24/L3dcxZ/nN+ShSnlVIF9CqQxbl/D3REu+yGXi2Ik0FNZvMNIgqfgo+7a6MZfiCfzypC9tmS7uEwkuLL9f+IMyi0lMr9+PupIOj1ywD3pv1J9Bjsqi9eNK8RHB16QpePxqQ3PtQAl5j8zwlx/8xcOYJzOKOsatRcKgJ6wjk2S+fsPF9TEztzEOgRdEObs3g4Y5zuAqUHinWJyT9BRxnDS3ix6uN8xnZTIcUSFWQRGvJ3mF6rZ2j1JXD9NxyX+I/QFSW2rTUt4UVnNRsSWslDw7lOuHI/INuT4sCwWryFx4SIuNb7gy7zwpXCqEEhWzeHhie2b3uC4DWEtGBU2beRhCDGb3Log+ZahiSoo08VY/t7RC0vlUZl8qnEN+F/SY+eULlBFdSXcTygmGXw9yON+CLP2lKJKJzf+JvxjmCmEc4R7EvtLsFOnUlzmL+zxO4fhG/Nu/qQZ6LRTdaEYo/tCF4XWzMMXgOS2w1lXuumaZIDC5D83jxCoF1qr3u54I3ya5kNhBWEVa8eiP9BaNJoVjTCUgsKH+bFXZSJGQBuUpbggsKhg7K1gppaLNkB09zyEQ5F4Q/U5Onm6iQra4sCt+tlHRGaWKpCKfkyqZ+cBd0PxUpHTGdl2k5Ed8bByfR4Wfk2/Wex5gSrQG6FTtVN2KaC37wMDUvo3EQa2JwBYuxq5zJ+KdPN17EfqKDFXjkbx9sMu/7npA7aJeEKqLtqfUgYyKEi7sWaBHOpen/lbZsJvZW0ZzI59uuWe4AMUkqN//Xmg68Yt6STa71TNA6yvwNLpJx7Ig/NldvDR/4zx9nhzsAJ//QKd5Dmp9ktWuugVFkgyU+dzx93kjwiHhQB3Q/Q/aia/Md+Y0OTjF+x+SlUffNrlas3+pTnz6AkBSQ51I1flxCAalhlZTG2zsnERa3ar0glj1fbEQmWVE81zGopRfU19RelIp3E0S1xwluHKJjgpXuKgFfvaw4chSFcyW2sOugNfQ/h3F4LQwOZJS83+M2Z3AwiRIyB7GwjgHXA7m5Af8s1WmnsS7IkGN6t023ioH61p6jTqm8qv75kdeo6ruL3S3K27hww7Xi25ha0WET5fDUJxCV2schNvnUrdYQDAxE4sX5m9NETVxRDKiKnraZcVDk3ilwIHlOnGGbiwsDchj89bwggrXLPleJsGdPBg/dPi7NH5iNvDXCLKArmysvd6YyBsdhjPKmieb+1vjWjQQBmPfQtZOLVunWFxXBUtvIk+B3Cnjq3xwzyUTRA5ih6wVNGcx+KymZTZrGlwUeOWnDzjeVzckM0LZpfujTvY3buEQwI/XxDOh6sGoXH6g3f10/JOhIPscBUl3MuvpVdWjaHgjoqFCG1ZRH4rDVHTOpvOknmJe90ahSlnBSjkBZ6xe50MTmgfQwiS1Qlg2Bu6Nd67I+gKho6Z4tyzCDNendSkXmJkxWeBc4JNmM9XvTra+grcs0xCJ04U/W2QQGhGIe23iRGTBQaPoYELiaXCExAwj3iiY1aHgQitbTQRBpn4QJarhYCIQAyFhEaoQRe+G9NPtU1U17Qjn/W1P4yH2gPZn9e3JeCrzE5adODGvD2hWLbnfBpp5tpNfjkcmoZdnhtd2t8Vp+ouxCwE/RSPAZzF6OAXMtZz/iuBuw+Kf9AhLreBzUux6IfHmNcJp3IBfrfzk7upxh5c6AoeXLO4CpaKJCrZFjNnLQdcwYmlkhInx5Jr0dsdhPg/VpGSELty2yIX8Z4mFYbWUj8srnSsk2WsiIlPOVVJ8VSQkh4tpv1BGTrimN4BFQq0M0ScjSS4ASH+FMPNGATZjMcyGfRSbPX8EwLW4COZedsztFyyP/GOBThCgIPJrNiBHKXw2uAtU89/9jPfWi9DqZJ5bifvM00jNlYJw53MWOVfj8OWofR2GWr+uyaSG4W5J3zeKLRJezIthO6wwbp63VE0vThYsEuB6VYjiRD9UxQxB/LYlkUfhtui7sMRQUJXhM4g9aWr0hceQuhE5EE1tG+GH0D4SvbFerX6fERvtGcxY4l1u3Ab4Idwwcnx26mLeIURcsQ0L+au7E3NdqneXUbZmdnyaBzkviSw1z0JqDwlowc2Vi473aHW5T4zTSMYPmrJ8cO/C3CmynmQjyxJWE9RCD/KcDRDuE2jKh/DbM48qPwnVtv+RCvvz4NoY2mEsXKoMN/8NuTLEQySfNajuEu3sUEfIQyNIKvjiGM4Nt7MueVoavigeLtJXHkL1gHzl7BnQ/2DKPV+ojHhvEV2zTklyE+o3BykpJBVzZU4EsOX9zkEYO7lkelJ3OvwJIlXpYFv1elMItZuLt8+x/9YDrf3geVZNRpu3GcYoS8dan+yu+GfeNnQwQ8b9AEl52lShB7PzwWrj1b9I1Yu68YaK6a3arkyYqbYMbHjij63PCTRpldF8AEj4E8/3ad5CQ6ga0VYFzTcnf/HTXT8JfCZ3P7s+w4J7J7EWzdu/8A8Id/bx9stJYmteypf57JG8Oexd1u5aobEScNAfljTRQMoSdzcJfFdSzQ6k9RiIdP2s2rqxRRY+CYselWU9r/bGEuVYxZRJcCrUymi+655RM/1+AGhGJKcNqQGoj5i4ewuk24MGKfYT0hn1YwB2CHyG1ZlKM8OqiGCvJpV9Bcn4PfB503RwzNg/HNdvq09gdOH87/oT7zojTVJG6E5ojrKQSBgHVP1V0obI92b1P62AnwzsZ2NLkvnRSTTEl09C9Ejm//RlGgJqUIbrq02FQtr0NNn7RT8S162FU3MNED6ZpUQlDc4UBVw2pe5MFnU9KGkbMImYIl45BXn/k8IgiOl2IJsf0QxC6P00g0TakNOdmksC/JqRQDv9zn/VAFftQl/ygHzkzjzlNbEM3bdnEV7HzzMSdO4lqvYLLx/D43JwM7bSJzv3FuBT3NGjR5epTbeF9IygFRheeetc1tf26shyeGVQKxbKDixGYqfGasCNyZkQLXwbuxUa3wqwUUeJBzeC8AkDD/iNf4uY1af4zPdwpTycEI9tLUDBMCoGjU7I9Ci2ci/e9CiWexAPEivgfXAZ8H6bF7NQ4PHWQcn+Bq3G4cocZdvlsyZAVSvOuy+3zkuxZde9JBWl9fk8mLJilSADN4RvdR7ep8Fhtf/3Xk/lGmi2vCnwIC0EMsHOVQXH1T/XC2u3Ly2A3rBAKfUeOpG80fhblPUYruumjGgf+bpFDrzurjWxtQcbT0OXIPdFnw5aPNTq8YMYKwAo9muHrwhoBk4PA4oz6YX9tgfiVRyAIMpfWy22Scg2TirrmRxrH9I8c+bZjqkf4+cdHWAUWGAQhEdH2BFQFFFY8GRLd7ZlrY23l9vce93V6S/whT2dPFMuV7RTYPHkarWKN3m2mY9o6KOliRyMwQo5NKCrEsj4PAiOj3s/AI55S8TU6x4Rm2Vng68YiIeCH6zvFRJVjFma+KRY4jAFplupb1qxwFXNMcfCEhwKR30zO4+iSN9P/H0BxvlTbKubEjW7fX647XxmfSjiPcvqNz38unV36TT2CjMH7/+PgqQ6CclnOMh0Mjj3FRd2LkK1hP1rn2p8w/OnKTKjv3Td8MTbzIRgzKwK7d1cgAz+rSV0N1UyZzswY6NxdxBRP9R8MSZi6CfNJqQoAhu5ZWQYX9OyE8mlsFd9qVmLSEyHtSdiczvHJIHoAB/ekjlxyWrr0dcnwOQB12oRH3rPKIibNnJllnVRkH0aR8yHWiR14yF4SHFxcvp5JHJEUS82G/XLOdUFmhR0VFwq+bAEw6wiitCfYS2Q27RB8VSsTC1Sv7qRKrhflsswgY3x8wahKTusWe7EDJM07tvC/LfGf4kzsDiMf0Huu2BpWBU6wwM6WCUT2DqgZFyGDK7Fs0SMThp5CvSqWE0T/3zZSLzw+S+XdBDS7cP4xvxAG9qQ9R+Mj+VBE/0gRFYUl+3gvWNdS+RwKtd8f+QZKLWZeZeiT1WvlH43LbnaTyLcD2sI5b2DmzKPYjkMkMNh8EPbCl0lSEA87v+uvFm9GD6gRU5orY2vrnWoV5QYfAcuYiSLQKUwYbqkFZW2fwKHUlxNwdFAxfcbGFNnYUMtl2D0Oj87c4nX0fFCiHL6jQTKzi4+hi1mHV/p7MuSZobNzYp/l2GPrDQJ8HpJB6KyxAV1tUeQ1BIlrSHjhTQFkTWsZWIMgEsg7XhZ45WszcsbpR7nOHtnmxqnIvLlmoQ7WKQU4/mcZe+OMQf/rO8p4MQYYYpl6/y6Inhm/PMs8KNmCqmzDadUy3u9h33i2N+8OLQfKGAvBZj/fSlX1kSS9JYk2c7r4pPbkvk0++o97O5JndStEzJz+29GVGrhCyViUNdrkI6STg+1U8+tZ+aGHKSoK/U0YnG86YD6ARzi4MD+42M/jDI3CSKVY2UMh75FBWzO+9uhH57W45B33XBTpw47FOr6gLaE8z6T84WJgTgH4KJxoyI2tEj7+aL8n9h9Ma5USeO1QuwouolP/np2eWcp8bKs2BzNQezobv1AYo/wSFDrqGzYB7JFqV90XHPbEL3KZ3UdxsYGwBek0sIWrQVjUO1Q0R6RyFRp2+tSwrC4fALoSNkBCeonIOsCjItvlmBmx/0NMwtuDOUwpxvCYNCiIjytoyC+r1J9UeIcSEuvSE20rigjXEJM1QeClsK/xpmpgqHXbxX6bs/utLz9G8s7b63D3o9ll/qBtFyuQTpFVD8TfCbO5N02TCFELwwA7a45QmvIkicctHloFaURlPzxy3PyLzn9LXcMx/GvZliB55ZLz76vRigrd7oBnZeJSUs6BzrL1jADutzQDq6kr3JXzn1sOZmteYDnz+ZMd5YFW0Xf9NDK+fMGS/AfdtrZ7ElfpFWynx/tl6Qi63//BbZCd5mD/CWZH+DT7JQzQ7u12NRfYwdqRqS+2+Fb8Op1yVkhTDZ4NJQZ8q/ggS4ew3qPOCzrHWSwLLGeDKcr5soFA+8HaKWTJHHWaj8mNa2CKOPI5ceMB3C8u6KpbZ6B6vXJqTRectJoNNY1UaRwJPDv2MXSFXEvKZnJyM+K86x7GiepzUhuf066qMuT1MzU4Rjzdn62I6/k3ONd4aAY7GRvOZnbB+o5+wubCGttybi1rPquZLYP+rx2KJQX/xbSG3gLDwZMCtyFtYci6yVGGzvNw8f9WSnwe70qzxVjs2b2Vh5DM1753AudOtHMtF/u6BfSYMxEj8m0djlV9m1tJK4sPrLN5ILedpiFZUakPQ2pt+JT/AlpRGdVKLum5j0ixZSTOxIe5Fer3MXzhEvfQxe/5CF6xgbv/N5WnLIwlci8EpXIf+LQy9ehVz+wcQs4vdb+B1NduqL4oPDyUo9MJBtjb+piKYq+mi9YtTiwUUo4a6lAN8U+Xzc0dwKXGY4F9l1YHqIx1srEWUvjpuuwOTtWE0Sk+9SgDr8DtTRUC9PKwoeBptMExGV9kJqiREKQNo4RtqyuLE8Mu7v7D3gcPwUZFaptzbvIkEjCtT5Ww76sjYrPbOUDLZqvWTBIavZiRhaaQIP5FzpGEgtCkPQxqcEQDknTy5brJR9nLawR1O/7kFvHnve0VZNSihOaJLc24igFUe+ulABVvWDNtah8ZRC1xT0W8U0F25pDx+srlb5ZXHkkUd+ZVdARHWlOjZtZUs0/6FIyb9Ks4odJviw+0jJzEnyY/cvgH8AgQMLPVCM/rDHu63o101ypB9Vu3MrCBUOjZZ5t5Ts1lW5ZF9t8Q1oYdMWyPDYkaly/YfwHlcFFEr/DwKt5BGt+SA8WV5ModbW1OVdzLUngocJ0MOS/oxmYrsbpKbR7tzd9iFMTaBsPuJghE+wWg+XwY6Uou1hpdqTzaLuaaXUFhKLyMNsaDcXvAPYdVMKN+Rme+z6BjUmxosW+vHznUhShh3R2XeEc5yjBQL7Vx5GvCdWdDMoRUVW/iZIhsX0uZGM+XvU+pFk7YXaY4SktzLfFioq6iyL5FvnCOhtbcgiQcER12qMgvRuUeERAv/oSqOOjrLgaINdvtTQblmnB9Ycsi8tQ5LSVJHldcpcszymHmJkfZXKO5hdN5M6ZH0X/a/vyzlhcdOBkem6FVxB6uy5pWFQWe10EF5T1QktnRs9bJLwy27JiS5ni613NkFUFOzVD610xg1MkKtnSi/mWoRMrObG4Moot58XbJDyIYmz0YkokLoJm4Uv04DF2VHdrVn6AGd0/W9I81xRBKs6N37IW1I+4qxQbMQyR9S/mh6Kpm3KqNFP76yS9HqVu2lI7V3mr+X7ONa7+3fUxSicDdwv+WJEV8OL6wQ0=
*/