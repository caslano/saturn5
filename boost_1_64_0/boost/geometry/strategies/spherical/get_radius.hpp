// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2016-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_GET_RADIUS_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_GET_RADIUS_HPP


#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace strategy_detail
{

template
<
    typename RadiusTypeOrSphere,
    typename Tag = typename tag<RadiusTypeOrSphere>::type
>
struct get_radius
{
    typedef typename geometry::radius_type<RadiusTypeOrSphere>::type type;
    static type apply(RadiusTypeOrSphere const& sphere)
    {
        return geometry::get_radius<0>(sphere);
    }
};

template <typename RadiusTypeOrSphere>
struct get_radius<RadiusTypeOrSphere, void>
{
    typedef RadiusTypeOrSphere type;
    static type apply(RadiusTypeOrSphere const& radius)
    {
        return radius;
    }
};

// For backward compatibility
template <typename Point>
struct get_radius<Point, point_tag>
{
    typedef typename select_most_precise
        <
            typename coordinate_type<Point>::type,
            double
        >::type type;

    template <typename RadiusOrSphere>
    static typename get_radius<RadiusOrSphere>::type
        apply(RadiusOrSphere const& radius_or_sphere)
    {
        return get_radius<RadiusOrSphere>::apply(radius_or_sphere);
    }
};


} // namespace strategy_detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_GET_RADIUS_HPP

/* get_radius.hpp
CVnnZV0nJKfU31MnpL63dZ2QfaVuXJ2Q5d7WdUJ8St/4OiH+pazrhNhK35g6IStLWdcJyS7936sTElbaGDuyKqExwZM05RWcpiJdc9KW1S1doS7XYZjrdSj5Yba0gb/Lm3VhO6StKxmZnq4YrXCGa8BRG6TQdq5aXxhN7csGRY2JSnC01c9yaec/UqWHex5lzGOT7W1ihzj1aVFJ6rLU1D9TPJyakOxY33CntsZVpc+IdEe5bFJsJsUxtuToeGnXrfLlFP4r+0O1j1VlLq/4S/2D8VHcrqT+gzmdCUl6Otv6Tr/F/p5T0td83wuTtvTa7zEN8BnMZb3ZFZz2py0lOTo2NdV5n172uHr9mmNO7egb3O5cv4b+UuRzXARTZPuYYNrfHBL37TOdF3R8JMs72r3fZV+elHqYjw37vJLpelc1a+R8NO9vP1NfHVGJoPo0GSf9UDjK4+dzPgaU1X8boB9q+Q3X1N8Icalj41wfI41HEGOM38dl2ff8ZUx+X/vnbf7mcb4bS5lvDOd9CPbF8qTd5q/PnxShP5LpcRazTxhTfy+pbLT0+eLYNxx8x/VbQrZN7Qf2bQnn8aR5nJR5bcb1wXOiXFtqWppLXyk8d8j6Zrr2zyLnSbbFdVDbXJfFGAvbQ9Kt9ZiTYk9PppT3S7ty/Rh24/jl36r/LudxtqIxpnO4U52fStJfQamK5vpcHBu1jvocG+333fjKRr2M4Rb1kSqZ66zEOOq2sC7Ttekv5dDab7dNcTuWIf7gaub6D9HJtolyyIt1bfrJdefc54KfXHuH/WXfSXp9SrikV22f6ZrS6tK41OtKSdZqbkl1K8u6VYFO+7mq87Ujy0q/CdJHjFo2SW2zHO9EX5dlIux9JVQ1Xfup0VFJklC3+lBSN8xRB4jj6VPB3u//igD2uawrzG2biU/WNdJ1XXyjbWNjc10b0zN+udukHgehGmEXoazWn0l113ou46l05KjpV/j7h9RvMV2/ql6Ze7m53L/c88jqpmMm0asaXkYdhob+ql4U1wfxm47tmOTkGHN/Njmy3Y/Iu00WoRzbfayGU59DyRHay1oKmXqh/WZIHx5uedhwtQ8mpHi4PfcnmK65UB/pC13StFnSlB1oSlN6kiNVRejPo/B0pRSYrqaSrim+9hX+Q/ren4hlWTa7ppEu7oiF1uVw6YtJ8lBJB9eU/Y2UY2quJxfhPD0TXfP6Cqbx8hNlTHzz/bexfHa9/4YZ/YCpuqJBxvOfmhaMrveiUNW3iLb19nvnolr2a/WMv/l8WykD8c5m/iDMwF8IuUFqHzo/Otr3ZSH3z7ASxnNOjVbm55wyrdyfcyJdnnNmuj9Xyr53e87Rp3dz//1A3w/zLfpdiXfpby3X/Iyk7pO+Fs+rMS7Hboh7vqBPTzPVvZTfM0x55Fh1j3/Xfk/RMmWL51zrfmDCzc9hepyzLJ5x/VS/bebnkkRjO1TCtbw9i/k2E3cJrqOnmhjPbStdnts4f9T8XqR/EfNHBhvzZ1k85/Flgc95K+up53D984wG9s8Py3PfMpfP77h8/sLlc62GLt/LttwmdStbN5PnSPl+azPzc+aTLczPmV3k/S+R5bW/E/IefFT6NrK1Na4VqXcZZbNF6JW5JkQlaBVpi/zbk3NfQj7m80Pel83ngodT309xafb973WVvsnyK0nbYskzQ9FXy8vbqXp8FvfVwvNzx7PhNKf0D7e4z0Ze5T4bX8B9tnHB91mVp6Y7XZfBBdx3g1zuu5VMddjTknkkjqUqsn5u29gnhyrZy71qdzDO7UCLths1zc8xpnvUuTvsO+mpCryb4DTU7lGRHdX+VveoTK+r56uRXkY/YVle5nNlppc=
*/