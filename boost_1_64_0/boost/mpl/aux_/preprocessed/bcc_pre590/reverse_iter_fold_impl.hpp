
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
XkfdklaHkWk6Wwwyg9qXd6nQ+/8y2elvKx06kWbzT69wOhRlF8dSb8drrPejpDA6JTnY8q80e5GF0SlWe/7nO8bjGMfjGG9aO9627Tz1urDrI+evq5jw0bR+XVrclDytceIYY3OgOQ3Z2FKG3mc4+LviGO8Dd/Cey35Icw+ak0gNsh/aTt/rAneDXeFBcAeYClNkT7gTzIXdoNvIhSVwF8mZTqqWnAWS0wrmGiGyk2kDb4FG51slp1xybocnwDtU7lx4GrwLXgjvll3lPHgzvAeSEu71201qHgHuJ/lWu8mrVc9rYEfZ9+wq+54esu/ZF16v8vqT6lReN5XXFPZQefervAdU3gKYAiv0fcZ0zQEgW99vASfq+8/K3uQl2ZeskD4rYV/ZHQ+R3fEYWC07k1fVLq+pPV6XvFRSjeQdKnlbwj6Sd4nkXQb3gpfLnukK2bFeqXLKEvQb23xH5bSBM1TOqSrnNNmfngG3hWfKLvYsuDM8W3ZS50CjTyn/HQbPhaPgearX+TBHdrQFsqMtkh0tCTtaXd8m+i2t39hGL9NeB5kPZCfYWnaCybIL7Cq7v51l93eA7PxSZd9n9NkHpsm+7xjYG54A95P93P5wKuwn+8L+siscAMvggbKrOxTeAgfCO+Eg2dkNlz3bUfB5OFL20GmwFo6VfdI4aOzDj4Ht4bGwJxwPe8Pj4AB4AhwDT4TjoQvmw3RYBCfB02E2PA9OhrfCKfA2OBVqPNFvbvqlw3jytPr3YtjMa1clOyr9ftbv6tQgO6ov1D++lB3VV3A7+LXuj1q4B/wmQfamsD/8Tv3kezgU/iB75rWyS/8JuuDPcLLs12fCdfAm+Ct8VPbsT8qefans2V+QPftK2bO/Lnv2tw0scZk/h011XbaC38qefS1sLjvcFrAldW0Jt4Vt4I4wCe4O28K9YTvYD7bXdUv2t7t+k8MODu2+h9p9T91f3Kv6nn5Xw56O47/281f79rKOY/rerg7j2MOS9wjcBj6q8fkx637+bwX0LUuw29edYPX7UL62EfKlR1leaZT5yqPMx2+csHaRY6x7FCpfiwj56gL1rTdf0uro5PZSvm0j5EuLUF4pA//4ddjDkGaS5pL6fIQNznLsa/j/VaRaUqtfsWV5CTsTmEqaSJpOmm0+J60gfUpq+hs2N6RUUjrpTNIcUhXJxLmufJ8yPvVu5vMen60nJf+OPRJpCKnPUr4Hp/8ene1grPs0xuNiN8w+sDFiYsfjYQfHw97wWNjxONgbFgd71u98RlpFWkfqsh7dSOmkUtJc0jLSWlLyH1wL0liSmzSbVEWqJSX/yfdIU0mzSJWkGlLTv/45O71GWv8nKsWGr/+btfzHk8x+w4r30CR0jugGMy/4sneOCL/0jKL8fREeeX/84L3W+N+wvubmH003bZL5Iud5oXDzSJv/fJHzvND/z+/7ds980YIeZ574/dykJrm/Dx91RPOVpzTefBH3TdjfGTvpvb+bfmfsDGc3JZ/e/977Lbp3tfh72qZ/T2us/Uvi72ob/10tvm/Jhr+v9fgH36fiR/yIH/EjfsSPzeFotN//kwvMBMAG/f73xfSfmmZiXg8cPHjomDGuIUPHDB49LG2ssQFRVP89ydeWfPO9+cZhHDV62NjjXMNGHjbKpa/lFGfnkdczp7AwKcEfH3y6Q/z/05gsd6/wzCk4CDWWZNHbARa1D9gcSiYxUsLEBw8nE+2jsT30xQgvS7PGCLfLHu+wD8CNVL7MUbaMq6KQbY1nX71FaJvO4aRCMpwuUOT90e3turhDaLuOSHRu1/T65OZEnivytWuVrV3tdX4kMbRdb6bO1fXJpmmjua7WOh4hA/odJac=
*/