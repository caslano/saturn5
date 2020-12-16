// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERSECTS_ANTIMERIDIAN_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERSECTS_ANTIMERIDIAN_HPP

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_system.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/algorithms/detail/normalize.hpp>


namespace boost { namespace geometry                  
{

namespace detail { namespace envelope
{


struct intersects_antimeridian
{
    template <typename Units, typename CoordinateType>
    static inline bool apply(CoordinateType const& lon1,
                             CoordinateType const& lat1,
                             CoordinateType const& lon2,
                             CoordinateType const& lat2)
    {
        typedef math::detail::constants_on_spheroid
            <
                CoordinateType, Units
            > constants;
    
        return
            math::equals(math::abs(lat1), constants::max_latitude())
            ||
            math::equals(math::abs(lat2), constants::max_latitude())
            ||
            math::larger(math::abs(lon1 - lon2), constants::half_period());
    }

    template <typename Segment>
    static inline bool apply(Segment const& segment)
    {
        return apply(detail::indexed_point_view<Segment, 0>(segment),
                     detail::indexed_point_view<Segment, 1>(segment));
    }

    template <typename Point>
    static inline bool apply(Point const& p1, Point const& p2)
    {
        Point p1_normalized = detail::return_normalized<Point>(p1);
        Point p2_normalized = detail::return_normalized<Point>(p2);

        return apply
            <
                typename coordinate_system<Point>::type::units
            >(geometry::get<0>(p1_normalized),
              geometry::get<1>(p1_normalized),
              geometry::get<0>(p2_normalized),
              geometry::get<1>(p2_normalized));
    }
};


}} // namespace detail::envelope

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERSECTS_ANTIMERIDIAN_HPP

/* intersects_antimeridian.hpp
cyLNEJ7OH+XiQac6yC41XuSn6UpyMQcyNYdjoJHLMs8lTxjr1Yasd1FONPDU0TX8SSaeuqjcC6eAOxiftD96P7dgXYp3mbp0qlXvVwf1BYOo68TpPjxI0daKy1X0IFB5xDIlVxDKHq124VD7dUL1fZYuXwrG0bYM5OoM7xzw2rXUNZwd+/TuYkO2am3DXR8BJ3ihoO8+zmWGTBhAm9dvFf7b3S/K8onnNc/zL7LKZ1VAPsHa+JU6PnC3+Gpzj3g+f2KARgnBf875uyAfAzHi74P8KPReSI4fRA8GP66w8mNlgB/BfO96HR94JmeVzg95U8tb5w0WXtHa09lVBp9kBzovbzBoZJ6el5eBOdwUxAfOe28O8lodscsc0/E/z+F/9i7YZqTS5h3Jm6z+53aXx/XlTculvL245U4dJ+/Vx9NZuYElr/LRSZLJefFdjhlAv/PScMK6yX4olTo0Xu6r0wTqWHf7cBlzPXY6tZ68eLWe/DSsZ5P9mOu517cHUEbtuYb7pY7pOI7q1nn9/9HQYUmkr/VPigYMN2eSqLH2jPSf/fjWDIErNkurh/vw/Mbb4uoZEGrQPnzSeZuE9n4AHx4mKR4+HtxDao0yVx/LPsSvDhMxdsF7JBMz98hj1j3yjCuDRuQUsMvP+nBCJ7kVLKMLjwfrgzRSxp4cn/PjjWdGng/iPYaomO4FnSZga1704TLaHAu17dy6NHj2jI9no4PPWpbW5srN6o6tkb8E/RhtDRq6UPxcZOJlPdwYo6ZeH8LoH7zq/iOzf/Cqe3httK+rqw6X1gbXFzgbyr8+RRNYn4lnAub8K7UJ0P9U/xyMd3vJieg1gjx0dDfVnUseGu/ubZ4xdb7nG0/n/eQ84+n8N+RbVTq7T/mC71O+4PvuX57fBeI0+g/g6d3sW+KCMc3L7l6sXVpdbdZ0FS5Q033F145Ojfmod7rQ0nfWZL6TRNwK8POdNZt0rq3rsy8xT5/8TBq/H2as4DtLJJmpn3Y6Uz9NGpfvE/OO6ehM3rECOmPiGcHkjTrWwfC5NdZ8NK6MTXyT29yYf9Oc4j51HnyfOg9e13mzvWNTAnOrHaad5Qf09tWxGs6QdfD9MpuQtaIzZW3Q9CVr9fyyuX/9eOv+BdennRMPHW/Kfwkaq/8y8Qxj+pBlVY1VaFqftlTRmLbUSuPTW8aihlfVgNmoa1iRfz2Kxr4ehbf7Y/CN9dWlK5rCy5ssZ04+vO/MaVEAJ/q1vqNNxQJWvPLled7xpnwt+mbgDf8ndSI/XZ9j4Xf6xkvfofPon2M1vPABIXN8w+5CE+zfb8PwE33iZTf6Wt9y5mHYOjGWnQZbBnqDORe/PVIyf0dvL2wKfZvzNO2AfQy1l/Pi1T4MmTxV+yefzAK6b7yTQ9PfkP/9gS2m7pp4U3cV3tRdP36Tumuj63MsdLdvvKm77yJP8Kbuqrb5dVfRGLobWOsmdfd9OY/8uqtoArprzCWv7n4g25u6q9puUncVndLd/HiluyZPle7mkZmpuwZe6a7IuT936lKvU8ue75yVfOnA3hewgvPw7myHkVOGR9hyyv945w9JDiLVs6xF4xRcfK0WvDLrhJTRpeOx46hc+OKlzcZpOL4xhHeC+3zWYB2f4X2SSs7UNdWzeZyxJBOxOFk3xw50ostxyDiNTvSTyvrwW2h4zk3iHS2CAr0PrjtjjlPQncN18q6MeZ65r5JDIH5SD4k0+vz1VuN0nP+Zpq39uJZuDbfvMB3nfw5pO187ebZsnwtT0eY51NfOn8MP9+My9OnZ3pEGjm/T0vodM07adUWj+h1v4Bq9uU4Ax56ytpto4Br7fw6xjvPoNs6rjH30kxH5ajNlVQs=
*/