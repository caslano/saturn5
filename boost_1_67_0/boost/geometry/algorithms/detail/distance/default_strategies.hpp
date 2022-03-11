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
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
*/