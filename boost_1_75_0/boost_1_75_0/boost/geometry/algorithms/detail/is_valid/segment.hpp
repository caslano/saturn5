// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_SEGMENT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_SEGMENT_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_invalid_coordinate.hpp>
#include <boost/geometry/algorithms/dispatch/is_valid.hpp>


namespace boost { namespace geometry
{



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// A segment is a curve.
// A curve is simple if it does not pass through the same point twice,
// with the possible exception of its two endpoints
// A curve is 1-dimensional, hence we have to check is the two
// endpoints of the segment coincide, since in this case it is
// 0-dimensional.
//
// Reference: OGC 06-103r4 (6.1.6.1)
template <typename Segment>
struct is_valid<Segment, segment_tag>
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Segment const& segment, VisitPolicy& visitor, Strategy const&)
    {
        typedef typename Strategy::equals_point_point_strategy_type eq_pp_strategy_type;

        boost::ignore_unused(visitor);

        typename point_type<Segment>::type p[2];
        detail::assign_point_from_index<0>(segment, p[0]);
        detail::assign_point_from_index<1>(segment, p[1]);

        if (detail::is_valid::has_invalid_coordinate
                <
                    Segment
                >::apply(segment, visitor))
        {
            return false;
        }
        else if (! geometry::detail::equals::equals_point_point(
                        p[0], p[1], eq_pp_strategy_type()))
        {
            return visitor.template apply<no_failure>();
        }
        else
        {
            return
                visitor.template apply<failure_wrong_topological_dimension>();
        }
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_SEGMENT_HPP

/* segment.hpp
uuRXZwoWn1TEj1i81osoy+pHRZJqdSO7Uq5WWlNlfi/0eDSm2gNlHIfGENl73gf9F7i8/Unw/OkCwXlSnoA1ZQL5y4e/LIJN1EnH0OvSSrEwvv7LZ4axlgyBzM/YmHV+Fj1mvxKnYJjPVLY3jq52hTGdb25JQzfAA3ELuU+DyWPHuQej+zMDvnUXBO7ned+r503vwUjC0mkY/eQeDLZHwf4E+KNxj3remP8ZCPyFp3X2s+j1LNEsfoHvBNQNDZuW46IhrQkQmHiRpTV5WRoS38Fr4evhvq02flsPgVv4t60Xo8vxAhbfxLezcgxzj3TPRcNeuR8CT19ka/8jF6P3ys8t3qcIftUfxz0B7iGyewmNGs0f755m5a/G+68h8IO/snKn/TV6HCwbIR4ZwZSZYvfBCojqmw1/TeBEy6w8GIbt5O9HMBaFoJAuIn7n4mhdBukU08Vd91cuF96amo62QODXf2X70Q49f2qL9HHB8gTeKryG/Wgp9gj+SJ2G3mE6+Fd+/xex0XAeAuZLLM3PDXUiyhn3CDK9I2A33kg0pYfr25xLMePiKnggfopXkPEwzF3LjZc4PnIzeO4F13eJnocyo8705KdBF0gZ4EqDLWlYkBXLtWGgOy3qrkvRQtszEjMTsFAH+FA/uIVSllxpKVX8cpvkF1qoLVRiCZVe+x53zl++ZNj7Ez7PQGM/Z+2S9Hn0GH0YK68KlWzv
*/