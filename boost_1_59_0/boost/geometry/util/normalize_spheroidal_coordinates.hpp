// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2015-2022, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Adeel Ahmad, as part of Google Summer of Code 2018 program

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_UTIL_NORMALIZE_SPHEROIDAL_COORDINATES_HPP
#define BOOST_GEOMETRY_UTIL_NORMALIZE_SPHEROIDAL_COORDINATES_HPP

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{

namespace math 
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// CoordinateType, radian, true
template <typename CoordinateType, typename Units, bool IsEquatorial = true>
struct constants_on_spheroid
{
    static inline CoordinateType period()
    {
        return math::two_pi<CoordinateType>();
    }

    static inline CoordinateType half_period()
    {
        return math::pi<CoordinateType>();
    }

    static inline CoordinateType quarter_period()
    {
        static CoordinateType const
            pi_half = math::pi<CoordinateType>() / CoordinateType(2);
        return pi_half;
    }

    static inline CoordinateType min_longitude()
    {
        static CoordinateType const minus_pi = -math::pi<CoordinateType>();
        return minus_pi;
    }

    static inline CoordinateType max_longitude()
    {
        return math::pi<CoordinateType>();
    }

    static inline CoordinateType min_latitude()
    {
        static CoordinateType const minus_half_pi
            = -math::half_pi<CoordinateType>();
        return minus_half_pi;
    }

    static inline CoordinateType max_latitude()
    {
        return math::half_pi<CoordinateType>();
    }
};

template <typename CoordinateType>
struct constants_on_spheroid<CoordinateType, radian, false>
    : constants_on_spheroid<CoordinateType, radian, true>
{
    static inline CoordinateType min_latitude()
    {
        return CoordinateType(0);
    }

    static inline CoordinateType max_latitude()
    {
        return math::pi<CoordinateType>();
    }
};

template <typename CoordinateType>
struct constants_on_spheroid<CoordinateType, degree, true>
{
    static inline CoordinateType period()
    {
        return CoordinateType(360.0);
    }

    static inline CoordinateType half_period()
    {
        return CoordinateType(180.0);
    }

    static inline CoordinateType quarter_period()
    {
        return CoordinateType(90.0);
    }

    static inline CoordinateType min_longitude()
    {
        return CoordinateType(-180.0);
    }

    static inline CoordinateType max_longitude()
    {
        return CoordinateType(180.0);
    }

    static inline CoordinateType min_latitude()
    {
        return CoordinateType(-90.0);
    }

    static inline CoordinateType max_latitude()
    {
        return CoordinateType(90.0);
    }
};

template <typename CoordinateType>
struct constants_on_spheroid<CoordinateType, degree, false>
    : constants_on_spheroid<CoordinateType, degree, true>
{
    static inline CoordinateType min_latitude()
    {
        return CoordinateType(0);
    }

    static inline CoordinateType max_latitude()
    {
        return CoordinateType(180.0);
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template <typename Units, typename CoordinateType>
inline CoordinateType latitude_convert_ep(CoordinateType const& lat)
{
    typedef math::detail::constants_on_spheroid
            <
                CoordinateType,
                Units
            > constants;

    return constants::quarter_period() - lat;
}


template <typename Units, bool IsEquatorial, typename T>
static bool is_latitude_pole(T const& lat)
{
    typedef math::detail::constants_on_spheroid
        <
            T,
            Units
        > constants;

    return math::equals(math::abs(IsEquatorial
                                    ? lat
                                    : math::latitude_convert_ep<Units>(lat)),
                        constants::quarter_period());

}


template <typename Units, typename T>
static bool is_longitude_antimeridian(T const& lon)
{
    typedef math::detail::constants_on_spheroid
        <
            T,
            Units
        > constants;

    return math::equals(math::abs(lon), constants::half_period());

}


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename Units, bool IsEquatorial>
struct latitude_convert_if_polar
{
    template <typename T>
    static inline void apply(T & /*lat*/) {}
};

template <typename Units>
struct latitude_convert_if_polar<Units, false>
{
    template <typename T>
    static inline void apply(T & lat)
    {
        lat = latitude_convert_ep<Units>(lat);
    }
};


template <typename Units, typename CoordinateType, bool IsEquatorial = true>
class normalize_spheroidal_coordinates
{
    typedef constants_on_spheroid<CoordinateType, Units> constants;

protected:
    static inline CoordinateType normalize_up(CoordinateType const& value)
    {
        return
            math::mod(value + constants::half_period(), constants::period())
            - constants::half_period();            
    }

    static inline CoordinateType normalize_down(CoordinateType const& value)
    {
        return
            math::mod(value - constants::half_period(), constants::period())
            + constants::half_period();            
    }

public:
    static inline void apply(CoordinateType& longitude)
    {
        // normalize longitude
        if (math::equals(math::abs(longitude), constants::half_period()))
        {
            longitude = constants::half_period();
        }
        else if (longitude > constants::half_period())
        {
            longitude = normalize_up(longitude);
            if (math::equals(longitude, -constants::half_period()))
            {
                longitude = constants::half_period();
            }
        }
        else if (longitude < -constants::half_period())
        {
            longitude = normalize_down(longitude);
        }
    }

    static inline void apply(CoordinateType& longitude,
                             CoordinateType& latitude,
                             bool normalize_poles = true)
    {
        latitude_convert_if_polar<Units, IsEquatorial>::apply(latitude);

#ifdef BOOST_GEOMETRY_NORMALIZE_LATITUDE
        // normalize latitude
        if (math::larger(latitude, constants::half_period()))
        {
            latitude = normalize_up(latitude);
        }
        else if (math::smaller(latitude, -constants::half_period()))
        {
            latitude = normalize_down(latitude);
        }

        // fix latitude range
        if (latitude < constants::min_latitude())
        {
            latitude = -constants::half_period() - latitude;
            longitude -= constants::half_period();
        }
        else if (latitude > constants::max_latitude())
        {
            latitude = constants::half_period() - latitude;
            longitude -= constants::half_period();
        }
#endif // BOOST_GEOMETRY_NORMALIZE_LATITUDE

        // normalize longitude
        apply(longitude);

        // finally normalize poles
        if (normalize_poles)
        {
            if (math::equals(math::abs(latitude), constants::max_latitude()))
            {
                // for the north and south pole we set the longitude to 0
                // (works for both radians and degrees)
                longitude = CoordinateType(0);
            }
        }

        latitude_convert_if_polar<Units, IsEquatorial>::apply(latitude);

#ifdef BOOST_GEOMETRY_NORMALIZE_LATITUDE
        BOOST_GEOMETRY_ASSERT(! math::larger(constants::min_latitude(), latitude));
        BOOST_GEOMETRY_ASSERT(! math::larger(latitude, constants::max_latitude()));
#endif // BOOST_GEOMETRY_NORMALIZE_LATITUDE

        BOOST_GEOMETRY_ASSERT(! math::larger_or_equals(constants::min_longitude(), longitude));
        BOOST_GEOMETRY_ASSERT(! math::larger(longitude, constants::max_longitude()));
    }
};


template <typename Units, typename CoordinateType>
inline void normalize_angle_loop(CoordinateType& angle)
{
    typedef constants_on_spheroid<CoordinateType, Units> constants;
    CoordinateType const pi = constants::half_period();
    CoordinateType const two_pi = constants::period();
    while (angle > pi)
        angle -= two_pi;
    while (angle <= -pi)
        angle += two_pi;
}

template <typename Units, typename CoordinateType>
inline void normalize_angle_cond(CoordinateType& angle)
{
    typedef constants_on_spheroid<CoordinateType, Units> constants;
    CoordinateType const pi = constants::half_period();
    CoordinateType const two_pi = constants::period();
    if (angle > pi)
        angle -= two_pi;
    else if (angle <= -pi)
        angle += two_pi;
}


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
\brief Short utility to normalize the coordinates on a spheroid
\tparam Units The units of the coordindate system in the spheroid
\tparam CoordinateType The type of the coordinates
\param longitude Longitude
\param latitude Latitude
\ingroup utility
*/
template <typename Units, typename CoordinateType>
inline void normalize_spheroidal_coordinates(CoordinateType& longitude,
                                             CoordinateType& latitude)
{
    detail::normalize_spheroidal_coordinates
        <
            Units, CoordinateType
        >::apply(longitude, latitude);
}

template <typename Units, bool IsEquatorial, typename CoordinateType>
inline void normalize_spheroidal_coordinates(CoordinateType& longitude,
                                             CoordinateType& latitude)
{
    detail::normalize_spheroidal_coordinates
        <
            Units, CoordinateType, IsEquatorial
        >::apply(longitude, latitude);
}

/*!
\brief Short utility to normalize the longitude on a spheroid.
       Note that in general both coordinates should be normalized at once.
       This utility is suitable e.g. for normalization of the difference of longitudes.
\tparam Units The units of the coordindate system in the spheroid
\tparam CoordinateType The type of the coordinates
\param longitude Longitude
\ingroup utility
*/
template <typename Units, typename CoordinateType>
inline void normalize_longitude(CoordinateType& longitude)
{
    detail::normalize_spheroidal_coordinates
        <
            Units, CoordinateType
        >::apply(longitude);
}

/*!
\brief Short utility to normalize the azimuth on a spheroid
       in the range (-180, 180].
\tparam Units The units of the coordindate system in the spheroid
\tparam CoordinateType The type of the coordinates
\param angle Angle
\ingroup utility
*/
template <typename Units, typename CoordinateType>
inline void normalize_azimuth(CoordinateType& angle)
{
    normalize_longitude<Units, CoordinateType>(angle);
}

/*!
\brief Normalize the given values.
\tparam ValueType The type of the values
\param x Value x
\param y Value y
TODO: adl1995 - Merge this function with
formulas/vertex_longitude.hpp
*/
template<typename ValueType>
inline void normalize_unit_vector(ValueType& x, ValueType& y)
{
    ValueType h = boost::math::hypot(x, y);

    BOOST_GEOMETRY_ASSERT(h > 0);

    x /= h; y /= h;
}

/*!
\brief Short utility to calculate difference between two longitudes
       normalized in range (-180, 180].
\tparam Units The units of the coordindate system in the spheroid
\tparam CoordinateType The type of the coordinates
\param longitude1 Longitude 1
\param longitude2 Longitude 2
\ingroup utility
*/
template <typename Units, typename CoordinateType>
inline CoordinateType longitude_distance_signed(CoordinateType const& longitude1,
                                                CoordinateType const& longitude2)
{
    CoordinateType diff = longitude2 - longitude1;
    math::normalize_longitude<Units, CoordinateType>(diff);
    return diff;
}


/*!
\brief Short utility to calculate difference between two longitudes
       normalized in range [0, 360).
\tparam Units The units of the coordindate system in the spheroid
\tparam CoordinateType The type of the coordinates
\param longitude1 Longitude 1
\param longitude2 Longitude 2
\ingroup utility
*/
template <typename Units, typename CoordinateType>
inline CoordinateType longitude_distance_unsigned(CoordinateType const& longitude1,
                                                  CoordinateType const& longitude2)
{
    typedef math::detail::constants_on_spheroid
        <
            CoordinateType, Units
        > constants;

    CoordinateType const c0 = 0;
    CoordinateType diff = longitude_distance_signed<Units>(longitude1, longitude2);
    if (diff < c0) // (-180, 180] -> [0, 360)
    {
        diff += constants::period();
    }
    return diff;
}

/*!
\brief The abs difference between longitudes in range [0, 180].
\tparam Units The units of the coordindate system in the spheroid
\tparam CoordinateType The type of the coordinates
\param longitude1 Longitude 1
\param longitude2 Longitude 2
\ingroup utility
*/
template <typename Units, typename CoordinateType>
inline CoordinateType longitude_difference(CoordinateType const& longitude1,
                                           CoordinateType const& longitude2)
{
    return math::abs(math::longitude_distance_signed<Units>(longitude1, longitude2));
}

template <typename Units, typename CoordinateType>
inline CoordinateType longitude_interval_distance_signed(CoordinateType const& longitude_a1,
                                                         CoordinateType const& longitude_a2,
                                                         CoordinateType const& longitude_b)
{
    CoordinateType const c0 = 0;
    CoordinateType dist_a12 = longitude_distance_signed<Units>(longitude_a1, longitude_a2);
    CoordinateType dist_a1b = longitude_distance_signed<Units>(longitude_a1, longitude_b);
    if (dist_a12 < c0)
    {
        dist_a12 = -dist_a12;
        dist_a1b = -dist_a1b;
    }
    
    return dist_a1b < c0 ? dist_a1b
         : dist_a1b > dist_a12 ? dist_a1b - dist_a12
         : c0;
}


} // namespace math


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_NORMALIZE_SPHEROIDAL_COORDINATES_HPP

/* normalize_spheroidal_coordinates.hpp
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
*/