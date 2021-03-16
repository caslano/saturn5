// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_FAILURE_POLICY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_FAILURE_POLICY_HPP

#include <boost/geometry/algorithms/validity_failure_type.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_simple
{


struct simplicity_failure_policy
{
    template <validity_failure_type Failure>
    static inline bool apply()
    {
        return Failure == no_failure;
    }

    template <validity_failure_type Failure, typename Data>
    static inline bool apply(Data const&)
    {
        return apply<Failure>();
    }

    template <validity_failure_type Failure, typename Data1, typename Data2>
    static inline bool apply(Data1 const&, Data2 const&)
    {
        return apply<Failure>();
    }
};


}} // namespace detail::is_simple
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_FAILURE_POLICY_HPP

/* failure_policy.hpp
tQHq0wHKo7m/B9TgfTSgvJ8fC+iZa0Bt1jweUDPXZiBdqH8GlNsfF/r8/UA38HmgF9ggyJ5Puf2xgLt1nC6eX48RR3mMOCr79BXMXcXcr5mbz9wK5m5n7j7mfsvceuZeYm4zc28z9xVz+5lrZu5H5mh7peL8DsP9grnezA1g7kLmRjM3nrmpzJUyt5e5L5k7xNwR5sheSHEup+E6MdeZuVDNDXkinBWKVK/G7zgmHHJa1Cj1CdRb5EKQp0XLReI=
*/