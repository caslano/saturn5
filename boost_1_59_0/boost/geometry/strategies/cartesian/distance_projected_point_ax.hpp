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
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
*/