// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015, 2019.
// Modifications copyright (c) 2015-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_SIDE_OF_INTERSECTION_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_SIDE_OF_INTERSECTION_HPP


#include <limits>

#include <boost/core/ignore_unused.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/make_unsigned.hpp>

#include <boost/geometry/arithmetic/determinant.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/strategies/cartesian/side_by_triangle.hpp>
#include <boost/geometry/util/math.hpp>

#ifdef BOOST_GEOMETRY_SIDE_OF_INTERSECTION_DEBUG
#include <boost/math/common_factor_ct.hpp>
#include <boost/math/common_factor_rt.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#endif

namespace boost { namespace geometry
{

namespace strategy { namespace side
{

namespace detail
{

// A tool for multiplication of integers avoiding overflow
// It's a temporary workaround until we can use Multiprecision
// The algorithm is based on Karatsuba algorithm
// see: http://en.wikipedia.org/wiki/Karatsuba_algorithm
template <typename T>
struct multiplicable_integral
{
    // Currently this tool can't be used with non-integral coordinate types.
    // Also side_of_intersection strategy sign_of_product() and sign_of_compare()
    // functions would have to be modified to properly support floating-point
    // types (comparisons and multiplication).
    BOOST_STATIC_ASSERT(boost::is_integral<T>::value);

    static const std::size_t bits = CHAR_BIT * sizeof(T);
    static const std::size_t half_bits = bits / 2;
    typedef typename boost::make_unsigned<T>::type unsigned_type;
    static const unsigned_type base = unsigned_type(1) << half_bits; // 2^half_bits

    int m_sign;
    unsigned_type m_ms;
    unsigned_type m_ls;

    multiplicable_integral(int sign, unsigned_type ms, unsigned_type ls)
        : m_sign(sign), m_ms(ms), m_ls(ls)
    {}

    explicit multiplicable_integral(T const& val)
    {
        unsigned_type val_u = val > 0 ?
                                unsigned_type(val)
                              : val == (std::numeric_limits<T>::min)() ?
                                  unsigned_type((std::numeric_limits<T>::max)()) + 1
                                : unsigned_type(-val);
        // MMLL -> S 00MM 00LL
        m_sign = math::sign(val);
        m_ms = val_u >> half_bits; // val_u / base
        m_ls = val_u - m_ms * base;
    }
    
    friend multiplicable_integral operator*(multiplicable_integral const& a,
                                            multiplicable_integral const& b)
    {
        // (S 00MM 00LL) * (S 00MM 00LL) -> (S Z2MM 00LL)
        unsigned_type z2 = a.m_ms * b.m_ms;
        unsigned_type z0 = a.m_ls * b.m_ls;
        unsigned_type z1 = (a.m_ms + a.m_ls) * (b.m_ms + b.m_ls) - z2 - z0;
        // z0 may be >= base so it must be normalized to allow comparison
        unsigned_type z0_ms = z0 >> half_bits; // z0 / base
        return multiplicable_integral(a.m_sign * b.m_sign,
                                      z2 * base + z1 + z0_ms,
                                      z0 - base * z0_ms);
    }

    friend bool operator<(multiplicable_integral const& a,
                          multiplicable_integral const& b)
    {
        if ( a.m_sign == b.m_sign )
        {
            bool u_less = a.m_ms < b.m_ms
                      || (a.m_ms == b.m_ms && a.m_ls < b.m_ls);
            return a.m_sign > 0 ? u_less : (! u_less);
        }
        else
        {
            return a.m_sign < b.m_sign;
        }
    }

    friend bool operator>(multiplicable_integral const& a,
                          multiplicable_integral const& b)
    {
        return b < a;
    }

#ifdef BOOST_GEOMETRY_SIDE_OF_INTERSECTION_DEBUG
    template <typename CmpVal>
    void check_value(CmpVal const& cmp_val) const
    {
        unsigned_type b = base; // a workaround for MinGW - undefined reference base
        CmpVal val = CmpVal(m_sign) * (CmpVal(m_ms) * CmpVal(b) + CmpVal(m_ls));
        BOOST_GEOMETRY_ASSERT(cmp_val == val);
    }
#endif // BOOST_GEOMETRY_SIDE_OF_INTERSECTION_DEBUG
};

} // namespace detail

// Calculates the side of the intersection-point (if any) of
// of segment a//b w.r.t. segment c
// This is calculated without (re)calculating the IP itself again and fully
// based on integer mathematics; there are no divisions
// It can be used for either integer (rescaled) points, and also for FP
class side_of_intersection
{
private :
    template <typename T, typename U>
    static inline
    int sign_of_product(T const& a, U const& b)
    {
        return a == 0 || b == 0 ? 0
            : a > 0 && b > 0 ? 1
            : a < 0 && b < 0 ? 1
            : -1;
    }

    template <typename T>
    static inline
    int sign_of_compare(T const& a, T const& b, T const& c, T const& d)
    {
        // Both a*b and c*d are positive
        // We have to judge if a*b > c*d

        using side::detail::multiplicable_integral;
        multiplicable_integral<T> ab = multiplicable_integral<T>(a)
                                     * multiplicable_integral<T>(b);
        multiplicable_integral<T> cd = multiplicable_integral<T>(c)
                                     * multiplicable_integral<T>(d);
        
        int result = ab > cd ? 1
                   : ab < cd ? -1
                   : 0
                   ;

#ifdef BOOST_GEOMETRY_SIDE_OF_INTERSECTION_DEBUG
        using namespace boost::multiprecision;
        cpp_int const lab = cpp_int(a) * cpp_int(b);
        cpp_int const lcd = cpp_int(c) * cpp_int(d);

        ab.check_value(lab);
        cd.check_value(lcd);

        int result2 = lab > lcd ? 1
                    : lab < lcd ? -1
                    : 0
                    ;
        BOOST_GEOMETRY_ASSERT(result == result2);
#endif

        return result;
    }

