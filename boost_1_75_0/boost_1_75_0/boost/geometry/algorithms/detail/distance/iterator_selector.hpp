// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_ITERATOR_SELECTOR_HPP
#define BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_ITERATOR_SELECTOR_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>
#include <boost/geometry/iterators/segment_iterator.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


// class to choose between point_iterator and segment_iterator
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct iterator_selector
{
    typedef geometry::segment_iterator<Geometry> iterator_type;

    static inline iterator_type begin(Geometry& geometry)
    {
        return segments_begin(geometry);
    }

    static inline iterator_type end(Geometry& geometry)
    {
        return segments_end(geometry);
    }
};

template <typename MultiPoint>
struct iterator_selector<MultiPoint, multi_point_tag>
{
    typedef geometry::point_iterator<MultiPoint> iterator_type;

    static inline iterator_type begin(MultiPoint& multipoint)
    {
        return points_begin(multipoint);
    }

    static inline iterator_type end(MultiPoint& multipoint)
    {
        return points_end(multipoint);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_ITERATOR_SELECTOR_HPP

/* iterator_selector.hpp
mSA7/wpk5z2Infm2Pjuhm8J06PMVqHgvmTavOgemus1tmN2lS4Tx0/rIfsVdf4cfFMxjv/O+ihvlM8oEYMgXu/QxnpBLr8eoxNDlmEFtrVyf64Y1biBzf9VeEjhdU6Cy+pIplzSLvACW7qW9hzm7M3gSTya10ktYLlL2qnlaQg3IUWksqtR0JY8EJRDpe/jptcMtIs/C5a9QFO6nt+d9M309Y0ak+UBLDyk9/XnQZZvtsT80vnSZ2x6zLzttj4cx2YPP92pjKb/cTQc7jv721T55hvmXbTxDCzQevMx5hjWXnTzDFJcMwuwe4Bka+pLr2x33/gWUy0wmr+3j+1ft37/9zyF0DT6Q9+FNqBEXpujNT4BmbgCauapHvuWC12CKVPj9TVD57C9hdGsXvGOedUjkW77CKUdIZFhOM8Ou+U7mGHtpGQLjkBMASQDpsehP5uLFl6SAytvBgfYE3l5LOvuRcFASseItEu+Q9yuQ/DocwbWddsLSwaPGQ4THorsETKIIUE93cXLHNA1p6cWcnJqhqjyWlyd3FnGpZLDENpg924PzTmbUu2s3MxbUp5exqN5088aMivInE1G9IcJTbreQMh7eW/xhor/5CzHiFkHKXYlRXqYqOYgNcTf6ZUGPxYDET0MkfSD77gL2J+R6f6A8b978gfAiFzYvj8IfefmKYfAHr1hV2pUiti346wty0IjZOK25g+6mDJEi
*/