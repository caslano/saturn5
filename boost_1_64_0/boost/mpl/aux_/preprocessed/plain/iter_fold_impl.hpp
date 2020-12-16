
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
Opy0kXH/faS7bWocv7901hbG2e8Azn5PcPZ7iPttXtz9fcPxNzac/Q7jrG2L++9ZnbWNekD9XWW64YlpPpNXbn/Td2b//cF/23Ptfv8x1X2W/V+OizO6us8n5T3fm+iLfK+roBl64wXsTCiV5WvJ8jUxQJa/nvm8sD6O4R/OXarjUv1k3Xs6XV1leV+H2nd25YzXi7TWXc6PtKu/LO/yrHWYfaMc12EuiyI+tK3DLPWXde/7DENILzrqX1Xe/1nqM2+Z4rxO84CpxIHxuBPl3aC5jrPD+s3S3+oV6zfLu0TqODt+nyj1nuW9oqn+sxG1daCrGJc+WR28a3RcJ7pejH3/rFUE0/vI6utFSx+tvKe01o+ufbmOIfCy5zc2z+AZPINn8AyewTN4hmsx/L7P/+nZSojLTk9NT/7t7/+VZ/skP+oxyvP2Lnne/os8279MaMCznjHS9Gw/cWrcyAw1KclJI+iujP5k1DGDG/1t1WN9ZMFSh/qTJtSXT15qqUOdS2BcrSEt3x1Vvx2bRKcdObIef5lmrnsdIMvNT0ugQoHuG9qa3xmUZUyrkb58JN/5Ui9/v+R7H8FHyXeUk3wnm8Zc+Y1D8m39RrbkuzcxJ6YaU5KzpG8pXVn4OigLf30+JV9SpjZtDXy87L9Z35j5oiab82Sp3l/t7yX6PDTV9OOi/giTkZqk+b65No3yXVupwy5pWivlXEjwJU0F1jQlUbxXvS9p9wmfq9wn+unaEcyStE4nNCW+kCk2aY1LpDaMK98ndrgfuLE9Q2tJe2vp168l+jNfsTU9cjRe/bE4mZiMi6zbcTbjiclZrPH3PxYHmdsdSH93/pJPX2xBOn2i9flUetXqFcfxUW3fms7yG+jt7Nwj7TfkmGTv1h5/jDMLavszzNLlNVXT18+Jvvx7arZl+x5vp4zbnoPqXS+/Fcn+9johgPQapznOtzEhO3tJZlaSK32L6vPfWJN/ZT3aY5e0q9PIocP8Xaomfxc1+dP+lttedshvZbt+ja2VY3+6k/yxIcx5C3Ajb67sy3b7pCaf6mUXlXPcOZmWnpCTmBJHjsx51pVBhbUM1HWdN687VW0eo9vutvv7MSmX1bLdVxACyUtljLVcUhckZ+eYzjQutUPTnWssZTIjgGlJUiYunHvMadwsPxW9Iml8iRCknHtm6tO4mM/mz196NfcDsk/anV98dOcX36s8v5jPo0XSX15N2Q9/IbRX8jLLkhe5urvSt1etRkWzLf2iquN5pvF0JljaPJXIvkd6bfPJBURz7GnvCRzmtbHse+zLtBdjTofnHOfXkBTpN++QbMdnZDtWzrbkfX5qRkKaa9uvVqPNsZq867en83xqt3H12zQ5x2absu55qZm29xVFspHiZZvGYkfScSbWkq/s1AUZLm3PHnNtt2eTudbt2VTyqJS/skLLtVFzzpHzluTVftv76stEf1/nwjZVvk2fxrbcSKRd+PeH55BGbKDZP/Jkv9fe05RJH3s7pZyKsXM/nGtTTnHsW8mpxhyX+gVuGW+/D7zQTikfuU90Ul4+DsrLV19e+rLRnKuVOLISc0iwnIMdXId7sq7MbNIh5UK5q8vIrmdXrg3k3L3bj3SxoLbsjA2kTZTcT7eTY6ck3lJ2uRnmO2oX3kFeq/Of9vjeIjH61WL7YiPsqhwHljTKCVrSN6CabVuWbN62vdXxacnVH+/67eeDP7MRs3Mys5J/w32ksg3PsG3U9fMIrMYhy57WnSvOyXh2YmYuEdjet0ga3md8v7KurDTL/U8508z7qvkcfF72m5x0I0mTc7DuXNRY9rcX+irLZszPzLbeG8qxoM5TYV2XcllWj+Mc9qsYpvVgfEI=
*/