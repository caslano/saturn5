// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_ITERATOR_TYPE_HPP
#define BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_ITERATOR_TYPE_HPP

#include <boost/range/iterator.hpp>

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