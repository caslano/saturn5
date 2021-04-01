// Boost.Geometry

// Copyright (c) 2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_RESULT_DIRECT_HPP
#define BOOST_GEOMETRY_FORMULAS_RESULT_DIRECT_HPP


namespace boost { namespace geometry { namespace formula
{

template <typename T>
struct result_direct
{
    result_direct()
        : lon2(0)
        , lat2(0)
        , reverse_azimuth(0)
        , reduced_length(0)
        , geodesic_scale(1)
    {}

    T lon2;
    T lat2;
    T reverse_azimuth;
    T reduced_length;
    T geodesic_scale;
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_RESULT_DIRECT_HPP

/* result_direct.hpp
kVPkZGwu45TfxgjtL3t/3v/wfUyQAtkMZX2z9pad3hE4TfTlSy5e7WJNr0cOsE8d8dIIULcc3n4t7r8uegC8QFU5hHSuXotAw9MuW9OfwqJE+pkKyNy6bU5nv2qNcsk0o6DIm8M5Gu6xg3qiwXke3B8Caz8MWirtNiSrTf3oRZ1HvUKZxLVnVKFChOYrOuJWkpGeuR5Xq5BSWvQpb/WzzLJnviDyd7eZXBB1DTykfqWfNJmQqQzljx42f5xzMTrBroiQVJV/ltvyN5Jp3sYRfcfyQuqOuwN+Ss3STn5sgxLZk965ok4mCKs5NKrE5TauQsRHcWVifMqgnP/WULv1KVId5V+sIf04vOeewLie7rB0oC3ardekF8fWQ38RkRv5cNLaTSMUdQAW8OokmYaAJOl7Y+eQpUpXGUXEi3fNtTwQ89fb7sFh3K2Y2B/m2G1NIjFVmyXE3X44+FdqtrRRq1roICu0/U4Rgu/8tFHoxup+MzyZ9G6a9O+WGS1/5ycvoFuF+E4+lynnZrt35jDh3quH8fYwv57ahQ36Kpker8uGg6yj1288tfygTg==
*/