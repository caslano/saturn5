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
L31GIORiFHkXGSnIIpMEIQIpQhA8owVZVTNB1gbo4kWgZEGWBO8kRwgkKUJGIjwJCU4jxKzU91bK3L/P3d++wE3bnv1/Evvsz13I+zBvoi8Po6bNJ55T55GfJsymNNj7VzJg9BTiPnI86TN0HCWXH72Ik7sncfx+JOnadxilLq5DyXe9BlPq7PwjpU49B5BvHN3UNHLIMPL4tz4kf88C8n77dPJ+wy86eZjkH0KmnEgj1YMTSfWgE5RqLDpCqeb8Q6TmvGhSa95+UmtOFPls9k5GM7aTz37dQqn25A3k84lrKFn8soJYeC+j9P2sJeTjyp/I+1PbSP6R1eT9/gDyPmIWeb9pgkYepgasIFNPXlfbIK93+CX57FA2MY/OJpX2Pycme58T46hnpFzkM6oHTNj5FAawv4iw4wkRtmUCPSbC1kdAD4mwOYMIGx8Qm82XCNk+meRfSSDv/zxI3ifupDp430cvIfm75pD3W3zUeZixeA2ZfvoGaXOa2YOmduEhHxaxzD591egXpCLkowLPhwzyIezGPPB8bM9k+Qh/xPKxJYOQ2CXUnn1++h8k/9ppDVuh7w8tJe8j55H88Kk0D77LwsjMM+mkC9pjP6Og9qDRBrk1twv/+aGXpHpMNqly4AUx2/eC5sMoivNi11PGD+TF9iJeWGxNJyQumOXh1gWSn3aG2hrNP7+HvD+5hbyPCyWpkx3R5ujMeaGb
*/