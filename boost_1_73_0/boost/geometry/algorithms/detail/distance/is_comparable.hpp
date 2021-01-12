// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP
#define BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP

#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/strategies/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


// metafunction to determine is a strategy is comparable or not
template <typename Strategy>
struct is_comparable
    : boost::is_same
        <
            Strategy,
            typename strategy::distance::services::comparable_type
              <
                  Strategy
              >::type
        >
{};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP

/* is_comparable.hpp
iH+wi7aff/Q0JlP4YxyxNBdfIfjB+htXWanDxivb8QSjkzOEJ/LQQpcwXvGqeN/9ukp8RxpFgZ83ylswbvKdT3mKKVpJ29u4KPMqrDIvaj2I2XHj3uWa8+KqDZNk73mqbr5wXir2EpXCyQ29j0PwCrAmcFd/ltesY7/j2PO+/V6/TcImLMssFzFkjfBopzNzez/HxuavKy4b5A163G/aOHEr5in2cdmGf6jE/hDUcBRRUeSx
*/