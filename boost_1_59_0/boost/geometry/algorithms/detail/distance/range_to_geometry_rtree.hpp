// Boost.Geometry

// Copyright (c) 2014-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_RANGE_TO_GEOMETRY_RTREE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_RANGE_TO_GEOMETRY_RTREE_HPP

#include <iterator>
#include <utility>

#include <boost/geometry/algorithms/detail/closest_feature/range_to_range.hpp>
#include <boost/geometry/algorithms/detail/distance/is_comparable.hpp>
#include <boost/geometry/algorithms/detail/distance/iterator_selector.hpp>
#include <boost/geometry/algorithms/detail/distance/strategy_utils.hpp>
#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/iterators/detail/has_one_element.hpp>

#include <boost/geometry/strategies/distance.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template
<
    typename PointOrSegmentIterator,
    typename Geometry,
    typename Strategies
>
class point_or_segment_range_to_geometry_rtree
{
private:
    typedef typename std::iterator_traits
        <
            PointOrSegmentIterator
        >::value_type point_or_segment_type;

    typedef iterator_selector<Geometry const> selector_type;

    typedef detail::closest_feature::range_to_range_rtree range_to_range;

    typedef distance::strategy_t<point_or_segment_type, Geometry, Strategies> strategy_type;

public:
    typedef distance::return_t<point_or_segment_type, Geometry, Strategies> return_type;

    static inline return_type apply(PointOrSegmentIterator first,
                                    PointOrSegmentIterator last,
                                    Geometry const& geometry,
                                    Strategies const& strategies)
    {
        BOOST_GEOMETRY_ASSERT( first != last );

        if ( detail::has_one_element(first, last) )
        {
            return dispatch::distance
                <
                    point_or_segment_type, Geometry, Strategies
                >::apply(*first, geometry, strategies);
        }

        distance::creturn_t<point_or_segment_type, Geometry, Strategies> cd_min;

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
                                    cd_min);

        return
            is_comparable<strategy_type>::value
            ?
            cd_min
            :
            dispatch::distance
                <
                    point_or_segment_type,                    
                    typename std::iterator_traits
                        <
                            typename selector_type::iterator_type
                        >::value_type,
                    Strategies
                >::apply(closest_features.first,
                         *closest_features.second,
                         strategies);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_RANGE_TO_GEOMETRY_RTREE_HPP

/* range_to_geometry_rtree.hpp
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
*/