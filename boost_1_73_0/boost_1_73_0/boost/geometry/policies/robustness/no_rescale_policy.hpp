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
beYC6uZ8PW3cmJVQxXinpzzUOtZd0lU9QPytORVG4wmA54CitiZXqF1ZvbZbj1GlIYxqIKJQFobUMDtDG/QDN2K1YC4NMApJX4oC/uPM+9rk2inwaFQvKzOSuSjm0mxs3BFvyQcBSwh6VF0VGmTXSJjyRbBsAWaM4hjcxVnzCY/w4c8QPTSO+SIA8QQhZo4Ltj8VR5nfsu2Rcm308+d/6WQwZaPc6HM586xFPpc9reyfUqqRYze6L7BiK0SjnGOOm4BuCsL0F1ovk8RlWhzTea+M+JXeVO2tB3ZZeG5JdZFXeVVVtixxIxXL8AMZqASLsiIezDDIXKQLj+/DBHMaAe2CMNiPl3hPJjit1llOAgtUUx77U/ELA+U0CI+K3vflaHTdPeupJyZ1S79Urpq9WNWgmrIUR4pb3w0+i6x+subgTu7sX46MpTliTSS4ThlIhren/oguZkjI0gAdcG6JZGJMeDuvrW5mZnpJvBFK4m4nCBPegsvgNTCsC+yI4cWZ+Onnn/4dRApPcR8dHj4WE1/CyoSBXS+I9aFo5jA2kF9dDBo0oDsuZMSkFd6OBoqBC9poE0N3ppO5mIAGuc1ujAYiB1MIXlVApxYT8TwVFqeoVcTnsIb0F5Ti7sku1aabNYXnZkXhO64nLeeU
*/