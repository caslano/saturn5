// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2011-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POLY_ORIENTED_WINDING_HPP
#define BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POLY_ORIENTED_WINDING_HPP


#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/within.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace within
{

/*!
\brief Within detection using winding rule, but checking if enclosing ring is
    counter clockwise and, if so, reverses the result
\ingroup strategies
\tparam Point \tparam_point
\tparam Reverse True if parameter should be reversed
\tparam PointOfSegment \tparam_segment_point
\tparam CalculationType \tparam_calculation
\author Barend Gehrels
\note Only dependant on "side", -> agnostic, suitable for spherical/latlong

\qbk{
[heading See also]
[link geometry.reference.algorithms.within.within_3_with_strategy within (with strategy)]
}
 */
template
<
    bool Reverse,
    typename Point,
    typename PointOfSegment = Point,
    typename CalculationType = void
>
class oriented_winding
{
    typedef typename select_calculation_type
        <
            Point,
            PointOfSegment,
            CalculationType
        >::type calculation_type;


    typedef typename strategy::side::services::default_strategy
        <
            typename cs_tag<Point>::type
        >::type strategy_side_type;


    /*! subclass to keep state */
    class counter
    {
        int m_count;
        bool m_touches;
        calculation_type m_sum_area;

        inline int code() const
        {
            return m_touches ? 0 : m_count == 0 ? -1 : 1;
        }
        inline int clockwise_oriented_code() const
        {
            return (m_sum_area > 0) ? code() : -code();
        }
        inline int oriented_code() const
        {
            return Reverse
                ? -clockwise_oriented_code()
                : clockwise_oriented_code();
        }

    public :
        friend class oriented_winding;

        inline counter()
            : m_count(0)
            , m_touches(false)
            , m_sum_area(0)
        {}

        inline void add_to_area(calculation_type triangle)
        {
            m_sum_area += triangle;
        }

    };


    template <size_t D>
    static inline int check_touch(Point const& point,
                PointOfSegment const& seg1, PointOfSegment const& seg2,
                counter& state)
    {
        calculation_type const p = get<D>(point);
        calculation_type const s1 = get<D>(seg1);
        calculation_type const s2 = get<D>(seg2);
        if ((s1 <= p && s2 >= p) || (s2 <= p && s1 >= p))
        {
            state.m_touches = true;
        }
        return 0;
    }


    template <size_t D>
    static inline int check_segment(Point const& point,
                PointOfSegment const& seg1, PointOfSegment const& seg2,
                counter& state)
    {
        calculation_type const p = get<D>(point);
        calculation_type const s1 = get<D>(seg1);
        calculation_type const s2 = get<D>(seg2);


        // Check if one of segment endpoints is at same level of point
        bool eq1 = math::equals(s1, p);
        bool eq2 = math::equals(s2, p);

        if (eq1 && eq2)
        {
            // Both equal p -> segment is horizontal (or vertical for D=0)
            // The only thing which has to be done is check if point is ON segment
            return check_touch<1 - D>(point, seg1, seg2, state);
        }

        return
              eq1 ? (s2 > p ?  1 : -1)  // Point on level s1, UP/DOWN depending on s2
            : eq2 ? (s1 > p ? -1 :  1)  // idem
            : s1 < p && s2 > p ?  2     // Point between s1 -> s2 --> UP
            : s2 < p && s1 > p ? -2     // Point between s2 -> s1 --> DOWN
            : 0;
    }




public :

    // Typedefs and static methods to fulfill the concept
    typedef Point point_type;
    typedef PointOfSegment segment_point_type;
    typedef counter state_type;

    static inline bool apply(Point const& point,
                PointOfSegment const& s1, PointOfSegment const& s2,
                counter& state)
    {
        state.add_to_area(get<0>(s2) * get<1>(s1) - get<0>(s1) * get<1>(s2));

        int count = check_segment<1>(point, s1, s2, state);
        if (count != 0)
        {
            int side = strategy_side_type::apply(s1, s2, point);
            if (side == 0)
            {
                // Point is lying on segment
                state.m_touches = true;
                state.m_count = 0;
                return false;
            }

            // Side is NEG for right, POS for left.
            // The count is -2 for down, 2 for up (or -1/1)
            // Side positive thus means UP and LEFTSIDE or DOWN and RIGHTSIDE
            // See accompagnying figure (TODO)
            if (side * count > 0)
            {
                state.m_count += count;
            }
        }
        return ! state.m_touches;
    }

    static inline int result(counter const& state)
    {
        return state.oriented_code();
    }
};


}} // namespace strategy::within


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POLY_ORIENTED_WINDING_HPP

/* point_in_poly_oriented_winding.hpp
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
*/