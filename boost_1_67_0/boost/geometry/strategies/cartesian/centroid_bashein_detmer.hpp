// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2018.
// Modifications copyright (c) 2015, 2018, Oracle and/or its affiliates.

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
#include <boost/mpl/if.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/type_traits/is_void.hpp>

#include <boost/geometry/arithmetic/determinant.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/strategies/centroid.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>


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
    typename Point,
    typename PointOfSegment = Point,
    typename CalculationType = void
>
class bashein_detmer
{
private :
    // If user specified a calculation type, use that type,
    //   whatever it is and whatever the point-type(s) are.
    // Else, use the most appropriate coordinate type
    //    of the two points, but at least double
    typedef typename
        boost::mpl::if_c
        <
            boost::is_void<CalculationType>::type::value,
            typename select_most_precise
            <
                typename select_coordinate_type
                    <
                        Point,
                        PointOfSegment
                    >::type,
                double
            >::type,
            CalculationType
        >::type calculation_type;

    /*! subclass to keep state */
    class sums
    {
        friend class bashein_detmer;
        std::size_t count;
        calculation_type sum_a2;
        calculation_type sum_x;
        calculation_type sum_y;

    public :
        inline sums()
            : count(0)
            , sum_a2(calculation_type())
            , sum_x(calculation_type())
            , sum_y(calculation_type())
        {}
    };

public :
    typedef sums state_type;

    static inline void apply(PointOfSegment const& p1,
            PointOfSegment const& p2, sums& state)
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

        // Get coordinates and promote them to calculation_type
        calculation_type const x1 = boost::numeric_cast<calculation_type>(get<0>(p1));
        calculation_type const y1 = boost::numeric_cast<calculation_type>(get<1>(p1));
        calculation_type const x2 = boost::numeric_cast<calculation_type>(get<0>(p2));
        calculation_type const y2 = boost::numeric_cast<calculation_type>(get<1>(p2));
        calculation_type const ai = geometry::detail::determinant<calculation_type>(p1, p2);
        state.count++;
        state.sum_a2 += ai;
        state.sum_x += ai * (x1 + x2);
        state.sum_y += ai * (y1 + y2);
    }

    static inline bool result(sums const& state, Point& centroid)
    {
        calculation_type const zero = calculation_type();
        if (state.count > 0 && ! math::equals(state.sum_a2, zero))
        {
            calculation_type const v3 = 3;
            calculation_type const a3 = v3 * state.sum_a2;

            typedef typename geometry::coordinate_type
                <
                    Point
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