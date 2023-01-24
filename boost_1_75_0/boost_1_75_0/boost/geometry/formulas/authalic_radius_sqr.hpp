// Boost.Geometry

// Copyright (c) 2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_AUTHALIC_RADIUS_SQR_HPP
#define BOOST_GEOMETRY_FORMULAS_AUTHALIC_RADIUS_SQR_HPP

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/formulas/eccentricity_sqr.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/math/special_functions/atanh.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace formula_dispatch
{

template <typename ResultType, typename Geometry, typename Tag = typename tag<Geometry>::type>
struct authalic_radius_sqr
    : not_implemented<Tag>
{};

template <typename ResultType, typename Geometry>
struct authalic_radius_sqr<ResultType, Geometry, srs_sphere_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        return math::sqr<ResultType>(get_radius<0>(geometry));
    }
};

template <typename ResultType, typename Geometry>
struct authalic_radius_sqr<ResultType, Geometry, srs_spheroid_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        ResultType const a2 = math::sqr<ResultType>(get_radius<0>(geometry));
        ResultType const e2 = formula::eccentricity_sqr<ResultType>(geometry);

        return apply(a2, e2);
    }

    static inline ResultType apply(ResultType const& a2, ResultType const& e2)
    {
        ResultType const c0 = 0;

        if (math::equals(e2, c0))
        {
            return a2;
        }

        ResultType const e = math::sqrt(e2);
        ResultType const c2 = 2;

        //ResultType const b2 = math::sqr(get_radius<2>(geometry));
        //return a2 / c2 + b2 * boost::math::atanh(e) / (c2 * e);

        ResultType const c1 = 1;
        return (a2 / c2) * ( c1 + (c1 - e2) * boost::math::atanh(e) / e );
    }
};

} // namespace formula_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Geometry>
inline ResultType authalic_radius_sqr(Geometry const& geometry)
{
    return formula_dispatch::authalic_radius_sqr<ResultType, Geometry>::apply(geometry);
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_AUTHALIC_RADIUS_SQR_HPP

/* authalic_radius_sqr.hpp
QP2xKkd1F3Pd8VRfOuYB2mZp9eRjX8y9J6f2n1V8OLt3q9qGBvI8ksp7aelGpJkgevQj5mnoSPyA4+SLx9zORQZRqmxMPGa2LpidCRgP7kIe7lymeTh3YDuZPLA7xUeeq2RQ/o7+2Pcvs2ge3tM8PGS2Nnge8tDeBtq/fpAGPOB5uH2Z6k+cOrgHxUeei+VgUB5ne7aSySM+y6NykaG8f6p09lL97HyMxHHhw6unajsbGnmAeYvaEci4Qcej3HtXaR7+jI2kcxfiI8/FuiCpTNBLzAOXCeJyWmyMyKE8/0jtF7D+iHMFG5u4XQlxHtCGwGNmyyCX5iGN2vzANjzDoxfF/zs817Ch8PYlHf8/cDsfOHer8qB8ep+Og6jHldUF5OF+Grl0PBrWDn105mbUUapqeJ8+sXGAtX+uI1+tn57ryVfbcchmfECd/TQP0CZxvsK5+a/7nA+3OR+u03nGd1S/YvAJ1wevGgeYfnx1HpS5av30RXME09fP8vCX2n4B5iGf5wHtweAa4kriUfLb6P7F4/M8kEIVHz6wcfl9Ppuj0K6H8h23F6CgthbE9hOoHQesC76OYnzAPnGbpJ09TvzGupeMr6oLVR4+Fumlp+MA2pCgeeD2G+jahefhVRbrE6o8PM1gfMi8S+c5/3G6Nlz042vVBbdVoMGHPHEeXvJ++Zy818iD5tiwcPwQHfwrK6YQFcmX/kLkASPJ
*/