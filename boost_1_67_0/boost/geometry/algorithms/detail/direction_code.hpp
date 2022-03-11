// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015, 2017, 2019.
// Modifications copyright (c) 2015-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DIRECTION_CODE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DIRECTION_CODE_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/arithmetic/infinite_line_functions.hpp>
#include <boost/geometry/algorithms/detail/make/make.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>

#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename CSTag>
struct direction_code_impl
{
    BOOST_MPL_ASSERT_MSG((false), NOT_IMPLEMENTED_FOR_THIS_CS, (CSTag));
};

template <>
struct direction_code_impl<cartesian_tag>
{
    template <typename Point1, typename Point2>
    static inline int apply(Point1 const& segment_a, Point1 const& segment_b,
                            Point2 const& point)
    {
        typedef typename geometry::select_coordinate_type
            <
                Point1, Point2
            >::type calc_t;

        typedef model::infinite_line<calc_t> line_type;

        // point b is often equal to the specified point, check that first
        line_type const q = detail::make::make_infinite_line<calc_t>(segment_b, point);
        if (arithmetic::is_degenerate(q))
        {
            return 0;
        }

        line_type const p = detail::make::make_infinite_line<calc_t>(segment_a, segment_b);
        if (arithmetic::is_degenerate(p))
        {
            return 0;
        }

        // p extends a-b if direction is similar
        return arithmetic::similar_direction(p, q) ? 1 : -1;
    }
};

template <>
struct direction_code_impl<spherical_equatorial_tag>
{
    template <typename Point1, typename Point2>
    static inline int apply(Point1 const& segment_a, Point1 const& segment_b,
                            Point2 const& p)
    {
        typedef typename coordinate_type<Point1>::type coord1_t;
        typedef typename coordinate_type<Point2>::type coord2_t;
        typedef typename cs_angular_units<Point1>::type units_t;
        typedef typename cs_angular_units<Point2>::type units2_t;
        BOOST_MPL_ASSERT_MSG((boost::is_same<units_t, units2_t>::value),
                             NOT_IMPLEMENTED_FOR_DIFFERENT_UNITS,
                             (units_t, units2_t));

        typedef typename geometry::select_coordinate_type <Point1, Point2>::type calc_t;
        typedef math::detail::constants_on_spheroid<coord1_t, units_t> constants1;
        typedef math::detail::constants_on_spheroid<coord2_t, units_t> constants2;
        static coord1_t const pi_half1 = constants1::max_latitude();
        static coord2_t const pi_half2 = constants2::max_latitude();
        static calc_t const c0 = 0;

        coord1_t const a0 = geometry::get<0>(segment_a);
        coord1_t const a1 = geometry::get<1>(segment_a);
        coord1_t const b0 = geometry::get<0>(segment_b);
        coord1_t const b1 = geometry::get<1>(segment_b);
        coord2_t const p0 = geometry::get<0>(p);
        coord2_t const p1 = geometry::get<1>(p);
        
        if ( (math::equals(b0, a0) && math::equals(b1, a1))
          || (math::equals(b0, p0) && math::equals(b1, p1)) )
        {
            return 0;
        }

        bool const is_a_pole = math::equals(pi_half1, math::abs(a1));
        bool const is_b_pole = math::equals(pi_half1, math::abs(b1));
        bool const is_p_pole = math::equals(pi_half2, math::abs(p1));

        if ( is_b_pole && ((is_a_pole && math::sign(b1) == math::sign(a1))
                        || (is_p_pole && math::sign(b1) == math::sign(p1))) )
        {
            return 0;
        }

        // NOTE: as opposed to the implementation for cartesian CS
        // here point b is the origin

        calc_t const dlon1 = math::longitude_distance_signed<units_t, calc_t>(b0, a0);
        calc_t const dlon2 = math::longitude_distance_signed<units_t, calc_t>(b0, p0);

        bool is_antilon1 = false, is_antilon2 = false;
        calc_t const dlat1 = latitude_distance_signed<units_t, calc_t>(b1, a1, dlon1, is_antilon1);
        calc_t const dlat2 = latitude_distance_signed<units_t, calc_t>(b1, p1, dlon2, is_antilon2);

        calc_t mx = is_a_pole || is_b_pole || is_p_pole ?
                    c0 :
                    (std::min)(is_antilon1 ? c0 : math::abs(dlon1),
                               is_antilon2 ? c0 : math::abs(dlon2));
        calc_t my = (std::min)(math::abs(dlat1),
                               math::abs(dlat2));

        int s1 = 0, s2 = 0;
        if (mx >= my)
        {
            s1 = dlon1 > 0 ? 1 : -1;
            s2 = dlon2 > 0 ? 1 : -1;
        }
        else
        {
            s1 = dlat1 > 0 ? 1 : -1;
            s2 = dlat2 > 0 ? 1 : -1;
        }

        return s1 == s2 ? -1 : 1;
    }

