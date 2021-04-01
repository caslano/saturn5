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
L4fDN4bX7hIOP/FFClRNjMljeP2TUFRcu+qgym5yIFS8hMNm0+5a6gEj7fOvD+/VVeTK35qH6l9jP9TWBaETxlnakRimsVgXpXniRtR9dKEcgSh04x3hkB+SkxCXWitatc+L1e4e6T9bFA7fX5tT5AJCXDvlLSiweNmS1Vk005n241ABPSVemriGkxYNOxPsSufTvEYnBtQU5kONOfgcWVi0a90zBeRnmOGiuudZmKY0ZpAiuznNZZ6hRD3gZ1jJ9QBD/xITsUsmVbCu0dDNBpUb8T4DJzwAAYnYfcPfrqA35ZsX2B5XXMtMNOkP+3o/2QUJF6iOubxtSOJ1Sliqm3YOTK0mzstxMpDKUSPVNOjJPi0lb4HecSdOpJGLWJlGQ2CMXCv2X2DlOGSkp8rBESWQBlKOSlWcjQVCJQnDq7hBJH5wFuvnXAoX2qs+05L0DmBDPz6orLD/D1MQm2SrOpxw9Yws7xE+E9f7SSoyjZhiwGGa4WZUJ9TfCTcJbIWaIRV44qWdUfMDrS3t82TklGzFRFxLaNpwmwjDUO+eYL8e5/GOLhvszgcVrw==
*/