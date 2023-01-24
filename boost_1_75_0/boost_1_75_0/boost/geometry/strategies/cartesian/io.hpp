// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_CARTESIAN_IO_HPP
#define BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_CARTESIAN_IO_HPP


#include <boost/geometry/strategies/io.hpp>

#include <boost/geometry/strategies/cartesian/point_order.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_winding.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace io
{

template <typename CalculationType = void>
struct cartesian
{
    typedef strategy::point_order::cartesian<CalculationType> point_order_strategy_type;
    
    static inline point_order_strategy_type get_point_order_strategy()
    {
        return point_order_strategy_type();
    }

    template <typename Geometry1, typename Geometry2>
    struct point_in_geometry_strategy
    {
        typedef strategy::within::cartesian_winding
            <
                typename point_type<Geometry1>::type,
                typename point_type<Geometry2>::type,
                CalculationType
            > type;
    };

    template <typename Geometry1, typename Geometry2>
    static inline typename point_in_geometry_strategy<Geometry1, Geometry2>::type
        get_point_in_geometry_strategy()
    {
        typedef typename point_in_geometry_strategy
            <
                Geometry1, Geometry2
            >::type strategy_type;
        return strategy_type();
    }
};

namespace services
{

template <>
struct default_strategy<cartesian_tag>
{
    typedef cartesian<> type;
};

} // namespace services

}} // namespace strategy::io

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_CARTESIAN_IO_HPP

/* io.hpp
a31MH2CNCvQlQlb+Jm88MPrzuFpvc8So0NNmd3OndXfpps+N6NocBy+m4/jJrsMD5KWRqgjSMNvE0ek6zzlbEMV6AqZc/r4EOlkMaUm8i+dM8FvS6Mfem86/iyu/zMfpOiQfBh9ZrHnN7QCtESKfRDyegVDjlZ5N+NeDpjv5qeT0i+aarOQ38ALgRYK1580ORDIVqOfxTNa6udW97F3m5LAezVZaAOr+MzAfIk5yz3FA356FyPfKVZvF+iEiaTJKok3ajJoaDkBzpXd9fUkJbf65/0wE1Yby/sA1IqhCr/mTCU4Xrf4rI6Wulk8gIWg3dhupPoYRjhGhJ5qjwJ9puolTeZylH2wsIBF27HUUy+jXfzL0ojKJONtZRYHUxTCCdG2hkr9XXx+pf+P4e5bdk+DWsDpJs5D7tNnCeMYMJE6O2+p51ShAdE7gbqPHP+sitxPW2o1YNPPpWrLFCvDf4bzy5fd9+7rVInexwLeTJIq5MB2VbtdK8ioiQLzP9a1oG/Mfyj/uepCKy3jDCM6ZPFk63mQW065qsfwb7CJdPXEimmvwIOU6SdSd9DdffiLtwsebDBAz+WOVJhg5OZZZuXTRIjZTHFh226NrVewZAGufNBO32lttximq9z3vd6R5yST9MLUo2TaGZy8ARx++1Z8hF3Yh/BZAFELrGPCB9E6WgBUjQbv8wskEcY6rUHibdPji9ps1eNOsCviG
*/