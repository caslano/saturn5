// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2016-2020.
// Modifications copyright (c) 2016-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_CARTESIAN_AREA_HPP
#define BOOST_GEOMETRY_STRATEGY_CARTESIAN_AREA_HPP


//#include <boost/geometry/arithmetic/determinant.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/strategy/area.hpp>
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
    static inline auto result(state<Geometry>& st)
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


#endif // BOOST_GEOMETRY_STRATEGY_CARTESIAN_AREA_HPP

/* area.hpp
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
*/