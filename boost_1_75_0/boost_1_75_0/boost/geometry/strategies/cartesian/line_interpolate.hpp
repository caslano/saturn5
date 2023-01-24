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
PBUDi0ZsO4y+EjBt7SalcMlFW6b4Md0/9Gp5a00D6HbOAwYVQbx2jzLy792RJ0cugMe6h/mR4am93Rd0L2+ZCtFakva/C/8Ri7ODy7VCQ2GXIPuErv3J9QZ7G626ixoMqHe2Bi93pBtoBKhkt86Y6l14P510eXGBLMPI2v1dEPIulZ3FxQXF3rmxUitjKVHDjOa03GlrseXzuYcxjdJP3oYh5xKxfuCTy7MA0ZYHH897MfSt72AMGY86737RDDpXKwWOw1jZMB+pDkm7gA9f9uq85ZyqK83lqscWNPWW5inU9LNPslYxCr43rywkvQD3411sVG0K6qqxje3LwQ3IspY6vH1aEkgvNsSzIMMcDplynKrbuN/6dd+UXOBfn5RWW13YPGXkFnNdnLQmLL+Hn8bmP85WOEw5fJo4hX1LHifG9Xpy3AjWUyCzMYs6wCeuPz431jqZNGN6rWPTfBewH45/oPfpwsjJeSUt6qbCX4CcBhESUkepvOwZAP1KQkkyOwWwCBkSdCqvWBWTeujJXfzqIC61t1/BNm6cXsc5rsGpaRLGaIltMqlmyC0O9OTu5KwKczVseyLSFSm8gu2N3vEM09C8n3qrM/ljTL1chf1YS+vER03dteXrlBrGQUkIfIYVzjQ1HfhT3Jxt5sa7w8IPT4OTxD64nYm/TpzvK9+VZ6LOHF50ysg+9RJkXMku1jNXB6wydKjNsUZ6
*/