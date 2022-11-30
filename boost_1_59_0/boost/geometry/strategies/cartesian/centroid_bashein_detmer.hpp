// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2021.
// Modifications copyright (c) 2015-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_CENTROID_BASHEIN_DETMER_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_CENTROID_BASHEIN_DETMER_HPP


#include <cstddef>

#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/arithmetic/determinant.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/strategies/centroid.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

// Note: when calling the namespace "centroid", it sometimes,
// somehow, in gcc, gives compilation problems (confusion with function centroid).

namespace strategy { namespace centroid
{



/*!
\brief Centroid calculation using algorithm Bashein / Detmer
\ingroup strategies
\details Calculates centroid using triangulation method published by
    Bashein / Detmer
\tparam Point point type of centroid to calculate
\tparam PointOfSegment point type of segments, defaults to Point
\tparam CalculationType \tparam_calculation

\author Adapted from  "Centroid of a Polygon" by
    Gerard Bashein and Paul R. Detmer<em>,
in "Graphics Gems IV", Academic Press, 1994</em>


\qbk{
[heading See also]
[link geometry.reference.algorithms.centroid.centroid_3_with_strategy centroid (with strategy)]
}
*/

/*
\par Research notes
The algorithm gives the same results as Oracle and PostGIS but
    differs from MySQL
(tried 5.0.21 / 5.0.45 / 5.0.51a / 5.1.23).

Without holes:
- this:       POINT(4.06923363095238 1.65055803571429)
- geolib:     POINT(4.07254 1.66819)
- MySQL:      POINT(3.6636363636364  1.6272727272727)'
- PostGIS:    POINT(4.06923363095238 1.65055803571429)
- Oracle:           4.06923363095238 1.65055803571429
- SQL Server: POINT(4.06923362245959 1.65055804168294)

Statements:
- \b MySQL/PostGIS: select AsText(Centroid(GeomFromText(
    'POLYGON((2 1.3,2.4 1.7,2.8 1.8,3.4 1.2,3.7 1.6,3.4 2,4.1 3,5.3 2.6
        ,5.4 1.2,4.9 0.8,2.9 0.7,2 1.3))')))
- \b Oracle: select sdo_geom.sdo_centroid(sdo_geometry(2003, null, null,
        sdo_elem_info_array(1, 1003, 1), sdo_ordinate_array(
            2,1.3,2.4,1.7,2.8,1.8,3.4,1.2,3.7,1.6,3.4,2,4.1,3,5.3,2.6
            ,5.4,1.2,4.9,0.8,2.9,0.7,2,1.3))
        , mdsys.sdo_dim_array(mdsys.sdo_dim_element('x',0,10,.00000005)
        ,mdsys.sdo_dim_element('y',0,10,.00000005)))
        from dual
- \b SQL Server 2008: select geometry::STGeomFromText(
    'POLYGON((2 1.3,2.4 1.7,2.8 1.8,3.4 1.2,3.7 1.6,3.4 2,4.1 3,5.3 2.6
        ,5.4 1.2,4.9 0.8,2.9 0.7,2 1.3))',0)
                .STCentroid()
                .STAsText()

With holes:
- this:       POINT(4.04663 1.6349)
- geolib:     POINT(4.04675 1.65735)
- MySQL:      POINT(3.6090580503834 1.607573932092)
- PostGIS:    POINT(4.0466265060241 1.63489959839357)
- Oracle:           4.0466265060241 1.63489959839357
- SQL Server: POINT(4.0466264962959677 1.6348996057331333)

Statements:
- \b MySQL/PostGIS: select AsText(Centroid(GeomFromText(
    'POLYGON((2 1.3,2.4 1.7,2.8 1.8,3.4 1.2
        ,3.7 1.6,3.4 2,4.1 3,5.3 2.6,5.4 1.2,4.9 0.8,2.9 0.7,2 1.3)
        ,(4 2,4.2 1.4,4.8 1.9,4.4 2.2,4 2))')));
- \b Oracle: select sdo_geom.sdo_centroid(sdo_geometry(2003, null, null
        , sdo_elem_info_array(1, 1003, 1, 25, 2003, 1)
        , sdo_ordinate_array(2,1.3,2.4,1.7,2.8,1.8,3.4,1.2,3.7,1.6,3.4,
        2,4.1,3,5.3,2.6,5.4,1.2,4.9,0.8,2.9,0.7,2,1.3,4,2, 4.2,1.4,
        4.8,1.9, 4.4,2.2, 4,2))
        , mdsys.sdo_dim_array(mdsys.sdo_dim_element('x',0,10,.00000005)
        ,mdsys.sdo_dim_element('y',0,10,.00000005)))
        from dual
 */
template
<
    typename Ignored1 = void,
    typename Ignored2 = void,
    typename CalculationType = void
>
class bashein_detmer
{
private :
    // If user specified a calculation type, use that type,
    //   whatever it is and whatever the point-type(s) are.
    // Else, use the most appropriate coordinate type
    //    of the two points, but at least double
    template <typename GeometryPoint, typename ResultPoint>
    struct calculation_type
        : std::conditional
            <
                std::is_void<CalculationType>::value,
                typename select_most_precise
                    <
                        typename coordinate_type<GeometryPoint>::type,
                        typename coordinate_type<ResultPoint>::type,
                        double
                    >::type,
                CalculationType
            >
    {};

