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