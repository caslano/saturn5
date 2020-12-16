// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_MAKE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_MAKE_HPP

#include <boost/geometry/algorithms/assign.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace make
{

/*!
\brief Construct a geometry
\ingroup make
\tparam Geometry \tparam_geometry
\tparam Range \tparam_range_point
\param range \param_range_point
\return The constructed geometry, here: a linestring or a ring

\qbk{distinguish, with a range}
\qbk{
[heading Example]
[make_with_range] [make_with_range_output]

[heading See also]
\* [link geometry.reference.algorithms.assign.assign_points assign]
}
 */
template <typename Geometry, typename Range>
inline Geometry make_points(Range const& range)
{
    concepts::check<Geometry>();

    Geometry geometry;
    geometry::append(geometry, range);
    return geometry;
}

}} // namespace detail::make
#endif // DOXYGEN_NO_DETAIL

/*!
\brief Construct a geometry
\ingroup make
\details
\note It does not work with array-point types, like int[2]
\tparam Geometry \tparam_geometry
\tparam Type \tparam_numeric to specify the coordinates
\param c1 \param_x
\param c2 \param_y
\return The constructed geometry, here: a 2D point

\qbk{distinguish, 2 coordinate values}
\qbk{
[heading Example]
[make_2d_point] [make_2d_point_output]

[heading See also]
\* [link geometry.reference.algorithms.assign.assign_values_3_2_coordinate_values assign]
}
*/
template <typename Geometry, typename Type>
inline Geometry make(Type const& c1, Type const& c2)
{
    concepts::check<Geometry>();

    Geometry geometry;
    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2);
    return geometry;
}

/*!
\brief Construct a geometry
\ingroup make
\tparam Geometry \tparam_geometry
\tparam Type \tparam_numeric to specify the coordinates
\param c1 \param_x
\param c2 \param_y
\param c3 \param_z
\return The constructed geometry, here: a 3D point

\qbk{distinguish, 3 coordinate values}
\qbk{
[heading Example]
[make_3d_point] [make_3d_point_output]

[heading See also]
\* [link geometry.reference.algorithms.assign.assign_values_4_3_coordinate_values assign]
}
 */
template <typename Geometry, typename Type>
inline Geometry make(Type const& c1, Type const& c2, Type const& c3)
{
    concepts::check<Geometry>();

    Geometry geometry;
    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2, c3);
    return geometry;
}

template <typename Geometry, typename Type>
inline Geometry make(Type const& c1, Type const& c2, Type const& c3, Type const& c4)
{
    concepts::check<Geometry>();

    Geometry geometry;
    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2, c3, c4);
    return geometry;
}





/*!
\brief Construct a box with inverse infinite coordinates
\ingroup make
\details The make_inverse function initializes a 2D or 3D box with large coordinates, the
    min corner is very large, the max corner is very small. This is useful e.g. in combination
    with the expand function, to determine the bounding box of a series of geometries.
\tparam Geometry \tparam_geometry
\return The constructed geometry, here: a box

\qbk{
[heading Example]
[make_inverse] [make_inverse_output]

[heading See also]
\* [link geometry.reference.algorithms.assign.assign_inverse assign_inverse]
}
 */
template <typename Geometry>
inline Geometry make_inverse()
{
    concepts::check<Geometry>();

    Geometry geometry;
    dispatch::assign_inverse
        <
            typename tag<Geometry>::type,
            Geometry
        >::apply(geometry);
    return geometry;
}

/*!
\brief Construct a geometry with its coordinates initialized to zero
\ingroup make
\details The make_zero function initializes a 2D or 3D point or box with coordinates of zero
\tparam Geometry \tparam_geometry
\return The constructed and zero-initialized geometry
 */
