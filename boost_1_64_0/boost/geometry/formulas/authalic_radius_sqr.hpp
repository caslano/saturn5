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
uQro0As2/Pn6v3eH+PW/+wVMWA92vjqy2tCxX0AFotaCYHhuAVkINBBrwkqw2/rEJvThAyi0dAHEgIKLGwXmSvxG3pXD2TncnGFcZWmsx/uhHcGN6T+M7xHDXP94d1jbtE0U40G9mqNn+H/TBg/OqbgqlOk1Dnbea3bENO0z7Le0OvY2PGyg8vJepDBzdc1lNBJD/JNN7OZPnh1YF//oR0G3t/l8auEKMb3Ve4kNJSZkqXC6mz96msz1Uw3V73qTcddU7gdv1lWZI4Xyv4+d14ZsIj0aFmpNnH4HC728WTuVK8EfWwsDPk9ZJy7GI3zzcEQNhbrPxQfFhBiTRUcuc6FuaI52ndpfRIqyAqAw9gjt/GM++liqMPmQrkzq3YAIfUY+z8T02xORoSK4fmcKua6XTN7GASufm7QWo7YCqCZOOrvdRYTFpzrvTQjdeXltUhBOwiZDTu9rqKwACSdjrpFiad9GYM2gDOB2kiztO1OzaUyCow8AqrnlRA//zc5NZ1+0VQfJ8r3G2axtxXLZN54LYY+ieBYHjkipI0tHRXSWP8kQ0fNm2N7RAA==
*/