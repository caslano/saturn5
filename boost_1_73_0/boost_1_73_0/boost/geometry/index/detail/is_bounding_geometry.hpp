// Boost.Geometry Index
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_IS_BOUNDING_GEOMETRY_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_IS_BOUNDING_GEOMETRY_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

template
<
    typename Geometry,
    typename Tag = typename geometry::tag<Geometry>::type
>
struct is_bounding_geometry
{
    static const bool value = false;
};

template <typename Box>
struct is_bounding_geometry<Box, box_tag>
{
    static const bool value = true;
};

}}}} // namespave boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_IS_BOUNDING_GEOMETRY_HPP

/* is_bounding_geometry.hpp
fcnXzHx3DfWrWjJsuV/B8oM4WfM7R21AfJzmu8Tz/6xdC1yUVdo/L4giYAyaSmrJKiVmGooX7CYI6JDDJcBLRc0OMODkAMMMoJSZitTSiHZ3zUpLLU37bWafWXYRNS/VpumXW227q1Z+arbxa71tWXzP85zLvO8wg2JS4znzn/e855znec5ze2fOSS/IzOLeNWrKWpvV6RDmpVMw/aqYhLr/4wS6irvh6hMc19+l7rCCS5eZSzJIo3hS55vlZOk=
*/