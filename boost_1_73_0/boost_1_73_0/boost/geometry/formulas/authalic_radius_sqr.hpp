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
7K3hH9EyFN0U35H274CbgeqVzXFrSAE+g5k16uaTgwlz5VjDFDrnPJ4TFbpjfbcFqPbRuybfhTQlJgDdYYWjok21sMMSaen0ZoQ31q6tN+6MgehMkw/t0iHVKehUK+IFOgnaF+n0AzhymXEWpsUR8yLjhfQWDiW/haLSMVEiiPPQ7mCw9qnhVjVuSQuyUQDCd6mGTOhqaV5VDUVdwJDHTVbQ3rnzugtNtQ4fXU+K/ZhpwHAWFvi6HmuastNkpUalEFuuRedL3RnJ/PcLNNcQZ9fh3Y/W4ZYMDJ8X/EB1/KkMVuef8pJgOEAvDbpY5YHigklg0Zhp4IDop+3D05nHTpcvmd4apUZ5MlZbVaxSlViy6Gig6wvLIO8DagZbYjYJjg93FCQ4np9Ib8iHRWGuuAtHO4D8YssoT8ShLY9u6P6hwCRvxw5YvbgXwD/VOwL8U7EvYLhI4Fl/5KZWf5ymQf5JttQM4s9sQlebfAVV1PiZeKOUnG90wwJf8xOxo1Mc5WccjJH1Zjwc2TMIMGZ0dgJPWAZdvIKNYkz0JZWIgYVQYQCWjb+S4Tf9yI4/+2rko/WOOv4Qaw4U84Xy/xvidMr5n5KKTY/bqN+DFKOJNokZ2A1tt8SsT7YuGuc/9OiIv8+ontBfucdYE57z
*/