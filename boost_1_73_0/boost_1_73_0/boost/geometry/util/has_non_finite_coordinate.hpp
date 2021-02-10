// Boost.Geometry

// Copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_HAS_NON_FINITE_COORDINATE_HPP
#define BOOST_GEOMETRY_UTIL_HAS_NON_FINITE_COORDINATE_HPP

#include <boost/type_traits/is_floating_point.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/has_nan_coordinate.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

namespace boost { namespace geometry
{
    
#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct is_not_finite
{
    template <typename T>
    static inline bool apply(T const& t)
    {
        return ! boost::math::isfinite(t);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

template <typename Point>
bool has_non_finite_coordinate(Point const& point)
{
    return detail::has_coordinate_with_property
        <
            Point,
            detail::is_not_finite,
            boost::is_floating_point
                <
                    typename coordinate_type<Point>::type
                >::value
        >::apply(point);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_HAS_NON_FINITE_COORDINATE_HPP

/* has_non_finite_coordinate.hpp
H9xfhpukSINvU03o/t3IvKtoyoWL9cDqhJEy03ZLblnKW6iY7sTHPKp3r4zr53jIOJ7bctePcanthmW7eeh/65r/ujU64OvluDLulXNK1kuOF6DAZSlOkcdRZq0c2AFlki4olFljCbc0VXurapat2lrGAQcweC3HqBiw5qu33CO2zSs4+d5l5+iB3HvOIzidFqjPmzcCPAQMSz1SqmdREXQnhBBkXm3H4L2tFaZFpcUoC7o4qm/YLZg0fV5r/Ra0AUgLrx9GdFFJEmRwJn1nA9arjHIbWVi0cZMSXCkevsdVen6wFlPVFtTeHO0OKjAlY5S2Mwwaj7mYfrdQ5+cBXRLpLhXLMKAIjlpW6UtbKgH72kkolv3sLWfHVfT3Xohn9QvqCrI1N93yTfDiAL9yoOAGlqCgaoaA71pidNSaxKb2jXr8ryJz+Ns+z5DaEm/cWiu47OAvqpE0CsgpXxdrUQSvnBF/8t/5BVQcjYpyHrLfHzorcktelCuWmG6XCpYte1ekpxOaoOha4Ona/CUTfFfcT3DSGwxHvJNCeNEj4LQRHA/ZaTWYq0d/VQ9q3cGnvbeGLsHo5vdDKX4riZSc/rklWoHUWNLObGwfoM5z1LDKWOVMcLvHhoE18HKBEKBUjraVZLk29dOlYSET
*/