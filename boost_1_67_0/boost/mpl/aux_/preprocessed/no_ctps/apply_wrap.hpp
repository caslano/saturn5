
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
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
*/