
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/list_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T, long C0 = LONG_MAX, long C1 = LONG_MAX, long C2 = LONG_MAX
    , long C3 = LONG_MAX, long C4 = LONG_MAX, long C5 = LONG_MAX
    , long C6 = LONG_MAX, long C7 = LONG_MAX, long C8 = LONG_MAX
    , long C9 = LONG_MAX, long C10 = LONG_MAX, long C11 = LONG_MAX
    , long C12 = LONG_MAX, long C13 = LONG_MAX, long C14 = LONG_MAX
    , long C15 = LONG_MAX, long C16 = LONG_MAX, long C17 = LONG_MAX
    , long C18 = LONG_MAX, long C19 = LONG_MAX
    >
struct list_c;

template<
      typename T
    >
struct list_c<
          T, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list0_c<T>
{
    typedef typename list0_c<T>::type type;
};

template<
      typename T, long C0
    >
struct list_c<
          T, C0, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list1_c< T,C0 >
{
    typedef typename list1_c< T,C0 >::type type;
};

template<
      typename T, long C0, long C1
    >
struct list_c<
          T, C0, C1, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list2_c< T,C0,C1 >
{
    typedef typename list2_c< T,C0,C1 >::type type;
};

template<
      typename T, long C0, long C1, long C2
    >
