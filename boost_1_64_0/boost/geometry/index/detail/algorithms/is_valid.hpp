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
cUh2b7pABFaO17vci3jW60AdOts16UI5WDZcyDexcRw/EVLhFTScZwxL3AygEP+sz9ZKP5lGZU5TCU+8O+XEZAnMqC0Al3AX5qKycQZ0iiz9w/amjZDdZ2wXbJbw5igiUT9LEIqzwTDuos495bKv4PF87O8qvpsDM4QT7otqGmCvbclLH4Ry3WcXaTAbWf0i8oKvjlC/kzrpG5PrFjKRu5AqYVcVs29cZp/TFrz+I6nHD+ydX2na0nr/BVGCpwGp3hkT+UcblhPvoT8L14FImF/qj8JLd3iC6x+7RZOxh9MupZDKf5n/8+7PQCqhSMZKTUYBKOvpFK1pQogGiJUUIe8YC1zcRxne52tr4tbjHY5vDphPADTmbO/IUDjQ9/R5HYraUrPWOTX+Eya3rhA9fGbeLJ+bD/rbgksLA5dTbeTRoVWFyCEs1CuBIPthiuohKDKmH+GBPFFV8odzPAVJ4jmpZ0Pr8NdsirrfEiLmqoMMK+J4RW4J+QTQn5nTcznrApNr/NDb9CSk2s9GvKxbgWmAX8fsMy4uUQ52HtJNEWr5fcpOjD7v6U4I3w==
*/