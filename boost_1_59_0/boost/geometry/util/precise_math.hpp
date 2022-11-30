// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2019 Tinko Bartels, Berlin, Germany.

// Contributed and/or modified by Tinko Bartels,
//   as part of Google Summer of Code 2019 program.

// This file was modified by Oracle on 2021.
// Modifications copyright (c) 2021, Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_TRIANGULATION_STRATEGIES_CARTESIAN_DETAIL_PRECISE_MATH_HPP
#define BOOST_GEOMETRY_EXTENSIONS_TRIANGULATION_STRATEGIES_CARTESIAN_DETAIL_PRECISE_MATH_HPP

#include<numeric>
#include<cmath>
#include<limits>
#include<array>

#include <boost/geometry/core/access.hpp>

// The following code is based on "Adaptive Precision Floating-Point Arithmetic
// and Fast Robust Geometric Predicates" by Richard Shewchuk,
// J. Discrete Comput Geom (1997) 18: 305. https://doi.org/10.1007/PL00009321

namespace boost { namespace geometry
{

namespace detail { namespace precise_math
{

// See Theorem 6, page 6
template
<
    typename RealNumber
>
inline std::array<RealNumber, 2> fast_two_sum(RealNumber const a,
                                              RealNumber const b)
{
    RealNumber x = a + b;
    RealNumber b_virtual = x - a;
    return {{x, b - b_virtual}};
}

// See Theorem 7, page 7 - 8
template
<
    typename RealNumber
>
inline std::array<RealNumber, 2> two_sum(RealNumber const a,
                                         RealNumber const b)
{
    RealNumber x = a + b;
    RealNumber b_virtual = x - a;
    RealNumber a_virtual = x - b_virtual;
    RealNumber b_roundoff = b - b_virtual;
    RealNumber a_roundoff = a - a_virtual;
    RealNumber y = a_roundoff + b_roundoff;
    return {{ x,  y }};
}

// See bottom of page 8
template
<
    typename RealNumber
>
inline RealNumber two_diff_tail(RealNumber const a,
                                RealNumber const b,
                                RealNumber const x)
{
    RealNumber b_virtual = a - x;
    RealNumber a_virtual = x + b_virtual;
    RealNumber b_roundoff = b_virtual - b;
    RealNumber a_roundoff = a - a_virtual;
    return a_roundoff + b_roundoff;
}

// see bottom of page 8
template
<
    typename RealNumber
>
inline std::array<RealNumber, 2> two_diff(RealNumber const a,
                                          RealNumber const b)
{
    RealNumber x = a - b;
    RealNumber y = two_diff_tail(a, b, x);
    return {{ x, y }};
}

// see theorem 18, page 19
template
<
    typename RealNumber
>
inline RealNumber two_product_tail(RealNumber const a,
                                   RealNumber const b,
                                   RealNumber const x)
{
    return std::fma(a, b, -x);
}

// see theorem 18, page 19
template
<
    typename RealNumber
>
inline std::array<RealNumber, 2> two_product(RealNumber const a,
                                             RealNumber const b)
{
    RealNumber x = a * b;
    RealNumber y = two_product_tail(a, b, x);
    return {{ x , y }};
}

// see theorem 12, figure 7, page 11 - 12,
// this is the 2 by 2 case for the corresponding diff-method
// note that this method takes input in descending order of magnitude and
// returns components in ascending order of magnitude
template
<
    typename RealNumber
>
inline std::array<RealNumber, 4> two_two_expansion_diff(
        std::array<RealNumber, 2> const a,
        std::array<RealNumber, 2> const b)
{
    std::array<RealNumber, 4> h;
    std::array<RealNumber, 2> Qh = two_diff(a[1], b[1]);
    h[0] = Qh[1];
    Qh = two_sum( a[0], Qh[0] );
    RealNumber _j = Qh[0];
    Qh = two_diff(Qh[1], b[0]);
    h[1] = Qh[1];
    Qh = two_sum( _j, Qh[0] );
    h[2] = Qh[1];
    h[3] = Qh[0];
    return h;
}

// see theorem 13, figure 8. This implementation uses zero elimination as
// suggested on page 17, second to last paragraph. Returns the number of
// non-zero components in the result and writes the result to h.
// the merger into a single sequence g is done implicitly
template
<
    typename RealNumber,
    std::size_t InSize1,
    std::size_t InSize2,
    std::size_t OutSize
>
inline int fast_expansion_sum_zeroelim(
        std::array<RealNumber, InSize1> const& e,
        std::array<RealNumber, InSize2> const& f,
        std::array<RealNumber, OutSize> & h,
        int m = InSize1,
        int n = InSize2)
{
    std::array<RealNumber, 2> Qh;
    int i_e = 0;
    int i_f = 0;
    int i_h = 0;
    if (std::abs(f[0]) > std::abs(e[0]))
    {
        Qh[0] = e[i_e++];
    }
    else
    {
        Qh[0] = f[i_f++];
    }
    i_h = 0;
    if ((i_e < m) && (i_f < n))
    {
        if (std::abs(f[i_f]) > std::abs(e[i_e]))
        {
            Qh = fast_two_sum(e[i_e++], Qh[0]);
        }
        else
        {
            Qh = fast_two_sum(f[i_f++], Qh[0]);
        }
        if (Qh[1] != 0.0)
        {
            h[i_h++] = Qh[1];
        }
        while ((i_e < m) && (i_f < n))
        {
            if (std::abs(f[i_f]) > std::abs(e[i_e]))
            {
                Qh = two_sum(Qh[0], e[i_e++]);
            }
            else
            {
                Qh = two_sum(Qh[0], f[i_f++]);
            }
            if (Qh[1] != 0.0)
            {
                h[i_h++] = Qh[1];
            }
        }
    }
    while (i_e < m)
    {
        Qh = two_sum(Qh[0], e[i_e++]);
        if (Qh[1] != 0.0)
        {
            h[i_h++] = Qh[1];
        }
    }
    while (i_f < n)
    {
        Qh = two_sum(Qh[0], f[i_f++]);
        if (Qh[1] != 0.0)
        {
            h[i_h++] = Qh[1];
        }
    }
    if ((Qh[0] != 0.0) || (i_h == 0))
    {
        h[i_h++] = Qh[0];
    }
    return i_h;
}

// see theorem 19, figure 13, page 20 - 21. This implementation uses zero
// elimination as suggested on page 17, second to last paragraph. Returns the
// number of non-zero components in the result and writes the result to h.
template
<
    typename RealNumber,
    std::size_t InSize
>
inline int scale_expansion_zeroelim(
        std::array<RealNumber, InSize> const& e,
        RealNumber const b,
        std::array<RealNumber, 2 * InSize> & h,
        int e_non_zeros = InSize)
{
    std::array<RealNumber, 2> Qh = two_product(e[0], b);
    int i_h = 0;
    if (Qh[1] != 0)
    {
        h[i_h++] = Qh[1];
    }
    for (int i_e = 1; i_e < e_non_zeros; i_e++)
    {
        std::array<RealNumber, 2> Tt = two_product(e[i_e], b);
        Qh = two_sum(Qh[0], Tt[1]);
        if (Qh[1] != 0)
        {
            h[i_h++] = Qh[1];
        }
        Qh = fast_two_sum(Tt[0], Qh[0]);
        if (Qh[1] != 0)
        {
            h[i_h++] = Qh[1];
        }
    }
    if ((Qh[0] != 0.0) || (i_h == 0))
    {
        h[i_h++] = Qh[0];
    }
    return i_h;
}

template<typename RealNumber>
struct vec2d
{
    RealNumber x;
    RealNumber y;
};

template
<
    typename RealNumber,
    std::size_t Robustness
>
inline RealNumber orient2dtail(vec2d<RealNumber> const& p1,
                               vec2d<RealNumber> const& p2,
                               vec2d<RealNumber> const& p3,
                               std::array<RealNumber, 2>& t1,
                               std::array<RealNumber, 2>& t2,
                               std::array<RealNumber, 2>& t3,
                               std::array<RealNumber, 2>& t4,
                               std::array<RealNumber, 2>& t5_01,
                               std::array<RealNumber, 2>& t6_01,
                               RealNumber const& magnitude)
{
    t5_01[1] = two_product_tail(t1[0], t2[0], t5_01[0]);
    t6_01[1] = two_product_tail(t3[0], t4[0], t6_01[0]);
    std::array<RealNumber, 4> tA_03 = two_two_expansion_diff(t5_01, t6_01);
    RealNumber det = std::accumulate(tA_03.begin(), tA_03.end(), static_cast<RealNumber>(0));
    if (Robustness == 1)
    {
        return det;
    }
    // see p.39, mind the different definition of epsilon for error bound
    RealNumber B_relative_bound =
          (1 + 3 * std::numeric_limits<RealNumber>::epsilon())
        * std::numeric_limits<RealNumber>::epsilon();
    RealNumber absolute_bound = B_relative_bound * magnitude;
    if (std::abs(det) >= absolute_bound)
    {
        return det; //B estimate
    }
    t1[1] = two_diff_tail(p1.x, p3.x, t1[0]);
    t2[1] = two_diff_tail(p2.y, p3.y, t2[0]);
    t3[1] = two_diff_tail(p1.y, p3.y, t3[0]);
    t4[1] = two_diff_tail(p2.x, p3.x, t4[0]);

    if ((t1[1] == 0) && (t3[1] == 0) && (t2[1] == 0) && (t4[1] == 0))
    {
        return det; //If all tails are zero, there is noething else to compute
    }
    RealNumber sub_bound =
          (1.5 + 2 * std::numeric_limits<RealNumber>::epsilon())
        * std::numeric_limits<RealNumber>::epsilon();
    // see p.39, mind the different definition of epsilon for error bound
    RealNumber C_relative_bound =
          (2.25 + 8 * std::numeric_limits<RealNumber>::epsilon())
        * std::numeric_limits<RealNumber>::epsilon()
        * std::numeric_limits<RealNumber>::epsilon();
    absolute_bound = C_relative_bound * magnitude + sub_bound * std::abs(det);
    det += (t1[0] * t2[1] + t2[0] * t1[1]) - (t3[0] * t4[1] + t4[0] * t3[1]);
    if (Robustness == 2 || std::abs(det) >= absolute_bound)
    {
        return det; //C estimate
    }
    std::array<RealNumber, 8> D_left;
    int D_left_nz;
    {
        std::array<RealNumber, 2> t5_23 = two_product(t1[1], t2[0]);
        std::array<RealNumber, 2> t6_23 = two_product(t3[1], t4[0]);
        std::array<RealNumber, 4> tA_47 = two_two_expansion_diff(t5_23, t6_23);
        D_left_nz = fast_expansion_sum_zeroelim(tA_03, tA_47, D_left);
    }
    std::array<RealNumber, 8> D_right;
    int D_right_nz;
    {
        std::array<RealNumber, 2> t5_45 = two_product(t1[0], t2[1]);
        std::array<RealNumber, 2> t6_45 = two_product(t3[0], t4[1]);
        std::array<RealNumber, 4> tA_8_11 = two_two_expansion_diff(t5_45, t6_45);
        std::array<RealNumber, 2> t5_67 = two_product(t1[1], t2[1]);
        std::array<RealNumber, 2> t6_67 = two_product(t3[1], t4[1]);
        std::array<RealNumber, 4> tA_12_15 = two_two_expansion_diff(t5_67, t6_67);
        D_right_nz = fast_expansion_sum_zeroelim(tA_8_11, tA_12_15, D_right);
    }
    std::array<RealNumber, 16> D;
    int D_nz = fast_expansion_sum_zeroelim(D_left, D_right, D, D_left_nz, D_right_nz);
    // only return component of highest magnitude because we mostly care about the sign.
    return(D[D_nz - 1]);
}

// see page 38, Figure 21 for the calculations, notation follows the notation
// in the figure.
template
<
    typename RealNumber,
    std::size_t Robustness = 3,
    typename EpsPolicy
>
inline RealNumber orient2d(vec2d<RealNumber> const& p1,
                           vec2d<RealNumber> const& p2,
                           vec2d<RealNumber> const& p3,
                           EpsPolicy& eps_policy)
{
    std::array<RealNumber, 2> t1, t2, t3, t4;
    t1[0] = p1.x - p3.x;
    t2[0] = p2.y - p3.y;
    t3[0] = p1.y - p3.y;
    t4[0] = p2.x - p3.x;

    eps_policy = EpsPolicy(t1[0], t2[0], t3[0], t4[0]);

    std::array<RealNumber, 2> t5_01, t6_01;
    t5_01[0] = t1[0] * t2[0];
    t6_01[0] = t3[0] * t4[0];
    RealNumber det = t5_01[0] - t6_01[0];

    if (Robustness == 0)
    {
        return det;
    }

    RealNumber const magnitude = std::abs(t5_01[0]) + std::abs(t6_01[0]);

    // see p.39, mind the different definition of epsilon for error bound
    RealNumber const A_relative_bound =
          (1.5 + 4 * std::numeric_limits<RealNumber>::epsilon())
        * std::numeric_limits<RealNumber>::epsilon();
    RealNumber absolute_bound = A_relative_bound * magnitude;
    if ( std::abs(det) >= absolute_bound )
    {
        return det; //A estimate
    }

    if ( (t5_01[0] > 0 && t6_01[0] <= 0) || (t5_01[0] < 0 && t6_01[0] >= 0) )
    {
        //if diagonal and antidiagonal have different sign, the sign of det is
        //obvious
        return det;
    }
    return orient2dtail<RealNumber, Robustness>(p1, p2, p3, t1, t2, t3, t4,
                                                t5_01, t6_01, magnitude);
}

// This method adaptively computes increasingly precise approximations of the following
// determinant using Laplace expansion along the last column.
// det A =
//      | p1_x - p4_x    p1_y - p4_y     ( p1_x - p4_x ) ^ 2 + ( p1_y - p4_y ) ^ 2 |
//      | p2_x - p4_x    p2_y - p4_y     ( p2_x - p4_x ) ^ 2 + ( p1_y - p4_y ) ^ 2 |
//      | p3_x - p4_x    p3_y - p4_y     ( p3_x - p4_x ) ^ 2 + ( p3_y - p4_y ) ^ 2 |
// = a_13 * C_13 + a_23 * C_23 + a_33 * C_33
// where a_ij is the i-j-entry and C_ij is the i_j Cofactor

template
<
    typename RealNumber,
    std::size_t Robustness = 2
>
RealNumber incircle(std::array<RealNumber, 2> const& p1,
                    std::array<RealNumber, 2> const& p2,
                    std::array<RealNumber, 2> const& p3,
                    std::array<RealNumber, 2> const& p4)
{
    RealNumber A_11 = p1[0] - p4[0];
    RealNumber A_21 = p2[0] - p4[0];
    RealNumber A_31 = p3[0] - p4[0];
    RealNumber A_12 = p1[1] - p4[1];
    RealNumber A_22 = p2[1] - p4[1];
    RealNumber A_32 = p3[1] - p4[1];

    std::array<RealNumber, 2> A_21_x_A_32,
                              A_31_x_A_22,
                              A_31_x_A_12,
                              A_11_x_A_32,
                              A_11_x_A_22,
                              A_21_x_A_12;
    A_21_x_A_32[0] = A_21 * A_32;
    A_31_x_A_22[0] = A_31 * A_22;
    RealNumber A_13 = A_11 * A_11 + A_12 * A_12;

    A_31_x_A_12[0] = A_31 * A_12;
    A_11_x_A_32[0] = A_11 * A_32;
    RealNumber A_23 = A_21 * A_21 + A_22 * A_22;

    A_11_x_A_22[0] = A_11 * A_22;
    A_21_x_A_12[0] = A_21 * A_12;
    RealNumber A_33 = A_31 * A_31 + A_32 * A_32;

    RealNumber det = A_13 * (A_21_x_A_32[0] - A_31_x_A_22[0])
      + A_23 * (A_31_x_A_12[0] - A_11_x_A_32[0])
      + A_33 * (A_11_x_A_22[0] - A_21_x_A_12[0]);
    if(Robustness == 0) return det;

    RealNumber magnitude =
          (std::abs(A_21_x_A_32[0]) + std::abs(A_31_x_A_22[0])) * A_13
        + (std::abs(A_31_x_A_12[0]) + std::abs(A_11_x_A_32[0])) * A_23
        + (std::abs(A_11_x_A_22[0]) + std::abs(A_21_x_A_12[0])) * A_33;
    RealNumber A_relative_bound =
          (5 + 24 * std::numeric_limits<RealNumber>::epsilon())
        * std::numeric_limits<RealNumber>::epsilon();
    RealNumber absolute_bound = A_relative_bound * magnitude;
    if (std::abs(det) > absolute_bound)
    {
        return det;
    }
    // (p2_x - p4_x) * (p3_y - p4_y)
    A_21_x_A_32[1] = two_product_tail(A_21, A_32, A_21_x_A_32[0]);
    // (p3_x - p4_x) * (p2_y - p4_y)
    A_31_x_A_22[1] = two_product_tail(A_31, A_22, A_31_x_A_22[0]);
    // (bx - dx) * (cy - dy) - (cx - dx) * (by - dy)
    std::array<RealNumber, 4> C_13 = two_two_expansion_diff(A_21_x_A_32, A_31_x_A_22);
    std::array<RealNumber, 8> C_13_x_A11;
    // ( (bx - dx) * (cy - dy) - (cx - dx) * (by - dy) ) * ( ax - dx )
    int C_13_x_A11_nz = scale_expansion_zeroelim(C_13, A_11, C_13_x_A11);
    std::array<RealNumber, 16> C_13_x_A11_sq;
    // ( (bx - dx) * (cy - dy) - (cx - dx) * (by - dy) ) * ( ax - dx ) * (ax - dx)
    int C_13_x_A11_sq_nz = scale_expansion_zeroelim(C_13_x_A11,
                                                    A_11,
                                                    C_13_x_A11_sq,
                                                    C_13_x_A11_nz);

    std::array<RealNumber, 8> C_13_x_A12;
    // ( (bx - dx) * (cy - dy) - (cx - dx) * (by - dy) ) * ( ay - dy )
    int C_13_x_A12_nz = scale_expansion_zeroelim(C_13, A_12, C_13_x_A12);

    std::array<RealNumber, 16> C_13_x_A12_sq;
    // ( (bx - dx) * (cy - dy) - (cx - dx) * (by - dy) ) * ( ay - dy ) * ( ay - dy )
    int C_13_x_A12_sq_nz = scale_expansion_zeroelim(C_13_x_A12, A_12,
                                                    C_13_x_A12_sq,
                                                    C_13_x_A12_nz);

    std::array<RealNumber, 32> A_13_x_C13;
    //   ( (bx - dx) * (cy - dy) - (cx - dx) * (by - dy) )
    // * ( ( ay - dy ) * ( ay - dy ) + ( ax - dx ) * (ax - dx) )
    int A_13_x_C13_nz = fast_expansion_sum_zeroelim(C_13_x_A11_sq,
                                                    C_13_x_A12_sq,
                                                    A_13_x_C13,
                                                    C_13_x_A11_sq_nz,
                                                    C_13_x_A12_sq_nz);

    // (cx - dx) * (ay - dy)
    A_31_x_A_12[1] = two_product_tail(A_31, A_12, A_31_x_A_12[0]);
    // (ax - dx) * (cy - dy)
    A_11_x_A_32[1] = two_product_tail(A_11, A_32, A_11_x_A_32[0]);
    // (cx - dx) * (ay - dy) - (ax - dx) * (cy - dy)
    std::array<RealNumber, 4> C_23 = two_two_expansion_diff(A_31_x_A_12,
                                                            A_11_x_A_32);
    std::array<RealNumber, 8> C_23_x_A_21;
    // ( (cx - dx) * (ay - dy) - (ax - dx) * (cy - dy) ) * ( bx - dx )
    int C_23_x_A_21_nz = scale_expansion_zeroelim(C_23, A_21, C_23_x_A_21);
    std::array<RealNumber, 16> C_23_x_A_21_sq;
    // ( (cx - dx) * (ay - dy) - (ax - dx) * (cy - dy) ) * ( bx - dx ) * ( bx - dx )
    int C_23_x_A_21_sq_nz = scale_expansion_zeroelim(C_23_x_A_21, A_21,
                                                     C_23_x_A_21_sq,
                                                     C_23_x_A_21_nz);
    std::array<RealNumber, 8>  C_23_x_A_22;
    // ( (cx - dx) * (ay - dy) - (ax - dx) * (cy - dy) ) * ( by - dy )
    int C_23_x_A_22_nz = scale_expansion_zeroelim(C_23, A_22, C_23_x_A_22);
    std::array<RealNumber, 16> C_23_x_A_22_sq;
    // ( (cx - dx) * (ay - dy) - (ax - dx) * (cy - dy) ) * ( by - dy ) * ( by - dy )
    int C_23_x_A_22_sq_nz = scale_expansion_zeroelim(C_23_x_A_22, A_22,
                                                     C_23_x_A_22_sq,
                                                     C_23_x_A_22_nz);
    std::array<RealNumber, 32> A_23_x_C_23;
    //   ( (cx - dx) * (ay - dy) - (ax - dx) * (cy - dy) )
    // * ( ( bx - dx ) * ( bx - dx ) + ( by - dy ) * ( by - dy ) )
    int A_23_x_C_23_nz = fast_expansion_sum_zeroelim(C_23_x_A_21_sq,
                                                     C_23_x_A_22_sq,
                                                     A_23_x_C_23,
                                                     C_23_x_A_21_sq_nz,
                                                     C_23_x_A_22_sq_nz);

    // (ax - dx) * (by - dy)
    A_11_x_A_22[1] = two_product_tail(A_11, A_22, A_11_x_A_22[0]);
    // (bx - dx) * (ay - dy)
    A_21_x_A_12[1] = two_product_tail(A_21, A_12, A_21_x_A_12[0]);
    // (ax - dx) * (by - dy) - (bx - dx) * (ay - dy)
    std::array<RealNumber, 4> C_33 = two_two_expansion_diff(A_11_x_A_22,
                                                            A_21_x_A_12);
    std::array<RealNumber, 8>  C_33_x_A31;
    // ( (ax - dx) * (by - dy) - (bx - dx) * (ay - dy) ) * ( cx - dx )
    int C_33_x_A31_nz = scale_expansion_zeroelim(C_33, A_31, C_33_x_A31);
    std::array<RealNumber, 16> C_33_x_A31_sq;
    // ( (ax - dx) * (by - dy) - (bx - dx) * (ay - dy) ) * ( cx - dx ) * ( cx - dx )
    int C_33_x_A31_sq_nz = scale_expansion_zeroelim(C_33_x_A31, A_31,
                                                    C_33_x_A31_sq,
                                                    C_33_x_A31_nz);
    std::array<RealNumber, 8>  C_33_x_A_32;
    // ( (ax - dx) * (by - dy) - (bx - dx) * (ay - dy) ) * ( cy - dy )
    int C_33_x_A_32_nz = scale_expansion_zeroelim(C_33, A_32, C_33_x_A_32);
    std::array<RealNumber, 16> C_33_x_A_32_sq;
    // ( (ax - dx) * (by - dy) - (bx - dx) * (ay - dy) ) * ( cy - dy ) * ( cy - dy )
    int C_33_x_A_32_sq_nz = scale_expansion_zeroelim(C_33_x_A_32, A_32,
                                                     C_33_x_A_32_sq,
                                                     C_33_x_A_32_nz);

    std::array<RealNumber, 32> A_33_x_C_33;
    int A_33_x_C_33_nz = fast_expansion_sum_zeroelim(C_33_x_A31_sq,
                                                     C_33_x_A_32_sq,
                                                     A_33_x_C_33,
                                                     C_33_x_A31_sq_nz,
                                                     C_33_x_A_32_sq_nz);
    std::array<RealNumber, 64> A_13_x_C13_p_A_13_x_C13;
    int A_13_x_C13_p_A_13_x_C13_nz = fast_expansion_sum_zeroelim(
            A_13_x_C13, A_23_x_C_23,
            A_13_x_C13_p_A_13_x_C13,
            A_13_x_C13_nz,
            A_23_x_C_23_nz);
    std::array<RealNumber, 96> det_expansion;
    int det_expansion_nz = fast_expansion_sum_zeroelim(
            A_13_x_C13_p_A_13_x_C13,
            A_33_x_C_33,
            det_expansion,
            A_13_x_C13_p_A_13_x_C13_nz,
            A_33_x_C_33_nz);

    det = std::accumulate(det_expansion.begin(),
                          det_expansion.begin() + det_expansion_nz,
                          static_cast<RealNumber>(0));
    if(Robustness == 1) return det;
    RealNumber B_relative_bound =
          (2 + 12 * std::numeric_limits<RealNumber>::epsilon())
        * std::numeric_limits<RealNumber>::epsilon();
    absolute_bound = B_relative_bound * magnitude;
    if (std::abs(det) >= absolute_bound)
    {
        return det;
    }
    RealNumber A_11tail = two_diff_tail(p1[0], p4[0], A_11);
    RealNumber A_12tail = two_diff_tail(p1[1], p4[1], A_12);
    RealNumber A_21tail = two_diff_tail(p2[0], p4[0], A_21);
    RealNumber A_22tail = two_diff_tail(p2[1], p4[1], A_22);
    RealNumber A_31tail = two_diff_tail(p3[0], p4[0], A_31);
    RealNumber A_32tail = two_diff_tail(p3[1], p4[1], A_32);
    if ((A_11tail == 0) && (A_21tail == 0) && (A_31tail == 0)
        && (A_12tail == 0) && (A_22tail == 0) && (A_32tail == 0))
    {
        return det;
    }
    //  RealNumber sub_bound =  (1.5 + 2.0 * std::numeric_limits<RealNumber>::epsilon())
    //    * std::numeric_limits<RealNumber>::epsilon();
    //  RealNumber C_relative_bound = (11.0 + 72.0 * std::numeric_limits<RealNumber>::epsilon())
    //    * std::numeric_limits<RealNumber>::epsilon()
    //    * std::numeric_limits<RealNumber>::epsilon();
    //absolute_bound = C_relative_bound * magnitude + sub_bound * std::abs(det);
    det += ((A_11 * A_11 + A_12 * A_12) * ((A_21 * A_32tail + A_32 * A_21tail)
        - (A_22 * A_31tail + A_31 * A_22tail))
    + 2 * (A_11 * A_11tail + A_12 * A_12tail) * (A_21 * A_32 - A_22 * A_31))
    + ((A_21 * A_21 + A_22 * A_22) * ((A_31 * A_12tail + A_12 * A_31tail)
        - (A_32 * A_11tail + A_11 * A_32tail))
    + 2 * (A_21 * A_21tail + A_22 * A_22tail) * (A_31 * A_12 - A_32 * A_11))
    + ((A_31 * A_31 + A_32 * A_32) * ((A_11 * A_22tail + A_22 * A_11tail)
        - (A_12 * A_21tail + A_21 * A_12tail))
    + 2 * (A_31 * A_31tail + A_32 * A_32tail) * (A_11 * A_22 - A_12 * A_21));
    //if (std::abs(det) >= absolute_bound)
    //{
    return det;
    //}
}

}} // namespace detail::precise_math

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_TRIANGULATION_STRATEGIES_CARTESIAN_DETAIL_PRECISE_MATH_HPP

/* precise_math.hpp
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
*/