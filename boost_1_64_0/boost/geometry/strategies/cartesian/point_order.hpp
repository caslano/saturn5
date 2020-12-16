// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_ORDER_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_ORDER_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/point_order.hpp>
#include <boost/geometry/strategies/cartesian/area.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace point_order
{

template <typename CalculationType = void>
struct cartesian
    : strategy::area::cartesian<CalculationType>
{
    typedef area_tag version_tag;
};

namespace services
{

template <>
struct default_strategy<cartesian_tag>
{
    typedef cartesian<> type;
};

} // namespace services

}} // namespace strategy::point_order

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_ORDER_HPP

/* point_order.hpp
lEfzK3bgL+zIvWznY1iRnViJnVmD3Xgwu7Mpe7Ave7I/T2ImB3IKT+U8DuISnsa7eTpXcDDHbqctUxHva4gZz/m7yGm7tFa8I7btbse00+2YdrYN0+72S//f7ZfWPfdbbZiSt19657nC2zBlPbdj7ZhKrFNuoqtIFwvEarFZlH1eeYoUMV+sEO+I8i/Isxgl5opVYrOo9qLpLxbZ/dr92v3a/dr92v3a/dr92v3a/dr92v3a/dr92v3aidd/qv3/8LHjM/+I9v+xdvs1KhVJjNPTPTzz7yz2EZ1i4e9zi+YdU08bk8F6oM/c8TH88vYtH/prN7ZDaJ8aplVj3URbg9COL+Rrc8hXH1FDdBfHWWZWJF/D09LPHjzs7ExNoXLa/24nb82S5K11pM10aPsUyVu073vP/ZOPeVjsjx/zcENIq7OoKjqI7uadHklrRNqEs4ZOSPmdZVDY+g4Mv4/sEvJwjOjp8xsjeYj9ar7570p/YmIbRMrA708L1oXelZRF8Xzpx6vC78pDg/Lbrwc5bQnWhHb8C8R+4grR1zKX589XaAAWa8+sS4LUlFBOXbeTxyHMP87EqMS0jInDYpPD9Np5+2SQVt42XPXzrlNY9xUVQ9uKfOu0oGTydUovsb11Ouy/bp1y6k+NUsnrb7OS+ddpvDjsd9Wfwurw4iR56B87zibNQ4vflYc6heSh3h7J85CVNA8t/9A85PSxsHaPgvvygEoSL5U/D+rC4PShw8ekZu7qsT20XctXtwrfrxPnxNLhe/BQTh3FQMtYHcljemrqmMHNdyZvXXegviTOfyEP3USNkJdTKlniHvnzsPPnv667eNzL2YYzQx8HfUPeeohBsXNSgbzlOUH/zvztyPk5p+zKhz4ARomqYnjYflkF8hff4X9v2RW2DReEfMwK+ZghTo+VU+mk+Wjxe/NRp5B81A5jBt4a8nFTyEezMknz0fKPzkdOvVkT8tFD1BBdxZBKse2VPx95dv5dzMuu7vstyyYfYzp9zz96jOl4eitDeheLquJ8cUF154VIepqUjk+ZmJ7TV8V20uuQZLt05c2Vc7ZL9PqudbncY3JF0V0c6PMd9srOQyx1BdUicayrtp30azM+3p1PhmlwLk9+fbk8pN88lEHj0BZ4eTz94UMHp8RHktqBPn5y2su+VyF37KjWiffDotcFe4c+pUVJcWLofyErpGuMZVv6zPgAz6kp293We4dtHdpyRsYcLRHa9J9Q1Dqycxi7bEjZ3HanoVuY3BFHDYu5I/3dxNqVXlQu0tY0+Vjjyc+P4bppeFramNGpsb9UD2U4UeRMD813k4wLFt3HZ4f17Cwqig5CmcpQdv7GpJ49OHVyvGm0f2gUnZm6Q+OTJmu/7i3j+Rg5eEykrfbSsKUaS9Q8DG214/lIiw2YGW6twziviZbbob3vjox/WBaODfvkjjnaYp+CY44ekjutec74ot/sHR1P9NO9o+OJbtg7Op7oM3tHxxN9MPG+ZdK+CurHtl/1+D7on5Gy+Tm0s98kKgbPMe/GfQorG3045ZRKdh9zO7K94mWzsHxu2cwpnyiHljllc3HutBY508aULzhG68jyBcdoPaV8dIzWfuWjZdq9fLRMjy4fLdPW5aNl2tz7UKZJ61vpJGXaM6e+hb4BeosqopswvqYfvRVWpulpGZmJXT4U7q73RRQZc7Pg9o8ci0aFfgPeKCqvfJmxvKb/dl7PSpsw5t+Wv1ib7nUV43Xl8Urx938P7zMqR/NfulI8wU9DWX8Yynr1voXmf0Jqdvb/veWb6Cci9DHQIRzr6Vhv/6qUPH8FqsEO9UlVFn4bVjl3/3qvcsF96fnKBY9HqyoX3L9uq1w=
*/