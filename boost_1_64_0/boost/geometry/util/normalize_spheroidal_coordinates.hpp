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
I25YkOdxFdAPDDE+XJTxwmYwXtgsxmE7DngK8PhYXCy+K/AdIjcuLhbayvHGZ2vg8ATjbQ779Rpeh+ZS/xsZJ+tmXmdvAw4B3m44xjHr3TW+Xsb/6gJ8HSi6vmlY4/Zd7kt7j/HxPmCcuqZYvSA+652g1EvieZsG7At0AQcAOwILgRsCi2Tssp+7Oa4781hvcYLrzmasty/r7cd6s9Isfd0cbwM43rbi+b214/7OZ0pjFH877xc9WX8v1pcBXITMczu6jEVIq5DcG7gUv8QS+Y1k+x8uXJ5uxve6BLyFSBLnaxVQYn116eQyY33lM95XNn5PQHL6K/o6uVrd21ePPOK3eAVQfBe7IC5XnWOP33zw42OAnYaUcL8f/RhvAi5BOacf40Akxv1qsf+vCXkl5tebn7Ue9+s75GXsL8yHulr4OGaDZ36TB1iPtAjpO6ShG7qMQqSjkS5BWoj0HVL2Ri5jCtJpSA8iLUPK3Nhl7IQURJqL1ITUpQvqRSpEqkTSpOnfTu0R/78WmcyN/6b3//r5/sv693Z9DM6dmrFSTbLPvnSuETS4YnNoFO7B0ofHq86kck23jfPS9UlkzUkiq+Xqx7rJW5VE3rzW5fn8f0JeHdfsO3EcbIA0UeZwk8pTZ8mMNsjjuiRj/nukoipM1ytr4p1difVY0kY9YqsAKdKn3tWyH87qhXtUYn0w8VduT/1x/aWqJuiPtsk+1lwS/RLMuSH3xdN3DL7RbdiPkZ4vn33F2SNjcxAc49Qr/lkDagv2Aoq+vZ3f8FtLuS1ZbgDLbeUoN28t5Qax3DYsl+0o18hynRKU68N34UygGc/f+e69lnL9WK4/y2U5yjWtRc9tqedQ6jmMz7jzN8F9Hql3V5eRj3Q00m1In3XV93VNmjRp0qRJkyZN/11qj/3/9P/HS2lkejRUs977ANrLr35+hhH7DlGU797daJOuSIPFR2W1w0/c5y+rnTYNHpyVodD01t/t+K4JX3CnT5/qdzGbrxvnpVlrsKcBh8h8him3s7xr0nGe34GDzFUdk8mkD/MGqKO3yBQvLrzbgbdbzA9lpjfS3JAa0ao6Sj9D8/2vpW9UFn0Wt1X8IDwoF55l+wEV00dKZIIfCnpqys33SvoW+eN8EOlrH7Hrrwe64vKEsYMhzO9ymd+zyXJ+i4w+a7DXiphcf12UpWyfrjpZX4KNpf1df2r2J6mJtdUfEUerQKQS5qgIe6v8ZnvqRJ8N5Hilt9oXxDGfN+o1+870m3yH8/5nQ2f5/Qt/N/B3AWVdwN+38zfmEczfy/m7nse/4+9AP9V3Kpvf7NuHa7z5SMNkfPzs9F0Sx6xIJXYMzIQfPwA+f5zrmtMGf8V+pl3pd2V6h1o63fkz15CyVP/Jszoknh8xfknivwitwtHWzxenjDyO8Rt4Pl5j+wKrMiKeKm81xipm3Gpq2uKXRP+jpD702TEf+ho/D5m2yLDkGiNwzOkH+SD1zKCePei72qToGfHLjJU1knwtvInb4lsqOqz4xR4z6jxeKf3ywxwjVUgjzQ/LNOvQFvlt8YWyfIljZ2/MbzQvK9G5u36+UqO2FP7iy+6YdEuPws6/P/P1Poc1XlWofaX+6b5SvGca3RKsic7gPN5RQHMtnfN4Swze83gvzKVf/kKWO45ryycY1lrticCt+Y214fStGc+1632At9IH6A7gDOA8rq3fS58kpPqX+O2rj+jD8CPwKX676mngJsBngP2BzwJ3Bi4GHgh8EegBvgSsBr4q9fObV6cBX3N8E4rXamOfBL4pGfQh6MN2ZbJdfYH5nO+07Ari+e9KYNfdOM85nvOcExy+Ft1Z7gajpa+Fm/2xJbAH54E34zw=
*/