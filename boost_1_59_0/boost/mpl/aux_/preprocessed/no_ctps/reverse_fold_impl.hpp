
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
DXxCFy7MgpTRlItx/XL+lomS9lL0+JkIbVodWtJvPBYMn9NnnISpB2mP63zIYweMZROpe5hkwU10ooQ9z3agyIWTgVComaYgR/BG7Wh7bRlvXwmZrvg+70KztKKgh6mew2auMtesG5fMPunUDF1/zQwjRq9RJFTt6yyd6mGqZCm4T7p/JTJ8J67glxr2njRTNdnohO1woOvQ2OJW4SjlbBioLWLlHOBNgLexpQ9m5Yn6U3QjBQ92rzuGPtaTBUPUP7healSnI5HNHIxkYFhl5zRrz5gGjAaTGsBhdRrRkQL73aCu4VPp5gqotEncHw+xlczPZfY1grAJZZR8yC8RbcqbNwaezLPHqPcHgnUhW4pSztxhxd6VhQCghyvXZptcI6RCiXmXcu35/L1a3GKQ8EfKHH9Tmpibs6s2fwSPwsZDhng8mbYrg4A+zIJ3LEeuVMAgkoj/pNUNaX5tUBNgCjsgzufAn2rky2XftQw8ALWB+ZUfckO7w+/0OrcphMELLpkT2e8xce+9BaaQH49DblJBRl+p1GKFY7ud8wIBOU66HUpyyYWpbkpxbtFGp5X3ujD/xei2Yd/KxTXcBNAz0hf/p8gi7yrG4fmuI5Xv0yG24fGO+YTiogxmRrsrYEtd2mqiOOHiYQnc7UxbXNWNvZ8cf+XOBCl8fdAghelLyzmIGZOjsmbxUEi26Qu+0xnuLXOLaqZT9cOm5KnQAAos9dNfRklwQbT6YMUWIHrydEPhtVpso/5y0AnyPMrhhsqGPzFxCUR56b7vAxVtqKzb9mCLFgAYG/jaflPyFuqm8zFPXaQda7heDgxBvgCMljtV7ZXW/NAF+kBtSZBJ5s4s0Yz2KJe8+9f/nmht5nhJ5qy2kJqF9sunZ3trPae7D4Xqm9J+XeLMxw2iHsXFJ7MAPjcqWbvQsngOnt6blvPMLszOJ/brl4zroVRR29IiLQqRwXdVisovtQPdDkhOc3+jZL6Sg8aQmDlTDKHef4Wed6wh1T9iKvctSFHlOVFIZ3asXAevxS6Mq8kILquerFxL4v8jypRimGg59c7tbyn1T95AHGMkpfjPyIAvHSiTrXEwEyrpvikAArr8DbA7Dm1xUVaM6OUJEaH0hzkpbiy9EhGBxuaIjGAiGGlNCQ0ZpMJKGCvWRRmjy9syimkusi9i4B51yZZSRQteNJdLmZEI5z+64+0y6Rg4ihy+dxSMYxmyBF5PKpFCL6kvKbztOdESTtjVXJUQqHc+/9oRnJBwzYrcNiXEXkhBRvRl3N11XwX9zCdGpSUvdhOGct6eGvZyqhXBLN0oL6GKx0XWkdTY0BlYYlzamBx4Lg+LUzN+muQirvM0HPn8+73zsWO5C2jUoMJYwtzThCAuenRjkpVkVbpQhQuS0cCi0vdkiftRAgR4Z/H5qYLX8FvCEHetVhPV2Xlaj24dn8ndGfIrMeXQ7OUUdk91n1o3jeFp4xiek/PJ6fuHUh7O0DzQdprajcd7MvxJ8xiR23lnAllL3A2lK01/U+FmOTxlQEYUiBn/jqCTzZJ66W1+Yev0VNtA9iDp+6dyC2imgF/mDbCLExOoXuUdOjPCp8fzfHDUHNtSg1zVtPVLwFPcXV6mndeK0B4Ut13bSDYKR4XWADg+uyD9s+oaAb8kEsKcybH32asEGpKuCI1f4/mPQwzcU8O2/BwMRb2386nzBCaRh90phtLeyBH2WkmFgCPZoFuQL5uEL3FKWH2Mr7pKXik3OBQdbpx3+qum0QAnzsR16ni46zvDxOwBWA/wUv4zb5f8V2gDNCvcs97kwkLTLRh+R5NYXLCEbpjMMxKvd5Rl9axj0sYnsU8uF1RCryIsWs4iprBFGEfe0qObSFuaO8mTVfovhbvch1HCyJ6Vuz3cToj7vWt4tzT8+z3M0SRYf9BYYQu3O0V/RFo/UNkH0OG3G1yf6ir16GmywpE6Z4BKEN5Vq5HO+2HjzDvcbCSEa3LMjt6zN6wcywppii6PyqXYQqqbO61tuJr7tVW2hHTGYqrZAa7DyQaRCcdrB50HPaP5Ti6dKQ9+PLbm3ehenajLzj0P+Iz6J/Sn2R4d6PDvF8O7RNadIthH/Lt4oZE+Umb7m9fddd6i30UJJKi5joSJvjoNUVYVwMGmg+H6mb40tx4gFPNpCazMAwlfg/sr+x+TlN3pHOG79cq1f29f9JNCap13Xfc3di3i6Nsv5CKLT73qC4hvS66BDBj8I3B1ruJnw/fpP7mfCm+1tcrkS8k+ci4vxkrvi/dNN9/JvsLwJy3X6awsT+t1WJs4t21YaWY3WFwPIBAuWYK5dI6l6aeC4A2LVfEJGo9FdeTJgC4W0Ei24LOs5nXooU0hyDsQsyBFIC/1hPkU0CVL5vbzsPdX77oF/EGLMJmapqy6MBSqpO98bJ2ObxGaoNBw9HM/APHMkH5b59NzW5Zm9iIAMnxmU5vd+56EQ5BoN/8uvEPk+iAfLN8YEasXhD8ac8nFpAfauBGZcYQ6TaAtjqE+tizlKMHMobPFDCghzrY2zMf1dwReJ17tx6fh17j8lVhC2mB8R+yVWCXts2amF4RnUY+Eet4z3h6Nh9bxX3PDQp1YLGgZHyrwDyu1iL6jVocKdzdf8s9fffnafRV/zCVXtnwqZ7US36rlT3ERQyJ0newvIyvszPz/2UEV94kFM0XzEeQ6qNTWx7jfXfLT9Ql5L/5UdfI6ooP08nKGk/RTvj1hFrBMQw7GQIdRvYPpHHJGrIJxjVKSKOu/8UXCPml+bptpNOKPKp984R4P4mgAIH5N6oEaxifcZ1BErZh0WUTUhZ8g0MFBFsaDTzLlE07HOyH0rpajs26VGCzG9i9sLi10T4Tq6JOJr+ISpzW/7ZnYAxLofKlW0JhMQ/R8fbyx4lW7iniLAXm7/KiTziYejjuiz+8cf92oyjf8d6jNM+efdBCsGOSoeS8qJsVICXRybVBphu7ykLDuokmv4R+Sy4jvQw8u6oMbZfTBr5cuV9vf0h2h/I94JE9RUQqvZQ5f8NTMYYt34HRzxrLnIl8QfCr8JfYKxVap/NIgs4PsvxKQ7mXFxL3WYB5eVJcWwR00kJty+r3CxzPnAm4I4HYjynbhcETezhBT2bPQ1Tnc2evLe8GJ0Mg9XyFr+5IyO+oDH3OHnAr7for6kcQqCpaZpQZpeWUtqcwGBy0J3eH2AQwG3+DfFCxIvf9mangy6MJPQWMpiaHKDVcS/dYzR2fuOkcGUNgoj5kDq9+UHxTShk520FzSxehn2TqmElSMq/pTWAhO+xUbu2D2J6AjSehvkQ5Nvmg8S1+NitEAXu62jJKBHd7vwVfMzD8CVoQhMlTBiv8CJ+PL8fTbgx8r9zyJUgRJECvhA5JGOrSmaimU1VBXP4a9eFMZjbzSlsvaQcthoHh8qn0biOf7WvLFJIibu5CGMknPp+L9DYbjOgeA43RGkbnxoB6GVrCJjugbNltBJuV4KoLp6KyJd7XZWbDQ9yJ03mCXCVhUxMqp5B6sYbB7otlZFK7J0XYb1PohQ3OzTKPViHxmJkAlNFEWD4XnFLfyNyQ6bHAQhTS6+sH1yWWZlJ4a+7/dGUl9IS+qPTSmgtIO33/TqkNId42XBhWxMWmgIlCYjRig/2Echi2mOavKXc/PTLXb8JmyaALtwizkstdPo+dfwnZFG/eZfQGMHjzN+9tq7l9LXW8T7ha7TtKEyi/yC7p0+ThHddsNt1QeZsV6v51GquG+6mBH+7K2xqnGJjvhA69qYZO+YX+h5qijFc4ZeuWRyjfe4b8YYNNimC6zkj5g4dSsIWBKkJPsgJQNHieCjc1H6wcAS2VpDnl0xM8MAoCXYoKWVVr4imK1gXUt8EZF5+3j/DoS9VE6accF6DKHyHUizHm1jtGmGjhagLuK703LkOCzB9Mkli6cGJm9KUj38NYMDmKxvww8aBOiR0i/i/oEwEnBy+OL1Mdj4gw+jnO1RtBv85IF3aWOGT9eu+vkYkeHwhPlRtd3L0+q6Je3X91N0MID6pr77WfYE8N0qD/n9hJ941H1bFbqVfi/3GFHUbnnWJE6zYuO1qWmVLit12gBRDioodAijH1BgkTK0j/3Bc9ayjxgKtKRJITPSod/aHFcUYXVOLybpJp1sqZOKV28+VOOAXXkTWsDYcwYQWHj2+YKEToS5qsQmhNkTBV3mbo0I/heAgYK/gNNfOct/oa41lWVHlAULdaXhy6c11FCRIxFqsWczyvkiyDwbiWRkVgTCvGBlWoaxMXp6HTT5NDRjkp9Li77urO8qhlcSDRneKu9jIfyr4THuB8nc7JVKKNThlCja1aTjsb8BYTMzCWI83Wu1Y2sHUyRToXAWuIdGf/vaZeMe+RuNgkjGQdR2WPPhQ8azEeaSWO0II1l3r2Ue+QnlYBNp1qYf1XeOp4viTaXYEm8h0nBsKJsfhhXJD0q3rpjmycSYx2kfga7dA7rxZ9cXvjpF7CDfjWciO3/89Bd2tB2SsopNzIZc32SHcYIYxR6FvxCgZ0WTqIUDMAGiF/hTqXSrBDSLq1LEy7XbFMb1v6CdGvmoaPH7TWWFnbIoqVqq+Tr1Jah6oyHeeDhTGCRZUtpaFjk0DOGiKNhNERpR9fvM961jx+k/0pLVijEe19vOm+3HG+5X7ccZ99n2L5RZv30S3bD2aKldrRIThXK2yhJJo6cDJL+i0tK1lZ6cFUxDxfstWjB5m1drts/dZmdGJn1TsMhHLrXeq14ZneTJsmqI+jRunBC4uDi5YGanRquNEjVAZQ/FP+JBaK1FmOnsGrfxVCYuZ/MADZQkWPaQlL652JZkqdoaUMXP71PhGB0pdZ8smGRg34/iUjVX2ZZj4OgmbK0BZcr0xtqnrG3vBwZLt+kagVCZoU3pjnUjNXfuxE5F3Da9+kh7I01UIuvTMcoDb2YMVNV1+SngaxL1IZFKofhyzvM6u6iuY6GwSDSnISKCaMl5WUzZD2ykX2k1jlWmb5uydIA9R9JteF4ilqVwmuMC8Yybubbp6V2umC0o8nkW7SPXXEdlNu/XviprotYbk42W5jGucWHivQP2RiKZnD9eQvF1g2ngCFEOowY4IBoxXB+E466KHc3VWAHYCSz59ELtQhBHkc3P76UdpcrUbjZXWimyg9DsG3uipXWwUwbZnMroTMd70fXsDaShcPNoNvl/0bzmwDDp3G8G1ixvRtUf6+4E3yX0rgy2W+d0fkXolC1J3AsUsfo/LDy4+uHzhnNntY+aq9XgBNzaLNy4HFm6nB3vYRxvo97YbSCvtMoJHCv2kv1LhtiLhZmdX0iYF8UYlNRjd8Mj7jV2s5uxzcYecp85zdNGQmoYKFPMeCNvk1htPp6eKUC1x83BCUMpsJmM+zxcM80ZR7UM97Zon3Di2C7NTLYrJR8kXNjnVxTgnU15eN6STDbqIQoK8zTjD+AsVPZAcshVj2Z9kEZ/aSumyMBUftKMG9nhcsjx0ajGWFSt0VsNnssK7cXRGI8rQhhKTcFJl4yDqwpI8V7ylzdhducADDdBVV+LDEOFK0+1BTvjz7QYG4RbO/0Ao5emrpAi2JE7f2EBj6o1eBTaHo+T9vMEnG+zGcfRrnBTl1IX3Ils3q3Hg9N0ebMPmPGUPLibUt48b+fm3MTEvYI2M+hz3/xafNEPUcRbejq3Dyt6CbwchZrf7byeOOrAAxuGjbNyDPNu37/qxqdlzyKrfTD9S5Z1aOblQvmvbDSupaaJPYEtrv/jkxAoMzMcMkclAby6bKJPKT4wCz+xQ5e/2Uf9UVBQln7IlZk8VxPTPzMfA0bYsiQuqgRERQB69PWWfzPuZR3jdls+p6FVgbzP/BiEqQk1B3yGKaIW2TJkv9WDB61IIdalwDus/s1RhEpxby1G56fWTxA6wDrgeVDSdQsiKo8P5obZftVQ2wvH+39VTH33whuv/dGFA9lBqT2RLMDQbhOnFHHpXg0y3jVSUGKFz/XMWpZVQDg/oWbb4eKtasfpACrqSPybpzJJfq9RG4X8nqlMOXWtVa0viOaPrqXnp7LaGRgFbR3/QfheWSU5CRZy1ajQ0HgfdFNAz+/7LlNwJC3Uzl3hzDV0aEHZlfpYz8pXfb7JBnndfUFA/qZVLuOFDzz9M3TMzumLFTB6NJMtgO1altoVRq0KIj/HRWAFEfLMsjcdUOiQvFxGpFsg3GkTZai3gFZbJk5LIHaOJBbT1LcOxHnrvUzQ/iJfi3ra0zSrXYIEqTBeJcHV5ok8dMt3lNhHfdfIk2oM6Y785QW9sH8MAWntSqspwZPyjR5xLbiMqbRL9FdjaSzanfph/YFhutSeY3Cf8V7byZLcZS1u1QBSQU+qA/hNQ6QIbJQ1td8q5U+wr8OO+SCDRz7nOyU9U3psAM4Fj5K5GHeukisC2+LXtQ/Zx1+6f703n6Be0KFVrea1THXzBPTM2r7LLuN4SUoooryB5/UNT6qA6sHA5UqCSLsLSzTe1uZzqsWWzrlM8SsD3uR9mAh5IORYfsYoGBv8GXzF8B4tk7/PvnTiI0J1B4FcCiWrfamkVTDunFhsy3tY/vJpxqsZpg8Zw84XnES34Y2i1SnELiihLcJSOhzE+4nCsIfBMM3KYzuXHLUVEb8UvlP8Y+HjX2IHrVFpVLb5REFc0rIrXF4ljDkVT3q8dXqyTDvialCEG0brmJEhaSF5TwagytmQgSi7aJEXIZfqFfDl5Hrkj/Zf96/qwqlfMQS/jsGpIx+rQRl7SUceNjBppLa1e1t6b+pPeQwS/SNJOGhXbtRXHs19qSe/rYeN2yisF6MEWT1xWEajavO0wBJUqIPIs4Bp1FFjUJ5G5QnLDPfrtv29choctPIPl4up+QNpfI+eNWbVWBa56ptjnil/spSEodmjsbl0oStLWo9ZmR295rCYChq+yi3tkwTxSXaxP3uNGvfuUoRlRsnNFzwh1hxFTfFrlYoPK3i+CgtfasVNCjkrLad7A+b1j+EuImFBXL0Q6n066Xvu/rmy5EfQ1Wr1+dQPTNciriwmY0JDqGnSWsHH5WVDjjlNc1HFiF/tQUrK5Te9l70wwjs9mbrDnCVHlaP0HlZIx+5fQfXrqhSWwiomLPACK62uUDjq+Kg/n7fy9AXxHXZfI38tbhGtX7DnPEMgbbCLJ2JS7+Bi9Wz20He/M/mUoetnef7NtV4A9C2g0EzF0S8Vo5ccndeC3Vs1jo3lz8je87janFRgK3+YPp5tee/sSk/stTKJaeDBo/OSLbanRuRoufriDdTVGpG/QVdPDw22y2Nbmf+n69OzVcxRyX069/I+qy2YeI46RH6JOmvC2OZqaPjz4OU4aILrMT3s7ePjZFPMYRJTdGYohYeaxOB+drCnkl6t7FTrEQX8Z7Twx/zj07fPBWHI7TxkNL/7HDmLJL9rJBc6othEn0hR95BS0Lj6G9wp6OImnfq3AJh6y9ALwr6bIdxKs1IvCryjQ1rKqDuNkKC2e3HzO69sWkV0H+I7kdsZgLskadhll0R8o/KR10zoaXeZfhED5aOO3TeXtDLEpa/qkPWXB9CMWeoJUZRZLNzc5BafhF6PfyfQ6o7pVmscyhTNl+CyqvdbO40/DkqNxilldC8rBXN+uix3TZ7CqW4c95fPmQU
*/