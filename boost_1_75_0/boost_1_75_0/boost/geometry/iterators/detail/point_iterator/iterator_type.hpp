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
6qgdzWk17079dUnHavumyrJawfjDq7ZVBeNpS0vLZcs2E1/c7ASVnJ//rMIODkcce+37IyI8hPl0NSLkOIYPghd16kaEh8/AHTtuE0PpQ0nXQs9hpMdEknV4uB/B2/D35uAvEklc5uFuKISL5dtXPiIpN4RZGmXz9aKTRDp0VLf+jv9nl+Giw/polfzP8UUUlR7R9Os02bUQuzfYpdDjzDnXwg7PbZVF3f6QmkI3pPd3X8fLOeg4QDsk9jGXh6WROF7B7rymfiU4JRL/+Zr9Yptj1f5EXuwH3tSds7f2NW2FWCICpPZI/cl6jJKBrbOVmrCCYAmsZ+ZYzir0TXhYT3Em1FZdn2EEsZdi/xcgnhUKUFe0Kd4Yp9BkDH53zYEb/fHOHXfGnBk6qfg6jacOLfs4fix7e0NZQNXxk16j564QGhpjhA1hywro2cyNTVYN7/a1rzrrYxRGOLu/hSWvnPcWzVjz/AzNSVg+OyMNc+J5JjLaw0efkYmT5HnE2mhU58Hs21yuYSJy2nyFKFcbmC3sHdoWnawqmA+RFs4/2VO7j/D9VTHiIOzPOTK6F14WncyYYkaF0a/vKnblv7iEkRIsLuVfWmEt5a5UX4KCLnNNUaCwhHHs3fUfOd19roWh0LYp0nnPvufAHpHNC9yxkYW8uFJjWLqDNwwK1To4WF3D1d9HDUDXd/Dc6ZEwR7wlBA19rlQtU4KD/YB/
*/