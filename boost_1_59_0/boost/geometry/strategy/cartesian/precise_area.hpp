// Boost.Geometry

// Copyright (c) 2020, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGY_CARTESIAN_PRECISE_AREA_HPP
#define BOOST_GEOMETRY_STRATEGY_CARTESIAN_PRECISE_AREA_HPP

#include <boost/mpl/if.hpp>

//#include <boost/geometry/arithmetic/determinant.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/strategy/area.hpp>
#include <boost/geometry/util/select_most_precise.hpp>
#include <boost/geometry/util/precise_math.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace area
{

/*!
\brief Cartesian area calculation
\ingroup strategies
\details Calculates cartesian area using the trapezoidal rule and precise
         summation (useful to increase precision with floating point arithmetic)
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
[link geometry.reference.algorithms.area.area_2_with_strategy area (with strategy)]
}

*/
template
<
    typename CalculationType = void
>
class precise_cartesian
{
public :
    template <typename Geometry>
    struct result_type
        : strategy::area::detail::result_type
            <
                Geometry,
                CalculationType
            >
    {};

    template <typename Geometry>
    class state
    {
        friend class precise_cartesian;

        typedef typename result_type<Geometry>::type return_type;

    public:
        inline state()
            : sum1(0)
            , sum2(0)
        {
            // Strategy supports only 2D areas
            assert_dimension<Geometry, 2>();
        }

    private:
        inline return_type area() const
        {
            return_type const two = 2;
            return (sum1 + sum2) / two;
        }

        return_type sum1;
        return_type sum2;
    };

    template <typename PointOfSegment, typename Geometry>
    static inline void apply(PointOfSegment const& p1,
                             PointOfSegment const& p2,
                             state<Geometry>& st)
    {
        typedef typename state<Geometry>::return_type return_type;

        auto const det = (return_type(get<0>(p1)) + return_type(get<0>(p2)))
                * (return_type(get<1>(p1)) - return_type(get<1>(p2)));

        auto const res = boost::geometry::detail::precise_math::two_sum(st.sum1, det);

        st.sum1 = res[0];
        st.sum2 += res[1];
    }

    template <typename Geometry>
    static inline auto result(state<Geometry>& st)
    {
        return st.area();
    }

};


}} // namespace strategy::area



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_CARTESIAN_PRECISE_AREA_HPP

/* precise_area.hpp
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
*/