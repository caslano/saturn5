// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_DEFAULT_STRATEGIES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_DEFAULT_STRATEGIES_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/reverse_dispatch.hpp>

#include <boost/geometry/strategies/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{



// Helper metafunction for default strategy retrieval
template
<
    typename Geometry1,
    typename Geometry2 = Geometry1,
    typename Tag1 = typename tag_cast
        <
            typename tag<Geometry1>::type, pointlike_tag
        >::type,
    typename Tag2 = typename tag_cast
        <
            typename tag<Geometry2>::type, pointlike_tag
        >::type,
    bool Reverse = geometry::reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct default_strategy
    : strategy::distance::services::default_strategy
          <
              point_tag, segment_tag,
              typename point_type<Geometry1>::type,
              typename point_type<Geometry2>::type
          >
{};

template
<
    typename Geometry1,
    typename Geometry2,
    typename Tag1,
    typename Tag2
>
struct default_strategy<Geometry1, Geometry2, Tag1, Tag2, true>
    : default_strategy<Geometry2, Geometry1, Tag2, Tag1, false>
{};


template <typename Pointlike1, typename Pointlike2>
struct default_strategy
    <
        Pointlike1, Pointlike2,
        pointlike_tag, pointlike_tag, false
    > : strategy::distance::services::default_strategy
          <
              point_tag, point_tag,
              typename point_type<Pointlike1>::type,
              typename point_type<Pointlike2>::type
          >
{};


template <typename Pointlike, typename Box>
struct default_strategy<Pointlike, Box, pointlike_tag, box_tag, false>
    : strategy::distance::services::default_strategy
          <
              point_tag, box_tag,
              typename point_type<Pointlike>::type,
              typename point_type<Box>::type
          >
{};


template <typename Box1, typename Box2>
struct default_strategy<Box1, Box2, box_tag, box_tag, false>
    : strategy::distance::services::default_strategy
          <
              box_tag, box_tag,
              typename point_type<Box1>::type,
              typename point_type<Box2>::type
          >
{};

template <typename Linear, typename Box>
struct default_strategy<Linear, Box, segment_tag, box_tag, false>
    : strategy::distance::services::default_strategy
          <
              segment_tag, box_tag,
              typename point_type<Linear>::type,
              typename point_type<Box>::type
          >
{};

template <typename Linear, typename Box>
struct default_strategy<Linear, Box, linear_tag, box_tag, false>
    : strategy::distance::services::default_strategy
          <
              segment_tag, box_tag,
              typename point_type<Linear>::type,
              typename point_type<Box>::type
          >
{};



// Helper metafunction for default point-segment strategy retrieval
template <typename Geometry1, typename Geometry2, typename Strategy>
struct default_ps_strategy
    : strategy::distance::services::default_strategy
          <
              point_tag, segment_tag,
              typename point_type<Geometry1>::type,
              typename point_type<Geometry2>::type,
              typename cs_tag<typename point_type<Geometry1>::type>::type,
              typename cs_tag<typename point_type<Geometry2>::type>::type,
              Strategy
          >
{};



}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_DEFAULT_STRATEGIES_HPP

/* default_strategies.hpp
7OH7odIG5Yh1v3bOLLP77bHux4SAa7pnFMFvkxdceJyLXMVvoFI8Dejaw1T3R3mZeNjKo9eZ2SSLs+HDZ4QdM+0PYTQWSsMfrNxZ9nQ6HXankmozozJnchgGyqecveF5R3bgNzH730EWXTv+D5bJ7Ms/yEEvZZeCHD5ZegTLb6ubtExFf0YrU2aRBC5DQTzJfUmJerKw0uidi5VtUgA+jzD+3qdVGkHqDe2p9AZ66FPb/2D3/4XG63/g7/2lPzjf+1F5A64C0u/54rgc92lxdoagMgfKitMsL4vNT44HgSX79Hqy5a3sAb/D5sfrW3jaclNqgfnp+HLDPVyke06UTCwqadi8DHMBcxLX4kbck+st9aW5vAF3gGX6jpG18P9G3wxcDKXE9yrQ8LOUkL8OZR5ZhRpg+2zwwVr0VZJdwv5+HffVFvZ39Vmx7p/8Jpx/0Pjqs9wmEXrWmksaFl6f7rkqVcjTQARoIuUgr4zBUZmFwQgex42yDnXz/35W0J4FUFkLpe3ZVA4vDsVdx87wOnaGb7RumFwGwtH9me6hhFTiUrkVD6NYFDSLV6EU7T1m6/yzwl/mClSuQpGeS+0nwS+w/fSxdZfWlcEc9KZmjEzHuzO54VHKowUz/3oF9qwXXX+uJ4ZXErqmiWkjo6Ey7zmKr2cB2nBfi+qiq/B6J73dpKKmItREq9ShIfgpTpJnXdLrsk+ZoOYqb2uT
*/