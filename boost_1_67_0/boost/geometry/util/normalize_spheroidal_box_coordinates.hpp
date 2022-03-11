// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2017, Oracle and/or its affiliates.

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
        return ! math::smaller(math::abs(longitude1 - longitude2),
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
        BOOST_GEOMETRY_ASSERT
            (! math::larger(longitude2 - longitude1, constants::period()));
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