template <typename Geometry>
inline Geometry make_zero()
{
    concepts::check<Geometry>();

    Geometry geometry;
    dispatch::assign_zero
        <
            typename tag<Geometry>::type,
            Geometry
        >::apply(geometry);
    return geometry;
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_MAKE_HPP

/* make.hpp
+W8JdiNjtwPMTthLE25eLli9YifrC1iDwmQ7AmsESyZs383jRwnWotjJOQpYK5NnbQqT9QysndHrVOxkvQbT5nZN+z3Td24RLBmM2n0t40pZRhmK3fQxx98TzKXYyX4JrESxm/rtCatlPWPs5ipM/u4k2AKFyb9fBbaUYSsJU/N6PVgyYa3v7H9D1hfFTp5Pg92uMNmmwe5RmPzdJrAHmVj2MPnyJGP3HJP2lxQm+1awA0oZfVC99llZzxQ7ec8X2AkmfR2EqXWwU2FyXAHT5pnHaVWYHHPA7ISpbcXB2DkVJvtrsDzGziWZkgbsJYQtwAcy7djdCpP9EvZShT3guv+4zkK1MsIuDwnV5PfRsZULprndi0NgiH/CZwWxWxJi0Qbk1r0qWKXCZg5b/3PhswoszPC5FHrU53pitxwfZH78s22CbVGY/Ptx2G9U2G/Hvxwv2A6FFfy66EHBblfYnne0qYLdw7AHFXagpvoenVm0PYRVUj2wJxW2I/UPsYI9x9i9BOYkbNyTjy0W7IRi9+9Xr35GsA6F3bp3xY8F66SM5jWYNt+cWRV26RU//qdgdjAbYZPD/2MVzKnYyXoNlkcZLT8wF8NKGOZmWCnDyhhWzrAKypQ6Uamw9OappwWrYuyqzRjabQ2YqBNXgb2876LvCPagtAOjdQJsj2I3YHbBTYK1MnZtCpNjB1i7wuTYAXaCsetQYlkxaXypYMmXdLV7O+S5U4JlEKbq5YKJMWcF2C1Vk9aKvqeE2K1E33Pqb4nThZ0bTNTdVbBzji9/U7AyMCtho2+o/Zpg5ZTROgFWofj82q0vtAhWRe2UfqmasNVquRO2hrZp7LWEVaHfpf1gHcN2EXYNTR/2epKGdfjgeNwTnwrWCJZM2LGa5scEawGzE5Z68ORCwY4wPj9mfIaVm/t0gIk0bMAHsmyxOcHEmLMRaff8k+1vZaR2+BD6C+DNZDwKBfX8q/DalTXbJAGD3Xo86z5dzSl43z7twhLBavBcadilw8/2xW/fpDP8g7wrVmcZeBuxyfKQYG12TYy3zcOpHvYThOUrrBMs2WAT8DztnCuX6WzCAnuChnh0vXO11et8doUbGwmbpFUX+9iCNWWJ+Nxgk7V1xG7xhnqwZoNdoK1ZMGLzR2E6G+mqTdI0uxHLbG3dSp/dsmvrwdrDdLsF2oa16d97cKOIZctAX34uRCznPHXpX0T6asCcht0GvN86Z+vzgq3Pgp5htwXPH/3xoiWC1YGJNOzA857ftH4k9No9LFpnD2rrVrfMmL5SxOkagTIy0rAHcdI8qwKrM3w+BrvKNaUOoecsQHsxWGOXMrq2qh2sLERn+7RFV4fNXfem4VNrHIUXFp09pW3Uth6MsXkZXncgkHbD7hmtSrvtFve1OluiLR3ny7PXtHXasiufa9LZWq0KzGnYva0t0JYXhv7KKD/tdLHP7h1tmXZoxoo2nVWhk8J80UjDUbCd9y/QRJwVYG7D55+1Ndo792a/oLOlmnOCr618jGPP+8l954g6WA9WFqqzT1EHZ7l/9h+RZ/UTNa3csPtcqdf2c311vlNhTrAOw86Tdx+si3Lr7IFQN16123QWYnkgdPX4uxcL1jTL5zMMzOdzT2gLYVGWPV1YG5jDYPEK6yR2iQqzlvlYksIchCUrLI+wlC7ssdASwjIsj3VhpWCiL8gEe8/57FHBKsDqjXaUBba/dPU4wTrm+drt4C4+Hw+1z0faw3U7l+Xx0NdGjX9UZ6M11wJf+U2yrNNevW/7LFEH6wk733Kltn3fa0cEs1+OMrTqrAx2B965I0HE0roc9cWwu1qJxYWzryqDVSOWoi+m/E5n+DvuYE4jDdsse0M=
*/