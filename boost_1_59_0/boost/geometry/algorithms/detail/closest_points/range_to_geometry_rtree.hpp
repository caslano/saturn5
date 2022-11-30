// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_RANGE_TO_GEOMETRY_RTREE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_RANGE_TO_GEOMETRY_RTREE_HPP

#include <iterator>
#include <utility>

#include <boost/geometry/algorithms/detail/closest_feature/range_to_range.hpp>
#include <boost/geometry/algorithms/detail/distance/is_comparable.hpp>
#include <boost/geometry/algorithms/detail/distance/iterator_selector.hpp>
#include <boost/geometry/algorithms/detail/distance/strategy_utils.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/iterators/detail/has_one_element.hpp>

#include <boost/geometry/strategies/distance.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace closest_points
{

class point_or_segment_range_to_geometry_rtree
{
public:

    template
    <
        typename PointOrSegmentIterator,
        typename Geometry,
        typename Segment,
        typename Strategies
    >
    static inline void apply(PointOrSegmentIterator first,
                             PointOrSegmentIterator last,
                             Geometry const& geometry,
                             Segment& shortest_seg,
                             Strategies const& strategies)
    {
        typedef typename std::iterator_traits
        <
            PointOrSegmentIterator
        >::value_type point_or_segment_type;

        typedef distance::iterator_selector<Geometry const> selector_type;

        typedef detail::closest_feature::range_to_range_rtree range_to_range;

        BOOST_GEOMETRY_ASSERT( first != last );

        //TODO: Is this special case needed?
        //if ( detail::has_one_element(first, last) )
        //{
        //    dispatch::closest_points
        //        <
        //            point_or_segment_type, Geometry
        //        >::apply(*first, geometry, shortest_seg, strategies);
        //}

        closest_points::creturn_t<point_or_segment_type, Geometry, Strategies> cd;

        std::pair
            <
                point_or_segment_type,
                typename selector_type::iterator_type
            > closest_features
            = range_to_range::apply(first,
                                    last,
                                    selector_type::begin(geometry),
                                    selector_type::end(geometry),
                                    strategies,
                                    cd);
        dispatch::closest_points
                <
                    point_or_segment_type,                    
                    typename std::iterator_traits
                        <
                            typename selector_type::iterator_type
                        >::value_type
                >::apply(closest_features.first,
                         *closest_features.second,
                         shortest_seg,
                         strategies);
    }
};


}} // namespace detail::closest_points
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_RANGE_TO_GEOMETRY_RTREE_HPP

/* range_to_geometry_rtree.hpp
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
*/