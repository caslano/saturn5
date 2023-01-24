// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_TAGS_HPP
#define BOOST_GEOMETRY_STRATEGIES_TAGS_HPP


namespace boost { namespace geometry
{

namespace strategy
{
    /*!
        \brief Indicate compiler/library user that strategy is not implemented.
        \details Strategies are defined for point types or for point type
        combinations. If there is no implementation for that specific point type, or point type
        combination, the calculation cannot be done. To indicate this, this not_implemented
        class is used as a typedef stub.

    */
    struct not_implemented {};
}


struct strategy_tag_distance_point_point {};
struct strategy_tag_distance_point_segment {};
struct strategy_tag_distance_point_box {};
struct strategy_tag_distance_box_box {};
struct strategy_tag_distance_segment_box {};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_TAGS_HPP

/* tags.hpp
/WI3ydMS5vuOTfaC281e5P2PglFBZ3iHFpwL8MLoClFWi0Mby6/PldGh3QzUG5C6/EBChwGFWyztr4uWp1DY17o3Q3Ghdv1xU1hEolgUou7kfjmx1FOHS2cFgnT+0kNSNcf87nWxGC2Hvp+qd38FCXYBCneHG2OpqWavDqgFN56TY/lyiMuBsSkb9m6WfoY6YBuhphZFcgcYh1WUsgO9b3JiLOMEKh6ADxKg8mNkZ57UIsGt6e82s3Xlp9TI3UbD8cENh5nFN983lBxUF5gXSA1sQRyK4m4C8o4Wafgc53yC0aSnqj7vfd7xTevGnmw6eL63oasEMfhkb7g8Ax9yZhF4B58npSixTcgd4I3cSQiTn6BRBMLV5XZ/aZcLdoFZkvGMsGK+XN2FtgTMECUo4bMLCsNxLP8AdwDw2FNEs/xm+OFULpvkwX7oCOQdxOYleU0mOkJ5izgHaLToUKd6iwqaW+zsBxIrXSBEKQoXmAeAxeASddZHrk2sds+XliR9m7cI2m2qoS7KAItMxBNjUdvW1ImEKenz8r3Fbs3BZueMTzgVLlUUKEqYHEdZMlFqy2RFhS0FKFSGGE6+MVnz4m1mrC9zaDeudUW/uUBXR7z4Ncx6QruXj6rGEQikv6E+w/ePGGn/M0b9X31nTv7/9J05/0X7Do6GQ17ghkCN5M/CLGPNljW0WfksCjtsaX9a6f/Zhudvd2LFKvXX
*/