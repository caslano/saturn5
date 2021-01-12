
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
Y+iuJW/uWoC+30WefNbT7GPnEzcb3U58nGr67yFOrw3GP7m/Bb8Mvl8osAf3j5E3yPOrdjPuA/C7jzhPvMgtJQ/PYb60h++ByDvLi0/w1ZdzO+prfxH56DPWK38ycPYKA/0PE1e+ox7twz73+8R77ktZ550ibqQ35dydffjFl/OeB3Ve7ivM9/6s76IN3LKJde0U5p+sXxXGD2MeRRHvjlDXpXBP/RfN+qn5ffB9Wbg5R+9J
*/