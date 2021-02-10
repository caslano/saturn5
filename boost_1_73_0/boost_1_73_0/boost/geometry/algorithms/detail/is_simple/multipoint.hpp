// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_MULTIPOINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_MULTIPOINT_HPP

#include <algorithm>

#include <boost/range.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/policies/compare.hpp>

#include <boost/geometry/algorithms/detail/is_valid/has_duplicates.hpp>
#include <boost/geometry/algorithms/detail/is_simple/failure_policy.hpp>

#include <boost/geometry/algorithms/dispatch/is_simple.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_simple
{


template <typename MultiPoint>
struct is_simple_multipoint
{
    template <typename Strategy>
    static inline bool apply(MultiPoint const& multipoint, Strategy const&)
    {
        typedef typename Strategy::cs_tag cs_tag;
        typedef geometry::less
            <
                typename point_type<MultiPoint>::type,
                -1,
                cs_tag
            > less_type;

        if (boost::empty(multipoint))
        {
            return true;
        }

        MultiPoint mp(multipoint);
        std::sort(boost::begin(mp), boost::end(mp), less_type());

        simplicity_failure_policy policy;
        return !detail::is_valid::has_duplicates
            <
                MultiPoint, closed, cs_tag
            >::apply(mp, policy);
    }
};


}} // namespace detail::is_simple
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// A MultiPoint is simple if no two Points in the MultiPoint are equal
// (have identical coordinate values in X and Y)
//
// Reference: OGC 06-103r4 (6.1.5)
template <typename MultiPoint>
struct is_simple<MultiPoint, multi_point_tag>
    : detail::is_simple::is_simple_multipoint<MultiPoint>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_MULTIPOINT_HPP

/* multipoint.hpp
OG19kwhR+hdvKe0kiBBaoWJNNAo8qO1dcbSyJA1i05ruLG2nFHg0pm50GEZ3p7ZBnM0qU6u4eVQ1KDZ6HhpANTCmiAKyiEA6qjMPcSFuHWyk1ou7jvh5sudapizu+Bq485a3nnFguN+jxZx2mmGyDdOsbtR4POZNnQ9UiFjwqteOq9qqrgiNmJAQjA2XoXd5VoaMHDtDdaxXAvFpKCcaMyBuMfZQDY3LfwteiOXo2US7tndghH8LIAJoqJAbdgAGvFHjC4LL0x2eX116w/Mfe2fgGmqH0HiYBs572J0356VpFvITWlYGgeohjRFPhqG1R+bf+UEk5nEILsbdfpo9htJGHgVvcke1R/uPgFZpV67N2V+8CtbWIIeXENOC29YxxP4NG+j3umcoEf3e4PrqEpaigOHR35NJEiNGN96OWfTlFHiyaeKAtpimymm6i7Pbx0ymFsxAgIHPXNTdB54E1C3pFU7MpwUiiE1BQF8ktE8YA5U5ze8j7qZDyRm6ClDVlkPe1QECT3CTDHG72iUFPI8ZGvAWiLOIF0C8uyS9mcMSyrRjqwZXMaDnpdjKdj5BM+CA2+IIvunJWiJuBEiDpJ7Xfdc9vyxoUOXJKsg9TnzMRGs7Wx4F+Sswg+qLt4zMhGjArVZd7e6bq/6w
*/