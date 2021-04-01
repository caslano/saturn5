
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
iP7UB6e+IJyGnKUCnediiXXxmq46t+eeiVBJL0C7LOmlIiTYeoUP1M+ExLfYT19mmEJfLToRwtC6PE/KbS8qLMYu912Sku4SLwHNES5TCSYeEcR5TB1ESTQ5Z0wvvy5RXx9yfsg2sjasncBC53OdmFtnUSGMTnbNEpF+yPqKc7WaDeB48LHaCIZYQG6YRM00edPFtFP9ZhMg3TYG+X4JHzEVAk5rT1ZXdYKys1qgMlufxZqaQcp4WtbQsxfSAL2QNxULECUceHxu/2/lZGctXEOK/QjMcg4raqkahs67wwgbvk0PbiXXPXE+y6z1LR9l2cVDA48DY3aB/CkGt8uopc4GdPxFRg+yUOhNpO6xkxjk/VRDdTjXFLgqgz362Jd4Rj52V7MRTwFZEmBHqFvUC19fs3FK0dhKOs8bxEpqsL7a82A8ekaZmi48fceBT3LcDQf9+QQKyRzKEPYXQG89RkgdQXkVVVZByaUftFE4m8DRzYIZbitfKKNWXeTIq8vqJD4R1S06Ian1ziOhyDbw+xwet0z1mhTgkWLk91X3/2pwZqnwEcJJ7QEYXQ==
*/