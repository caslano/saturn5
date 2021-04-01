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
DcbqZWD6hKAb1LPdK+MhJJ+ibW7QdkW0lzqCZJv3OTzNERNLiqXMDUqrua5vOv5RAmNGuoM+KGUx23xD/X095TrmiWfqz2aLska0volK8ekWch7fia3WNybXPerOLyEGnEHrvpaqzkBKUnLS8GQCuHhlimKTSZhnd7whwhI26glL4D7b31CRY3Im44YoEjItzfG0rKQfQ16LmttaApJ22pLkvE9xmUmIHFSKqwH/NT6hMlxJoDC8SSk+il3eF8GPdhA44Xdto/v8t3tc2NsZvddXQj9hqRURUWnOWUA/KM/jM1rI5uKONE7XvgD/lX80HJGYLaPFQmHWZLIkgi1zpiTWuDPQ/9cswq1q3L3iplUAyVq1+zssIqDQf23r6EEodWetqzFMF64ZDpF3KZPRYJm1B67By8mgLlTwIQ7rUg0a6r1WoqghVxJscgcr+u3SHQ9jJXEmhOgz5Z4v/VrVbfdQABz389qMqrL02oADgqstjZVpJWr0+VCZ7pqkB0dcy4kOJKZqUT8bWyFa+P4rRuUxhx1DeeL+7GTOHKK70B8Jq6NYk8q1g6fCaQ==
*/