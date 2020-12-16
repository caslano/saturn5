// Boost.Geometry - gis-projections (based on PROJ4)

// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018, 2019.
// Modifications copyright (c) 2017-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Boost.Geometry by Barend Gehrels

// Last updated version of proj: 5.0.0

// Original copyright notice:

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef BOOST_GEOMETRY_PROJECTIONS_MBT_FPS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_MBT_FPS_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/aasincos.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace mbt_fps
    {

            static const int max_iter = 10;
            static const double loop_tol = 1e-7;
            static const double C1 = 0.45503;
            static const double C2 = 1.36509;
            static const double C3 = 1.41546;
            static const double C_x = 0.22248;
            static const double C_y = 1.44492;
            //static const double C1_2 = 0.33333333333333333333333333;

            template <typename T>
            inline T C1_2() { return detail::third<T>(); }

            template <typename T, typename Parameters>
            struct base_mbt_fps_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T C1_2 = mbt_fps::C1_2<T>();

                    T k, V, t;
                    int i;

                    k = C3 * sin(lp_lat);
                    for (i = max_iter; i ; --i) {
                        t = lp_lat / C2;
                        lp_lat -= V = (C1 * sin(t) + sin(lp_lat) - k) /
                            (C1_2 * cos(t) + cos(lp_lat));
                        if (fabs(V) < loop_tol)
                            break;
                    }
                    t = lp_lat / C2;
                    xy_x = C_x * lp_lon * (1. + 3. * cos(lp_lat)/cos(t) );
                    xy_y = C_y * sin(t);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const&, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T t;

                    lp_lat = C2 * (t = aasin(xy_y / C_y));
                    lp_lon = xy_x / (C_x * (1. + 3. * cos(lp_lat)/cos(t)));
                    lp_lat = aasin((C1 * sin(t) + sin(lp_lat)) / C3);
                }

                static inline std::string get_name()
                {
                    return "mbt_fps_spheroid";
                }

            };

            // McBryde-Thomas Flat-Pole Sine (No. 2)
            template <typename Parameters>
            inline void setup_mbt_fps(Parameters& par)
            {
                par.es = 0;
            }

    }} // namespace detail::mbt_fps
    #endif // doxygen

    /*!
        \brief McBryde-Thomas Flat-Pole Sine (No. 2) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Example
        \image html ex_mbt_fps.gif
    */
    template <typename T, typename Parameters>
    struct mbt_fps_spheroid : public detail::mbt_fps::base_mbt_fps_spheroid<T, Parameters>
    {
        template <typename Params>
        inline mbt_fps_spheroid(Params const& , Parameters & par)
        {
            detail::mbt_fps::setup_mbt_fps(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_mbt_fps, mbt_fps_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(mbt_fps_entry, mbt_fps_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(mbt_fps_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(mbt_fps, mbt_fps_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_MBT_FPS_HPP


/* mbt_fps.hpp
DDgRAFlmGn4AXLXUBPAC4NPpBkDoYeGYtAwXlBrm6A6AKF/9MS6qsHL/otPox1t/gZMhTm99h4OdLm99hoBq3vps4fR4673CCU0jD5yxT4Q/6K0/1snJAB+QzHDhczjRd6P0uaQv1ixBgL/oDHZh4GgJ96Dvcunzoe9dmRM/+mLSF0TfB1gTF0t0hxNAf5cIkKzZp4HvSIXpEb5YwEnV+MNl4i3Y2FAG3KcA/RhwrwI4GfADBdjNTeEeBXiTAcUK8CcGRBVgEwNuUoCHGNCoAN9jQIMC3MSAGyWAOpTCpw6l6FOHWiF91KFukT7qULdKH3Wo1dJHHep26aMOdaf0UYdaVip8UZYt4JwNTWG2f9EY+gkvxh9nuAx/XOFz8Aca00pARacnfB3++MKh2J0CFAzPXQY/JDyq0UXC42xyucC1IF4F6Y6r4XSrKZ8jpI/yWSJ9lM8J0kf5/Hut8FE+F10vfJTPPdJH+XxFYlI+75omfCTRpTVpXjiDqwJdxXKio4yVVqIrgOC1AuxHz3qaSc8AMzbuPbdm0mwToDSTGX8/z7ea2PTJOnq3c9JEl+Ms+LsI/hbCXz383Q9/t8Pfb+CvDf4cTo+LHq3nT/NYP7en6y/T88V+/8ZX9L/6vqgv5f7fK2o+pSxUFtOyg6dTXZwfrjWiBkthOtPsYYPKjRe44ZzoaIdDbvwkaJ/Xx6cIsF6A8GjpZi2tjc3k98eGQqLGJVXe1wwfjb8BYXaNdxvBpB/p8oArOBE2JNO1Im3KX9PLHUnvd4yXeS1oHsB5nfl1yOvcozrN6/Ff70Fek9IvftlSvv7mHE7zOkzzbX+naZ7XkzSNXXFQ5t7Stf7fSxZ+BjRnMz8zkJ/ZnfNzXM/5ASoeYebTg60yngXy3A2yfksX6wkP8ycOJrMhxgvfccMVcjYmW10I+2IMdlwL4D4Exvn08ucgXtf6j/mU/xeZPjcqP7+Ykg0tkZZeWaJJdt3QuD0bm6izXzRvoubyJmr+j3FDRN6uWycmPJvBU9MLXQlwLRmFS8RhWbx/QwevYwCx+adqBX7SvZqDKVwC/7Jpll//SAPE4Vm0rvk2HupSzq6413qoW8y66PWATdfUOJUScbxrSWXbD2QqDrlDSs9YeYzzRzyJ0heQcZ5JhQ/DUin8TXGNv89A8Op/7kXGRMpKmsYxYzvU8etr92hCL779h8xLMfPyKKAAvjXHpZKX+CJIauN6TCpPJvUgePVZvemOFiQ1kZO6UiX1bZXUCpHUZE7q9LBNtv98j0wqhyPNhUiH+izzQD5qr6rfbOlkvf/687ze/xPZDXHf8iux4O9SPkDns8p/IGJY6erLu2UX3aeJA7BstYlhPGXUZf8KMT3gJ/FL4Ee9KtDo/gj9smN1Gt/zfMcXb7/A9n7bym2WTWSxhwytpg/rE3jDbmm63JPIO/GwLGyEfRjd6YixqmBvxt270IzrZtx+SNKpzp0zHPHykqZsjrDdEuHFgRShl0I8ViFutCA+yIgeRnTxBZfw8Xz/DLZuE4nPE3z7rKSAgdBLIKD3ZgmN91XIkJJxu0YKrg3qBEOdXtANGzZzvkej3vVBFfauH2DvOkMdcl9/Nx1yXyue1hgLQm8sllR4CrmA2/B0ckGyYVd8BpvtIHYqYMApp4m/J+6VgOeuYYBfAjKTMY5gwH/euYVpfAv8SSjl9GLZ9fDVUnY9urbTLTfuqh/+kaKqHqlv/j530wCPC3eDF0rhzUxww+1ECHJf/2CmeMGoEQKhF6FMvRiAYCSspOlt3moedbUcQgJ3WU722Vy2nwhIfW5/Kw4RgugpQFQ8j1viEXY6+mQBef0BSB/c/3wA3G+AW8j/7x3QcXg=
*/