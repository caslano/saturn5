
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
Tw+85riIad5LAPQAVVVPBzxprGWN7LV5KyU0N/49cvnb7746ONILM+kbZgT2YbiN/CHYctJk/vxH47fXqpakuCSRvLB6NWD4568XyUf/albqZDSVAsW7QQmVW4vpofLY3ESz2g9o28HfSn37eylXTQlgAZv8iyjFZ7Vm134n6/P1b1/g14PVhuPXSBt7cou7CqNIR6lX/0EikXpOAA2v1juyA1C4wC3+X1MfiiVxb4ulAyDEm+6zl77PgFdrYybx2ZqW10tUyekeBEqApt2iEJcDsj1V9lVYf4vPDIkhHXTv+4gkHGI7PCgl4QqCe8Vi3DHBUfTeak4YV+BY4XijsFN3KjV0+hvO8CmolKSqvq7RUDFTudwVpQSe5uidDG+pIA7hI5XHMI/88/T8MBhriFNovYWvJoKet/5zUFtn/4XrvkaKs5+JMgxOMHXWlf1jFaJxbydsmhCJ9LcBsOL2BZfe7yt9h2C1sS2JAgHjHXFj55dWCTv/cmRwl12+hqo3IoQEefX4/qMrsMz4qwB0WYmuuRHsUs9jvCVAt3RYX7SQF/dFmUX3jgT5yQ==
*/