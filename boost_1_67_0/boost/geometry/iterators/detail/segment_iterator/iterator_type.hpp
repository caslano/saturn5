// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DETAIL_SEGMENT_ITERATOR_ITERATOR_TYPE_HPP
#define BOOST_GEOMETRY_ITERATORS_DETAIL_SEGMENT_ITERATOR_ITERATOR_TYPE_HPP

#include <boost/range.hpp>

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