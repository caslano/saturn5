// Boost.Geometry Index
//
// n-dimensional Indexable validity check
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_IS_VALID_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_IS_VALID_HPP

#include <cstddef>
#include <boost/geometry/core/access.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

namespace dispatch {

template <typename Box,
          std::size_t Dimension = geometry::dimension<Box>::value>
struct is_valid_box
{
    static inline bool apply(Box const& b)
    {
        return is_valid_box<Box, Dimension - 1>::apply(b) &&
            ( get<min_corner, Dimension - 1>(b) <= get<max_corner, Dimension - 1>(b) );
    }
};

template <typename Box>
struct is_valid_box<Box, 1>
{
    static inline bool apply(Box const& b)
    {
        return get<min_corner, 0>(b) <= get<max_corner, 0>(b);
    }
};

template <typename Indexable,
          typename Tag = typename geometry::tag<Indexable>::type>
struct is_valid
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_INDEXABLE,
        (is_valid));
};

template <typename Indexable>
struct is_valid<Indexable, point_tag>
{
    static inline bool apply(Indexable const&)
    {
        return true;
    }
};

template <typename Indexable>
struct is_valid<Indexable, box_tag>
{
    static inline bool apply(Indexable const& b)
    {
        return dispatch::is_valid_box<Indexable>::apply(b);
    }
};

template <typename Indexable>
struct is_valid<Indexable, segment_tag>
{
    static inline bool apply(Indexable const&)
    {
        return true;
    }
};

} // namespace dispatch

template <typename Indexable>
inline bool is_valid(Indexable const& b)
{
    // CONSIDER: detection of NaNs
    // e.g. by comparison of b with copy of b

    return dispatch::is_valid<Indexable>::apply(b);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_DETAIL_INDEX_ALGORITHMS_IS_VALID_HPP

/* is_valid.hpp
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
*/