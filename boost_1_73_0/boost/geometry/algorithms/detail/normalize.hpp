// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_NORMALIZE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_NORMALIZE_HPP


// For backward compatibility
#include <boost/geometry/strategies/normalize.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename GeometryIn, typename GeometryOut, typename Strategy>
inline void normalize(GeometryIn const& geometry_in, GeometryOut& geometry_out, Strategy const& )
{
    Strategy::apply(geometry_in, geometry_out);
}

template <typename GeometryOut, typename GeometryIn, typename Strategy>
inline GeometryOut return_normalized(GeometryIn const& geometry_in, Strategy const& strategy)
{
    GeometryOut geometry_out;
    detail::normalize(geometry_in, geometry_out, strategy);
    return geometry_out;
}


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_NORMALIZE_HPP

/* normalize.hpp
1Ln5A/dfWztXWq096v5Bfwzb3FU4+4Fb6+2B1bW+obsf4vxykP+qGLgV6M2mHSfmz4nFje3lISbJZHLiTmnnLniM/xw/P6kI6quqLG2U8UrhxiR5jjpxE2n8jDO82NOH+aBvakCQDcnA47xxyOLBfLUylYlVC8vEcBt0ZXDv26UjL0jHIJne3OypC3Oz9GPXYlir4AdNq625P0vfZdPRmYT1UwHpwJOnL8DhvNAOm7IYrt2w
*/