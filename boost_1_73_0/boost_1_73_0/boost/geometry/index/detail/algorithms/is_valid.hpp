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
2ILrI8tnoMNMocTlllS8h8qGU/ZQuaKECAgHsmzyJDnB+OJbZYmQTrJ2aUIs6tykuq9m0/QWU82OM1cLgErcZ+m05s4I7QBlVbcNsgGf3TImciSXpBQP8eIaQyLqfy5g6Io7Y52b5GLFAqPZ5CmPO5E5Sm1PnATPfxLNlrhSWeh+lHzD8bOP4XAeJ5/S6SJz2gRR1FFy7/I8nD93p7YXVx9O6ujRJUnJXumi4ut8jGWmo3QItJO61Kzw8WHAds/z6opHJSUaGbTogORQeG+0djQNApPhziirsGzUA3qEh+7qO8o9wY7omjuffdivi6w+Q1cHAteoIUCxgjtWfTPVhtnOx/vv1qxKQDldpFJcI8HRIuYmAd1T0QgHBn7sQVJvvpylt+iFxxdDEbXckxgLeixQLK5H6TT/lCmCUUzHjmB6l3gRtP4F8Xc0i7mKi0GtW/2GcHcr6hYZtxN1r0LSzTe4MfyWV9GJY+Vsl2DS9XCpA4/r9CIfk78l8xo12+fT4pYSHKvkjOHf+bya1xaBwK9pjueS0CqiuiEd6LoNYSeJbkCI4DxLFtTIJUcL4NkNYxBxuKxmwyQwGXmRcalgvsK+DorhllaaEAPDiOMRJ0VFWfRJZtTckj++3n3945CPL2Ib2XlHjbILYuFK
*/