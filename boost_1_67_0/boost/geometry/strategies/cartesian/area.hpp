// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2016, 2017, 2018.
// Modifications copyright (c) 2016-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AREA_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AREA_HPP


#include <boost/mpl/if.hpp>

//#include <boost/geometry/arithmetic/determinant.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/strategies/area.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace area
{

/*!
\brief Cartesian area calculation
\ingroup strategies
\details Calculates cartesian area using the trapezoidal rule
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
class cartesian
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
        friend class cartesian;

        typedef typename result_type<Geometry>::type return_type;

    public:        
        inline state()
            : sum(0)
        {
            // Strategy supports only 2D areas
            assert_dimension<Geometry, 2>();
        }

    private:
        inline return_type area() const
        {
            return_type const two = 2;
            return sum / two;
        }

        return_type sum;
    };

    template <typename PointOfSegment, typename Geometry>
    static inline void apply(PointOfSegment const& p1,
                             PointOfSegment const& p2,
                             state<Geometry>& st)
    {
        typedef typename state<Geometry>::return_type return_type;

        // Below formulas are equivalent, however the two lower ones
        // suffer less from accuracy loss for great values of coordinates.
        // See: https://svn.boost.org/trac/boost/ticket/11928

        // SUM += x2 * y1 - x1 * y2;
        // state.sum += detail::determinant<return_type>(p2, p1);

        // SUM += (x2 - x1) * (y2 + y1)
        //state.sum += (return_type(get<0>(p2)) - return_type(get<0>(p1)))
        //           * (return_type(get<1>(p2)) + return_type(get<1>(p1)));

        // SUM += (x1 + x2) * (y1 - y2)
        st.sum += (return_type(get<0>(p1)) + return_type(get<0>(p2)))
                * (return_type(get<1>(p1)) - return_type(get<1>(p2)));
    }

    template <typename Geometry>
    static inline typename result_type<Geometry>::type
        result(state<Geometry>& st)
    {
        return st.area();
    }

};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{
    template <>
    struct default_strategy<cartesian_tag>
    {
        typedef strategy::area::cartesian<> type;
    };

} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::area



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AREA_HPP

/* area.hpp
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
*/