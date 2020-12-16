// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_ANDOYER_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_ANDOYER_HPP


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
class andoyer
    : public side::geographic<strategy::andoyer, Spheroid, CalculationType>
{
    typedef side::geographic<strategy::andoyer, Spheroid, CalculationType> base_t;

public:
    andoyer()
    {}

    explicit andoyer(Spheroid const& model)
        : base_t(model)
    {}
};

}} // namespace strategy::side


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_ANDOYER_HPP

/* side_andoyer.hpp
rYDWTqCI0DaAdgF/rU2AVXuAsm0BpA2A9fN/efavPfcvIq4T9J/v2362r/9c35P4kESSKs/u5Zm9PK8v+6z+CrlJnCZbP5MPIUvYnm5/Fn+JWD6D156/m5+9k1SGO06ukLoxPB8kRpJKcmP+N8/D/t3rf6751Mv/v3f9r1zPT3BiOXZQjptcsioXMFz0BsZGRXLBpP7fV/l/X8v/h8ZFBnOFKtfFfnWog1wXD5ZZ6yPn/8Pk+ixli7rvHjB6tOlSiZLMl0r3fA2QWt72uab+uZTtc0H9c03b58T656C2z5X1z7n//DWA/rmjrXPfP3+O+2fP0W84quOt7RWSFX4icNXkp1e9Mn0IHyAhn4sjy1k+c6K81efiqJ8PXQv3YGvci10xEwfiARyGWejL9Nl9xbNyYvt4WvZYqh1HrY+hHD/l2Gl13JTj5D0eH2taHQ9Nx8GxctzjmGfreMexruwxruzxzfrYFn+X45iX/vFLO27Zmdu6WR2T7nws0o5Descg6+OOdszRjjc6xxntGGM+vtzj8aSIeMoxRDt+3MOxI4QkWx0frI8NecrfX/1v9v33f+7/3P+5/3P/5/7P/Z/7P/d//v9+/t3r/+CoyNC///xfub6v68R5fIhyna2WO5MHmXPCjcFhBnnW7Mj/vaZp/2e8Sk+x6rW/Rx3uOcu1f7ScWrci1Yj6biTD5i9RrgnVmwf9Ro4Y6N9vrK9/cIQhkPsIEYHTYu/6TFZ5Nl4VG6rPwYODjfGmbvam5wB0U8sxPUuVunjIs+9Z5ekXI7ANw9svLVuXUB56xoaVu+dn9Jb1qE03F+25fbj6tzLdlRiAfniGX9HBqIyb+gyh+251/KbhPLCSvdJftFJ3q/rnS/2zlfGSA6Qt4y1YplP/GIPB/Gy7613q72Vdf7V+nozrLFE/Q0Itv+x0Sf209g9e8hy+o9znaaeEcnOXl61fpGHOPdXNRasbjS7Mz65lfAUyvsPyWUv7SWP6Lbei7PhoCtHePzrGEBoef0/j9dJZtwZry4aCLOoXXVnpZpwZfVv9IuTZenNZ911l3S/Qr59pzb+H9gh/Zd0vlroUkOrkU+LB8PYr9evCVv236tFCnU+UYj1PeOBWth4dGN7jcZv18Kfgv1UXR3W7o5PUpYN5+UiDkT2M2Bl3oCfD+zxhXRd2bH9pP6B089XWGUqR/gK0brMDI+IMapseZX3sZFrP4yLVXk3b4RLmly/1PMPfl5R6SRkeaCT0P1va+LB9dnNonGzqpzNlWS7//rzcrCrT2hu70U/AqjLT6h8YM40y/9q+zzzNRnWbiKaoYG2auziZu81Wu7lp84FO2vZkNV3atGr9RVqvT3ZV5Xs1ZR8wxrwPWFN2utS57W9MiDb8tf2i9T6AEmUZDVbmLfVoCa1N46U701J2mWr7zA7m9j1S/1GyT/cmTeqyTzGVo9wPjzBEdmxvXh5OulV2Kd1favVjSOkGsl+gqNva5gRUM5UwWdqsjUd1/i1Qx6/Mtn6GGGN4aHhwoNHw99YJi3W+zDGxzLKXebuC+eNHHRP5+9SC0nnrgXseUten0HAmK3CmQeZt6bRdkWlrL+tGG1k3AhaWTltYYHhkvz4DKeLu7aZkXSwzbV2tp82qDmHVTQV4SB3cpQ4uZergE2gM+3fqUK6GtHuQOiySOhTNLa1DeHSYIWaM+vDlH9g21DroLVOrei2RehmkXgFSL49FpfWKCDdEGk0L6F+ZN1Vr6tchu0wd1AX0j9bB3H4xW+qwVOqQZF5P42+rw5jwaZGBxrgYQ5+IaVEx4cawmbF/9Rzvzywv876qfy39etonlNYzLma2IfZ/UCfz8qtbu/S4Rp04rsk6tFg=
*/