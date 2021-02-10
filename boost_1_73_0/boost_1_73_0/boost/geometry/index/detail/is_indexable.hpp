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
xX4dmgR6/4feU2QVdXIvLSH0Gho/d//aUD5zM1IKSAntarYO4kA8QcopSYSb2/6YVbfijl7rj7nhnYJv5aReKycJz9z3cRRom5a+1TZ6byX8/VXw91DAr69+V+V74NVvlqqRbTrVgZ2BHQO/lZxO7eNpuqeunSXe5f/ubNfOUia61uGoYN4yiEUk27mzzpgeVomiyhg+nlOdzVyM8SVSEpmPVAZmn1UMbMGgbY2+TMekVkKspYwrf2VmInMjKzliDQpAkYhMnlzDrKApHiWBgM0M/TVmiA42TDgXQ6N92YO84rWiSbQG5DfhUiJYu4tUdxLZLXt1zbwBvMOZmw1q2V7xQmH9b86RfaJHKlzpLQ0cjwrjRKULu5lDx9xtC2+Hv5Nf4LZVJBlmDn1lyP6LkgZn6eD5btKSAMVfZEU2T6cDF+g/djU0OYexh2P2guNwS9hVicirWPtLyQ/Q9ruoXR2zsRYhQdbE1X/DH5GKXBeTMuPZcbmwgVQZQ68MYvnKKw7Emk5tJgOqgoGrM/yphPtHbCqHcN6GFydYGclaU4ohaJ47hUlTkRsnGHLdhsuQ8+XcPMie0hcxLepvoY3CHYgva04Fdnw3N5xZk2eT11yNjWpHo4S2ICDEe6tHFuTp9N24GD3JRV1GeIMm
*/