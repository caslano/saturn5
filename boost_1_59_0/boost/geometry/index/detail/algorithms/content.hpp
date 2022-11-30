// Boost.Geometry Index
//
// n-dimensional content (hypervolume) - 2d area, 3d volume, ...
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2020-2022.
// Modifications copyright (c) 2020-2022 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_CONTENT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_CONTENT_HPP

#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

template <typename Indexable>
struct default_content_result
{
    using type = typename select_most_precise
        <
            typename coordinate_type<Indexable>::type,
            double
        >::type;
};

namespace dispatch {

template <typename Box,
          std::size_t CurrentDimension = dimension<Box>::value>
struct content_box
{
    BOOST_STATIC_ASSERT(0 < CurrentDimension);

    static inline typename detail::default_content_result<Box>::type apply(Box const& b)
    {
        return content_box<Box, CurrentDimension - 1>::apply(b) *
            ( get<max_corner, CurrentDimension - 1>(b) - get<min_corner, CurrentDimension - 1>(b) );
    }
};

template <typename Box>
struct content_box<Box, 1>
{
    static inline typename detail::default_content_result<Box>::type apply(Box const& b)
    {
        return get<max_corner, 0>(b) - get<min_corner, 0>(b);
    }
};

template <typename Indexable, typename Tag>
struct content
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Indexable and Tag.",
        Indexable, Tag);
};

template <typename Indexable>
struct content<Indexable, point_tag>
{
    static typename detail::default_content_result<Indexable>::type apply(Indexable const&)
    {
        return 0;
    }
};

template <typename Indexable>
struct content<Indexable, box_tag>
{
    static typename default_content_result<Indexable>::type apply(Indexable const& b)
    {
        return dispatch::content_box<Indexable>::apply(b);
    }
};

} // namespace dispatch

template <typename Indexable>
typename default_content_result<Indexable>::type content(Indexable const& b)
{
    return dispatch::content
            <
                Indexable,
                typename tag<Indexable>::type
            >::apply(b);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_CONTENT_HPP

/* content.hpp
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
*/