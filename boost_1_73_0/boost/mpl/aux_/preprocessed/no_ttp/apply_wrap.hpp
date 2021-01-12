
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
v/KXZ8txUOUYauvlt4prY/f9nY7Xysb9UXEf2bycENw8p078q+rU8bUvlYZTx36rOrjYluOs2q2BzXN4LbHbq3a7uoLbv9XGNRTcvNtt2aK1XS+bv4sEV/iE3fcnirvBriNiBVe+3R4vXnBDrrL5ay+4cSV2305K15mXXQRXscG2b6q2c/oKu77EaJtGH5Vtnc1Lf8Edzbf7Zil/v7DbDRVcobP+GKmy1bZpjNbx3rD1klvr
*/