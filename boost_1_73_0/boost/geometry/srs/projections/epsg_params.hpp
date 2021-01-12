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
kqjsX5OAX51wzz+L43c2/EkOPykbx+8c+HaHj8Ktfw98q8O/DLdXGMd3evyPpsO3BmL9wzk//AD8Y7Mqt8/r4F9jANkm+Dv74/r3IviXHP4ruNl/fxD+BYevHYj3378E/hmHvw5u11dfwfOe8/1a4PeI84Pc78el4B8X3P1+XCv8Y4K7349bD79DcHd9uvaV9B+e78fVwbumaL9zdfxOgjd55r+L4Bd5zp86Fb7Gox8V4PcK
*/