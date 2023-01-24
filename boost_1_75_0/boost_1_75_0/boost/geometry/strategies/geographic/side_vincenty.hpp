// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_VINCENTY_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_VINCENTY_HPP


#include <boost/geometry/strategies/geographic/side.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace side
{

/*!
\brief Check at which side of a segment a point lies
         left of segment (> 0), right of segment (< 0), on segment (0)
\ingroup strategies
\tparam Spheroid Reference model of coordinate system.
\tparam CalculationType \tparam_calculation
 */
template
<
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class vincenty
    : public side::geographic<strategy::vincenty, Spheroid, CalculationType>
{
    typedef side::geographic<strategy::vincenty, Spheroid, CalculationType> base_t;

public:
    vincenty()
    {}

    explicit vincenty(Spheroid const& model)
        : base_t(model)
    {}
};

}} // namespace strategy::side


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_VINCENTY_HPP

/* side_vincenty.hpp
jnCFcQXxNXb0vEc8dOSpM3a1z/pb/RJYq7YSSRUHsCdgW3BrrJXZ9fnyVn9azHBGznIXXRq2WBwYOTtFvqddw/2RT2WR68Cf4h2Etsyp0m9JOarbdbWWCEqANvHdvxH+eW8ybro4YeWu+m7pNTxzXLDSXOjQ3vKsBtX9XGIz1tAFnR2k5DO6WSncgGJpTCiywPBUFqBxt8Kvpu4FvMdtGm6W3AfPD3x9Lxx89Of16unqqZeqIVYM+e3qtNi7CvxA9dJn6UVeZHdzSaybZr221LOweEfLp2W6Plc2gUWwK4nPhQmv+/Uz31UjkwzXQtScOoMXgqlm2QpM3khT0/9dPFh98Vc+RcOT089JA0avdeTG9FWz4S5GL/lzTVBBJfoHKW4vApmzSKrA1Ti4uThVidSyHE7opL50zlZLh2saV+5SHdHmw0zl1WH8RkWxqLD4I2Pg1pMU00WuLwJdblMBGLm/cRv99qIIGL2fe5+f0LX0gjwKOptQ3HSmMb2OEx7bF4WiZ3adBAaPPp3rK266A/NGQedLGV0XL8TJ0PUta7cX4YVrnI7H0rJDcRiMraarR/PKbVJ+SJ0g7hwgsPz2ovfRmdaagzlUBSzJT9Cs7resOKyR/Mz6Nd1YD7Z9/CPz/VuxXn7tiec2pwGXvzIacVrDW+pe/4t2mavHjM7j34UpsVPqV1TVsG4C9PobYbcrMqpkApWRKVrZALtY
*/