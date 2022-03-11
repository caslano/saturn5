// Boost.Geometry Index
//
// n-dimensional box-linestring intersection
//
// Copyright (c) 2011-2017 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_PATH_INTERSECTION_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_PATH_INTERSECTION_HPP


#include <boost/geometry/index/detail/algorithms/segment_intersection.hpp>

#include <boost/geometry/strategies/default_length_result.hpp>


namespace boost { namespace geometry { namespace index { namespace detail {

namespace dispatch {

template <typename Indexable, typename Geometry, typename IndexableTag, typename GeometryTag>
struct path_intersection
{
    BOOST_MPL_ASSERT_MSG((false), NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_OR_INDEXABLE, (path_intersection));
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