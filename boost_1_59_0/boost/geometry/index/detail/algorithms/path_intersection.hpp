// Boost.Geometry Index
//
// n-dimensional box-linestring intersection
//
// Copyright (c) 2011-2017 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2020-2021.
// Modifications copyright (c) 2020-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_PATH_INTERSECTION_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_PATH_INTERSECTION_HPP


#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/index/detail/algorithms/segment_intersection.hpp>

#include <boost/geometry/strategies/default_distance_result.hpp>
#include <boost/geometry/strategies/default_length_result.hpp>


namespace boost { namespace geometry { namespace index { namespace detail {

namespace dispatch {

template <typename Indexable, typename Geometry, typename IndexableTag, typename GeometryTag>
struct path_intersection
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry or Indexable.",
        Indexable, Geometry, IndexableTag, GeometryTag);
};

// TODO: FP type must be used as a relative distance type!
// and default_distance_result can be some user-defined int type
// BUT! This code is experimental and probably won't be released at all
// since more flexible user-defined-nearest predicate should be added instead

template <typename Indexable, typename Segment>
struct path_intersection<Indexable, Segment, box_tag, segment_tag>
{
    typedef typename default_distance_result<typename point_type<Segment>::type>::type comparable_distance_type;

    static inline bool apply(Indexable const& b, Segment const& segment, comparable_distance_type & comparable_distance)
    {
        typedef typename point_type<Segment>::type point_type;
        point_type p1, p2;
        geometry::detail::assign_point_from_index<0>(segment, p1);
        geometry::detail::assign_point_from_index<1>(segment, p2);
        return index::detail::segment_intersection(b, p1, p2, comparable_distance);
    }
};

template <typename Indexable, typename Linestring>
struct path_intersection<Indexable, Linestring, box_tag, linestring_tag>
{
    typedef typename default_length_result<Linestring>::type comparable_distance_type;

    static inline bool apply(Indexable const& b, Linestring const& path, comparable_distance_type & comparable_distance)
    {
        typedef typename ::boost::range_value<Linestring>::type point_type;
        typedef typename ::boost::range_const_iterator<Linestring>::type const_iterator;        
        typedef typename ::boost::range_size<Linestring>::type size_type;
        
        const size_type count = ::boost::size(path);

        if ( count == 2 )
        {
            return index::detail::segment_intersection(b, *::boost::begin(path), *(::boost::begin(path)+1), comparable_distance);
        }
        else if ( 2 < count )
        {
            const_iterator it0 = ::boost::begin(path);
            const_iterator it1 = ::boost::begin(path) + 1;
            const_iterator last = ::boost::end(path);

            comparable_distance = 0;

            for ( ; it1 != last ; ++it0, ++it1 )
            {
                typename default_distance_result<point_type, point_type>::type
                    dist = geometry::distance(*it0, *it1);

                comparable_distance_type rel_dist;
                if ( index::detail::segment_intersection(b, *it0, *it1, rel_dist) )
                {
                    comparable_distance += dist * rel_dist;
                    return true;
                }
                else
                    comparable_distance += dist;
            }
        }

        return false;
    }
};

} // namespace dispatch

template <typename Indexable, typename SegmentOrLinestring>
struct default_path_intersection_distance_type
{
    typedef typename dispatch::path_intersection<
        Indexable, SegmentOrLinestring,
        typename tag<Indexable>::type,
        typename tag<SegmentOrLinestring>::type
    >::comparable_distance_type type;
};

template <typename Indexable, typename SegmentOrLinestring> inline
bool path_intersection(Indexable const& b,
                       SegmentOrLinestring const& path,
                       typename default_path_intersection_distance_type<Indexable, SegmentOrLinestring>::type & comparable_distance)
{
    // TODO check Indexable and Linestring concepts

    return dispatch::path_intersection<
            Indexable, SegmentOrLinestring,
            typename tag<Indexable>::type,
            typename tag<SegmentOrLinestring>::type
        >::apply(b, path, comparable_distance);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_PATH_INTERSECTION_HPP

/* path_intersection.hpp
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
*/