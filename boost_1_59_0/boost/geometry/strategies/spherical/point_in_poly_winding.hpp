// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2021.
// Modifications copyright (c) 2013-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_SPHERICAL_POINT_IN_POLY_WINDING_HPP
#define BOOST_GEOMETRY_STRATEGY_SPHERICAL_POINT_IN_POLY_WINDING_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>

#include <boost/geometry/strategy/spherical/expand_point.hpp>

#include <boost/geometry/strategies/cartesian/point_in_box.hpp>
#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/spherical/disjoint_box_box.hpp>
#include <boost/geometry/strategies/spherical/ssf.hpp>
#include <boost/geometry/strategies/within.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace within
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename SideStrategy, typename CalculationType>
class spherical_winding_base
{
    template <typename Point, typename PointOfSegment>
    struct calculation_type
        : select_calculation_type
            <
                Point,
                PointOfSegment,
                CalculationType
            >
    {};

    /*! subclass to keep state */
    class counter
    {
        int m_count;
        //int m_count_n;
        int m_count_s;
        int m_raw_count;
        int m_raw_count_anti;
        bool m_touches;

        inline int code() const
        {
            if (m_touches)
            {
                return 0;
            }
            
            if (m_raw_count != 0 && m_raw_count_anti != 0)
            {
                if (m_raw_count > 0) // right, wrap around south pole
                {
                    return (m_count + m_count_s) == 0 ? -1 : 1;
                }
                else // left, wrap around north pole
                {
                    //return (m_count + m_count_n) == 0 ? -1 : 1;
                    // m_count_n is 0
                    return m_count == 0 ? -1 : 1;
                }
            }

            return m_count == 0 ? -1 : 1;
        }

    public :
        friend class spherical_winding_base;

        inline counter()
            : m_count(0)
            //, m_count_n(0)
            , m_count_s(0)
            , m_raw_count(0)
            , m_raw_count_anti(0)
            , m_touches(false)
        {}

    };

    struct count_info
    {
        explicit count_info(int c = 0, bool ia = false)
            : count(c)
            , is_anti(ia)
        {}

        int count;
        bool is_anti;
    };

public:
    typedef typename SideStrategy::cs_tag cs_tag;

    spherical_winding_base() = default;

    template <typename Model>
    explicit spherical_winding_base(Model const& model)
        : m_side_strategy(model)
    {}

    // Typedefs and static methods to fulfill the concept
    typedef counter state_type;

    template <typename Point, typename PointOfSegment>
    inline bool apply(Point const& point,
                      PointOfSegment const& s1, PointOfSegment const& s2,
                      counter& state) const
    {
        typedef typename calculation_type<Point, PointOfSegment>::type calc_t;
        typedef typename geometry::detail::cs_angular_units<Point>::type units_t;
        typedef math::detail::constants_on_spheroid<calc_t, units_t> constants;

        bool eq1 = false;
        bool eq2 = false;
        bool s_antipodal = false;

        count_info ci = check_segment(point, s1, s2, state, eq1, eq2, s_antipodal);
        if (ci.count != 0)
        {
            if (! ci.is_anti)
            {
                int side = 0;
                if (ci.count == 1 || ci.count == -1)
                {
                    side = side_equal(point, eq1 ? s1 : s2, ci);
                }
                else // count == 2 || count == -2
                {
                    if (! s_antipodal)
                    {
                        // 1 left, -1 right
                        side = m_side_strategy.apply(s1, s2, point);
                    }
                    else
                    {
                        calc_t const pi = constants::half_period();
                        calc_t const s1_lat = get<1>(s1);
                        calc_t const s2_lat = get<1>(s2);

                        side = math::sign(ci.count)
                             * (pi - s1_lat - s2_lat <= pi // segment goes through north pole
                                ? -1 // going right all points will be on right side
                                : 1); // going right all points will be on left side
                    }
                }
            
                if (side == 0)
                {
                    // Point is lying on segment
                    state.m_touches = true;
                    state.m_count = 0;
                    return false;
                }

                // Side is NEG for right, POS for left.
                // The count is -2 for left, 2 for right (or -1/1)
                // Side positive thus means RIGHT and LEFTSIDE or LEFT and RIGHTSIDE
                // See accompagnying figure (TODO)
                if (side * ci.count > 0)
                {
                    state.m_count += ci.count;
                }

                state.m_raw_count += ci.count;
            }
            else
            {
                // Count negated because the segment is on the other side of the globe
                // so it is reversed to match this side of the globe

                // Assuming geometry wraps around north pole, for segments on the other side of the globe
                // the point will always be RIGHT+RIGHTSIDE or LEFT+LEFTSIDE, so side*-count always < 0
                //state.m_count_n -= 0;

                // Assuming geometry wraps around south pole, for segments on the other side of the globe
                // the point will always be RIGHT+LEFTSIDE or LEFT+RIGHTSIDE, so side*-count always > 0
                state.m_count_s -= ci.count;

                state.m_raw_count_anti -= ci.count;
            }
        }
        return ! state.m_touches;
    }

