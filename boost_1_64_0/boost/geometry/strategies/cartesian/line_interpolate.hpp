// Boost.Geometry

// Copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_LINE_INTERPOLATE_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_LINE_INTERPOLATE_HPP

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/strategies/line_interpolate.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace line_interpolate
{


/*!
\brief Interpolate point on a cartesian segment.
\ingroup strategies
\tparam CalculationType \tparam_calculation
\tparam DistanceStrategy The underlying point-point distance strategy

\qbk{
[heading See also]
\* [link geometry.reference.algorithms.line_interpolate.line_interpolate_4_with_strategy line_interpolate (with strategy)]
}

*/
template
<
    typename CalculationType = void,
    typename DistanceStrategy = distance::pythagoras<CalculationType>
>
class cartesian
{
public:

    // point-point strategy getters
    struct distance_pp_strategy
    {
        typedef DistanceStrategy type;
    };

    inline typename distance_pp_strategy::type get_distance_pp_strategy() const
    {
        typedef typename distance_pp_strategy::type distance_type;
        return distance_type();
    }

    template <typename Point, typename Fraction, typename Distance>
    inline void apply(Point const& p0,
                      Point const& p1,
                      Fraction const& fraction,
                      Point & p,
                      Distance const&) const
    {
        typedef typename select_calculation_type_alt
            <
                CalculationType,
                Point
            >::type calc_t;

        typedef model::point
            <
                calc_t,
                geometry::dimension<Point>::value,
                cs::cartesian
            > calc_point_t;

        calc_point_t cp0, cp1;
        geometry::detail::conversion::convert_point_to_point(p0, cp0);
        geometry::detail::conversion::convert_point_to_point(p1, cp1);

        //segment convex combination: p0*fraction + p1*(1-fraction)
        Fraction const one_minus_fraction = 1-fraction;
        for_each_coordinate(cp1, detail::value_operation
                                 <
                                    Fraction,
                                    std::multiplies
                                 >(fraction));
        for_each_coordinate(cp0, detail::value_operation
                                 <
                                    Fraction,
                                    std::multiplies
                                 >(one_minus_fraction));
        for_each_coordinate(cp1, detail::point_operation
                                 <
                                    calc_point_t,
                                    std::plus
                                 >(cp0));

        assert_dimension_equal<calc_point_t, Point>();
        geometry::detail::conversion::convert_point_to_point(cp1, p);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <>
struct default_strategy<cartesian_tag>
{
    typedef strategy::line_interpolate::cartesian<> type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::line_interpolate


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_LINE_INTERPOLATE_HPP

/* line_interpolate.hpp
N9cwcj15LU/hG2zPDbyObzGFG7mVm3iAf2ThwvZHnsXNrMUtvI/b+DA/5WR+xhXczjXcyU+5i9/yC1Y82f7K8/gVr+dBDuV3nMhDnMvDXM6fuIM/80s6Zo84vYjjM5sxL69iPg5gfiaxAJN5IsewIOewEBewCN9hUe5nMR5gcR5kCR5hSeYv6ryb1ViatXgqz2MZXsKyvIrleBdP4zhW5BxW4iZW5iGewfyRcW9ZhWeyKc9iS57NVjyHbViNHfgbXsPq7Mwa7MGaHMHavIdNOJmX8CO24CHGMzL21WUsx5Y8g5ezBVvxMrbhlbyCPdiWo9iO97ADJ/BqPsaOnMdOXMrOXMvruJ5dGK7jhDEmHONyuI6z+8RwvzBP53424De8ngfZg98ymYc4kt/zHv7A53iY8/kz1zIucn0QuXiQufk98/AI8zLSzzofKzE/z+IJrM8CbMsT2YEF2Ysn8TYW4p0szAd4Mp9lEc5iUaaxGDeyON9hCW5iSX7IUxinTEozN8vyRJZnUZ7GKjydnVmRKazMW3gGb2MVRvtBhLEwuC6HfhDagPTy7stWvIFJ7MdkDuQEJvFJDuJTTOU83sg0DuUKDuNK3sTI8a95Y9PKDNkshZr4DC5JMnS2cyaZJitluxS18WpLK+knY2W2rJVdUuB5xz5pLgkyWmbISolr7D0izrF/SHk/t2c/GStzZa1slcNSfq75N/H+Uqipv5F46SrDZa3slrzNlKdcKENliiyRTbJLDknJ5pZL4iVJxso0WSnb5aCUvMQ0cqGMkIkyVzbLYSl6qflIY2krSTJJZsgbsl9ObeHvpbOMkPEyRebKJjkoheKVobSXfjJcJsoC2Spxl5mPNJf2MlzGyjRZIpvkkJRsaXklXjrKCHlc0mRtE8vNXRJ3uWWX6tJbxspsWSmb5JDUVrk+9Dfx7CojZIrMlbVStLV5SG8ZKmNltiyRQ1KojfeQ9pIgo2W2rJXdEneFZZXGMkLGywxJk81ySMq39XvpKkkyVmbLStkv5dvZ1lJdLpTOkip3yiSZIWmyVnZL3iuVkVSR86SVJMgImSgLZKPsl7irzE9DVZHNpbeMlRnyhuySou2to7SVrpIqd8rjkiYbZasU6GBd5UJpK6kyURbIStkou6TQ1eYn9aWrDJdpskDWymbZLwWusQ7SUYbLWJkiC2SlbJcCHU0jzaW3TJTZsky2yn4p+jvzk/OkrQyXSTJb9supnSyLdJR+MkIel9myRLbLoSb2BZ56rfeR5tJeEmSszJA0WSsfymEp2dm00ly6ynB5XBbISrlwrm0pw2WSLJBNsl+KzvN76S2jZYa8IbukwHzrLM2ln4yV2bJJDkrJF9QVaSVJMkmWyHbJu8A2krZyp8yV7XLqi16T4TJDPpSiL5mHJMhYWSCb5JBUXKjOSoKMlhmyVnZJoTTzl3jpLXfKFFki26XoIuUtvWWirJSDUn6xv5GhMk02S9zL1lXipZ9MkiWyVYou8T7Se0ncf8R/eaVvXK7ouIsNOw9MMubawMHJPRKj/0zpV6P74D79EmrUqVmnZu2eNW5MqVu7zgWZvxta77waKb27JScm1EhI7D64V8bv/a5z9MmnAQ+J6l5zYPe+rm9eWCyuq/0qroTTiJe7xWXauk+P5IEpA3umVqx65TkVr0jyZPw+NxnUqWIzg4X16ZeYnD7+3PyyylEZ504fjipjLMzUbpExTyv7/Qt+3/XlyO8TjpkgOg5Dq2LdS8ZlPmOsazhXOlnSu85Ly5Jed9LuV22bNLv8kvbpw1cf//M+4zPHsYp9vtfGMK8iki/Ms5tpR8TMKzIMZ58BVvwfmF90PK/U3Eef9V+KvdjQb6ZE52c=
*/