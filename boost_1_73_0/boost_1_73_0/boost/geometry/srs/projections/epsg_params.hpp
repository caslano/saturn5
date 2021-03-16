// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP


#include <string>

#include <boost/geometry/srs/spheroid.hpp>


namespace boost { namespace geometry
{
    
namespace srs
{


struct epsg
{
    explicit epsg(int c)
        : code(c)
    {}

    int code;
};


template <int Code>
struct static_epsg
{
    static const int code = Code;
};


} // namespace srs


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP

/* epsg_params.hpp
kXRVwE8lwz0Y7aAQcWBM7PFor9WXey2M+8ZJ/wrpJ7LUifiTW882j0LZNhTZOZO9yrMtQeounlNaQg+pML063s672gqEfuClSRXkfW5mk30nEhHH9O/sLpDBPsN1hnAbVF0LuL9FOQx5kulCLl6lk7Vw+FWK44jSlu1X+nE9PboLLe0wTqFSfo1N49H9XunPBljSebZ3gdwlPAsG2Mez+6xP2pLBZyZgTCn5CWyK0s7Sj2chjXScjO8wlVfoZBo=
*/