// Boost.Geometry (aka GGL, Generic Geometry Library)
// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_SIDE_STRAIGHT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_SIDE_STRAIGHT_HPP

#include <cstddef>

#include <boost/math/special_functions/fpclassify.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/strategies/side.hpp>



namespace boost { namespace geometry
{

namespace strategy { namespace buffer
{



/*!
\brief Let the buffer use straight sides along segments (the default)
\ingroup strategies
\details This strategy can be used as SideStrategy for the buffer algorithm.
    It is currently the only provided strategy for this purpose

\qbk{
[heading Example]
See the examples for other buffer strategies\, for example
[link geometry.reference.strategies.strategy_buffer_join_round join_round]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
}
 */
class side_straight
{
public :
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template
    <
        typename Point,
        typename OutputRange,
        typename DistanceStrategy
    >
    static inline result_code apply(
                Point const& input_p1, Point const& input_p2,
                buffer_side_selector side,
                DistanceStrategy const& distance,
                OutputRange& output_range)
    {
        typedef typename coordinate_type<Point>::type coordinate_type;
        typedef typename geometry::select_most_precise
        <
            coordinate_type,
            double
        >::type promoted_type;

        // Generate a block along (left or right of) the segment

        // Simulate a vector d (dx,dy)
        coordinate_type const dx = get<0>(input_p2) - get<0>(input_p1);
        coordinate_type const dy = get<1>(input_p2) - get<1>(input_p1);

        // For normalization [0,1] (=dot product d.d, sqrt)
        promoted_type const length = geometry::math::sqrt(dx * dx + dy * dy);

        if (! boost::math::isfinite(length))
        {
            // In case of coordinates differences of e.g. 1e300, length
            // will overflow and we should not generate output
#ifdef BOOST_GEOMETRY_DEBUG_BUFFER_WARN
            std::cout << "Error in length calculation for points "
                << geometry::wkt(input_p1) << " " << geometry::wkt(input_p2)
                << " length: " << length << std::endl;
#endif
            return result_error_numerical;
        }

        if (geometry::math::equals(length, 0))
        {
            // Coordinates are simplified and therefore most often not equal.
            // But if simplify is skipped, or for lines with two
            // equal points, length is 0 and we cannot generate output.
            return result_no_output;
        }

        promoted_type const d = distance.apply(input_p1, input_p2, side);

        // Generate the normalized perpendicular p, to the left (ccw)
        promoted_type const px = -dy / length;
        promoted_type const py = dx / length;

        if (geometry::math::equals(px, 0)
            && geometry::math::equals(py, 0))
        {
            // This basically should not occur - because of the checks above.
            // There are no unit tests triggering this condition
#ifdef BOOST_GEOMETRY_DEBUG_BUFFER_WARN
            std::cout << "Error in perpendicular calculation for points "
                << geometry::wkt(input_p1) << " " << geometry::wkt(input_p2)
                << " length: " << length
                << " distance: " << d
                << std::endl;
#endif
            return result_no_output;
        }

        output_range.resize(2);

        set<0>(output_range.front(), get<0>(input_p1) + px * d);
        set<1>(output_range.front(), get<1>(input_p1) + py * d);
        set<0>(output_range.back(), get<0>(input_p2) + px * d);
        set<1>(output_range.back(), get<1>(input_p2) + py * d);

        return result_normal;
    }
#endif // DOXYGEN_SHOULD_SKIP_THIS
};


}} // namespace strategy::buffer

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_SIDE_STRAIGHT_HPP

/* buffer_side_straight.hpp
wiOE3YQjhBOEsMmkSehJSCQsJqybzHyEfZOZh9BwCnkiJBOyCcWEDVOYh7CLcIzwM6HhVOIhxBCSCBmEVYRthJ2EvYTDU5mXUHca8xJiCKmExdOIk7BjGvknHCG4riT/hDiCh7CVsI9witB0OtuOoCrgzYTdhMOEs4SmKZQNIZOwNoV0U4iPEJbK9FRXxa/iV/Gr+FX8Kn4Vv4pfxa/iV/Gr+FX8/kO/f2P//24phcTzG/X/v6we95rS/u/8PL/k5+fO/URK7q/h3M+i5H4czs//S+qXUf7+Ec79OEruj+Dcn6LkfjTO/RRK7p/i3I+m5P4yzv1xSu5X4twfp+R+N879hkruR+PcT6Tkfh/O/WLK3z/Fub9Myf1QNgeX3lbrinZum91rbZO1t8dKW2z52mF/yzbY37L99ULaXp3bXUtubw1zameV9tXIMrSplrcdVbWhhvyb2lF/yzZUv/ZTaTu1tps6t5m2+o3aSm3tpP/h9lFpG634VfwqfhW/il/Fr+JX8fu/+/1b7/+NFxKrBoCLv/9vUM/lHWvVTvrsDZcxskMICXW5jnzU6IeTOHjoqNgkYxhht/OM44uwjYMdUtcYbzS70DIOtqiKmqZeTytjQSX93ZL+WKMfux7rlcjyrsf805+xoNBdcFF5aB9m5sE31qelyxwDZs9XjIzRHyblMpiQTJwea76Mt1OndONPZc5XXBnKpp/k4YjkYZQqG8nLFJbfH5AHXTgXm4/ylE+ijM+vJWNPaxLSiDPyD9a85btz0rJy2QFl3On58xVqzZdfeu9Iev0IVXVfbddc5k3U6XnSjNfQ8ibMeWlq6H6Z0/PfT8JknZ3GBdLny/h9J+/K+FpNU8eKzgMHquWzSJnu7Ow822vEeQ9t+ceC1bSNyfMYeUx0ydgwyWN9PVZQxrPlpM1Xk/3yHi9j9FcH6byvDNJ537/dmncZuPY/kvcEc/y6jJWfGqSPg4m4TuX9CW/eGWlX4D5/yV/4uF3/fSTVZR+bZ45BbKePHznGzPGlWayRfX2qy5j0nyrp9TmDan3W7LCvz3m2RhnHTpJXv/XJdFgfj9/6mMd+O0t90Ni2Tu75Hv0lDNZNz98zcH11v9vgktqYy992WN4xe85t0iW3ATu3cZbcxuzcZlxy27lzG21JbcblbxN1btMtf1tpedvmyzsW0bkNuOQ2cuc275Latn+7sa/lbZu/2tiO7/3++cQ3Eq7/qU3fXw/9vGE2g190X3e5ppJrLZdfX3dW3+jb/BV2kDEUXWTsxEAZMzFExkxIfHKNRPkHxKf7WDfF7tK3uwdGYS8cLn3h46UvvBmfR+Ib5hDfR5K/j2VswFHJ5yeo5vknDsbjlvztl/hGOcR3ueQvQvriN8du0udcxdNa+uS38Y4Rk2sLuebgZxsj1lHGDnaSYdqdJR9qnRNluX6+63Tm4ydjIauqdPFyFR/2VenL8h6XeX6n7OWZWTXMkOXDZexGbewsYzrjZExntozl9MiYzRuxiYzZuAxflzGZn0n6X0v6MkbDPDe7VjuM0Rgj6SZKuuPwShyPS3ACrsDJ+CecKmMer5QxGil4GfGm4Xh04zIZw7USsyQf61zmeZY4JB/qGmmV5KODS2/HSByB3TBHxt7Nl7F318oYOxVXX9wlY+tekbF1b8hYulDiH4ydZOxcHxk711/Gyo2VMXITcaTkj+PDPG9yPtX5a2KMhdG/PMmfR7bLXBnbNg8P4kL8ChdhOJFcrebHa7AlXoe9cSlOwevRjcsxG2/EuXgTrseb8X5cLWNdbsNa5Gkt9sDf4RV4J8bi3bgN78F9uAnfx814CLfgt7gVz+D9qnxCyvYsq6xjDwLGHfyGYw4=
*/