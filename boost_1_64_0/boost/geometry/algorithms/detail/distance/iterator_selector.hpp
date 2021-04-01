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
73g1pQSMkAvjLyc/VzBv8KdicuorEKus/TSL5MNDyxAHkGcNFM8lkPd7p0Zn9OZm3sY2E0k+YVH4xt0us0IOKVZCGyBPVbGv2tLOW8b7vlBX6wJ2cK4BPsd0HXqSCQKEGbXfrmNhCrXgVoaqUgi5EJGd0r/HMsT/OtJlpnCFWaRO2rh6gUj6z5+1/bJftnUhQU3z0MLF44JFlz9US49jIjuLR3pViW8B+tPYFSfdVyOOZg+r5xoe6ovhGl8MLBzgqlCxf6TfTNiQViAlP66xPzlrlLLUAOoGTm/9OSB4Uq4C273ytQxkuTuWc04DX3lTaOZoYw8xGi0bN9oXZi+H+4pIDI3PYHXqp7gt0j414jANyZil2VFfX3v0Xm79+wW8/8iqz4mJxw4KfmjB8S2y4LU0dCYiWQmOSdcu+YfuK/1vqFENTh7MXDI5cy5crK3jAEvKX6UFxUx6Gdp6z93INx1TqqgL3KGvz9pZpNR7E9/sbg4YbwsYvE98YE8vI+q1PiuYbaDdPWdxTZKcTyVM2FySK4r6OM9mx2f0RZjpiPka4HKfVZTRTxR7RQ==
*/