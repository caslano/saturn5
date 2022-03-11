// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PROJECTED_POINT_AX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PROJECTED_POINT_AX_HPP


#include <algorithm>

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>

#include <boost/geometry/strategies/tags.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/default_distance_result.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/strategies/cartesian/distance_projected_point.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>

// Helper geometry (projected point on line)
#include <boost/geometry/geometries/point.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace distance
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename T>
struct projected_point_ax_result
{
    typedef T value_type;

    projected_point_ax_result(T const& c = T(0))
        : atd(c), xtd(c)
    {}

    projected_point_ax_result(T const& a, T const& x)
        : atd(a), xtd(x)
    {}

    friend inline bool operator<(projected_point_ax_result const& left,
                                 projected_point_ax_result const& right)
    {
        return left.xtd < right.xtd || left.atd < right.atd;
    }

    T atd, xtd;
};

// This less-comparator may be used as a parameter of detail::douglas_peucker.
// In this simplify strategy distances are compared in 2 places
// 1. to choose the furthest candidate (md < dist)
// 2. to check if the candidate is further than max_distance (max_distance < md)
template <typename Distance>
class projected_point_ax_less
{
public:
    projected_point_ax_less(Distance const& max_distance)
        : m_max_distance(max_distance)
    {}

    inline bool operator()(Distance const& left, Distance const& right) const
    {
        //return left.xtd < right.xtd && right.atd < m_max_distance.atd;

        typedef typename Distance::value_type value_type;

        value_type const lx = left.xtd > m_max_distance.xtd ? left.xtd - m_max_distance.xtd : 0;
        value_type const rx = right.xtd > m_max_distance.xtd ? right.xtd - m_max_distance.xtd : 0;
        value_type const la = left.atd > m_max_distance.atd ? left.atd - m_max_distance.atd : 0;
        value_type const ra = right.atd > m_max_distance.atd ? right.atd - m_max_distance.atd : 0;

        value_type const l = (std::max)(lx, la);
        value_type const r = (std::max)(rx, ra);

        return l < r;
    }
private:
    Distance const& m_max_distance;
};

// This strategy returns 2-component Point/Segment distance.
// The ATD (along track distance) is parallel to the Segment
// and is a distance between Point projected into a line defined by a Segment and the nearest Segment's endpoint.
// If the projected Point intersects the Segment the ATD is equal to 0.
// The XTD (cross track distance) is perpendicular to the Segment
// and is a distance between input Point and its projection.
// If the Segment has length equal to 0, ATD and XTD has value equal
// to the distance between the input Point and one of the Segment's endpoints.
//
//          p3         p4
//          ^         7
//          |        /
// p1<-----e========e----->p2
//
// p1: atd=D,   xtd=0
// p2: atd=D,   xtd=0
// p3: atd=0,   xtd=D
// p4: atd=D/2, xtd=D
template
<
    typename CalculationType = void,
    typename Strategy = pythagoras<CalculationType>
>
class projected_point_ax
{
public :
    template <typename Point, typename PointOfSegment>
    struct calculation_type
        : public projected_point<CalculationType, Strategy>
            ::template calculation_type<Point, PointOfSegment>
    {};

    template <typename Point, typename PointOfSegment>
    struct result_type
    {
        typedef projected_point_ax_result
                    <
                        typename calculation_type<Point, PointOfSegment>::type
                    > type;
    };

public :

    template <typename Point, typename PointOfSegment>
    inline typename result_type<Point, PointOfSegment>::type
    apply(Point const& p, PointOfSegment const& p1, PointOfSegment const& p2) const
    {
        assert_dimension_equal<Point, PointOfSegment>();

        typedef typename calculation_type<Point, PointOfSegment>::type calculation_type;

        // A projected point of points in Integer coordinates must be able to be
        // represented in FP.
        typedef model::point
            <
                calculation_type,
                dimension<PointOfSegment>::value,
                typename coordinate_system<PointOfSegment>::type
            > fp_point_type;

        // For convenience
        typedef fp_point_type fp_vector_type;

        /*
            Algorithm [p: (px,py), p1: (x1,y1), p2: (x2,y2)]
            VECTOR v(x2 - x1, y2 - y1)
            VECTOR w(px - x1, py - y1)
            c1 = w . v
            c2 = v . v
            b = c1 / c2
            RETURN POINT(x1 + b * vx, y1 + b * vy)
        */

        // v is multiplied below with a (possibly) FP-value, so should be in FP
        // For consistency we define w also in FP
        fp_vector_type v, w, projected;

        geometry::convert(p2, v);
        geometry::convert(p, w);
        geometry::convert(p1, projected);
        subtract_point(v, projected);
        subtract_point(w, projected);

        Strategy strategy;
        boost::ignore_unused(strategy);

        typename result_type<Point, PointOfSegment>::type result;

        calculation_type const zero = calculation_type();
        calculation_type const c2 = dot_product(v, v);
        if ( math::equals(c2, zero) )
        {
            result.xtd = strategy.apply(p, projected);
            // assume that the 0-length segment is perpendicular to the Pt->ProjPt vector
            result.atd = 0;
            return result;
        }

        calculation_type const c1 = dot_product(w, v);
        calculation_type const b = c1 / c2;
        multiply_value(v, b);
        add_point(projected, v);

        result.xtd = strategy.apply(p, projected);

        if (c1 <= zero)
        {
            result.atd = strategy.apply(p1, projected);
        }
        else if (c2 <= c1)
        {
            result.atd = strategy.apply(p2, projected);
        }
        else
        {
            result.atd = 0;
        }

        return result;
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{


template <typename CalculationType, typename Strategy>
struct tag<detail::projected_point_ax<CalculationType, Strategy> >
{
    typedef strategy_tag_distance_point_segment type;
};


template <typename CalculationType, typename Strategy, typename P, typename PS>
struct return_type<detail::projected_point_ax<CalculationType, Strategy>, P, PS>
{
    typedef typename detail::projected_point_ax<CalculationType, Strategy>
                        ::template result_type<P, PS>::type type;
};


template <typename CalculationType, typename Strategy>
struct comparable_type<detail::projected_point_ax<CalculationType, Strategy> >
{
    // Define a projected_point strategy with its underlying point-point-strategy
    // being comparable
    typedef detail::projected_point_ax
        <
            CalculationType,
            typename comparable_type<Strategy>::type
        > type;
};


template <typename CalculationType, typename Strategy>
struct get_comparable<detail::projected_point_ax<CalculationType, Strategy> >
{
    typedef typename comparable_type
        <
            detail::projected_point_ax<CalculationType, Strategy>
        >::type comparable_type;
public :
    static inline comparable_type apply(detail::projected_point_ax<CalculationType, Strategy> const& )
    {
        return comparable_type();
    }
};


template <typename CalculationType, typename Strategy, typename P, typename PS>
struct result_from_distance<detail::projected_point_ax<CalculationType, Strategy>, P, PS>
{
private :
    typedef typename return_type<detail::projected_point_ax<CalculationType, Strategy>, P, PS>::type return_type;
public :
    template <typename T>
    static inline return_type apply(detail::projected_point_ax<CalculationType, Strategy> const& , T const& value)
    {
        Strategy s;
        return_type ret;
        ret.atd = result_from_distance<Strategy, P, PS>::apply(s, value.atd);
        ret.xtd = result_from_distance<Strategy, P, PS>::apply(s, value.xtd);
        return ret;
    }
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PROJECTED_POINT_AX_HPP

/* distance_projected_point_ax.hpp
+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
*/