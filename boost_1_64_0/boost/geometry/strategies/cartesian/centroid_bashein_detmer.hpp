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
MVwazUvJLcrOLv16xHrtFaMil/NqbTkem5HGEec0inLKcb3TVJcZ50/7er0jaXaUdWtDWNqIc8RnTml68jzGpxLLnm67cEnXcp21pKGapuKZWZSbbi+DaQ0D8xNB3hOd81NUkHlheTHrpGsamu0+9nwck3y0V/mWPtAtyMcax3zMTcsucpc5H2yLgHxYz6HWfCQ3CtwnEuqxP3rzYXxic0RiXOw4tUuU53o8vp6ZD78xcY0C1z2ReV2fB6ZprHo59of4eqWv+xDzerdx4L6wmrxFe/OR3Cuyb0psclJswvgRYxK8u2c5yqCDw/75VB3r/unXTt44cHsUkblie54SBo+OVZujzPkoaOC8LbKbBG6LBcy7PTA9Y1OUZ90LGpS+LczrmQNNAtf7apY/Yc8Hq1z29BdZ0reW8bSmgeu8hHkjvrCmpVe3PPv7ojKs7xDzm91qRaWtRf3zJWxFGaSShxLGIfIgjEFj5vVkUInXSKxT5fCuZ4mHKAtmZ3nMsWa1mX5f5SrG9Iy8XLfLvOcI8rvnCJJrYcszlEjvtGyeRxbq9QuyjDmT/Xu7d52LCrgnTeEpo17ed33tNq8Ztnmn5eVnzdLj06Z5lyfT6vaQ07iOOzg8le0W2YyxUGoMi1FOepnjuEbfq2V5Mt35XHxzWaPT2GeMD9F55DzP+sq9guWaaq9tntlGWusY3NGJtDJVeX9JWlJWJ3C1TsvYngRv3lKZfwIz7pH5VdwxvvXJBtv8a5n/GWaM+1rPb96ztJTrkoVudRthX2Yvy0xn5oYnfMtk+q698mZl5aZQZLZl1lzO+VZ9i+dbX77WSdmb1zTNmLbTG488GVaPlVVssu4HvH/PMtLd7Ls/0gvI9lhjfbaRIk+hJa9nfcvIH/Qy+23LSHR+5bWH9Vheie1/Wtbd9hylMCt9Nnn1WyYigvoziHI761t3/iF5KGCD62keW3nouOfruGW+wLj3E/f9wdx7/ejLzwpjGdl/1SIyPdp6XapSkDId4LcvFvvKOIM5jWlHzOsIppnHQivS3kfYou6xfvbtn7u96zEnYP90Ndf7506mmWURd579M5L5BzDjrBDmD6jTMs0xorZ6LbqV1Gu19HfHnkJVrx2p7jRGObBeO1DK9f9e8/qfuqx108C67Ii9/YC6IaAu4xgOqMvYLwPrssRy1GVorWfkuUdg/RZTQv3WwnafmMsfecqSV5jHpf4sSouZzP00sK6Kas4+0EJv20Y1rdsqcNua87diJ0tgxsww5veN4ZZ9z6OOfO+44GI5ZmW6LZ6kljrdmXV86Q44T7qrmL8oiHTq6fkbSz1yprFR7+Qv8BTmseKcsuzpHGO58Sxwsn4V776+2JtOvvcYK9Ll55FyNe//yL9M98tPp1Z6HP2Gxr5yWOedv8CdbYyRlmMl8B7XuKcb0EAv+2K4/drquBwLC9T1peS1jfq2d4R5LJhtmWkp+jPOpbeRme0EjcLN7/gHtmmabQKP6HXO8Z7nfXWNfq+A5HN7a53AxCDix7HyDeDo5n75DLwaSXGn5WcvuMBx+RSP9Zu+zt+cpnyfaW5+Y1r/v1kL8//29yNsaCPPzYPkubl82/dEi9LXI5sx+RfzfgFb3cG+tYMyXUF+nuf/E1oa6Tuus9lWUKCvKdz5hZ7Z7gW+fesJWfbqMPu+ta+tztQl6phH45ym7h9b+a0rZ9mUgrSZaflZZfietfN3wa3t9x3om9WedBoafc9mjzdipmdaTl5u7PxCesFl5eUWxBuP7ox1i7SeD+Vaog1xdCCOE3+2xOFbekh2Xrr3GjrO+4y3IDfLvIeyPvfV2ZKyNY//wgUet/1er2F7vaJXBOt9vC+qffxIa78=
*/