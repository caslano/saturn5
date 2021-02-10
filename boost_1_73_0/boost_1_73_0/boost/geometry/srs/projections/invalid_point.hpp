// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_INVALID_POINT_HPP
#define BOOST_GEOMETRY_PROJECTIONS_INVALID_POINT_HPP


#include <cmath>

#include <boost/geometry/core/access.hpp>


namespace boost { namespace geometry { namespace projections
{

// Originally in pj_transform()
template <typename Point>
inline void set_invalid_point(Point & point)
{
    geometry::set<0>(point, HUGE_VAL);
    geometry::set<1>(point, HUGE_VAL);
}

template <typename Point>
inline bool is_invalid_point(Point const& point)
{
    return geometry::get<0>(point) == HUGE_VAL;
}

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_INVALID_POINT_HPP

/* invalid_point.hpp
Ho7iyZJ189wZcPYMhprWUtNRv7pmQtlVzCgQA7ymdmwjVqkP0x8sw+AG6Z3+dBL4sEljy/EnwJ/+TfpbWOmJHTmZD+fACemP7mIvOsL/pD8GlvG93JQRIDBLf4Qb7F22VQx7KP3ZYuXFrpvpa3txdDfJjBfFNOmzo9e0vz07io1vDdkAGTwSh8XYYQeLi6yI+wLYJsM1y9D148y89MXCWQThYwZKZzF1xisi5bPm1aADlIW9xbkPSAp41SZAROB0/LHEE8IHANlnUf3Zfz+DQ/61MXA8B6hPWxO2yp0brADoOAjtGzqW/oN6v6LzIHSWnj1xjPGjYRvTR99euBPR9hkd5ngK4Ub/j+jVIQwdw7FgIHSm1fuEe5D/fjWyemfWpXnZG3w5RFJAbwa7PXNmoePUGND19/iNO6tFdeO/aQYOfhwaH2DmcLpawnfUirWLQ9HSMCL3vxwrNjzHZ43hF2rwnn8P7fG7jwSVddn4CXZhH0DrmN3z0UUyjmEQSGpXA2ihIHfaaFlnV93mqN3rWo3B+dWl2R2Jtr8+S/4LUz7HcZ5pBklRhaPEyMDAx/F+xY/TvT69f/arhgXGXjBGHoCOKxAKiJHwM+AH/LE8kJjk/jFGyXfE/0q+QZIUMw1NsSnTYKdDoz1j63Ha
*/