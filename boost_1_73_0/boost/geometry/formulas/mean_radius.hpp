// Boost.Geometry

// Copyright (c) 2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_MEAN_RADIUS_HPP
#define BOOST_GEOMETRY_FORMULAS_MEAN_RADIUS_HPP

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace formula_dispatch
{

template <typename ResultType, typename Geometry, typename Tag = typename tag<Geometry>::type>
struct mean_radius
    : not_implemented<Tag>
{};

template <typename ResultType, typename Geometry>
struct mean_radius<ResultType, Geometry, srs_sphere_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        return ResultType(get_radius<0>(geometry));
    }
};

template <typename ResultType, typename Geometry>
struct mean_radius<ResultType, Geometry, srs_spheroid_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        // (2*a + b) / 3
        return (ResultType(2) * ResultType(get_radius<0>(geometry))
                + ResultType(get_radius<2>(geometry)))
             / ResultType(3);
    }
};

} // namespace formula_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Geometry>
inline ResultType mean_radius(Geometry const& geometry)
{
    return formula_dispatch::mean_radius<ResultType, Geometry>::apply(geometry);
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_MEAN_RADIUS_HPP

/* mean_radius.hpp
/boJ/PnatZM79hcwA2E6zwNtBqtI7ERY93LiflN+7hd25maS+E0/Qs2KE7v14pQJxhPMnJg0w6wOno/ArIg5NB4cg30CzIzYbtdq4tkrsMrEIp0/Yx2ywKYQq/ricSTOIfBjVTlim2xtmuHxInXznBZeVdzvDdaTWPKVMW+w7lFqVolY72n322E7gPkTe2ZeVpyrwGILCDvtOOgBtns8zAVGwmqfqFUK+9kYfi0qbOqzDzFY
*/