// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014, 2016, 2017.
// Modifications copyright (c) 2014-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_AZIMUTH_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_AZIMUTH_HPP


#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/formulas/spherical.hpp>
#include <boost/geometry/formulas/vincenty_inverse.hpp>

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{

// An azimuth is an angle between a vector/segment from origin to a point of
// interest and a reference vector. Typically north-based azimuth is used.
// North direction is used as a reference, angle is measured clockwise
// (North - 0deg, East - 90deg). For consistency in 2d cartesian CS
// the reference vector is Y axis, angle is measured clockwise.
// http://en.wikipedia.org/wiki/Azimuth

#ifndef DOXYGEN_NO_DISPATCH
namespace detail_dispatch
{

template <typename ReturnType, typename Tag>
struct azimuth
    : not_implemented<Tag>
{};

template <typename ReturnType>
struct azimuth<ReturnType, geographic_tag>
{
    template <typename P1, typename P2, typename Spheroid>
    static inline ReturnType apply(P1 const& p1, P2 const& p2, Spheroid const& spheroid)
    {
        return geometry::formula::vincenty_inverse<ReturnType, false, true>().apply
                    ( get_as_radian<0>(p1), get_as_radian<1>(p1),
                      get_as_radian<0>(p2), get_as_radian<1>(p2),
                      spheroid ).azimuth;
    }

    template <typename P1, typename P2>
    static inline ReturnType apply(P1 const& p1, P2 const& p2)
    {
        return apply(p1, p2, srs::spheroid<ReturnType>());
    }
};

template <typename ReturnType>
struct azimuth<ReturnType, spherical_equatorial_tag>
{
    template <typename P1, typename P2, typename Sphere>
    static inline ReturnType apply(P1 const& p1, P2 const& p2, Sphere const& /*unused*/)
    {
        return geometry::formula::spherical_azimuth<ReturnType, false>
                    ( get_as_radian<0>(p1), get_as_radian<1>(p1),
                      get_as_radian<0>(p2), get_as_radian<1>(p2)).azimuth;
    }

    template <typename P1, typename P2>
    static inline ReturnType apply(P1 const& p1, P2 const& p2)
    {
        return apply(p1, p2, 0); // dummy model
    }
};

template <typename ReturnType>
struct azimuth<ReturnType, spherical_polar_tag>
    : azimuth<ReturnType, spherical_equatorial_tag>
{};

template <typename ReturnType>
struct azimuth<ReturnType, cartesian_tag>
{
    template <typename P1, typename P2, typename Plane>
    static inline ReturnType apply(P1 const& p1, P2 const& p2, Plane const& /*unused*/)
    {
        ReturnType x = get<0>(p2) - get<0>(p1);
        ReturnType y = get<1>(p2) - get<1>(p1);

        // NOTE: azimuth 0 is at Y axis, increasing right
        // as in spherical/geographic where 0 is at North axis
        return atan2(x, y);
    }

    template <typename P1, typename P2>
    static inline ReturnType apply(P1 const& p1, P2 const& p2)
    {
        return apply(p1, p2, 0); // dummy model
    }
};

} // detail_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

/// Calculate azimuth between two points.
/// The result is in radians.
template <typename ReturnType, typename Point1, typename Point2>
inline ReturnType azimuth(Point1 const& p1, Point2 const& p2)
{
    return detail_dispatch::azimuth
            <
                ReturnType,
                typename geometry::cs_tag<Point1>::type
            >::apply(p1, p2);
}

/// Calculate azimuth between two points.
/// The result is in radians.
template <typename ReturnType, typename Point1, typename Point2, typename Model>
inline ReturnType azimuth(Point1 const& p1, Point2 const& p2, Model const& model)
{
    return detail_dispatch::azimuth
            <
                ReturnType,
                typename geometry::cs_tag<Point1>::type
            >::apply(p1, p2, model);
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_AZIMUTH_HPP

/* azimuth.hpp
B9r34YtPd+8jOxym3Eg/INtM+mv9wLdhR98JbJHmkqLuTMWEJ+S/0fo682A62kH4vO9Kn/cuxxDTRV24WdWF71XRp+rCLcjDrcDdN5Ab/rk7WLOIeFvwNilzEWtPkW3sDvp3ez5I1V28dSmXUD17bsbqOpEKMfKCO8h/IOXfwbXZJUX0u7vWtjs/MBpseQR9zeh3/O5G+fyI2wqMUaPljh7xixGrbttg05zevUjvviqxB0/UgUsjzo79BDQ/Bc0bysdlu9UZLAvDnCP2alIZcf3OmTGSo4ufArrppa6OZ8V7TPdU2fNW8xLA+ba9Fzsxz0+rg+LnUjiD8AUUpjNWjH8DhRdT/EaE76dws7eR4x+gcDvFpwX9Gi/N8UYf64I5T+szdzPrbqJsBotc86gV9fYhVW8frqJP1dtHoPNHC/Vdd3Acafj9oir8dtovbV76ya+mkri3A3Mm6XhPhpokosO4msqM3pHAcx7BOyf9qW6g2nU99Pkfk33+IsZxkX2kHbB7u06GvM2L8hnt6fhAwp0x/Q36usxDzAc8/l/2c59Q/dwnZT3e8bk79/aX6mP9DrbxVFWB824FxhNPqz7Yh8D/GfTBngX/Pyg8ig/thXoeeC/IfrXFw50Var/oH4H/p4AvyRL0Df+s6sXLlo9aYwOPv0bgprww7qvAfS1CvlkR8v0N+G8A/3Z5j4noIz5ny7gvHRd3LrxYxfcycJjqhnlSOLnZC3BqAZNv0b1E8NnUX+jp76bnUh3sFevb+nPDKRd+3fq2RKabbpvspfoHGPm3bLJb3C30d+PjLC/vFf9s15vCBtt3YNx8m1gre1vp+x9V7pP6/if09y9uu6X+KNekwvCZXH0e1/Ud/X73O7LumLjQM5kczv+2ZlHzU+NKS6rDfbpxFPYw90VeAz4R/fQsuXYv2L8wvlrIWNSeuJLSy4TN71Qd6Hgi/ZY6nlTtPqnjyRS2a2HV6p0+tbY9BXjvUXhtfl3HfO1uwNsdeBjfskxlSqbyavOpt07Ao1KlVab8VjXwpoq0Dlc+pga8V8MXTQPNdNAsQhndaOPNlWGenOenCjicG+a5f7x57GA8F/teUWaxHd634eRcpvK2F+SsFXkrF3qcofQ4s9p86mwQeOyj9LhVpbUf8Gb7OsHeyM+4+5UGxYxVN3mQ4c22BYuAoz2YIuTcX8l5QDV9Ss73I/0DAzlpD2Ng03OFTR+s+M2rpk/xmw9+h6h8r1b5XgC8Q4WOL1L2c1h1mGYRaA4XNCWKZjzSObLa0RwFmqMFzVwlWx3SuQn1aAlo6kWZsD/awTIph403WnkctrFdSndck7Ddye9i7vJilfdm5OMw5L0F+Vgm8n6VsI9WVZ7Lq+lT5bkCPNqUzhpUeR4LvA6R1jiRVpdKa2U1fSqtVeCxWvD4h1oPWwuaG+FTjgPN8Uq+I5XtfBB4JwreOymadaC5HLx7QNOrZKc2kPtPU3BWqZ9wZPx5Kn5Axc9Qd1wNUnz0XGjBeQ8r30lEK889bKBw1tNf+NzDEPL2TdWfwnmLUXdsJwmfz5ByHsF7oszrTt7J4H0XeMt8llXkyecYfQLjl3LVgV/aWB2cc6Xf7k186mqpfNAXPqO1uRrnIwrmYYL3IYUHHPrC4+nTYDMZ+qvPtBlYW5k6C0MwGa/vVDmTYCavw6Jf8VFlp2fJekPwswVPiuM874J1qHNE/GER59DPBb/aibjnDfETStX956DPeuqsS7W8ay76TP02hcPns+V5F99/ibPG8vy8vlf9YpGv9RHxn2WbRTyfB6Lf+u4uli9fnaG7iAgHZUDyhMvgiiAtiouue+OR1ucD2yK5IA9kkrb1hWqR/wi9f0nwuRQ=
*/