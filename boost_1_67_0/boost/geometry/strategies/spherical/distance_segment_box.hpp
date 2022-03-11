// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2018-2019 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_SEGMENT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_SEGMENT_BOX_HPP

#include <boost/geometry/algorithms/detail/distance/segment_to_box.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategies/spherical/disjoint_box_box.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track.hpp>
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
            typename SegmentBoxStrategy,
            typename AzimuthStrategy,
            typename EnvelopeSegmentStrategy,
            typename NormalizePointStrategy,
            typename DisjointPointBoxStrategy,
            typename DisjointBoxBoxStrategy
    >
    static inline ReturnType segment_below_of_box(
            SegmentPoint const& p0,
            SegmentPoint const& p1,
            BoxPoint const&,
            BoxPoint const& top_right,
            BoxPoint const& bottom_left,
            BoxPoint const& bottom_right,
            SegmentBoxStrategy const& sb_strategy,
            AzimuthStrategy const& az_strategy,
            EnvelopeSegmentStrategy const& es_strategy,
            NormalizePointStrategy const& np_strategy,
            DisjointPointBoxStrategy const& dpb_strategy,
            DisjointBoxBoxStrategy const& dbb_strategy)
    {
        ReturnType result;
        typename LessEqual::other less_equal;
        typedef geometry::model::segment<SegmentPoint> segment_type;
        // if cs_tag is spherical_tag check segment's cs_tag with spherical_equatorial_tag as default
        typedef typename boost::mpl::if_c
            <
                boost::is_same<typename SegmentBoxStrategy::cs_tag, spherical_tag>::value,
                typename boost::mpl::if_c
                    <
                        boost::is_same
                            <
                                typename geometry::cs_tag<segment_type>::type,
                                spherical_polar_tag
                            >::value,
                        spherical_polar_tag, spherical_equatorial_tag
                    >::type,
                typename SegmentBoxStrategy::cs_tag
            >::type cs_tag;
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

        disjoint_info_type disjoint_result = disjoint_sb::
                apply(seg, input_box, p_max,
                      az_strategy, np_strategy, dpb_strategy, dbb_strategy);

        if (disjoint_result == disjoint_info_type::intersect) //intersect
        {
            return 0;
        }
        // disjoint but vertex not computed
        if (disjoint_result == disjoint_info_type::disjoint_no_vertex)
        {
            typedef typename coordinate_type<SegmentPoint>::type CT;

            geometry::model::box<SegmentPoint> mbr;
            geometry::envelope(seg, mbr, es_strategy);

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
            az_strategy.apply(lon1, lat1, lon2, lat2, alp1);
            CT vertex_lon = geometry::formula::vertex_longitude
                    <
                    CT,
                    cs_tag
                    >::apply(lon1, lat1, lon2, lat2,
                             vertex_lat, alp1, az_strategy);

            geometry::set_from_radian<0>(p_max, vertex_lon);
            geometry::set_from_radian<1>(p_max, vertex_lat);
        }
        //otherwise disjoint and vertex computed inside disjoint

        if (less_equal(geometry::get_as_radian<0>(bottom_left),
                       geometry::get_as_radian<0>(p_max)))
        {
            result = boost::numeric_cast<ReturnType>(typename
                        SegmentBoxStrategy::distance_ps_strategy::type().apply(bottom_left, p0, p1));
        }
        else
        {
            result = geometry::detail::distance::segment_to_box_2D
                    <
                        ReturnType,
                        SegmentPoint,
                        BoxPoint,
                        SegmentBoxStrategy
                    >::template call_above_of_box
                    <
                    typename LessEqual::other
                    >(p1, p0, p_max, bottom_right, sb_strategy);
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

    // strategy getters

    // point-point strategy getters
    struct distance_pp_strategy
    {
        typedef Strategy type;
    };

    inline typename distance_pp_strategy::type get_distance_pp_strategy() const
    {
        return typename distance_pp_strategy::type();
    }
    // point-segment strategy getters
    struct distance_ps_strategy
    {
        typedef cross_track<CalculationType, Strategy> type;
    };

    inline typename distance_ps_strategy::type get_distance_ps_strategy() const
    {
        return typename distance_ps_strategy::type();
    }

    struct distance_pb_strategy
    {
        typedef cross_track_point_box<CalculationType, Strategy> type;
    };

    inline typename distance_pb_strategy::type get_distance_pb_strategy() const
    {
        return typename distance_pb_strategy::type();
    }

    // TODO: why is the Radius not propagated above?

    typedef side::spherical_side_formula<CalculationType> side_strategy_type;

    static inline side_strategy_type get_side_strategy()
    {
        return side_strategy_type();
    }

    typedef within::spherical_point_point equals_point_point_strategy_type;

    static inline equals_point_point_strategy_type get_equals_point_point_strategy()
    {
        return equals_point_point_strategy_type();
    }

    // methods

    template <typename LessEqual, typename ReturnType,
              typename SegmentPoint, typename BoxPoint>
    inline ReturnType segment_below_of_box(SegmentPoint const& p0,
                                   SegmentPoint const& p1,
                                   BoxPoint const& top_left,
                                   BoxPoint const& top_right,
                                   BoxPoint const& bottom_left,
                                   BoxPoint const& bottom_right) const
    {
        typedef typename azimuth::spherical<CalculationType> azimuth_strategy_type;
        azimuth_strategy_type az_strategy;

        typedef typename envelope::spherical_segment<CalculationType>
                                             envelope_segment_strategy_type;
        envelope_segment_strategy_type es_strategy;

        return generic_segment_box::segment_below_of_box
               <
                    LessEqual,
                    ReturnType
               >(p0,p1,top_left,top_right,bottom_left,bottom_right,
                 spherical_segment_box<CalculationType>(),
                 az_strategy, es_strategy,
                 normalize::spherical_point(),
                 covered_by::spherical_point_box(),
                 disjoint::spherical_box_box());
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