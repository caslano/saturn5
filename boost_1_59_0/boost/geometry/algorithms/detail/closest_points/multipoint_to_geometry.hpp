// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_MULTIPOINT_TO_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_MULTIPOINT_TO_GEOMETRY_HPP

#include <iterator>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/detail/closest_points/range_to_geometry_rtree.hpp>
#include <boost/geometry/algorithms/detail/closest_points/utilities.hpp>
#include <boost/geometry/algorithms/dispatch/closest_points.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/linestring.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace closest_points
{


struct multipoint_to_multipoint
{
    template 
    <
        typename MultiPoint1, 
        typename MultiPoint2, 
        typename Segment, 
        typename Strategies
    >
    static inline void apply(MultiPoint1 const& multipoint1,
                             MultiPoint2 const& multipoint2,
                             Segment& shortest_seg,
                             Strategies const& strategies)
    {
        if (boost::size(multipoint1) < boost::size(multipoint2))
        {
            point_or_segment_range_to_geometry_rtree::apply(
                boost::begin(multipoint2),
                boost::end(multipoint2),
                multipoint1,
                shortest_seg,
                strategies);
            detail::closest_points::swap_segment_points::apply(shortest_seg);
            return;
        }
        point_or_segment_range_to_geometry_rtree::apply(
            boost::begin(multipoint1),
            boost::end(multipoint1),
            multipoint2,
            shortest_seg,
            strategies);
    }
};

struct multipoint_to_linear
{
    template 
    <
        typename MultiPoint, 
        typename Linear, 
        typename Segment, 
        typename Strategies
    >
    static inline void apply(MultiPoint const& multipoint,
                             Linear const& linear,
                             Segment& shortest_seg,
                             Strategies const& strategies)
    {
        point_or_segment_range_to_geometry_rtree::apply(
            boost::begin(multipoint),
            boost::end(multipoint),
            linear,
            shortest_seg,
            strategies);
    }
};

struct linear_to_multipoint
{
    template 
    <
        typename Linear, 
        typename MultiPoint, 
        typename Segment, 
        typename Strategies
    >
    static inline void apply(Linear const& linear,
                             MultiPoint const& multipoint,
                             Segment& shortest_seg,
                             Strategies const& strategies)
    {
        multipoint_to_linear::apply(multipoint, linear, shortest_seg, strategies);
        detail::closest_points::swap_segment_points::apply(shortest_seg);
    }
};

struct segment_to_multipoint
{
    template 
    <
        typename Segment, 
        typename MultiPoint, 
        typename OutSegment, 
        typename Strategies
    >
    static inline void apply(Segment const& segment,
                             MultiPoint const& multipoint,
                             OutSegment& shortest_seg,
                             Strategies const& strategies)
    {
        using linestring_type = geometry::model::linestring
            <
                typename point_type<Segment>::type
            >;
        linestring_type linestring;
        convert(segment, linestring);
        multipoint_to_linear::apply(multipoint, linestring, shortest_seg, strategies);
        detail::closest_points::swap_segment_points::apply(shortest_seg);
    }
};

struct multipoint_to_segment
{
    template 
    <
        typename MultiPoint, 
        typename Segment, 
        typename OutSegment, 
        typename Strategies
    >
    static inline void apply(MultiPoint const& multipoint,
                             Segment const& segment,
                             OutSegment& shortest_seg,
                             Strategies const& strategies)
    {
        using linestring_type = geometry::model::linestring
            <
                typename point_type<Segment>::type
            >;
        linestring_type linestring;
        convert(segment, linestring);
        multipoint_to_linear::apply(multipoint, linestring, shortest_seg, 
            strategies);
    }
};


struct multipoint_to_areal
{

private:

    template <typename Areal, typename Strategies>
    struct covered_by_areal
    {
        covered_by_areal(Areal const& areal, Strategies const& strategy)
            : m_areal(areal), m_strategy(strategy)
        {}

        template <typename Point>
        inline bool operator()(Point const& point) const
        {
            return geometry::covered_by(point, m_areal, m_strategy);
        }

        Areal const& m_areal;
        Strategies const& m_strategy;
    };

public:

    template 
    <
        typename MultiPoint, 
        typename Areal, 
        typename Segment, 
        typename Strategies
    >
    static inline void apply(MultiPoint const& multipoint,
                             Areal const& areal,
                             Segment& shortest_seg,
                             Strategies const& strategies)
    {
        covered_by_areal<Areal, Strategies> predicate(areal, strategies);

        auto it = std::find_if(
                boost::begin(multipoint),
                boost::end(multipoint),
                predicate);
        
        if (it != boost::end(multipoint))
        {
            return set_segment_from_points::apply(*it, *it, shortest_seg);
            
        }

        point_or_segment_range_to_geometry_rtree::apply(
            boost::begin(multipoint),
            boost::end(multipoint),
            areal,
            shortest_seg,
            strategies);
    }
};

struct areal_to_multipoint
{
    template 
    <
        typename Areal, 
        typename MultiPoint, 
        typename Segment, 
        typename Strategies
    >
    static inline void apply(Areal const& areal,
                             MultiPoint const& multipoint,
                             Segment& shortest_seg,
                             Strategies const& strategies)
    {
        multipoint_to_areal::apply(multipoint, areal, shortest_seg, strategies);
        detail::closest_points::swap_segment_points::apply(shortest_seg);
    }
};

}} // namespace detail::closest_points
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename MultiPoint1, typename MultiPoint2>
struct closest_points
    <
        MultiPoint1, MultiPoint2, 
        multi_point_tag, multi_point_tag,
        false
    > : detail::closest_points::multipoint_to_multipoint
{};


template <typename MultiPoint, typename Linear>
struct closest_points
    <
        MultiPoint, Linear, 
        multi_point_tag, linear_tag,
        false
    > : detail::closest_points::multipoint_to_linear
{};


template <typename Linear, typename MultiPoint>
struct closest_points
    <
         Linear, MultiPoint, 
         linear_tag, multi_point_tag,
         false
    > : detail::closest_points::linear_to_multipoint
{};


template <typename MultiPoint, typename Segment>
struct closest_points
    <
        MultiPoint, Segment, 
        multi_point_tag, segment_tag,
        false
    > : detail::closest_points::multipoint_to_segment
{};


template <typename Segment, typename MultiPoint>
struct closest_points
    <
         Segment, MultiPoint, 
         segment_tag, multi_point_tag,
         false
    > : detail::closest_points::segment_to_multipoint
{};


template <typename MultiPoint, typename Areal>
struct closest_points
    <
        MultiPoint, Areal, 
        multi_point_tag, areal_tag,
        false
    > : detail::closest_points::multipoint_to_areal
{};


template <typename Areal, typename MultiPoint>
struct closest_points
    <
        Areal, MultiPoint, 
        areal_tag, multi_point_tag,
        false
    > : detail::closest_points::areal_to_multipoint
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_MULTIPOINT_TO_GEOMETRY_HPP

/* multipoint_to_geometry.hpp
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
*/