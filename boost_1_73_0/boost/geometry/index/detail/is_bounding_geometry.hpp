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
fsIC5foVmVaEeaZYrs2KENYQ5V56HTTjs+ExWEFhN9/M+p17TLmX4JxBH7juME9hP/rU4HOOa2/krrTePrwXX8UWRg+eyn0LCxX2JazdLO5bmJWwOzGp/2G+wDyE1V7XohP3LayEsGr2hZNYd2FueT2DtqgbntXXe8ze+nsNzYIOXl/P+fXRc0mz0xO7e3F+MFNhEeFzNrKvgzkJSyw5jHssVrER03Zu516BxQhbGH5/MmsP
*/