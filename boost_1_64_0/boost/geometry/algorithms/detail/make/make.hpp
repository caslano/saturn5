// Boost.Geometry

// Copyright (c) 2019 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MAKE_MAKE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MAKE_MAKE_HPP

#include <boost/geometry/geometries/infinite_line.hpp>
#include <boost/geometry/core/access.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace make
{

template <typename Type, typename Coordinate>
inline
model::infinite_line<Type> make_infinite_line(Coordinate const& x1,
    Coordinate const& y1, Coordinate const& x2, Coordinate const& y2)
{
    model::infinite_line<Type> result;
    result.a = y1 - y2;
    result.b = x2 - x1;
    result.c = -result.a * x1 - result.b * y1;
    return result;
}

template <typename Type, typename Point>
inline
model::infinite_line<Type> make_infinite_line(Point const& a, Point const& b)
{
    return make_infinite_line<Type>(geometry::get<0>(a), geometry::get<1>(a),
        geometry::get<0>(b), geometry::get<1>(b));
}

template <typename Type, typename Segment>
inline
model::infinite_line<Type> make_infinite_line(Segment const& segment)
{
    return make_infinite_line<Type>(geometry::get<0, 0>(segment),
        geometry::get<0, 1>(segment),
        geometry::get<1, 0>(segment),
        geometry::get<1, 1>(segment));
}



}} // namespace detail::make
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MAKE_MAKE_HPP

/* make.hpp
Okm8awYj1Hur3QBbs8IwnOj0k2I6vH8MX6rzq7G+z8Z/gqWdxCB2+uDfrNFUNjCVDkfAjf5wYQpsdL/eefROxJYfXqIT92nEdhs14HdN49AypxpTe3WRd+kB/hc+4fhqajDJPq26RPs0cOopn6UVN9Ugwy72UA/OfiHPdG65TxPhiD17Ree5tzV+QX5RYAEsEMvfTivnG84/F5v/PDjANjZ+j4Phu2W62x/1lf1STXGdVvLD+8zd+Vd9l/sy7LCul9fiLaPsObwZ3+omf/gY3nXyGU61rDHsTpGL5WQ3dFRusnijdvoa7pK6HleYkLQb15YXb8LnruvLhsSUBo5Jd0reC0fL3Kl+WS5SD0iE6+l4rtpqxQzyPzG53gW4e4QP9JXn9pTDNWVDWeVdzdgIXN0GEx9qbg+HvKQGnx4g/m2Hqd0G2q9+lG0Za2HfPQV/njkGc9QhN4s1G+uykfH6BlXY6ni1I+O56zq+ond/B67y4Of89W1Y0l8/Sf33WXEijRjafZBa6WYY0Zw91cRb2GkrcTn913jkr9ZODT+fHKsnjO0yWB2Gfc2raW58sBVb/pjvbSitnt/NGJL9/VbWx33vlkNdFSNvdJ1FTXBMOFQcjk81tldS6Rw3/+EtdlRKvrOF3SV9ua7ja7EJHKmLHGRUW76cfHFtcu9SNbUGa7Fc7aKP9exH5hyDOTlhXQMxeZxnN07zt3fYLnvbwRZb44Eb35NLbuIPFZJ9DX2WquzGvTfhccfyqtPkhUn0fX4623DN58l88in5nHxARlSFDXfC8NzWdbz1yGavAj1+NdneVbEgFqMPwp5aMDv8aDyV5Ifi4fNsb9r1UWinxtuxl7ywO71+CzPb8v9lYtAC2LM16IXB1Vm4w/DIXNi2OJqTFCb7njFG+qxRxT6BcvhxYXGsuBjE/hbt5ut/qjWUpJPp4pHzG5l/v4ReMrwbmRF/V1vuDDeuzOBi9D9enbp5Ac8j8PNG1qI9bH06BaeATdEYvKeyGth5ceI7XKGRWoQedgtcOxt7eVj94qXf+cBV9Yvy+gvLxfgibM7890Zs5AEcSfwpys8GWMt8xjTMM1WV9+M0fP0j1+mlHj4yPV5q7p9Pl8//ie/KLXf2l/dXVnOdiOMugU+w+9oL9sbd4ji18u6p8Ijef+MjqUVwG/tqGjfH1ZPvPM6shpVbvd8aD/kCjsC/vX/TI/6QD32Pk+jxLqenqn3s/cMrDt5PX3TbjzQlT+SQFxRka/NwYDaR5QD9tKI3tp7zOuniaPvSGsOlNcbXXj61Coa45xRcaTedLLQ3vp6fjcby3f58XV+vDUyclOyDTIQ/XT1bkE2duIo9evyoJB0e/gNvW2ztPmfe1nh6YxytOm49TG1bbztVDaubsfUifckbyXcfme+SXfitMb7fQc4txpXEp1uxj8piygw9ou144vjaMAVvaztJ7VB9sC2/fCOb9TPuAreIm0/qsSf7/S31ZNrgW9nZ6yR7LMrDB/f6ZfVfz161GYa3Gdtya/f5puTzBXokp/nISefqU9yojz7GNV+sjO8N8XwKPKklTlbMAxNnqwmKZ5+pWaVthaPQyZhe6kFs6nQDz0qwtRzDjEl86Wp98yQxUp+3pB7rJPr6Q17dWKxPtebvi+fpDsNaXKFSLj/pezBsHPqDnC7YXxervTa3br1hcPI5qxfl2/YqvCWHGF0BvxKbsqVnAxv51pFk7Zx9sI1HYEQOudMWNlO6irhaTu9Ib6K29cnyvTqAPnc5OVBz+zaGDYRzYvDLG9RK7A/4m/pmxQ3srhCcdZ/5xtVebNsViT2T6Nl9Xje368SAPlmMEV+tfUIORc/jYGJR/r5jFG4Be4Y=
*/