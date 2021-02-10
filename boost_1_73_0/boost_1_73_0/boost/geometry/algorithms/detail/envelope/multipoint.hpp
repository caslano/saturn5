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
C/QCCDJ+EIpVIfYurHg3HE8A0PejgBlUYn33wml+iR/hWGrLtCHlU0QlV3IUNqMG8QV73YCjNIwcV+jHXZclfDXCLkUGaSsnk5xT1M3CwsSr0P0J6+4V9q0G4uvuqcMfj8tx8c34aTG+ZLqq7bwm3z/V7NncIIhJnOUn3amgUteuVErZzUcmww0JyGzMyOLCkA5J/qx8iZjXNHNxUaaIieGP6A+jfDjfUCiTFIDHIoJ5h0lczX57BExie0YsDF7GHdqX9LyNqyJzL7jf3P0Ea+FP7jbLQgrEqRDbqjOH7yfO8Mx52387HH0swRVdCz/arsLsoDweX+8bT9TwkfR1A3rrdO+RVJYoHKv5GCN9H+q6hbwaIlYbuTXHqspuqazVsPrGwnXR7572R9sstLV00eu+8rW5q20ljF5fd+7+nEcUFlD169KKoltppNMb1VxeA5W6y2RA9WxNCWw5dM1ZFtI29d04KDOBLT2RYD4dZT+roHsbLkRL6deOMdt3QyWnuiOjDtfUKNxDpHk3kq5vaZGsKD/+3H0n+NSzOSc6R3eeA7eymBreVBX5vwoJvPyoMvx4w25cn9QVKhvwscXygU0YHWrnCnaguZlnxVdzgC092Mye/ss4pit+HRXXGfaJuHnx2QNAy48h+MLd
*/