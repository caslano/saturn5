// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_RANGE_TO_GEOMETRY_RTREE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_RANGE_TO_GEOMETRY_RTREE_HPP

#include <iterator>
#include <utility>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/iterators/has_one_element.hpp>

#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/algorithms/detail/closest_feature/range_to_range.hpp>
#include <boost/geometry/algorithms/detail/distance/is_comparable.hpp>
#include <boost/geometry/algorithms/detail/distance/iterator_selector.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template
<
    typename PointOrSegmentIterator,
    typename Geometry,
    typename Strategy
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

public:
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<point_or_segment_type>::type,
            typename point_type<Geometry>::type
        >::type return_type;

    static inline return_type apply(PointOrSegmentIterator first,
                                    PointOrSegmentIterator last,
                                    Geometry const& geometry,
                                    Strategy const& strategy)
    {
        namespace sds = strategy::distance::services;

        BOOST_GEOMETRY_ASSERT( first != last );

        if ( geometry::has_one_element(first, last) )
        {
            return dispatch::distance
                <
                    point_or_segment_type, Geometry, Strategy
                >::apply(*first, geometry, strategy);
        }

        typename sds::return_type
            <
                typename sds::comparable_type<Strategy>::type,
                typename point_type<point_or_segment_type>::type,
                typename point_type<Geometry>::type
            >::type cd_min;

        std::pair
            <
                point_or_segment_type,
                typename selector_type::iterator_type
            > closest_features
            = range_to_range::apply(first,
                                    last,
                                    selector_type::begin(geometry),
                                    selector_type::end(geometry),
                                    sds::get_comparable
                                        <
                                            Strategy
                                        >::apply(strategy),
                                    cd_min);

        return
            is_comparable<Strategy>::value
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
                    Strategy
                >::apply(closest_features.first,
                         *closest_features.second,
                         strategy);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_RANGE_TO_GEOMETRY_RTREE_HPP

/* range_to_geometry_rtree.hpp
+1fWPJeQIX9FuGme3zDTPQ2J5L9z/R/L8zUjz+stc8qLRBY6IOBpg+j//m6iPQESP+W0y//O7N//nqCdbqH9JFnH59LMD5b3jWb6OyHxH5z+o4z+kwb9ly3096VA3kG+vDZw3j82074GiVHXGW3pOqWddj1Be5qF9iWS9703zXv59V79ewbcgJ7bxYbggPlacd0k42yCxJ+uM76i8zodefuMfO2z8OVT2Mg7xLrxoHn78LpZ/wcJxw1W9lVMPyDcsPa1E4L4tjCWOOgYnG7xDRPd2yHxS0637gale9eNRN7vtegdrhC9wzSMOwen33nDVKePQeK5GxbZmHB0TAgmks8g+s8bpjq+AgnH1xbeTfjaOnemssl8DZnMB6JZ+LVu/w6ROyC0fM3mzn/uPXfO7kV9Z2LKHIzPelCnv+9rK591bPGgMsMb+nune7137uZrjPaNqT1HQuL737D6jnxD63v8N4n2PGId34Rx+GhQXrTZTHsxJDZx2qu/MXg/Rnu0ACNuscBtRQeg99w3JplQL+cgz3+sP3/tG2u94CU3rZcwyjTyPh4SlRBM895ESJqrw0Oq43ZhUD5qqZnmGkg8zGly3nx7L5qTyDR0Y/A+0w3vJOrk/0Ifg5IyjX2KVEhkJ2Ui0y6OLynT0nPHJjZvlg1Is0qnSXQ8+ri4yTyyOslUF1sh8VgSq4uH4Ne6zj4mMO3MWGGQcr1ppneO
*/