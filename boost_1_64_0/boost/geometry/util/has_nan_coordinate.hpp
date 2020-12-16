// Boost.Geometry

// Copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_HAS_NAN_COORDINATE_HPP
#define BOOST_GEOMETRY_UTIL_HAS_NAN_COORDINATE_HPP

#include <cstddef>

#include <boost/type_traits/is_floating_point.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/math/special_functions/fpclassify.hpp>


namespace boost { namespace geometry
{
    
#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct isnan
{
    template <typename T>
    static inline bool apply(T const& t)
    {
        return boost::math::isnan(t);
    }
};

template
<
    typename Point,
    typename Predicate,
    bool Enable,
    std::size_t I = 0,
    std::size_t N = geometry::dimension<Point>::value
>
struct has_coordinate_with_property
{
    static bool apply(Point const& point)
    {
        return Predicate::apply(geometry::get<I>(point))
            || has_coordinate_with_property
                <
                    Point, Predicate, Enable, I+1, N
                >::apply(point);
    }
};

template <typename Point, typename Predicate, std::size_t I, std::size_t N>
struct has_coordinate_with_property<Point, Predicate, false, I, N>
{
    static inline bool apply(Point const&)
    {
        return false;
    }
};

template <typename Point, typename Predicate, std::size_t N>
struct has_coordinate_with_property<Point, Predicate, true, N, N>
{
    static bool apply(Point const& )
    {
        return false;
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

template <typename Point>
bool has_nan_coordinate(Point const& point)
{
    return detail::has_coordinate_with_property
        <
            Point,
            detail::isnan,
            boost::is_floating_point
                <
                    typename coordinate_type<Point>::type
                >::value
        >::apply(point);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_HAS_NAN_COORDINATE_HPP

/* has_nan_coordinate.hpp
B/ri+6N31Yzv74p9qbtYH8VgMBgMBoPBYISDyMj/FLbeSPL/uDhNynX7tPDlq+C55SIvHwbP2RZ+zvuNmpIPZ+8KyOcmZcRi7CvdGZmc8V7ZrkfwPPH+udxqyw0fKi88g8FgMBgMBoPBYDAaGBGS/90yF10DyP9d4EPfJBG2SciITbTBwyw1TfBaEs75BfJxxkg6J9DMLu+h4x6Vq2ADDriHOdch2umpe00BoWeYGaf57PEHyM+gN8rJKD1RJqGOmK3CHh9tsbitDo/uy+aXSVn56vQ38K4VOFHa23UvoxaXl1PK3d9B1qNp9ySq7bNoeyxt96Dtgni13Ye270+UdnDfeolTyIS6ntpRgvIgzsmgdtBIWrI83iaoNqSEbAPZ9X32d7gU+OcxJLv+FNk+m79t3hcXsY94akPzsxXKwzjftS2QJ7fVmaXLNIle3uruX3+fClcTdWCupmIcZqH0bQufCllPmree6oNYZx2n0xh2ke2nq9ADdj2wnaNOokgYDIzYcTLoVNH326mdwesfmB/GGATjgfxO6JjLKlwyMLdwNM9p0LVm0Hbt/Y7T3BPrSRrot3TwLu7f8Wc1r1qpcaV7OkQ7qa9Pk22d3VQxN4Pm2aMoj4nnWl1vs7oMwSAa6tadhsWmnmDVzvw6/FcKff41rsAnn3xBzL65ePU4a5b0PvH1z/fyukF5Tpt4zAY6DXcBjvn7xPh5tFB96XS/mv4yqr4033HBjjs3x2yTz+B66qvH6RmtpO0ZtD2oTG3PxLZ/35U3Uw1+i/puCfVdYVlA37nc+gRHbp7H23kN0nfpIfourZa+y66l7zLq6DtzkL6Lp7Ey1FwWJ/t+B2eUBfbp12WBfdp5h69PG3VN09ZJYv9Dw8e+MC/hh8t3F3XWzrvo3SvC1+82lB46XL14uGuaVkg1NL3/6L0oxlo89hfRpLsTU1bM30L8ixXvLtBEMXag4vdyGqi4z2xxLd1nPd0nhn4zBIrpPqtB24F+BpoEGoVFcrqL33jQi8UcBB0k3iGgNwleQDPU72yh+C45BVTMqVNBJ4G2AJ0l6gJ9FTQWtEj4voGWiOchSvHXU6N3Eb2j5G8FSlfirz3cqE4Sv6Og4t3VAbRCtZveLXjn0HUtaV4LfIj7i/fQctB40JVRql2HqV1/ULv+pHZVUbs03H+0aD+ofPZA3aLdoI+I9plUu1oQH8s0esfQu0fw0RblNeLjyig1Pn1BO4H2Bz1bfJOA9gK9G7Sv+N4BvQF0MuhtoPeBZolvDNDx4jsCVLR5CugU0Kmg08RvF+gc0RegL4pnFXQF6JOgm0CfAv1TvI9Bj4A+DSrejXOp/80oRd7fTurH5iipxP/5ND960/y4BPRc0BTQAco3tPBa0MtBxZwaRPPOpdFvKv3WZoi+Q7HTfa+m+95I9x1G9x2uqfFI19Q43AqaCToKdBGoDvoyaLam5tVYUPEbfjtoISoLtNsoW87SX2C7QalEgR0HD5fy9UssV759/UAnbg307yM7D/n31bT1kG9fcHsP+feZy5WPnx3Ua/8xyoP6+QVdP3heuanONYQX4xxa78frA+hb82cdSjGOe9f+KcffVSgLh0sfwVrXF0741RTSX7AbjplRDJQFKJ+jHEBJ3MM+hIz/LyIk/3vyXF4FQP3k/2ORy9f7yeVvklzeOkq1rWUU5dgrr5ZfXy79T2IpyVNptXwrx5PP+Topt3oKPGBV9/M1XyP3u3R3ps1w0/5k37csVUPfrKf+qt4xXyeSLE/bN7VT272qbZtpu9TvGzY6KvxvuhPN1yG6ldhftuKUA4ufcl1y35oNh9Z3PCM//G/kCunTT2NMY19EsQPzaBCv19Q3mRk=
*/