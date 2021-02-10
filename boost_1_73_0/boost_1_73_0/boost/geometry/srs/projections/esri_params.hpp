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
lQQ/eEIPFR6qglhpSsOE2hyFO583dk6lNXanMonKMoahh/B20Twrr9uaZLeqFFtamqdfWXiyurSsZJZ8JrlAX0fmPeLjI8tuAcTjW+L0otvpXTERv+uffeJZfdi63N6EMYDetTZ460Z53zk5A8niKn1XBtDoLeVQPbw3nUjkEXbER+Ilfq0MwMk2tOSAsObnUp+iTDDUWizmZhA9re1howQNkF3onExQnpqzZn9o/6F90CwXEZSIs2xiVXf353Uv3qwHqDlcdgq8rcPKWoiQLNK44zNfiYsYmlJBbMRUjj/fHtXJqD/juzd1b5xXYpHvpXl5CsrQGt2nHewCtI1lSkOc+cJVAnNa98jRVIOo9qBlV9zyQAL+QvMZM1DFkMlfsyLCLdF2zq97p8xCaADQ9L4FYEPUtr4dj/cpoGIqb7+8Cnr9XucKq4NWTnRd6kp4fQYXq6isl5PKgr6PwxSVxUgbxVHbuHFlIRqOiwXRKFUdn3cvOm/299kBSbNly5yMhNG2C2OXkt1ZOq1JgsUUx8R0iDLCU2cc10Ju2EzRkEg2ueoyAteiXTaoSy7Ix5LSAi17C4yBcozhScYq7k4t5nM89BO9cKUrK5KUictzJ/DjjrU9W7SVOxKFIkm9OLIU5COqtJ9znbXD8cmk
*/