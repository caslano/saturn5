// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DETAIL_SEGMENT_ITERATOR_ITERATOR_TYPE_HPP
#define BOOST_GEOMETRY_ITERATORS_DETAIL_SEGMENT_ITERATOR_ITERATOR_TYPE_HPP

#include <boost/range/iterator.hpp>

#include <boost/geometry/core/interior_type.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/iterators/concatenate_iterator.hpp>
#include <boost/geometry/iterators/flatten_iterator.hpp>
#include <boost/geometry/iterators/detail/point_iterator/inner_range_type.hpp>

#include <boost/geometry/iterators/detail/segment_iterator/range_segment_iterator.hpp>
#include <boost/geometry/iterators/detail/segment_iterator/value_type.hpp>

#include <boost/geometry/iterators/dispatch/segment_iterator.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace segment_iterator
{


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct iterator_type
    : not_implemented<Geometry>
{};


template <typename Linestring>
struct iterator_type<Linestring, linestring_tag>
{
    typedef range_segment_iterator
        <
            Linestring, typename value_type<Linestring>::type
        > type;
};


template <typename Ring>
struct iterator_type<Ring, ring_tag>
{
    typedef range_segment_iterator
        <
            Ring, typename value_type<Ring>::type
        > type;
};


template <typename Polygon>
class iterator_type<Polygon, polygon_tag>
{
private:
    typedef typename detail::point_iterator::inner_range_type
        <
            Polygon
        >::type inner_range;

public:
    typedef concatenate_iterator
        <
            range_segment_iterator
                <
                    inner_range,
                    typename value_type<Polygon>::type
                >,
            flatten_iterator
                <
                    typename boost::range_iterator
                        <
                            typename geometry::interior_type<Polygon>::type
                        >::type,
                    typename iterator_type<inner_range>::type,
                    typename value_type<Polygon>::type,
                    dispatch::segments_begin<inner_range>,
                    dispatch::segments_end<inner_range>,
                    typename value_type<Polygon>::type
                >,
            typename value_type<Polygon>::type,
            typename value_type<Polygon>::type
        > type;
};


template <typename MultiLinestring>
class iterator_type<MultiLinestring, multi_linestring_tag>
{
private:
    typedef typename detail::point_iterator::inner_range_type
        <
            MultiLinestring
        >::type inner_range;

public:
    typedef flatten_iterator
        <
            typename boost::range_iterator<MultiLinestring>::type,
            typename iterator_type<inner_range>::type,
            typename value_type<MultiLinestring>::type,
            dispatch::segments_begin<inner_range>,
            dispatch::segments_end<inner_range>,
            typename value_type<MultiLinestring>::type
        > type;
};


template <typename MultiPolygon>
class iterator_type<MultiPolygon, multi_polygon_tag>
{
private:
    typedef typename detail::point_iterator::inner_range_type
        <
            MultiPolygon
        >::type inner_range;
public:
    typedef flatten_iterator
        <
            typename boost::range_iterator<MultiPolygon>::type,
            typename iterator_type<inner_range>::type,
            typename value_type<MultiPolygon>::type,
            dispatch::segments_begin<inner_range>,
            dispatch::segments_end<inner_range>,
            typename value_type<MultiPolygon>::type
        > type;
};



}} // namespace detail::segment_iterator
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_DETAIL_SEGMENT_ITERATOR_ITERATOR_TYPE_HPP

/* iterator_type.hpp
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
*/