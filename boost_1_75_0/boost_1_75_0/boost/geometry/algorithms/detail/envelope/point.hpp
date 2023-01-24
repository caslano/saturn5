// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_POINT_HPP

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/envelope_point.hpp>
#include <boost/geometry/strategies/spherical/envelope_point.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{


struct envelope_point
{
    template <typename Point, typename Box, typename Strategy>
    static inline void apply(Point const& point, Box& mbr, Strategy const& )
    {
        Strategy::apply(point, mbr);
    }
};


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Point>
struct envelope<Point, point_tag>
    : detail::envelope::envelope_point
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_POINT_HPP

/* point.hpp
aj/GEyF8LQeVHC3imAz5juAqxzxcBNXrh9wWOgbyTb4xxzQn7ITEv+awOWFvjlW2ehKDvHiQujygeGBtHuRuALk1bzjDBOthY6Ynh+/lXYCI45ZMNOGWRF9kIJQ9JlQwXQMbjY2jThUD8DD0xFtuMXb6dkBPHJOiMxtHIHVazerEE8WL0nb5C5B22nCFel4Zj2lfjIjQPHg5UeuJ0Bt1GTUdZFQnyKjDkOd1Q0ZddwsfNzsgcgTC/9yS0JGZPeJ2mScxqijrZL7MXr7F2Ld4WYP2UMPHpCroLzHpBJZPKR9LB9VmqR5yRpxn5cB0nY3bqeI3n45n4ouE2T8x/X+U6P/hkg+hPJpYC2fpTHQ7WQ2LooY61vEbDzpgU8+KqwQndiIvfKdM5OvyUCQfZG3cFuXyZAdENkJ42KDNWJx6us5uNyi3/xQoP2bT3hYbgXIOUI7gOsKJsP2DvD77B2/Cu/cT2eEcRNA4GKMQFPNaXs99Tnz4DEY9FINOGmeUZIbHg25LCT6BFwk+MSgtkl+SvsJRqUisFHLg+7k4Q/LLDFYceH0ZeYHX9wKv771s7BJQ/cc4rh+/GyJbIfzzONqmbOuCSbYm2yVmCsf4Z9amO41M1f/6nButTM3aJuQRL55ys/KFulHpUg8quepxZbZ8HU0lvragQRW1JsHDjwEePgw8fEYfHv76OL6epORmwqdBDoEQYnnbbUGOLNGB
*/