    template <typename T>
    static inline
    int sign_of_addition_of_two_products(T const& a, T const& b, T const& c, T const& d)
    {
        // sign of a*b+c*d, 1 if positive, -1 if negative, else 0
        int const ab = sign_of_product(a, b);
        int const cd = sign_of_product(c, d);
        if (ab == 0)
        {
            return cd;
        }
        if (cd == 0)
        {
            return ab;
        }

        if (ab == cd)
        {
            // Both positive or both negative
            return ab;
        }

        // One is positive, one is negative, both are non zero
        // If ab is positive, we have to judge if a*b > -c*d (then 1 because sum is positive)
        // If ab is negative, we have to judge if c*d > -a*b (idem)
        return ab == 1
            ? sign_of_compare(a, b, -c, d)
            : sign_of_compare(c, d, -a, b);
    }


public :

    // Calculates the side of the intersection-point (if any) of
    // of segment a//b w.r.t. segment c
    // This is calculated without (re)calculating the IP itself again and fully
    // based on integer mathematics
    template <typename T, typename Segment, typename Point>
    static inline T side_value(Segment const& a, Segment const& b,
                Segment const& c, Point const& fallback_point)
    {
        // The first point of the three segments is reused several times
        T const ax = get<0, 0>(a);
        T const ay = get<0, 1>(a);
        T const bx = get<0, 0>(b);
        T const by = get<0, 1>(b);
        T const cx = get<0, 0>(c);
        T const cy = get<0, 1>(c);

        T const dx_a = get<1, 0>(a) - ax;
        T const dy_a = get<1, 1>(a) - ay;

        T const dx_b = get<1, 0>(b) - bx;
        T const dy_b = get<1, 1>(b) - by;

        T const dx_c = get<1, 0>(c) - cx;
        T const dy_c = get<1, 1>(c) - cy;

        // Cramer's rule: d (see cart_intersect.hpp)
        T const d = geometry::detail::determinant<T>
                    (
                        dx_a, dy_a,
                        dx_b, dy_b
                    );

        T const zero = T();
        if (d == zero)
        {
            // There is no IP of a//b, they are collinear or parallel
            // Assuming they intersect (this method should be called for
            // segments known to intersect), they are collinear and overlap.
            // They have one or two intersection points - we don't know and
            // have to rely on the fallback intersection point

            Point c1, c2;
            geometry::detail::assign_point_from_index<0>(c, c1);
            geometry::detail::assign_point_from_index<1>(c, c2);
            return side_by_triangle<>::apply(c1, c2, fallback_point);
        }

        // Cramer's rule: da (see cart_intersect.hpp)
        T const da = geometry::detail::determinant<T>
                    (
                        dx_b,    dy_b,
                        ax - bx, ay - by
                    );

        // IP is at (ax + (da/d) * dx_a, ay + (da/d) * dy_a)
        // Side of IP is w.r.t. c is: determinant(dx_c, dy_c, ipx-cx, ipy-cy)
        // We replace ipx by expression above and multiply each term by d

#ifdef BOOST_GEOMETRY_SIDE_OF_INTERSECTION_DEBUG
        T const result1 = geometry::detail::determinant<T>
                    (
                        dx_c * d,                   dy_c * d,
                        d * (ax - cx) + dx_a * da,  d * (ay - cy) + dy_a * da
                    );

        // Note: result / (d * d)
        // is identical to the side_value of side_by_triangle
        // Therefore, the sign is always the same as that result, and the
        // resulting side (left,right,collinear) is the same

        // The first row we divide again by d because of determinant multiply rule
        T const result2 = d * geometry::detail::determinant<T>
                    (
                        dx_c,                   dy_c,
                        d * (ax - cx) + dx_a * da,  d * (ay - cy) + dy_a * da
                    );
        // Write out:
        T const result3 = d * (dx_c * (d * (ay - cy) + dy_a * da)
                             - dy_c * (d * (ax - cx) + dx_a * da));
        // Write out in braces:
        T const result4 = d * (dx_c * d * (ay - cy) + dx_c * dy_a * da
                             - dy_c * d * (ax - cx) - dy_c * dx_a * da);
        // Write in terms of d * XX + da * YY
        T const result5 = d * (d * (dx_c * (ay - cy) - dy_c * (ax - cx))
                             + da * (dx_c * dy_a - dy_c * dx_a));

        boost::ignore_unused(result1, result2, result3, result4, result5);
        //return result;
#endif

        // We consider the results separately
        // (in the end we only have to return the side-value 1,0 or -1)

        // To avoid multiplications we judge the product (easy, avoids *d)
        // and the sign of p*q+r*s (more elaborate)
        T const result = sign_of_product
            (
                d,
                sign_of_addition_of_two_products
                    (
                        d, dx_c * (ay - cy) - dy_c * (ax - cx),
                        da, dx_c * dy_a - dy_c * dx_a
                    )
                );
        return result;


    }

    template <typename Segment, typename Point>
    static inline int apply(Segment const& a, Segment const& b,
            Segment const& c,
            Point const& fallback_point)
    {
        typedef typename geometry::coordinate_type<Segment>::type coordinate_type;
        coordinate_type const s = side_value<coordinate_type>(a, b, c, fallback_point);
        coordinate_type const zero = coordinate_type();
        return math::equals(s, zero) ? 0
            : s > zero ? 1
            : -1;
    }

};


}} // namespace strategy::side

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_SIDE_OF_INTERSECTION_HPP

/* side_of_intersection.hpp
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
*/