// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_BOX_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_BOX_BOX_HPP

#include <cstddef>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/disjoint_box_box.hpp>
#include <boost/geometry/strategies/spherical/disjoint_box_box.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


/*!
    \brief Internal utility function to detect if boxes are disjoint
    \note Is used from other algorithms, declared separately
        to avoid circular references
 */
template <typename Box1, typename Box2, typename Strategy>
inline bool disjoint_box_box(Box1 const& box1, Box2 const& box2, Strategy const&)
{
    return Strategy::apply(box1, box2);
}


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Box1, typename Box2, std::size_t DimensionCount>
struct disjoint<Box1, Box2, DimensionCount, box_tag, box_tag, false>
{
    template <typename Strategy>
    static inline bool apply(Box1 const& box1, Box2 const& box2, Strategy const&)
    {
        return Strategy::apply(box1, box2);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_BOX_BOX_HPP

/* box_box.hpp
enaw4BAplxLyWaw8rqmrtCp9u7GA+DZ6qT5/EZmM42iywE0/TWUcYmJTfDkTZYO8mk3xDVNZYQX+9VqhD3uP3vg+kFXvY2chRRDotMFJtnH86/ssApX/IWxWSf2UPElwMZos65Ln8/b/fTYcgNuh8f37+DqeYuuSnoUdkvwUPkmyCBA8ZL6bALybQfBuvI538/B9Qg/1GFSuQpHWpXz8kzYbpBkqwhXqdi9OGvAt5PFOm1NS2zjm3v+xNTTmXvqenniCxKRVcpMShOlv0re5yzwRb7PnU3fYeB/rr6puJcZyo7jRKparVqUx2J5co1A8Rz48x1B4jojjORpg2Dey/G9QuQDlMyi5jviXAoUzQIw95x56FqQnC6pIwbTY2E6bE8j/KoK5F6J2iNyfPkwiUiD4JtwMBcNX16UW3pyplvvng1B/wV1yiASkEuLGcTlXma9WaXv0TMn/RGBC8Hwg4U94s7GaUIqkDfANN4haNZTpp+5rQViFEvf7ZjmGitD1wN9fn1bgyDHUsB74Svb8UHkDSv8NYRRxYKMXCJcg2/Obz8if/0oq1zTbccQeYrIjpbQT2rpLMBudpqMhn5S5UlYGkcK5/4Lbo9y8z9anZuOaNRtpOP7dHPTewORp23SsUp9SEnIRroZJmSsHR+HwhNyS8CAcTPjX02lJSttIAKYlCdMS0PRgIBwUk5IzVEH+tFt7RNIw+xdMQQ1s
*/