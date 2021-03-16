// Boost.Geometry

// Copyright (c) 2014-2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_FLATTENING_HPP
#define BOOST_GEOMETRY_FORMULAS_FLATTENING_HPP

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
struct flattening
    : not_implemented<Tag>
{};

template <typename ResultType, typename Geometry>
struct flattening<ResultType, Geometry, srs_sphere_tag>
{
    static inline ResultType apply(Geometry const& /*geometry*/)
    {
        return ResultType(0);
    }
};

template <typename ResultType, typename Geometry>
struct flattening<ResultType, Geometry, srs_spheroid_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        // (a - b) / a
        return ResultType(get_radius<0>(geometry) - get_radius<2>(geometry))
                    / ResultType(get_radius<0>(geometry));
    }
};

} // namespace formula_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Geometry>
ResultType flattening(Geometry const& geometry)
{
    return formula_dispatch::flattening<ResultType, Geometry>::apply(geometry);
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_FLATTENING_HPP

/* flattening.hpp
wBh4VTOR19aVl3XrWPPzBBgDrxrCKuRY/daOX6hjRfIEGAOvWUzk9cI7N4d0rFvyBBgDr9mENYTDdY7eOKJYw/pzngBj4FXLRF69eQc/1rHeyhNgDLzmMJUXYs1+NThcx/o6T4Ax8Po1E3lddsPT5TpWSb4AY+A1l4k6vOXoox4dqyJfgDHwOp+JvHZ6n+3RsS7IF2AMvOYRlujzQ/R4mC/AGHjVMZHXc19N8ulY1+QLMAZe9SyZ1zAN6858AcY=
*/