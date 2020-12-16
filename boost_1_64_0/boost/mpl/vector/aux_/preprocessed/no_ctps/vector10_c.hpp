
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/vector/vector10_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T
    , T C0
    >
struct vector1_c
    : vector1< integral_c< T,C0 > >
{
    typedef vector1_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1
    >
struct vector2_c
    : vector2< integral_c< T,C0 >, integral_c< T,C1 > >
{
    typedef vector2_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2
    >
struct vector3_c
    : vector3< integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 > >
{
    typedef vector3_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3
    >
struct vector4_c
    : vector4<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >, integral_c<T
        , C3> 
 >
{
    typedef vector4_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4
    >
struct vector5_c
    : vector5<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 > 
 >
{
    typedef vector5_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5
    >
struct vector6_c
    : vector6<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 > 
 >
{
    typedef vector6_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6
    >
struct vector7_c
    : vector7<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 >, integral_c<T
        , C6> 
 >
{
    typedef vector7_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7
    >
struct vector8_c
    : vector8<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 >, integral_c< T,C6 >
        , integral_c< T,C7 > 
 >
{
    typedef vector8_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8
    >
struct vector9_c
    : vector9<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 >, integral_c< T,C6 >
        , integral_c< T,C7 >, integral_c< T,C8 > 
 >
{
    typedef vector9_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9
    >
struct vector10_c
    : vector10<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 >, integral_c< T,C6 >
        , integral_c< T,C7 >, integral_c< T,C8 >, integral_c< T,C9 > 
 >
{
    typedef vector10_c type;
    typedef T value_type;
};

}}

/* vector10_c.hpp
WvMNz3XT+xtTzK/7jqpn0AP4JfKe93vq3OnBPRvR8FP/HnQm/PuTaPfG0wHoDdmLouicMd4LDpeH1vj3teajY5w+iVY46gjzdJi8zD+RcAjd+Vg8M9Vz9DV/nr/+cvWbc/GNVv9vunO6jlKPphunrYRjT6C/GJ+W3eqvReJ+LB3yraCuIx/RldM998bT6V+nmudH+AWuicJb+Mn+sG+aw/QC94LeLU48Z71F3Dsq72fcxWdxqt8fzb+Hh6aap7Vj4G6fmzgIj34bnvnTzyXW0Uo++Ml0f/2Wjd9ZB6X8YK+pI/ZX7/IcCXBT8m3GO9o+7m39HM534r6V1Dw+m7Hi2Yvw6jX2VU+4hU6ca97S18Fh9Onql/Gf++h3x8t/IbpPHZ+P5+x8AX637hKGiFO/6h8/UF/fKHksTp4fbJ9/zX9QK379YZ5Ptu/wojWf4IFT4Z1bxLejrNeP7EPP1R70c0Z5/qX8Nvqgl4ijheZzVV/43HNVPy8vPeX7oulN1kPp4mj9OPgUfXfNPvgtPfIeOklVsG42iNerxLcPrQf6UPc9cCLdr+4Y9/Kc5s/R4m+ueI33tE3CB67E30/lBzsD36HX5wzXjzBLXv6APgs/t22lO38gzr4tLz0ljlzjXP4deFBsmL8TLulWfxkpr+hDylukr/Nf1lslnehL6+o1n3cY/AqPVTuHfz2eVnq6ustX8nHgrxtsHvGFjgj8eiv9Ps/67hLvjseLH8bXI3wuG/SBB/vjJjrPj/oa8bm6C+0r31dztD6V2fbln+L20eoy6sNJzuUpTPD+dNpM/fdF0bHiGZ2TDrz8LTxa32Q6P3QBHj/vas9zNh2ef6/tfuvrfPEgV5yv8T5z8QLjnT3e/5d3yyvEyafF5QK62MHyTi797yp60U/iy7/Vf/vR3fLgq2HOK/xK/D7WPpffO96O1hcD5zTCDeqy5frMFw/G1zx/HV264k46rvvO8nPgHs+7+QT1LXgjPiM4b5V/sB3uHBXiZ8fH28T7AuvqGuc5tdH//4qFi/G4HHVaumqrOtiC6fRj+LTjZ/F0GD/Bz+LM7z43xr7gq1mQR1/P0ZeXp858WQ/jiJcU4ku95LcS+Z9etfFm69p71PbwHMaxls5WzEdaow5dcD3/hXiTa96Tl6rv6YsqpAOFfsILv9J/WELn9t4JJzi3dLp8cox18yC+UIH/Gf/i0+GQodYbXXqO51gwFi/VF9g2oC89xnp+SxyIiGtPiJP4UCLfacR6y+uN31vPOeOD/eSciJv0zzxmHz4oH/8iPj1MVwl8vofKJ6P5W9eJ29X22f7GH37IiNafFEUvWmQ9L8N7l9Gt5uvfOF2dpBkOoTOlvhiWP+1X8S2LDrr4NDhsrn29L70yzvP5vW32bRMc14RPFq2hb3uOjRfKh8fAOa/ikwPVAen985rkcd/T1Cm+X2OepkTorxE+RnmJvl0/Vh9fmn1yuHgRwj8DfSJWnyg8mRFnfL8Wf+fR4dbAK/BsSiWd1/lZoRh1G76kUE/7gA9s8fvyb4t4/LX98Y46dR86wp3W7Wx8Xz1zWz4/7qV40750uPP4PTLoBEH9vkJ/R7V1ORpOeEm+mB9Sfwr0X/vocH7jX+hMB+ObcG+4v/eRV1Lq5LOX1avxgiT4olhfVPla+LzDOn9U/TMH3i+nh71AZxuur9J+imunQ9lPHfBtZyE80SUu289Np+ung4/y1MlDB4pT7lMLl4j/8kz1bHH+F7r3tfJPm/jymbz0irzyqLzZzh+lLhdaR1eIpifdpY8pg851kPlugNs20q0vtV+yxflv6SE94E51ycbX+Vy9XxFdufJ3v9dEF6m0b+kXy9Wxi4bB59Xe/wI=
*/