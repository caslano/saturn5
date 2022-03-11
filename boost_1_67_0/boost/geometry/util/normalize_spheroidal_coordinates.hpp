// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2015-2019, Oracle and/or its affiliates.

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

        BOOST_GEOMETRY_ASSERT(math::smaller(constants::min_longitude(), longitude));
        BOOST_GEOMETRY_ASSERT(! math::larger(longitude, constants::max_longitude()));
    }
};


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