// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2018-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_SEGMENT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_SEGMENT_BOX_HPP

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/core/coordinate_promotion.hpp>

#include <boost/geometry/algorithms/detail/distance/segment_to_box.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/geographic/azimuth.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track_point_box.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/geographic/side.hpp>
#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategies/spherical/disjoint_box_box.hpp>
#include <boost/geometry/strategies/spherical/distance_segment_box.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>

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

    //constructor

    explicit geographic_segment_box(Spheroid const& spheroid = Spheroid())
             : m_spheroid(spheroid)
    {}

    Spheroid model() const
    {
        return m_spheroid;
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