    template <typename Units, typename T>
    static inline T latitude_distance_signed(T const& lat1, T const& lat2, T const& lon_ds, bool & is_antilon)
    {
        typedef math::detail::constants_on_spheroid<T, Units> constants;
        static T const pi = constants::half_period();
        static T const c0 = 0;

        T res = lat2 - lat1;

        is_antilon = math::equals(math::abs(lon_ds), pi);
        if (is_antilon)
        {
            res = lat2 + lat1;
            if (res >= c0)
                res = pi - res;
            else
                res = -pi - res;
        }

        return res;
    }
};

template <>
struct direction_code_impl<spherical_polar_tag>
{
    template <typename Point1, typename Point2>
    static inline int apply(Point1 segment_a, Point1 segment_b,
                            Point2 p)
    {
        typedef math::detail::constants_on_spheroid
            <
                typename coordinate_type<Point1>::type,
                typename cs_angular_units<Point1>::type
            > constants1;
        typedef math::detail::constants_on_spheroid
            <
                typename coordinate_type<Point2>::type,
                typename cs_angular_units<Point2>::type
            > constants2;

        geometry::set<1>(segment_a,
            constants1::max_latitude() - geometry::get<1>(segment_a));
        geometry::set<1>(segment_b,
            constants1::max_latitude() - geometry::get<1>(segment_b));
        geometry::set<1>(p,
            constants2::max_latitude() - geometry::get<1>(p));

        return direction_code_impl
                <
                    spherical_equatorial_tag
                >::apply(segment_a, segment_b, p);
    }
};

// if spherical_tag is passed then pick cs_tag based on Point1 type
// with spherical_equatorial_tag as the default
template <>
struct direction_code_impl<spherical_tag>
{
    template <typename Point1, typename Point2>
    static inline int apply(Point1 segment_a, Point1 segment_b,
                            Point2 p)
    {
        return direction_code_impl
            <
                typename boost::mpl::if_c
                    <
                        boost::is_same
                            <
                                typename geometry::cs_tag<Point1>::type,
                                spherical_polar_tag
                            >::value,
                        spherical_polar_tag,
                        spherical_equatorial_tag
                    >::type
            >::apply(segment_a, segment_b, p);
    }
};

template <>
struct direction_code_impl<geographic_tag>
    : direction_code_impl<spherical_equatorial_tag>
{};

// Gives sense of direction for point p, collinear w.r.t. segment (a,b)
// Returns -1 if p goes backward w.r.t (a,b), so goes from b in direction of a
// Returns 1 if p goes forward, so extends (a,b)
// Returns 0 if p is equal with b, or if (a,b) is degenerate
// Note that it does not do any collinearity test, that should be done before
template <typename CSTag, typename Point1, typename Point2>
inline int direction_code(Point1 const& segment_a, Point1 const& segment_b,
                          Point2 const& p)
{
    return direction_code_impl<CSTag>::apply(segment_a, segment_b, p);
}


} // namespace detail
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DIRECTION_CODE_HPP

/* direction_code.hpp
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
*/