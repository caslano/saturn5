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
AgCrYKJG/nPQmmogqaCizJSuTrwCH+r7QO0GfHBFwlNT6VXYLwdRRKM10uYtOwjOGynVB3xXnUSdcPKSwNbAIYRR63onEdKF9B6/BR7UBH3yjlIvMsKJApJGd67d+X5E2mw5xtBbeoLUXHq4fVs0SxEt2O4n+GCuDJdJXPnzkapDxcDJzMcRyhFYKB4LtWhMlGszsUAVkhxm0g4effUzxoSnAzvozJcg4X8vo3A8jDu0SrD1E2QMQ5Onh0YXbW2ymKquH/cH7dyk8vUVMbmsC3BwD0kiYIySY+QB+N4JCkRcNLFEIL4VpuBQ2SoMstQQXGEW7/SSL2mudttTFfYtUcrtJ9T1Br/u4F3OqUWQENIDYBfAP//NCsyzoKkjxVITo4KfalJWODFOlTZzP/pcZ6WjF0TSs3ge5tR/Njl5EBXuPSqAIAtM1kG10Reb577ome4wgpeAaQLWm72x25AuCrd+tZkBNX8JTeyJDJHYAzJsVGOrz7W8wII685igmY0LAVF9UprLxK8h4ISDxO39/UdCkmnn44h/7Fh83goL8IFqKFs8sa3utsjWSg==
*/