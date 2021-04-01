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
1UvOhyd16MLb9zInEPy7eN/7EFOv4cAN2p3LLUUgAv/yA/nPpSMwKaAOESQph9xc3+i4whKAzMAV+NzRUCg1eW/QsTkihUUWMpprMthuKl2Slj6ZI04h9c//2vUNxE2WHPs3EQox4jrIhvuOwWs7PEnOM/CFOfV+IwUMFtI6Zkz7exwln+fFa2ygQngAoN2SB0qCLH/7EXeVwJJWIhbNzv89gAP3PUiSdReX6UVuAyrBqcj3AmcKlq50ks9zQr3VZPy3T5tnTJ0XpCqBktJHByltpmZEB+sBH8h4l7vphY+4go3CNFuWD71C6ylyojLElBEGiarcbEX+CpNejUpIqXdnKpSMye26bXiQhZEOwqdU1IpYmWQ5sHXc3Gn38Ipl2iE7kkmOUS19nPKynaC4yvgyZHOYYKzx6Boj0zskUUBuWtm1lI+9dmGZ3u1webIUb/Mw5XZoIn2Vxx+L91WCqjbqdourmICpCNy7pXsKqXO2IvXuAdD/bjAMdtX8uVZL/Dao9a8Bk1ZsmFaTkqycB3BlIagvTtWXBGj5hamRZ0fj60wY6z5JiwceLA==
*/