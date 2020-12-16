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
2gcuF+PpjFvSij2zY/aMVqKDKgJltBnGwdFoUy7k7yTng8hjGXesTGhmNe5KLBUbD3tR97nUfRh1z6bupd84dI95w3krcH1xRpItb8v1zSmvN/fz96e8TMqbk1Bemb8iFPYrAtsobw/Kq6e8XMrblvKWJJQn/0crwxhCDKiyTrJWdm5xbYQs4LetyPL511lWFw7iw5D6IB2EtHEW2plQlr+u3G+eOhgGQXRh69fHVMV26MsYFpebfIdOPHdLY3U162jeX3m8Eni0etyMH4zjpn/hTKu9qF+1Tx3tk8O+GMzYxPMS2qe2en3G9GcbJY6DvKoNssL4Fw9lbZK3C+VVbmwdKEDqzP3Cm8g4+y5JvGf8bEub7Gv3AtPefGaUiM1xY29oF8OkLmnWtbRjmiW/Jpn8UHXzEye/7VzZih71ifTgNS+I9mdDh+Pw+wtLJu+Z9jOU9Yzmgw7mHcxxHyxiG0o3MUw6k/eBU5C6og2N3yttQBycUPVMdBIflj3l1i3CuifSplNaiXGz+w9KXKFY/JZDeprXdDwO+a3+oX9tt6xmfuxGZt8LEj2z0C65sMlUtEsG8AdmO/ic43yW8ajycmPPJnwssW+tDpsdwGeHKV0Nk3ZmvJzRhkXzduzUdpsNtKPnGK3GNBLbfeKMRUXeQ8283Hh7FiWxZ1Er9ixS7Kne399ku4fzfBuC1EPG+w/OsRL2B3E1VO/vrZ9z9LVOFEMqdr5Huxkm7YrUBWksUq8s2P2HpHHWwWhdNvt/rfGtxsSOV4RDVeYrpugW8zlfQ91O4Hl0DNKm0M340dSNp37rzzn2/aNbpimrtprPyH2VdyNeSMxHbL4fUI9FfForph6TkPqIjSw9lHfktnzD3b7/ZWa11MedUB/rHDSgx0KkzWVd3pLN2GdsW6wMq+RYc9o0rwfj4LEtOWyLezXbIhWsRxvWxw9/kemHX9bhkV1u/eXyUSNKVj+W/nzD1dpv4J/qN2DFA+H8Cuc1xqSp8UC+TrPitXwDHA1cDWQ5zn+gfIJya1juV6DU60pvLtfEcpslKLec5T4HZgJXUJ7b4DwCn6U6p6lxU45kvjrJy3xPU14XpCDz7cx4Q7sAMxn3Z4TZBkvPicD9GHenBrgn4wMVAB8ATgI+CpwMfAy4N/BxYDHjpDQYfF8GnkH53ZBOovx+jH/Tn3F6tgBuyvhHWYx/NJT7G6RsNnBPxj/ah/GPDgMOZVyb4dQzF3gc4x+dyPhHJ1v3Ydqd77J8x70kzu4rJ1vf+/8CKPp9CZRylQbfVfkOm8vytqvFmfxOwlnATYDnsl3nA7cAzmZcoYuA+zO+zEGMK3MI8ArG6bmSepYafL/ke2cur3MllFeXZsmblWbJOwrYE3gMsDfwOGB/4PHALcXuwEHAU4HZwNOA3H/C90r0RYL9J9WUE2L9RwAzgFGOy1rWM8Xg+yLrQFLiZ93Neu4FdgfeTz0fArqBjwC3Bs4HDgY+BtwW2OjQk++IxqYJ9HyS9T/F8+ZpYFfgM5S3iPUUG3z/43thblw8ocOQrw/QA9wGOA04mnGEduTvScDD06z+m+6ol+9NRk6Ces+kfmexv84BbgZsAG4u4wQ4EDib7b+Y9Y5BWhXX7g7muLfoMtZ7O3Bj4B1s750sX2PwnQdYwPKSz8fyD/H1/2HGoZoPzGDcqM0ZL2obxonalnGitgc+C9yF8aJ2Z5woaeuLsThdfNfhO1BuXJyubOi3EXAwUNq1LbCf2A5ojh/gWOAo4GTgaOChwDFA0X1HYBS4M/Ao4DjgMcCJwHOAewKfAuYD1wAnpVlxyQqBHYGTaZ/TDL7P8D0nl3OnR1PPKbxOHQTsBTyY53M5r0t+YJ4=
*/