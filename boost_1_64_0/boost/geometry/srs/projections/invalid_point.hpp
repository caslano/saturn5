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
YGDcfUHLywKuQl/EDoWeESwGwdFd7d2LDkMvHbIoSOKL5D18Vtr+9HO0rG6MzlIBORCH9BNtZEqx9S6Kgbv1hGdVUW3BxiRt7JIDfXyJVyI+gF5qYQ8mC5u974cbDVmOmxDLtDH9Cs5/90PrfZmaWk/n1CILgBWW9nYATbBIJWDURWkgNaUMbRALMHi3n3EXzdCx/sLKlEuapwfkN0VmjiGvT+aDb6+Ocq+hECcSobTwVgx7ke1aE8D9f2GXkLlK+HI6aM5Xjn3zHDbdSi11xPp1Ih0CMS629wcpU7BxvrFQ9bb1m9y7Bj7OzgHqol4YAeiW/gyBWdJ87U697h2ZAaT7NkSdGVQ9ycr6hZ9Z5qfCOh2n8clFCHcmXAd3yATwcLSOm0gAKsVM/WY5JFvKXxw7unG8Cc2mCUB9DQjsDfPnTQOLJCvyKhZduBBd1wkJU5En2VzZUivaSN2+K0Jaw+2HvuLAB2YxJF7rgGUZd9gRfzbARoBEZ/KA+O+5IxNbXTBF/ulhDteIVVbTALUS/CxZVYWT968PirobvVFt6sG2UPxYhAKeUQAifg==
*/