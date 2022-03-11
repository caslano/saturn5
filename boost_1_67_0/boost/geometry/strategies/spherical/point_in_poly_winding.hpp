// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013, 2014, 2016, 2017, 2018, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.
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

    typedef SideStrategy side_strategy_type;

    inline side_strategy_type get_side_strategy() const
    {
        return m_side_strategy;
    }

    typedef expand::spherical_point expand_point_strategy_type;

    typedef typename SideStrategy::envelope_strategy_type envelope_strategy_type;

    inline envelope_strategy_type get_envelope_strategy() const
    {
        return m_side_strategy.get_envelope_strategy();
    }

    typedef typename SideStrategy::disjoint_strategy_type disjoint_strategy_type;

    inline disjoint_strategy_type get_disjoint_strategy() const
    {
        return m_side_strategy.get_disjoint_strategy();
    }

    typedef typename SideStrategy::equals_point_point_strategy_type equals_point_point_strategy_type;
    inline equals_point_point_strategy_type get_equals_point_point_strategy() const
    {
        return m_side_strategy.get_equals_point_point_strategy();
    }

    typedef disjoint::spherical_box_box disjoint_box_box_strategy_type;
    static inline disjoint_box_box_strategy_type get_disjoint_box_box_strategy()
    {
        return disjoint_box_box_strategy_type();
    }

    typedef covered_by::spherical_point_box disjoint_point_box_strategy_type;

    spherical_winding_base()
    {}

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
    typedef within::detail::spherical_winding_base
        <
            typename strategy::side::services::default_strategy
                <
                    typename cs_tag<PointLike>::type
                >::type,
            void
        > type;
};

template <typename PointLike, typename Geometry, typename AnyTag1, typename AnyTag2>
struct default_strategy<PointLike, Geometry, AnyTag1, AnyTag2, pointlike_tag, linear_tag, spherical_tag, spherical_tag>
{
    typedef within::detail::spherical_winding_base
        <
            typename strategy::side::services::default_strategy
                <
                    typename cs_tag<PointLike>::type
                >::type,
            void
        > type;
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
    typedef within::detail::spherical_winding_base
        <
            typename strategy::side::services::default_strategy
                <
                    typename cs_tag<PointLike>::type
                >::type,
            void
        > type;
};

template <typename PointLike, typename Geometry, typename AnyTag1, typename AnyTag2>
struct default_strategy<PointLike, Geometry, AnyTag1, AnyTag2, pointlike_tag, linear_tag, spherical_tag, spherical_tag>
{
    typedef within::detail::spherical_winding_base
        <
            typename strategy::side::services::default_strategy
                <
                    typename cs_tag<PointLike>::type
                >::type,
            void
        > type;
};

}}} // namespace strategy::covered_by::services
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_SPHERICAL_POINT_IN_POLY_WINDING_HPP

/* point_in_poly_winding.hpp
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
*/