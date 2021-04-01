// Boost.Geometry

// Copyright (c) 2016-2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SEGMENT_INTERSECTION_HPP
#define BOOST_GEOMETRY_STRATEGIES_SEGMENT_INTERSECTION_HPP


#include <boost/geometry/strategies/tags.hpp>


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace intersection
{

namespace services
{

/*!
\brief Traits class binding a segments intersection strategy to a coordinate system
\ingroup util
\tparam CSTag tag of coordinate system of point-type
\tparam CalculationType \tparam_calculation
*/
template <typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::intersection

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SEGMENT_INTERSECTION_HPP

/* intersection.hpp
gIDRKlEwJEpXMrVqQ6gfZRK288b+qSP7bewfipGfQ5kjbAxvfGqnFh5JdSjsvydCVm3lqVVnKu6/Fce0ppcVge7E6wb4lcCPq66AXNq7ay/AkMJ8m+QjCAef+6rYMmt9zbWgP2zydlanYdHYjJgIBanC6o/xUNDnEIm/YluO3vfyrZ0iAWG00/KhJ76618sk2ZgEUpLucX9iFmxdU+bZd2cCdrdH5yojBudo8CFcKFdfMgmzWJszJwdOUguHIdlXOBt4nBdkq5jLovKElpAQUGO2elbl5DeB12wcIg0h+HOdMjOip3gUmNNmuK2NBlY/n6bojvFcDOdpauGMFBDd49o+cbmyQ827RM8YsUaF2XOKYaPF69KFOxxSlc/hPqQaq632OdUktwZGHWJtHTeBoTSyhOOaFV6p1MMNslTvXHoMEU/hYk/g4lZNqAZmG4ai8oXktASLJClYYNSzpGXF98ISog5OB7NYFx59EnbQ6mWkVNvQ9odlUDN+4kzNeNnU6XNqw96Rl+eAMVQ3kw2wxVF+5EAfhdJrDdCgWCW6FDkGtqueT1nefTiUyQ==
*/