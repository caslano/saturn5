// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_ITERATOR_TYPE_HPP
#define BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_ITERATOR_TYPE_HPP

#include <boost/range.hpp>

#include <boost/geometry/core/interior_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/iterators/flatten_iterator.hpp>
#include <boost/geometry/iterators/concatenate_iterator.hpp>

#include <boost/geometry/iterators/detail/point_iterator/inner_range_type.hpp>
#include <boost/geometry/iterators/detail/point_iterator/value_type.hpp>

#include <boost/geometry/iterators/dispatch/point_iterator.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace point_iterator
{


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct iterator_type
    : not_implemented<Geometry>
{};




template <typename Linestring>
struct iterator_type<Linestring, linestring_tag>
{
    typedef typename boost::range_iterator<Linestring>::type type;
};


template <typename Ring>
struct iterator_type<Ring, ring_tag>
{
    typedef typename boost::range_iterator<Ring>::type type;
};


template <typename Polygon>
class iterator_type<Polygon, polygon_tag>
{
private:
    typedef typename inner_range_type<Polygon>::type inner_range;

public:
    typedef concatenate_iterator
        <
            typename boost::range_iterator<inner_range>::type,
            flatten_iterator
                <
                    typename boost::range_iterator
                        <
                            typename geometry::interior_type<Polygon>::type
                        >::type,
                    typename iterator_type<inner_range>::type,
                    typename value_type<Polygon>::type,
                    dispatch::points_begin<inner_range>,
                    dispatch::points_end<inner_range>
                >,
            typename value_type<Polygon>::type
        > type;
};


template <typename MultiPoint>
struct iterator_type<MultiPoint, multi_point_tag>
{
    typedef typename boost::range_iterator<MultiPoint>::type type;
};


template <typename MultiLinestring>
class iterator_type<MultiLinestring, multi_linestring_tag>
{
private:
    typedef typename inner_range_type<MultiLinestring>::type inner_range;

public:
    typedef flatten_iterator
        <
            typename boost::range_iterator<MultiLinestring>::type,
            typename iterator_type<inner_range>::type,
            typename value_type<MultiLinestring>::type,
            dispatch::points_begin<inner_range>,
            dispatch::points_end<inner_range>
        > type;
};


template <typename MultiPolygon>
class iterator_type<MultiPolygon, multi_polygon_tag>
{
private:
    typedef typename inner_range_type<MultiPolygon>::type inner_range;

public:
    typedef flatten_iterator
        <
            typename boost::range_iterator<MultiPolygon>::type,
            typename iterator_type<inner_range>::type,
            typename value_type<MultiPolygon>::type,
            dispatch::points_begin<inner_range>,
            dispatch::points_end<inner_range>
        > type;
};


}} // namespace detail::point_iterator
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_ITERATOR_TYPE_HPP

/* iterator_type.hpp
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
*/