    /*! subclass to keep state */
    template <typename GeometryPoint, typename ResultPoint>
    class sums
    {
        typedef typename calculation_type<GeometryPoint, ResultPoint>::type calc_type;

        friend class bashein_detmer;
        std::size_t count;
        calc_type sum_a2;
        calc_type sum_x;
        calc_type sum_y;

    public :
        inline sums()
            : count(0)
            , sum_a2(calc_type())
            , sum_x(calc_type())
            , sum_y(calc_type())
        {}
    };

public :
    template <typename GeometryPoint, typename ResultPoint>
    struct state_type
    {
        typedef sums<GeometryPoint, ResultPoint> type;
    };

    template <typename GeometryPoint, typename ResultPoint>
    static inline void apply(GeometryPoint const& p1, GeometryPoint const& p2,
                             sums<GeometryPoint, ResultPoint>& state)
    {
        /* Algorithm:
        For each segment:
        begin
            ai = x1 * y2 - x2 * y1;
            sum_a2 += ai;
            sum_x += ai * (x1 + x2);
            sum_y += ai * (y1 + y2);
        end
        return POINT(sum_x / (3 * sum_a2), sum_y / (3 * sum_a2) )
        */

        typedef typename calculation_type<GeometryPoint, ResultPoint>::type calc_type;

        // Get coordinates and promote them to calculation_type
        calc_type const x1 = boost::numeric_cast<calc_type>(get<0>(p1));
        calc_type const y1 = boost::numeric_cast<calc_type>(get<1>(p1));
        calc_type const x2 = boost::numeric_cast<calc_type>(get<0>(p2));
        calc_type const y2 = boost::numeric_cast<calc_type>(get<1>(p2));
        calc_type const ai = geometry::detail::determinant<calc_type>(p1, p2);
        state.count++;
        state.sum_a2 += ai;
        state.sum_x += ai * (x1 + x2);
        state.sum_y += ai * (y1 + y2);
    }

    template <typename GeometryPoint, typename ResultPoint>
    static inline bool result(sums<GeometryPoint, ResultPoint> const& state,
                              ResultPoint& centroid)
    {
        typedef typename calculation_type<GeometryPoint, ResultPoint>::type calc_type;

        calc_type const zero = calc_type();
        if (state.count > 0 && ! math::equals(state.sum_a2, zero))
        {
            calc_type const v3 = 3;
            calc_type const a3 = v3 * state.sum_a2;

            typedef typename geometry::coordinate_type
                <
                    ResultPoint
                >::type coordinate_type;

            // Prevent NaN centroid coordinates
            if (boost::math::isfinite(a3))
            {
                // NOTE: above calculation_type is checked, not the centroid coordinate_type
                // which means that the centroid can still be filled with INF
                // if e.g. calculation_type is double and centroid contains floats
                set<0>(centroid,
                    boost::numeric_cast<coordinate_type>(state.sum_x / a3));
                set<1>(centroid,
                    boost::numeric_cast<coordinate_type>(state.sum_y / a3));
                return true;
            }
        }

        return false;
    }

};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

// Register this strategy for rings and (multi)polygons, in two dimensions
template <typename Point, typename Geometry>
struct default_strategy<cartesian_tag, areal_tag, 2, Point, Geometry>
{
    typedef bashein_detmer
        <
            Point,
            typename point_type<Geometry>::type
        > type;
};


} // namespace services


#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::centroid


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_CENTROID_BASHEIN_DETMER_HPP

/* centroid_bashein_detmer.hpp
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
*/