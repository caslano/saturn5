
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

    : F::template apply<  >
{
};

template< typename F >
struct apply_wrap0< F,true_ >
    : F::apply
{
};

template<
      typename F, typename T1

    >
struct apply_wrap1

    : F::template apply<T1>
{
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

    : F::template apply< T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

    : F::template apply< T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

    : F::template apply< T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

    : F::template apply< T1,T2,T3,T4,T5 >
{
};

}}


/* apply_wrap.hpp
zMRmbzXniOalH7sH410gcfQ66z7xCbK8vjOtHsTh44JFua1bFJRfMniFBRcXGvCt7jrJm7Be7AmHu7trzuRQm41Va7jmkdvPQ5typmaFN+tq3CYpi47QToz5GEVHXqfooCFSYNzpChMuxbssJCN+fbfc7kHUe0Oi5QcI+Sj4iwlvYyKA6GlAPF/wuJt+KydewiLBxaVQt1wM+TQQR/uA3YO+Zd6JtdQQ6qZZnLf0189A+DoIfksZP93fEdg/sDw4d+VkIOvAy+WUYGMnuTa7AY38Xbz64+knQyn93jW1fad8fPgkeXwbipDrHJVT3Jmw0p6NY6/XOHIG2aqgQZO4hpEGCCzG/rIvGT1tzCDKdI6DeLPZRWhWqB7gOY1cGL00f6N+li6XT/nccP7pVXA6tu6ISlws7dEwkzJaAUxL84S0ZZXBY5we+9vyD/nxFpI1WPRf7A7NN1GNBuwUe58WoW5r5HezC2yVdjYERRNTgxxGB7xz+O7/qi9yQu0eB23T/TM9U8FR79IPQUcQWmoRkazBVj1FPC3xn9RfZVz1+NDaNZx59SDw0vY2Vg==
*/