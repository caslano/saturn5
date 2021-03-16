// Boost.Geometry Index
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_IS_INDEXABLE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_IS_INDEXABLE_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

template
<
    typename Geometry,
    typename Tag = typename geometry::tag<Geometry>::type
>
struct is_indexable
{
    static const bool value = false;
};

template <typename Point>
struct is_indexable<Point, geometry::point_tag>
{
    static const bool value = true;
};

template <typename Box>
struct is_indexable<Box, geometry::box_tag>
{
    static const bool value = true;
};

template <typename Segment>
struct is_indexable<Segment, geometry::segment_tag>
{
    static const bool value = true;
};

}}}} // namespave boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_IS_INDEXABLE_HPP

/* is_indexable.hpp
TCWuA3Dx2fg7QRoNTu/4TOVy4lKzmFAySDD6BCCydeqISfm5w4l8+4CszultFndJTXl5HfXxB4NS46NEyfpNJ5vKtzZ6kVeIplnpZBe3X8nfkgOBC2ReGydUTRXl+QOhCaS9w9EM5zZ9fGaOkSzdhQdBVuMXo8Iab4G5G+OItkpGRmaKpBAEZBM/dZrkLAwYRMOan5FPs00bT4PazHmcr3e50B4MlvcCszw5g+ZkGQT2GpmalVFgzkknMiwI4Is=
*/