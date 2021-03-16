// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_ESRI_PARAMS_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_ESRI_PARAMS_HPP


#include <string>

#include <boost/geometry/srs/spheroid.hpp>


namespace boost { namespace geometry
{
    
namespace srs
{


struct esri
{
    explicit esri(int c)
        : code(c)
    {}

    int code;
};


template <int Code>
struct static_esri
{
    static const int code = Code;
};


} // namespace srs


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_ESRI_PARAMS_HPP

/* esri_params.hpp
JdDopUChJYHoj05vjouM/RPg3hqnz+jzexJNB+yIM077dwJDwx9q1wsU2a4TTQ1jgOvK9rU36EPSZMttJQVLDV0Dn4DmbV8iUUyntHaPJqrpuriZT6riQuli+ki2oeTas7SEfO3yy81j3H2tXbj35Qv3n5r7Lc293GH2P6K5T/iYYUb8hIXJg/oCVElp99hRjV9iYUG6l1wFpCthFZAq+BrgHGAISHfHiVYWPKK5j2vuk5rcHxpPbSDx9NV2dMA=
*/