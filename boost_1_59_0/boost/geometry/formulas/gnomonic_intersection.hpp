// Boost.Geometry

// Copyright (c) 2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_GNOMONIC_INTERSECTION_HPP
#define BOOST_GEOMETRY_FORMULAS_GNOMONIC_INTERSECTION_HPP

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>

#include <boost/geometry/arithmetic/cross_product.hpp>
#include <boost/geometry/formulas/gnomonic_spheroid.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry { namespace formula
{

/*!
\brief The intersection of two geodesics using spheroidal gnomonic projection
       as proposed by Karney.
\author See
    - Charles F.F Karney, Algorithms for geodesics, 2011
      https://arxiv.org/pdf/1109.4448.pdf
    - GeographicLib forum thread: Intersection between two geodesic lines
      https://sourceforge.net/p/geographiclib/discussion/1026621/thread/21aaff9f/
*/
template
<
    typename CT,
    template <typename, bool, bool, bool, bool, bool> class Inverse,
    template <typename, bool, bool, bool, bool> class Direct
>
class gnomonic_intersection
{
public:
    template <typename T1, typename T2, typename Spheroid>
    static inline bool apply(T1 const& lona1, T1 const& lata1,
                             T1 const& lona2, T1 const& lata2,
                             T2 const& lonb1, T2 const& latb1,
                             T2 const& lonb2, T2 const& latb2,
                             CT & lon, CT & lat,
                             Spheroid const& spheroid)
    {
        CT const lon_a1 = lona1;
        CT const lat_a1 = lata1;
        CT const lon_a2 = lona2;
        CT const lat_a2 = lata2;
        CT const lon_b1 = lonb1;
        CT const lat_b1 = latb1;
        CT const lon_b2 = lonb2;
        CT const lat_b2 = latb2;

        return apply(lon_a1, lat_a1, lon_a2, lat_a2, lon_b1, lat_b1, lon_b2, lat_b2, lon, lat, spheroid);
    }
    
    template <typename Spheroid>
    static inline bool apply(CT const& lona1, CT const& lata1,
                             CT const& lona2, CT const& lata2,
                             CT const& lonb1, CT const& latb1,
                             CT const& lonb2, CT const& latb2,
                             CT & lon, CT & lat,
                             Spheroid const& spheroid)
    {
        typedef gnomonic_spheroid<CT, Inverse, Direct> gnom_t;

        lon = (lona1 + lona2 + lonb1 + lonb2) / 4;
        lat = (lata1 + lata2 + latb1 + latb2) / 4;
        // TODO: consider normalizing lon

        for (int i = 0; i < 10; ++i)
        {
            CT xa1, ya1, xa2, ya2;
            CT xb1, yb1, xb2, yb2;
            CT x, y;
            double lat1, lon1;

            bool ok = gnom_t::forward(lon, lat, lona1, lata1, xa1, ya1, spheroid)
                   && gnom_t::forward(lon, lat, lona2, lata2, xa2, ya2, spheroid)
                   && gnom_t::forward(lon, lat, lonb1, latb1, xb1, yb1, spheroid)
                   && gnom_t::forward(lon, lat, lonb2, latb2, xb2, yb2, spheroid)
                   && intersect(xa1, ya1, xa2, ya2, xb1, yb1, xb2, yb2, x, y)
                   && gnom_t::inverse(lon, lat, x, y, lon1, lat1, spheroid);

            if (! ok)
            {
                return false;
            }
            
            if (math::equals(lat1, lat) && math::equals(lon1, lon))
            {
                break;
            }

            lat = lat1;
            lon = lon1;
        }

        // NOTE: true is also returned if the number of iterations is too great
        //       which means that the accuracy of the result is low
        return true;
    }

private:
    static inline bool intersect(CT const& xa1, CT const& ya1, CT const& xa2, CT const& ya2,
                                 CT const& xb1, CT const& yb1, CT const& xb2, CT const& yb2,
                                 CT & x, CT & y)
    {
        typedef model::point<CT, 3, cs::cartesian> v3d_t;

        CT const c0 = 0;
        CT const c1 = 1;

        v3d_t const va1(xa1, ya1, c1);
        v3d_t const va2(xa2, ya2, c1);
        v3d_t const vb1(xb1, yb1, c1);
        v3d_t const vb2(xb2, yb2, c1);

        v3d_t const la = cross_product(va1, va2);
        v3d_t const lb = cross_product(vb1, vb2);
        v3d_t const p = cross_product(la, lb);

        CT const z = get<2>(p);

        if (math::equals(z, c0))
        {
            // degenerated or collinear segments
            return false;
        }

        x = get<0>(p) / z;
        y = get<1>(p) / z;
        
        return true;
    }
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_GNOMONIC_INTERSECTION_HPP

/* gnomonic_intersection.hpp
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
*/