    static inline int result(counter const& state)
    {
        return state.code();
    }

protected:
    template <typename Point, typename PointOfSegment>
    static inline count_info check_segment(Point const& point,
                                    PointOfSegment const& seg1,
                                    PointOfSegment const& seg2,
                                    counter& state,
                                    bool& eq1, bool& eq2, bool& s_antipodal)
    {
        if (check_touch(point, seg1, seg2, state, eq1, eq2, s_antipodal))
        {
            return count_info(0, false);
        }

        return calculate_count(point, seg1, seg2, eq1, eq2, s_antipodal);
    }

    template <typename Point, typename PointOfSegment>
    static inline int check_touch(Point const& point,
                                  PointOfSegment const& seg1,
                                  PointOfSegment const& seg2,
                                  counter& state,
                                  bool& eq1,
                                  bool& eq2,
                                  bool& s_antipodal)
    {
        typedef typename calculation_type<Point, PointOfSegment>::type calc_t;
        typedef typename geometry::detail::cs_angular_units<Point>::type units_t;
        typedef math::detail::constants_on_spheroid<calc_t, units_t> constants;

        calc_t const c0 = 0;
        calc_t const c2 = 2;
        calc_t const pi = constants::half_period();
        calc_t const half_pi = pi / c2;

        calc_t const p_lon = get<0>(point);
        calc_t const s1_lon = get<0>(seg1);
        calc_t const s2_lon = get<0>(seg2);
        calc_t const p_lat = get<1>(point);
        calc_t const s1_lat = get<1>(seg1);
        calc_t const s2_lat = get<1>(seg2);

        // NOTE: lat in {-90, 90} and arbitrary lon
        //  it doesn't matter what lon it is if it's a pole
        //  so e.g. if one of the segment endpoints is a pole
        //  then only the other lon matters
        
        bool eq1_strict = longitudes_equal<units_t>(s1_lon, p_lon);
        bool eq2_strict = longitudes_equal<units_t>(s2_lon, p_lon);
        bool eq1_anti = false;
        bool eq2_anti = false;

        calc_t const anti_p_lon = p_lon + (p_lon <= c0 ? pi : -pi);

        eq1 = eq1_strict // lon strictly equal to s1
            || (eq1_anti = longitudes_equal<units_t>(s1_lon, anti_p_lon)) // anti-lon strictly equal to s1
            || math::equals(math::abs(s1_lat), half_pi); // s1 is pole
        eq2 = eq2_strict // lon strictly equal to s2
            || (eq2_anti = longitudes_equal<units_t>(s2_lon, anti_p_lon)) // anti-lon strictly equal to s2
            || math::equals(math::abs(s2_lat), half_pi); // s2 is pole

        // segment overlapping pole
        calc_t const s_lon_diff = math::longitude_distance_signed<units_t>(s1_lon, s2_lon);
        s_antipodal = math::equals(s_lon_diff, pi);
        if (s_antipodal)
        {
            eq1 = eq2 = eq1 || eq2;

            // segment overlapping pole and point is pole
            if (math::equals(math::abs(p_lat), half_pi))
            {
                eq1 = eq2 = true;
            }
        }
        
        // Both equal p -> segment vertical
        // The only thing which has to be done is check if point is ON segment
        if (eq1 && eq2)
        {
            // segment endpoints on the same sides of the globe
            if (! s_antipodal)
            {
                // p's lat between segment endpoints' lats
                if ( (s1_lat <= p_lat && s2_lat >= p_lat) || (s2_lat <= p_lat && s1_lat >= p_lat) )
                {
                    if (!eq1_anti || !eq2_anti)
                    {
                        state.m_touches = true;
                    }
                }
            }
            else
            {
                // going through north or south pole?
                if (pi - s1_lat - s2_lat <= pi)
                {
                    if ( (eq1_strict && s1_lat <= p_lat) || (eq2_strict && s2_lat <= p_lat) // north
                            || math::equals(p_lat, half_pi) ) // point on north pole
                    {
                        state.m_touches = true;
                    }
                    else if (! eq1_strict && ! eq2_strict && math::equals(p_lat, -half_pi) ) // point on south pole
                    {
                        return false;
                    }
                }
                else // south pole
                {
                    if ( (eq1_strict && s1_lat >= p_lat) || (eq2_strict && s2_lat >= p_lat) // south
                            || math::equals(p_lat, -half_pi) ) // point on south pole
                    {
                        state.m_touches = true;
                    }
                    else if (! eq1_strict && ! eq2_strict && math::equals(p_lat, half_pi) ) // point on north pole
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        return false;
    }

    // Called if point is not aligned with a vertical segment
    template <typename Point, typename PointOfSegment>
    static inline count_info calculate_count(Point const& point,
                                             PointOfSegment const& seg1,
                                             PointOfSegment const& seg2,
                                             bool eq1, bool eq2, bool s_antipodal)
    {
        typedef typename calculation_type<Point, PointOfSegment>::type calc_t;
        typedef typename geometry::detail::cs_angular_units<Point>::type units_t;
        typedef math::detail::constants_on_spheroid<calc_t, units_t> constants;

        // If both segment endpoints were poles below checks wouldn't be enough
        // but this means that either both are the same or that they are N/S poles
        // and therefore the segment is not valid.
        // If needed (eq1 && eq2 ? 0) could be returned

        calc_t const c0 = 0;
        calc_t const pi = constants::half_period();

        calc_t const p = get<0>(point);
        calc_t const s1 = get<0>(seg1);
        calc_t const s2 = get<0>(seg2);

        calc_t const s1_p = math::longitude_distance_signed<units_t>(s1, p);
        
        if (s_antipodal)
        {
            return count_info(s1_p < c0 ? -2 : 2, false); // choose W/E
        }

        calc_t const s1_s2 = math::longitude_distance_signed<units_t>(s1, s2);

        if (eq1 || eq2) // Point on level s1 or s2
        {
            return count_info(s1_s2 < c0 ? -1 : 1, // choose W/E
                              longitudes_equal<units_t>(p + pi, (eq1 ? s1 : s2)));
        }

        // Point between s1 and s2
        if ( math::sign(s1_p) == math::sign(s1_s2)
          && math::abs(s1_p) < math::abs(s1_s2) )
        {
            return count_info(s1_s2 < c0 ? -2 : 2, false); // choose W/E
        }
        
        calc_t const s1_p_anti = math::longitude_distance_signed<units_t>(s1, p + pi);

        // Anti-Point between s1 and s2
        if ( math::sign(s1_p_anti) == math::sign(s1_s2)
          && math::abs(s1_p_anti) < math::abs(s1_s2) )
        {
            return count_info(s1_s2 < c0 ? -2 : 2, true); // choose W/E
        }

        return count_info(0, false);
    }


    // Fix for https://svn.boost.org/trac/boost/ticket/9628
    // For floating point coordinates, the <D> coordinate of a point is compared
    // with the segment's points using some EPS. If the coordinates are "equal"
    // the sides are calculated. Therefore we can treat a segment as a long areal
    // geometry having some width. There is a small ~triangular area somewhere
    // between the segment's effective area and a segment's line used in sides
    // calculation where the segment is on the one side of the line but on the
    // other side of a segment (due to the width).
    // Below picture assuming D = 1, if D = 0 horiz<->vert, E<->N, RIGHT<->UP.
    // For the s1 of a segment going NE the real side is RIGHT but the point may
    // be detected as LEFT, like this:
    //                     RIGHT
    //                 ___----->
    //                  ^      O Pt  __ __
    //                 EPS     __ __
    //                  v__ __ BUT DETECTED AS LEFT OF THIS LINE
    //             _____7
    //       _____/
    // _____/
    // In the code below actually D = 0, so segments are nearly-vertical
    // Called when the point is on the same level as one of the segment's points
    // but the point is not aligned with a vertical segment
    template <typename Point, typename PointOfSegment>
    inline int side_equal(Point const& point,
                          PointOfSegment const& se,
                          count_info const& ci) const
    {
        typedef typename coordinate_type<PointOfSegment>::type scoord_t;
        typedef typename geometry::detail::cs_angular_units<Point>::type units_t;

        if (math::equals(get<1>(point), get<1>(se)))
        {
            return 0;
        }

        // Create a horizontal segment intersecting the original segment's endpoint
        // equal to the point, with the derived direction (E/W).
        PointOfSegment ss1, ss2;
        set<1>(ss1, get<1>(se));
        set<0>(ss1, get<0>(se));
        set<1>(ss2, get<1>(se));
        scoord_t ss20 = get<0>(se);
        if (ci.count > 0)
        {
            ss20 += small_angle<scoord_t, units_t>();
        }
        else
        {
            ss20 -= small_angle<scoord_t, units_t>();
        }
        math::normalize_longitude<units_t>(ss20);
        set<0>(ss2, ss20);

        // Check the side using this vertical segment
        return m_side_strategy.apply(ss1, ss2, point);
    }

    // 1 deg or pi/180 rad
    template <typename CalcT, typename Units>
    static inline CalcT small_angle()
    {
        typedef math::detail::constants_on_spheroid<CalcT, Units> constants;

        return constants::half_period() / CalcT(180);
    }

    template <typename Units, typename CalcT>
    static inline bool longitudes_equal(CalcT const& lon1, CalcT const& lon2)
    {
        return math::equals(
                math::longitude_distance_signed<Units>(lon1, lon2),
                CalcT(0));
    }

    SideStrategy m_side_strategy;
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
\brief Within detection using winding rule in spherical coordinate system.
\ingroup strategies
\tparam Point \tparam_point
\tparam PointOfSegment \tparam_segment_point
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
[link geometry.reference.algorithms.within.within_3_with_strategy within (with strategy)]
}
 */
template
<
    typename Point = void, // for backward compatibility
    typename PointOfSegment = Point, // for backward compatibility
    typename CalculationType = void
>
class spherical_winding
    : public within::detail::spherical_winding_base
        <
            side::spherical_side_formula<CalculationType>,
            CalculationType
        >
{};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename PointLike, typename Geometry, typename AnyTag1, typename AnyTag2>
struct default_strategy<PointLike, Geometry, AnyTag1, AnyTag2, pointlike_tag, polygonal_tag, spherical_tag, spherical_tag>
{
    typedef within::spherical_winding<> type;
};

template <typename PointLike, typename Geometry, typename AnyTag1, typename AnyTag2>
struct default_strategy<PointLike, Geometry, AnyTag1, AnyTag2, pointlike_tag, linear_tag, spherical_tag, spherical_tag>
{
    typedef within::spherical_winding<> type;
};

} // namespace services

#endif


}} // namespace strategy::within


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace strategy { namespace covered_by { namespace services
{

template <typename PointLike, typename Geometry, typename AnyTag1, typename AnyTag2>
struct default_strategy<PointLike, Geometry, AnyTag1, AnyTag2, pointlike_tag, polygonal_tag, spherical_tag, spherical_tag>
{
    typedef within::spherical_winding<> type;
};

template <typename PointLike, typename Geometry, typename AnyTag1, typename AnyTag2>
struct default_strategy<PointLike, Geometry, AnyTag1, AnyTag2, pointlike_tag, linear_tag, spherical_tag, spherical_tag>
{
    typedef within::spherical_winding<> type;
};

}}} // namespace strategy::covered_by::services
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_SPHERICAL_POINT_IN_POLY_WINDING_HPP

/* point_in_poly_winding.hpp
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
*/