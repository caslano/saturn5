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