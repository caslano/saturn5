// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_MULTIPOINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_MULTIPOINT_HPP

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/envelope_multipoint.hpp>
#include <boost/geometry/strategies/spherical/envelope_multipoint.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename MultiPoint>
struct envelope<MultiPoint, multi_point_tag>
{
    template <typename Box, typename Strategy>
    static inline void apply(MultiPoint const& multipoint, Box& mbr, Strategy const& )
    {
        Strategy::apply(multipoint, mbr);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_MULTIPOINT_HPP

/* multipoint.hpp
w8kRK697rrifBCe5QoriHuj666PzLOhzwxD6LT04hOm39rRlBFOp1YaGrXoUsOEkMqEHKd/ZPfbGqyziOiUL0HQ7RL3akchu+bYdCUkRfjYbsFiZTj+K95sIYqFLsqAD8nXd2DYz41lVoLh3xfqmsrUEX2U2LtlLG+H/ZFVetvWzkVCrqa/DM8CJIfoaMxCSRAX9W++7+F5AeQKfsyfcm85yVHQg1eiPYHm1ORq0tjJhT8vAkBdkkgb2UqxpW9zawgj9+Eb+KgqTo9LUoAH8lgYT/ZB8fMp4UWHqMe0Qzz7uUBR9KpaaLBJDcpsxpgXtR7qozjJbfaCcmx8siHXKDW0MzoDF7KCfPtV3AfbP33hf/IeD1Y0XN0iTsk4a2G9gq0EWkjHJ6zXKvht9QQvhHuaN5Vgb+grUWfhpccT5BwPz1OqehpaHyDsQRDpFCN44KJ6eOFbyENCu/o/yiusjcaR0VAKj14p/WSaF3OcOq6S2dbysplM/AYQ4qdb5WASlBpGXugQhhOlmf0j2V7Jgwbm7h/JtlKBGA9/jWVzdNt50/AiZan8fMx7KkQ==
*/