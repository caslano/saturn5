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
LmIeNK77w1enzcrhd3TYxDv8ucJDrRHKC28l4lenxKXcucdIIJ72bRnBKhGby+jQOEIHaG2OjzQQI6YyKI5QHFSO6Rl/C2jQFtsFX8h0vckY1wI+W95qxgNnctHz+kO3d9GbQIdo5in//aw2kzIyz0J9xpiyUXqRcoaAONPqXCLMEP4IDZGEUcKSpB1EEamAZzPhw+WnUfdq0APlhf3kMkqcRHTxwHsYXg0GhsdYijgjpEmNLzH3YrbgGa4G/CsiM/YpB4ln/9wbOp967ggR0vvVOx9a1TYpqrz1vva2J2KRNZqUDHNJcNarcBvJGYuANgWLxB8sl9W5mgx8iZ7aZhHJ+BbmEbtVzdqfNSyzKAXPeheD0Qdn4GmUYFbGWSojpS06wjxHriw6qpQYvi3Tlij6YAL9tsQYo6JwLWIl/TuqMES0kAseZ21w4jXWrt+XIsUMM6Zs8jOcLCwydschiZiP5WOufU0JO4uQcZuMRZHzhrYJXuxa04Q/KREwD+Bq2qO16ajzUQu4Hk26sPpsYD1BfThCPzgze1On67gOrBTrsoyZRQw16q0wOvS0Q4nB++R87BHbxmkLTpuGCilwBxlOM3TgMmnsELbghZXTtLzRIiJ79h5OmjV7I2L+YNnUjsSiS25At644hgu9
*/