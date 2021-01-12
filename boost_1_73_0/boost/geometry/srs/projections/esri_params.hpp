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
xvSFIv+P0s9Ph9/t8KpttAGdvmPg75bcPb/9jejXMyavz+7Uz1wD76ihn0/G/Alb4v15r4Sf7/BRuFkffB18ucPvhpv3Pwr/QXU5X7ZVzC/eQf0V3790/SdfCK/mxz7Bl6Tj/D3rndH6quSDcNM+nwZ/pLqcfwhu4vd1+CscfkqvsI+9m/UDj/3uffDPVMGSMb+xN+5/74Df6fBvw2uMfRh+u8PP7hP7f97L+pfv+5Pw5/n2
*/