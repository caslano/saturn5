// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Bruno Lalande, Paris, France.
// Copyright (c) 2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_NO_RESCALE_POLICY_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_NO_RESCALE_POLICY_HPP

#include <stddef.h>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/policies/robustness/robust_point_type.hpp>
#include <boost/geometry/policies/robustness/segment_ratio.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// Redudant later.
struct no_rescale_policy
{
    static bool const enabled = false;

    // We don't rescale but return the reference of the input
    template <std::size_t Dimension, typename Value>
    inline Value const& apply(Value const& value) const
    {
        return value;
    }
};

} // namespace detail
#endif


// Implement meta-functions for this policy
template <typename Point>
struct robust_point_type<Point, detail::no_rescale_policy>
{
    // The point itself
    typedef Point type;
};

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_NO_RESCALE_POLICY_HPP

/* no_rescale_policy.hpp
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
*/