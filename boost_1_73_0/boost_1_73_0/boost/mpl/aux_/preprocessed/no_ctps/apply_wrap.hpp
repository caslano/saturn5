
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
h3z5p9uXdR6+7AnIYvpK9F9Mfd1wmPgO7w0b/TvVGT4xkNZAPdp9Tka7zzMGaPfH8tLb/RjDbDklI6S2gz4U3JTEkIw3JGZDlIWjdzub3UkznCmo9VP67bzX5yWrSNLSJjNKZa5eV3rn6FinNDBqYSWJkcptzoBuUwK6C32e1tDWeXiJOw9Xe+Th7/3JCKeEwLv14+LVgpQ3AsXZ3VTBDTIyUJA+fpQLJzN4W686mVFJHVMl4SYnXccq4TbYdpc=
*/