struct list_c<
          T, C0, C1, C2, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list3_c< T,C0,C1,C2 >
{
    typedef typename list3_c< T,C0,C1,C2 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3
    >
struct list_c<
          T, C0, C1, C2, C3, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list4_c< T,C0,C1,C2,C3 >
{
    typedef typename list4_c< T,C0,C1,C2,C3 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4
    >
struct list_c<
          T, C0, C1, C2, C3, C4, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list5_c< T,C0,C1,C2,C3,C4 >
{
    typedef typename list5_c< T,C0,C1,C2,C3,C4 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    >
struct list_c<
          T, C0, C1, C2, C3, C4, C5, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list6_c< T,C0,C1,C2,C3,C4,C5 >
{
    typedef typename list6_c< T,C0,C1,C2,C3,C4,C5 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6
    >
struct list_c<
          T, C0, C1, C2, C3, C4, C5, C6, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list7_c< T,C0,C1,C2,C3,C4,C5,C6 >
{
    typedef typename list7_c< T,C0,C1,C2,C3,C4,C5,C6 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7
    >
struct list_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX
        >
    : list8_c< T,C0,C1,C2,C3,C4,C5,C6,C7 >
{
    typedef typename list8_c< T,C0,C1,C2,C3,C4,C5,C6,C7 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8
    >
struct list_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX
        >
    : list9_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8 >
{
    typedef typename list9_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9
    >
struct list_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX
        >
    : list10_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9 >
{
    typedef typename list10_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10
    >
struct list_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list11_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10 >
{
    typedef typename list11_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11
    >
struct list_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list12_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11 >
{
    typedef typename list12_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    >
struct list_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list13_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12 >
{
    typedef typename list13_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13
    >
struct list_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list14_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13
        >
{
    typedef typename list14_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14
    >
struct list_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list15_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        >
{
    typedef typename list15_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15
    >
struct list_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list16_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15
        >
{
    typedef typename list16_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16
    >
struct list_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : list17_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16
        >
{
    typedef typename list17_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17
    >
struct list_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17, LONG_MAX, LONG_MAX
        >
    : list18_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17
        >
{
    typedef typename list18_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17, long C18
    >
struct list_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17, C18, LONG_MAX
        >
    : list19_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17, C18
        >
{
    typedef typename list19_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17,C18 >::type type;
};

/// primary template (not a specialization!)

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17, long C18, long C19
    >
struct list_c
    : list20_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17, C18, C19
        >
{
    typedef typename list20_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17,C18,C19 >::type type;
};

}}


/* list_c.hpp
e+pneFeV7VWT7VWX7dWQ7V0h26uJnbEW9kYfdIwhOSTbby7bV48hCZC+v+boiy3QD1tiMwx0lpdcg4G/Tnm9JNvZLfFfdsXj+slzOYdLvAHogwOd8QgSr55OvDYSLwjrYFuJR7nL9Q7XQXI+tlb2U+q3+plGrXAYtsfhGI4jcCiOwjF4NU7G0ZiAUTgbx+ByHItrcRxuxgmYjzG4Cyfim3gtfoKTsBCn4Dc4Fb/DaXK+xuI/8To0k+frsTnGYQjGYyhaMBKTMQFTcDregLfgTNyE6VKfM/BJnIX5mIVyfsj1F2Whc37skXJ+DRvh6zgI9+IQ3OcawyHXVewbob7mmUTd5TwOxQbYC/2wDwZgGHbGvhiK/bEfhuMoHIDjMQIn4WA8h8tMcu2Ed0m6dXG+pOsr6TbAYGwo228k2/eT7TeW7TfBydgUk7EZWrE5zsYWeAu2xNXYGtdhG+f3klwzYR2d87axlKc/XolN1PVE4gXoxNsl8Z7Hpljgisf1iefvz7Gy/9dIuUdj8fEiSLxZOserg9STbuiH3bElBmM3DMEB2BNHYi+Mxt44BftgCoZhOvZ1nidybQA366SbJ+luk/Qewx74OPbBJ3AgPomj8WmMxXy04A7MxWdwHj6rHiMm6dbVlJN2zipfHO38vJff6ThP5/N+veT3buyKGyW/m/F63IJz8F7Mk2cKHcr2KXM+JMfzhLaV+kyhy/88obCSzxS6rM8S0s6x5Pn5QeV/dpD/BJ35l/SfHSTPDSp7PqY/++ygv+ozgy7X84IuUId8bcz9RIgkxBMWErYQCgiFBFMO42sIYYTJhFzCekI+4TjhIsE8m2NHiCKkzTbG0hiLsRhL5S+Xpf+f/obK6P9X+vafUp7/r7n/v4e0n3aX9svgR1X9YhmWrASbxfu+lOwEe/ty1KOaPiOZcztI+tyzpE8rA5W0rY8659xWCs6WmuG4TUw7b7l+v9YD2zR97zpz+sv8227ziGfOLO5bv+Shb/2ie9+6/bnxwSQUyH4ksk47e7rSvu3cxkz7Prvm7/bc9qnfpuupTbTy2ib12269b4P0ti3W27ZJb9tuK6st3FPb7Xl7m2vWlprHjiQGW95+yu+X0xfHf+y5rVS/7dz7+7SKr+2ljkrd3a+5f6ihXFOasR42wjboh92xMdq3U0Xqm9TD/YS2ynZQWZrKNVAzNGMANsPm2BFbYh8MxHBsjcOxDU7AIJyMbXEqtsPp2BFvxE54M3bGNdgVN2I33Ird8QkMxiexB+7CUHwFe+M+7INvYhgex374B/bH2uxLOPriIPRHexsRDsVOOAx74EgMx0iMxFE4Aa/GOByNMzEKM3AMcilU2vWezJHrxTh7Yw7c/9s5cJdxnbLNuFYxFmMxFmMxFmP5r18uy/U/l7+Vdf2fb+b3r2NcqfzO306QvhnTTmXc78qS1//2+UQsNktWNmP2vB3PZLG5jaWSMaD29+rL88CyLZYkJqaxX4ObZT3lPXn+nP19f7RR4NMzczLISZxjuwG835r3U5R3JO1AnN2GdRNN9mv1nbw+xf4mYONV7B82kGv1HP6eJZlyXOtPYqOW2dZ0GXtqb8uoK/Fq9nQf/1pfxjZPq822cQz6sE7+Km1bhnOKF3v5FZp0lyWUH8e0n70two+UlHaN29cXt2tkkCHl9cm7HO0cnss6R6estftqRte+yjPadI5JgMTVHpNADKwu72fm2BzvB3k4Vh10jlUX17Gyv46W9pPJ8v9Yx3hBeW3VtOF0kf9nyP+Hae6niJBjnCL7lyL/t1lcz6CLUj97UN7Lle3OUkY6ynvzeW9/I/tYxBCTbL+DbG+6vLZpxjNO1tzPEe5qc7K/TuI=
*/