
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
Pe7ZF9pjobS2s5D1pY7q4vdsE71ZW0fqFYyPmowVVsH169vN7jrRX8f9rg/ltROUy/NZ9T4v2lIcGfpxzUlQGWvc/R1Ajgn3Z8xzLvB8xuQc4nXclMoR11jGUAvHH9i2YIu2TvLyc+Sz0RQNFv1YXudVF5EG33OO664rJzxlVsehOlKb/R/h/L2s51YZh0rqpj7PFNTa0oxD1U/KP5x/lUWhivwm9pPyuVHjqGSflaxeYkeMGjNkfMJQ9YNa4Zg+rrIrzxvss+T6I+ltqeN7/3wmln+eMEpPHas/Jz8rq8I0tWVqWte3TL+SRoRJGvnZFY9T5CrTz1ImbXrLDdL7jffFGKdny7X5n94hg/TC6znfGSXpKau/875Ek/Ty7RkBp6d+J5LzvM2R57UPVxikX6kn7/NOX5JPs2ZZHVaLH2N1ufJwUJcHuTZq6oAlUl/nSB5WGOWhwuuLcfraMqdF+h63IaRXZJCe57CtOE1tmQ4blCmUNIoN0+CwDaBOL+rpexwlRfnux+q876hvenIY+Z+efh+Ok+PIq7wG6YeTvmWbUfrKGdL/cw/l9T2G0uZ5pT+kvm99l5GZaO/0rxqYMF6t7kCO4W+jfOt7b33f8v7ISrxBempxAzhmSc+0vOo8AhewvVGg82iYtDcyaVdk1o4n8PY6xu1vAh/jK9B2OYG2WzJunxR4e51A2yeZtEMybU/2D7Vd0ddP7FnZYsuv1WsU/tj2xAMFT5q1EzJrf2bezuy0OnaQ/L6AnxDiqfvauFiO+g9lrLBj2Bw/wTb4KQ7AzzARv8BJ+CVm4de4DL/BO/BbvBtP4Wb8Dl/G7/ED/AE/wh/dYyrJ7wpYgxCvazf0qowZtg/D8DXNdvGyXXWD7V6S7V7GUNyr2S7xLOk9Idttk/SKtGM/nWW73bLdM7LdHs12trNst0O22ynb7dJsVyDb1TLYbr9sdwDD8U3NdoVn2e452e552e4F2S6eUCzbdZDttGO3rZPt1mMzLMSL8SFsjw970ueP5uU9KPG8LeU95NmO573m+X5XtntP8l0q200kxMh2V8t22jHwFslxvRhb4M3YDZfgZbgUB+AyHIW34AS8FWW+EnkGqz6bJX7v+UpGSnu2URiJY7ExXoltMAk74HgcgBNwHE7ETJyMuXg1OnAKXo/JeBem4P04HVdjGj6PVjyI6XgaZ+AZzEAls5lYFWdiNczCcMyR95da5Dkrviv11hD3S7nypFx2KZcDm2A+tsI52BXnYk+ch71xPl6GC3AoLsQr8DochdfjGLwBx+ONOAsXIcGyGJfizXgHLsUVeCtuxNtxK96BL+Od+BbehW/j3VK+Aos8W8VdUr6a6JDypcpxkY51MQN7YyYm4CxMxSy0Yg7Ow1xcjDZcgrNxFebhRrTjdszH03jUIs9UsZscP434/2HJR+XK5AMvwnpYDTtiKHbHGtgHa2J/rIVTsDbOwDq4AOvi7VgPCzEKN2B93I4N8VVshAewMR7DJngSm6FynLTAmhiNdbElNsRW2AJbY3tsg52xLTrHjJNnnRgp9a0dM26DfH43Yihuknp/DN3zSMn2IVJP2nmkjsvx+BlG4ufYDL/AdngCY/BL7I1f4Wj8GpPwJF6N32IqnsIbsAyX4Xd4F57GB/F7LMJy3Ik/4et4Bj/FfyHB8jP+hgT1c/dvOf7mWeT5Jjws9RGOWVKeanL81cAWWBPbYi2MwQgcgHXRivVwPkbifRiFq7E+rsWGuB4bS31mEEok/cWSfnWcIunfKftjBYbhXVgD78b6eA+2w3uxH67EcXgfZuH9uAhXua8f8uwRBxH0149rJb35WAcXYAdciPF4HZ6WOfOPSjwvynHQRjk=
*/