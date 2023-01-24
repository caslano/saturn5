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
p5f0WvwDRhsh3lJrPKW4k8J6kwPbHMzHM2w89GurOo+KWwNaL9ZvdsPoKcoXOZ6vxjVe2OS59zzp3WSOpnsJdL59b+KJjRFhiyEEtdKuZI3Gb3FV87U5PTtSmtkzMcbGJ33m3GuFAeMkiKejP/8sl9q2xC9fD1ZzfbrP6Qd6aEcSbfzk2QphqOKvawRPlScMyTxRJt9Va5/ydz8erOR4MMRkrLDfy9jG6z3G7+1n5OO3PXJJK4Kro+hEtUcqSWr5ajEjByiiI6209cmjldZZjGnrst9zcdPX0wdSnViBF3F8ijZ4g/ULPrSL0Wo6zYGKbdGhtlKsg8voPP9MZPV/L9fOZfR5vdLTxUrxLGLSZwKS+JT+HX+X59vJ3+X3VQ5l5lOtumUZexXAkKI2Vhjn1OlUlqbN9BqySx3Ib9K0cb/oU4+IepTrSV0C0xFSWeksS9+TtTyFLyo2wY4AUi34NGFXXq32ng0XlgjVgip2sCbgjtjTdbFnXdTCZ7UPSu+f4qhq5zGuafV4LIywtVnDI7z1s5rDtmSxETGEHemjYvCS87tMnESdvp/pr3SRIHHan91bU8K7/KmUlf5kH3p6r7Z5rWfuHlJ/xGbykzIm0PekP6qz1vOkOa6HPE+EYit9z4ZiQfF6MPF5kpjrPM8pPdM3BlMrvc/zhK7F3u/53Y6E88HUr6fVZYAYje9Jb//Sxon+oqS3lY7nnw03
*/