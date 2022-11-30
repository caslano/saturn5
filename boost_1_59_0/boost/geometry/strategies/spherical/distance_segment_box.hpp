// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2018-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_SEGMENT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_SEGMENT_BOX_HPP

#include <type_traits>

#include <boost/geometry/algorithms/detail/distance/segment_to_box.hpp>
#include <boost/geometry/algorithms/envelope.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategies/spherical/disjoint_box_box.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track_point_box.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
#include <boost/geometry/strategies/cartesian/point_in_box.hpp> // spherical
#include <boost/geometry/strategies/spherical/ssf.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace distance
{

struct generic_segment_box
{
    template
    <
            typename LessEqual,
            typename ReturnType,
            typename SegmentPoint,
            typename BoxPoint,
            typename Strategies
    >
    static inline ReturnType segment_below_of_box(
            SegmentPoint const& p0,
            SegmentPoint const& p1,
            BoxPoint const&,
            BoxPoint const& top_right,
            BoxPoint const& bottom_left,
            BoxPoint const& bottom_right,
            Strategies const& strategies)
    {
        ReturnType result;
        typename LessEqual::other less_equal;
        typedef geometry::model::segment<SegmentPoint> segment_type;
        // if cs_tag is spherical_tag check segment's cs_tag with spherical_equatorial_tag as default
        typedef std::conditional_t
            <
                std::is_same<typename Strategies::cs_tag, spherical_tag>::value,
                std::conditional_t
                    <
                        std::is_same
                            <
                                typename geometry::cs_tag<segment_type>::type,
                                spherical_polar_tag
                            >::value,
                        spherical_polar_tag, spherical_equatorial_tag
                    >,
                typename Strategies::cs_tag
            > cs_tag;
        typedef geometry::detail::disjoint::
                disjoint_segment_box_sphere_or_spheroid<cs_tag>
                disjoint_sb;
        typedef typename disjoint_sb::disjoint_info disjoint_info_type;

        segment_type seg(p0, p1);

        geometry::model::box<BoxPoint> input_box;
        geometry::set_from_radian<geometry::min_corner, 0>
                (input_box, geometry::get_as_radian<0>(bottom_left));
        geometry::set_from_radian<geometry::min_corner, 1>
                (input_box, geometry::get_as_radian<1>(bottom_left));
        geometry::set_from_radian<geometry::max_corner, 0>
                (input_box, geometry::get_as_radian<0>(top_right));
        geometry::set_from_radian<geometry::max_corner, 1>
                (input_box, geometry::get_as_radian<1>(top_right));

        SegmentPoint p_max;

        // TODO: Think about rewriting this and simply passing strategies
        //       The problem is that this algorithm is called by disjoint(S/B) strategies.
        disjoint_info_type disjoint_result = disjoint_sb::
                apply(seg, input_box, p_max,
                      strategies.azimuth(),
                      strategies.normalize(p0),
                      strategies.covered_by(p0, input_box), // disjoint
                      strategies.disjoint(input_box, input_box));

        if (disjoint_result == disjoint_info_type::intersect) //intersect
        {
            return 0;
        }
        // disjoint but vertex not computed
        if (disjoint_result == disjoint_info_type::disjoint_no_vertex)
        {
            typedef typename coordinate_type<SegmentPoint>::type CT;

            geometry::model::box<SegmentPoint> mbr;
            geometry::envelope(seg, mbr, strategies);

            CT lon1 = geometry::get_as_radian<0>(p0);
            CT lat1 = geometry::get_as_radian<1>(p0);
            CT lon2 = geometry::get_as_radian<0>(p1);
            CT lat2 = geometry::get_as_radian<1>(p1);

            if (lon1 > lon2)
            {
                std::swap(lon1, lon2);
                std::swap(lat1, lat2);
            }

            CT vertex_lat;
            CT lat_sum = lat1 + lat2;
            if (lat_sum > CT(0))
            {
                vertex_lat = geometry::get_as_radian<geometry::max_corner, 1>(mbr);
            } else {
                vertex_lat = geometry::get_as_radian<geometry::min_corner, 1>(mbr);
            }

            CT alp1;
            strategies.azimuth().apply(lon1, lat1, lon2, lat2, alp1);

            // TODO: formula should not call strategy!
            CT vertex_lon = geometry::formula::vertex_longitude
                    <
                        CT,
                        cs_tag
                    >::apply(lon1, lat1, lon2, lat2,
                             vertex_lat, alp1, strategies.azimuth());

            geometry::set_from_radian<0>(p_max, vertex_lon);
            geometry::set_from_radian<1>(p_max, vertex_lat);
        }
        //otherwise disjoint and vertex computed inside disjoint

        if (less_equal(geometry::get_as_radian<0>(bottom_left),
                       geometry::get_as_radian<0>(p_max)))
        {
            result = boost::numeric_cast<ReturnType>(
                strategies.distance(bottom_left, seg).apply(bottom_left, p0, p1));
        }
        else
        {
            // TODO: The strategy should not call the algorithm like that
            result = geometry::detail::distance::segment_to_box_2D
                        <
                            ReturnType,
                            SegmentPoint,
                            BoxPoint,
                            Strategies
                        >::template call_above_of_box
                            <
                                typename LessEqual::other
                            >(p1, p0, p_max, bottom_right, strategies);
        }
        return result;
    }

    template <typename SPoint, typename BPoint>
    static void mirror(SPoint& p0,
                       SPoint& p1,
                       BPoint& bottom_left,
                       BPoint& bottom_right,
                       BPoint& top_left,
                       BPoint& top_right)
    {
        //if segment's vertex is the southest point then mirror geometries
        if (geometry::get<1>(p0) + geometry::get<1>(p1) < 0)
        {
            BPoint bl = bottom_left;
            BPoint br = bottom_right;
            geometry::set<1>(p0, geometry::get<1>(p0) * -1);
            geometry::set<1>(p1, geometry::get<1>(p1) * -1);
            geometry::set<1>(bottom_left, geometry::get<1>(top_left) * -1);
            geometry::set<1>(top_left, geometry::get<1>(bl) * -1);
            geometry::set<1>(bottom_right, geometry::get<1>(top_right) * -1);
            geometry::set<1>(top_right, geometry::get<1>(br) * -1);
        }
    }
};

//===========================================================================

template
<
    typename CalculationType = void,
    typename Strategy = haversine<double, CalculationType>
>
struct spherical_segment_box
{
    template <typename PointOfSegment, typename PointOfBox>
    struct calculation_type
        : promote_floating_point
          <
              typename strategy::distance::services::return_type
                  <
                      Strategy,
                      PointOfSegment,
                      PointOfBox
                  >::type
          >
    {};

    typedef spherical_tag cs_tag;

    // constructors

    inline spherical_segment_box()
    {}

    explicit inline spherical_segment_box(typename Strategy::radius_type const& r)
        : m_strategy(r)
    {}

    inline spherical_segment_box(Strategy const& s)
        : m_strategy(s)
    {}

    typename Strategy::radius_type radius() const
    {
        return m_strategy.radius();
    }

    // methods

    template
    <
        typename LessEqual, typename ReturnType,
        typename SegmentPoint, typename BoxPoint,
        typename Strategies
    >
    inline ReturnType segment_below_of_box(SegmentPoint const& p0,
                                           SegmentPoint const& p1,
                                           BoxPoint const& top_left,
                                           BoxPoint const& top_right,
                                           BoxPoint const& bottom_left,
                                           BoxPoint const& bottom_right,
                                           Strategies const& strategies) const
    {
        return generic_segment_box::segment_below_of_box
               <
                    LessEqual,
                    ReturnType
               >(p0,p1,top_left,top_right,bottom_left,bottom_right,
                 strategies);
    }

    template <typename SPoint, typename BPoint>
    static void mirror(SPoint& p0,
                       SPoint& p1,
                       BPoint& bottom_left,
                       BPoint& bottom_right,
                       BPoint& top_left,
                       BPoint& top_right)
    {

       generic_segment_box::mirror(p0, p1,
                                   bottom_left, bottom_right,
                                   top_left, top_right);
    }

private:
    Strategy m_strategy;
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename CalculationType, typename Strategy>
struct tag<spherical_segment_box<CalculationType, Strategy> >
{
    typedef strategy_tag_distance_segment_box type;
};

template <typename CalculationType, typename Strategy, typename PS, typename PB>
struct return_type<spherical_segment_box<CalculationType, Strategy>, PS, PB>
    : spherical_segment_box<CalculationType, Strategy>::template calculation_type<PS, PB>
{};

template <typename CalculationType, typename Strategy>
struct comparable_type<spherical_segment_box<CalculationType, Strategy> >
{
    // Define a cartesian_segment_box strategy with its underlying point-segment
    // strategy being comparable
    typedef spherical_segment_box
        <
            CalculationType,
            typename comparable_type<Strategy>::type
        > type;
};


template <typename CalculationType, typename Strategy>
struct get_comparable<spherical_segment_box<CalculationType, Strategy> >
{
    typedef typename comparable_type
        <
            spherical_segment_box<CalculationType, Strategy>
        >::type comparable_type;
public :
    static inline comparable_type apply(spherical_segment_box<CalculationType, Strategy> const& )
    {
        return comparable_type();
    }
};

template <typename CalculationType, typename Strategy, typename PS, typename PB>
struct result_from_distance<spherical_segment_box<CalculationType, Strategy>, PS, PB>
{
private :
    typedef typename return_type<
                                    spherical_segment_box
                                    <
                                        CalculationType,
                                        Strategy
                                    >,
                                    PS,
                                    PB
                                 >::type return_type;
public :
    template <typename T>
    static inline return_type apply(spherical_segment_box<CalculationType,
                                                          Strategy> const& ,
                                    T const& value)
    {
        Strategy s;
        return result_from_distance<Strategy, PS, PB>::apply(s, value);
    }
};

template <typename Segment, typename Box>
struct default_strategy
    <
        segment_tag, box_tag, Segment, Box,
        spherical_equatorial_tag, spherical_equatorial_tag
    >
{
    typedef spherical_segment_box<> type;
};

template <typename Box, typename Segment>
struct default_strategy
    <
        box_tag, segment_tag, Box, Segment,
        spherical_equatorial_tag, spherical_equatorial_tag
    >
{
    typedef typename default_strategy
        <
            segment_tag, box_tag, Segment, Box,
            spherical_equatorial_tag, spherical_equatorial_tag
        >::type type;
};

}
#endif

}} // namespace strategy::distance

}} // namespace boost::geometry
#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_SEGMENT_BOX_HPP

/* distance_segment_box.hpp
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
*/