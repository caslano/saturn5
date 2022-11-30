// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2022, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_UTIL_NORMALIZE_SPHEROIDAL_BOX_COORDINATES_HPP
#define BOOST_GEOMETRY_UTIL_NORMALIZE_SPHEROIDAL_BOX_COORDINATES_HPP

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>


namespace boost { namespace geometry
{

namespace math 
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename Units, typename CoordinateType, bool IsEquatorial = true>
class normalize_spheroidal_box_coordinates
{
private:
    typedef normalize_spheroidal_coordinates<Units, CoordinateType> normalize;
    typedef constants_on_spheroid<CoordinateType, Units> constants;

    static inline bool is_band(CoordinateType const& longitude1,
                               CoordinateType const& longitude2)
    {
        return math::larger_or_equals(math::abs(longitude1 - longitude2),
                                      constants::period());
    }

public:
    static inline void apply(CoordinateType& longitude1,
                             CoordinateType& latitude1,
                             CoordinateType& longitude2,
                             CoordinateType& latitude2,
                             bool band)
    {
        normalize::apply(longitude1, latitude1, false);
        normalize::apply(longitude2, latitude2, false);

        latitude_convert_if_polar<Units, IsEquatorial>::apply(latitude1);
        latitude_convert_if_polar<Units, IsEquatorial>::apply(latitude2);

        if (math::equals(latitude1, constants::min_latitude())
            && math::equals(latitude2, constants::min_latitude()))
        {
            // box degenerates to the south pole
            longitude1 = longitude2 = CoordinateType(0);
        }
        else if (math::equals(latitude1, constants::max_latitude())
                 && math::equals(latitude2, constants::max_latitude()))
        {
            // box degenerates to the north pole
            longitude1 = longitude2 = CoordinateType(0);
        }
        else if (band)
        {
            // the box is a band between two small circles (parallel
            // to the equator) on the spheroid
            longitude1 = constants::min_longitude();
            longitude2 = constants::max_longitude();
        }
        else if (longitude1 > longitude2)
        {
            // the box crosses the antimeridian, so we need to adjust
            // the longitudes
            longitude2 += constants::period();
        }

        latitude_convert_if_polar<Units, IsEquatorial>::apply(latitude1);
        latitude_convert_if_polar<Units, IsEquatorial>::apply(latitude2);

#ifdef BOOST_GEOMETRY_NORMALIZE_LATITUDE
        BOOST_GEOMETRY_ASSERT(! math::larger(latitude1, latitude2));
        BOOST_GEOMETRY_ASSERT(! math::smaller(latitude1, constants::min_latitude()));
        BOOST_GEOMETRY_ASSERT(! math::larger(latitude2, constants::max_latitude()));
#endif

        BOOST_GEOMETRY_ASSERT(! math::larger(longitude1, longitude2));
        BOOST_GEOMETRY_ASSERT(! math::smaller(longitude1, constants::min_longitude()));
        BOOST_GEOMETRY_ASSERT(! math::larger(longitude2 - longitude1, constants::period()));
    }

    static inline void apply(CoordinateType& longitude1,
                             CoordinateType& latitude1,
                             CoordinateType& longitude2,
                             CoordinateType& latitude2)
    {
        bool const band = is_band(longitude1, longitude2);

        apply(longitude1, latitude1, longitude2, latitude2, band);
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
\brief Short utility to normalize the coordinates of a box on a spheroid
\tparam Units The units of the coordindate system in the spheroid
\tparam CoordinateType The type of the coordinates
\param longitude1 Minimum longitude of the box
\param latitude1 Minimum latitude of the box
\param longitude2 Maximum longitude of the box
\param latitude2 Maximum latitude of the box
\ingroup utility
*/
template <typename Units, typename CoordinateType>
inline void normalize_spheroidal_box_coordinates(CoordinateType& longitude1,
                                                 CoordinateType& latitude1,
                                                 CoordinateType& longitude2,
                                                 CoordinateType& latitude2)
{
    detail::normalize_spheroidal_box_coordinates
        <
            Units, CoordinateType
        >::apply(longitude1, latitude1, longitude2, latitude2);
}

template <typename Units, bool IsEquatorial, typename CoordinateType>
inline void normalize_spheroidal_box_coordinates(CoordinateType& longitude1,
                                                 CoordinateType& latitude1,
                                                 CoordinateType& longitude2,
                                                 CoordinateType& latitude2)
{
    detail::normalize_spheroidal_box_coordinates
        <
            Units, CoordinateType, IsEquatorial
        >::apply(longitude1, latitude1, longitude2, latitude2);
}

/*!
\brief Short utility to normalize the coordinates of a box on a spheroid
\tparam Units The units of the coordindate system in the spheroid
\tparam CoordinateType The type of the coordinates
\param longitude1 Minimum longitude of the box
\param latitude1 Minimum latitude of the box
\param longitude2 Maximum longitude of the box
\param latitude2 Maximum latitude of the box
\param band Indicates whether the box should be treated as a band or
       not and avoid the computation done in the other version of the function
\ingroup utility
*/
template <typename Units, typename CoordinateType>
inline void normalize_spheroidal_box_coordinates(CoordinateType& longitude1,
                                                 CoordinateType& latitude1,
                                                 CoordinateType& longitude2,
                                                 CoordinateType& latitude2,
                                                 bool band)
{
    detail::normalize_spheroidal_box_coordinates
        <
            Units, CoordinateType
        >::apply(longitude1, latitude1, longitude2, latitude2, band);
}

template <typename Units, bool IsEquatorial, typename CoordinateType>
inline void normalize_spheroidal_box_coordinates(CoordinateType& longitude1,
                                                 CoordinateType& latitude1,
                                                 CoordinateType& longitude2,
                                                 CoordinateType& latitude2,
                                                 bool band)
{
    detail::normalize_spheroidal_box_coordinates
        <
            Units, CoordinateType, IsEquatorial
        >::apply(longitude1, latitude1, longitude2, latitude2, band);
}


} // namespace math


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_NORMALIZE_SPHEROIDAL_BOX_COORDINATES_HPP

/* normalize_spheroidal_box_coordinates.hpp
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
*/