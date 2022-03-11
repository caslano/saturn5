// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2018-2019 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_SEGMENT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_SEGMENT_BOX_HPP

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/algorithms/detail/distance/segment_to_box.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/geographic/azimuth.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/geographic/side.hpp>
#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategies/spherical/disjoint_box_box.hpp>
#include <boost/geometry/strategies/spherical/distance_segment_box.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>

#include <boost/geometry/util/promote_floating_point.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace distance
{

template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
struct geographic_segment_box
{
    template <typename PointOfSegment, typename PointOfBox>
    struct return_type
        : promote_floating_point
          <
              typename select_calculation_type
                  <
                      PointOfSegment,
                      PointOfBox,
                      CalculationType
                  >::type
          >
    {};

    typedef geographic_tag cs_tag;

    // point-point strategy getters
    struct distance_pp_strategy
    {
        typedef geographic<FormulaPolicy, Spheroid, CalculationType> type;
    };

    inline typename distance_pp_strategy::type get_distance_pp_strategy() const
    {
        typedef typename distance_pp_strategy::type distance_type;
        return distance_type(m_spheroid);
    }
    // point-segment strategy getters
    struct distance_ps_strategy
    {
        typedef geographic_cross_track
                <
                    FormulaPolicy,
                    Spheroid,
                    CalculationType
                > type;
    };

    inline typename distance_ps_strategy::type get_distance_ps_strategy() const
    {
        typedef typename distance_ps_strategy::type distance_type;
        return distance_type(m_spheroid);
    }

    struct distance_pb_strategy
    {
        typedef geographic_cross_track_point_box
                <
                    FormulaPolicy,
                    Spheroid,
                    CalculationType
                > type;
    };

    inline typename distance_pb_strategy::type get_distance_pb_strategy() const
    {
        return typename distance_pb_strategy::type(m_spheroid);
    }

    typedef side::geographic
            <
                FormulaPolicy,
                Spheroid,
                CalculationType
            > side_strategy_type;

    inline side_strategy_type get_side_strategy() const
    {
        return side_strategy_type(m_spheroid);
    }

    typedef within::spherical_point_point equals_point_point_strategy_type;

    static inline equals_point_point_strategy_type get_equals_point_point_strategy()
    {
        return equals_point_point_strategy_type();
    }

    //constructor

    explicit geographic_segment_box(Spheroid const& spheroid = Spheroid())
             : m_spheroid(spheroid)
    {}

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
        typedef typename azimuth::geographic
        <
                FormulaPolicy,
                Spheroid,
                CalculationType
        > azimuth_strategy_type;
        azimuth_strategy_type az_strategy(m_spheroid);

        typedef typename envelope::geographic_segment
        <
                FormulaPolicy,
                Spheroid,
                CalculationType
        > envelope_segment_strategy_type;
        envelope_segment_strategy_type es_strategy(m_spheroid);

        return generic_segment_box::segment_below_of_box
               <
                    LessEqual,
                    ReturnType
               >(p0,p1,top_left,top_right,bottom_left,bottom_right,
                 geographic_segment_box<FormulaPolicy, Spheroid, CalculationType>(),
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

private :
    Spheroid m_spheroid;
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

//tags

template <typename FormulaPolicy>
struct tag<geographic_segment_box<FormulaPolicy> >
{
    typedef strategy_tag_distance_segment_box type;
};

template
<
        typename FormulaPolicy,
        typename Spheroid
>
struct tag<geographic_segment_box<FormulaPolicy, Spheroid> >
{
    typedef strategy_tag_distance_segment_box type;
};

template
<
        typename FormulaPolicy,
        typename Spheroid,
        typename CalculationType
>
struct tag<geographic_segment_box<FormulaPolicy, Spheroid, CalculationType> >
{
    typedef strategy_tag_distance_segment_box type;
};

// return types

template <typename FormulaPolicy, typename PS, typename PB>
struct return_type<geographic_segment_box<FormulaPolicy>, PS, PB>
    : geographic_segment_box<FormulaPolicy>::template return_type<PS, PB>
{};

template
<
        typename FormulaPolicy,
        typename Spheroid,
        typename PS,
        typename PB
>
struct return_type<geographic_segment_box<FormulaPolicy, Spheroid>, PS, PB>
    : geographic_segment_box<FormulaPolicy, Spheroid>::template return_type<PS, PB>
{};

template
<
        typename FormulaPolicy,
        typename Spheroid,
        typename CalculationType,
        typename PS,
        typename PB
>
struct return_type<geographic_segment_box<FormulaPolicy, Spheroid, CalculationType>, PS, PB>
    : geographic_segment_box<FormulaPolicy, Spheroid, CalculationType>::template return_type<PS, PB>
{};

//comparable types

template
<
        typename FormulaPolicy,
        typename Spheroid,
        typename CalculationType
>
struct comparable_type<geographic_segment_box<FormulaPolicy, Spheroid, CalculationType> >
{
    typedef geographic_segment_box
        <
            FormulaPolicy, Spheroid, CalculationType
        >  type;
};

template
<
        typename FormulaPolicy,
        typename Spheroid,
        typename CalculationType
>
struct get_comparable<geographic_segment_box<FormulaPolicy, Spheroid, CalculationType> >
{
    typedef typename comparable_type
        <
            geographic_segment_box<FormulaPolicy, Spheroid, CalculationType>
        >::type comparable_type;
public :
    static inline comparable_type
    apply(geographic_segment_box<FormulaPolicy, Spheroid, CalculationType> const& )
    {
        return comparable_type();
    }
};

// result from distance

template
<
    typename FormulaPolicy,
    typename PS,
    typename PB
>
struct result_from_distance<geographic_segment_box<FormulaPolicy>, PS, PB>
{
private :
    typedef typename geographic_segment_box
        <
            FormulaPolicy
        >::template return_type<PS, PB>::type return_type;
public :
    template <typename T>
    static inline return_type
    apply(geographic_segment_box<FormulaPolicy> const& , T const& distance)
    {
        return distance;
    }
};

template
<
    typename FormulaPolicy,
    typename Spheroid,
    typename CalculationType,
    typename PS,
    typename PB
>
struct result_from_distance<geographic_segment_box<FormulaPolicy, Spheroid, CalculationType>, PS, PB>
{
private :
    typedef typename geographic_segment_box
        <
            FormulaPolicy, Spheroid, CalculationType
        >::template return_type<PS, PB>::type return_type;
public :
    template <typename T>
    static inline return_type
    apply(geographic_segment_box<FormulaPolicy, Spheroid, CalculationType> const& , T const& distance)
    {
        return distance;
    }
};


// default strategies

template <typename Segment, typename Box>
struct default_strategy
    <
        segment_tag, box_tag, Segment, Box,
        geographic_tag, geographic_tag
    >
{
    typedef geographic_segment_box<> type;
};

template <typename Box, typename Segment>
struct default_strategy
    <
        box_tag, segment_tag, Box, Segment,
        geographic_tag, geographic_tag
    >
{
    typedef typename default_strategy
        <
            segment_tag, box_tag, Segment, Box,
            geographic_tag, geographic_tag
        >::type type;
};

}
#endif

}} // namespace strategy::distance

}} // namespace boost::geometry
#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_SEGMENT_BOX_HPP

/* distance_segment_box.hpp
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
*/