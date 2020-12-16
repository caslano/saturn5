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

#ifndef BOOST_GEOMETRY_PROJECTIONS_HATANO_HPP
#define BOOST_GEOMETRY_PROJECTIONS_HATANO_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace hatano
    {

            static const int n_iter = 20;
            static const double epsilon = 1e-7;
            static const double one_plus_tol = 1.000001;
            static const double CN_ = 2.67595;
            static const double CS_ = 2.43763;
            static const double RCN = 0.37369906014686373063;
            static const double RCS = 0.41023453108141924738;
            static const double FYCN = 1.75859;
            static const double FYCS = 1.93052;
            static const double RYCN = 0.56863737426006061674;
            static const double RYCS = 0.51799515156538134803;
            static const double FXC = 0.85;
            static const double RXC = 1.17647058823529411764;

            template <typename T, typename Parameters>
            struct base_hatano_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    T th1, c;
                    int i;

                    c = sin(lp_lat) * (lp_lat < 0. ? CS_ : CN_);
                    for (i = n_iter; i; --i) {
                        lp_lat -= th1 = (lp_lat + sin(lp_lat) - c) / (1. + cos(lp_lat));
                        if (fabs(th1) < epsilon) break;
                    }
                    xy_x = FXC * lp_lon * cos(lp_lat *= .5);
                    xy_y = sin(lp_lat) * (lp_lat < 0. ? FYCS : FYCN);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static T const half_pi = detail::half_pi<T>();

                    T th;

                    th = xy_y * ( xy_y < 0. ? RYCS : RYCN);
                    if (fabs(th) > 1.) {
                        if (fabs(th) > one_plus_tol) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        } else {
                            th = th > 0. ? half_pi : - half_pi;
                        }
                    } else {
                        th = asin(th);
                    }

                    lp_lon = RXC * xy_x / cos(th);
                    th += th;
                    lp_lat = (th + sin(th)) * (xy_y < 0. ? RCS : RCN);
                    if (fabs(lp_lat) > 1.) {
                        if (fabs(lp_lat) > one_plus_tol) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        } else {
                            lp_lat = lp_lat > 0. ? half_pi : - half_pi;
                        }
                    } else {
                        lp_lat = asin(lp_lat);
                    }
                }

                static inline std::string get_name()
                {
                    return "hatano_spheroid";
                }

            };

            // Hatano Asymmetrical Equal Area
            template <typename Parameters>
            inline void setup_hatano(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::hatano
    #endif // doxygen

    /*!
        \brief Hatano Asymmetrical Equal Area projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_hatano.gif
    */
    template <typename T, typename Parameters>
    struct hatano_spheroid : public detail::hatano::base_hatano_spheroid<T, Parameters>
    {
        template <typename Params>
        inline hatano_spheroid(Params const& , Parameters & par)
        {
            detail::hatano::setup_hatano(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_hatano, hatano_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(hatano_entry, hatano_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(hatano_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(hatano, hatano_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_HATANO_HPP


/* hatano.hpp
1hgaY/yyNYb8Xhux0zFZMh/XTxLKL+CjF7OnSMgxe+oX5CwbdL3L7Kl+V1DNnlJ9NU2nGHqVo2s61TYo++2J75woMugtdhl0+khc90EQMuh2yOUf6EgXItKUYzhwfiWnfJBRxRs/sMdaebBkzG/dJiiP+Dlbn7T5oe/z03T9Xo9LO7nZ0007we5g7ZLMRlJzcRcNpGaWzWMTC/Z78D8e8VB1P8w5zTHp1XMLrz2NH4xBRhX81ZYPLdSjQSHqPH8XDFM/SCevpj26eFZZzRfk8Ou+2bza62Zj6T/10GxMZKszDQLWE0Trp6Y+Jx7ZKlCjnR70wpcJiC4ab0I8iM6eRRGqCp63q31gvI0ilHAmG950YA1dqFR2peLTtKa3naVmkIxelFmc4dv4Gr0o+3B6hrTN2muMXpTVNn+/E90ZieGwEUcz3bfUi/Cl9aIOBFqqmBDnSQSFKoKLJIIhHMEsZwQNFMErtAc5zCup9mEOnTXzds8E5gT5aTSqLpOY7lotGlVWNCMRTRkFgkbVs1fbNKrayfdC+JJGVTsDh95/tdao+iI8ukxydvYr7SrzabSrLhjH2lU5WruqXGtX1QvDf7vaaFdZPFe/h6yhgTN517um5VnaVQdl5ZB7e0a81/lsmlbOwr9GGKi72mX2/9a7YGC623B+nH2Y2DZKtLAOtQOPnmSUnwBwV36ysAeONAl0Kj8BIspPvRt17vI6Rp3bJXE3rXIZdfq/qweAWu8/NOo0jZVRp9U+6tBHYtQONeoYSHCHjpQSmNz2jkPzaT5Ynz9k0UB6DVtSTK/hNWfbS+spSdDTK40+kJWgEtBOroTLHuB5CXDjSpeZeQgBUmebdPx1lNFQAqAHDSUTwXaJoNiNo++/Q40OyJt99gy7c4RNQ+lVZZpv24S9pvn2/vb+9v72/tz0Ucqc5yHVPISNMdLlMbXTWidCjnXJv2EylmErLWpddJYvdpKKx9mPP54KmJ3NkUAvYrcWBTN2n3sQBYvp7erw8t979IXjg8y+BomB0cxb24Nbo3CC4RXNet6iBN7g8HsdRnrFbCRtZTTsHl47x6zXDRjTa21sIYANEALm9s9pO7IesEVTYnP1pZksSQduIMfAaOmhHbNCHjuTWYyIWbTmZe3hDPNs6jPOn6R5ZLLNb7eSPR8E4CppIgI1p6llgbf2BCUQPo0N6K4DRwp7tcRUTtwdCu4sItqU4lyKzLY1ma9QnCJ0Idq9UMWgy6aGRFZf8aniWTJYXaRetyRErma4qA4BUrToBFvq/ACKjd9l9Kn2hIrMri5M/6r6k0+omi2ujxf4skoXu7pSb0rMxfIjxKjTnxrNdOV6M5s44y09dxqlaM1vaFnH8moTu0p57QCKXJ8cVXKq5GNxjvHpmjGFu2RMVwgqvM6t8EqacU/dmh7aUqFKTC4KPJHdauZIeaxO4zjr5qL0uRrK1nZsLhmX9ZstbgRkQ6Pn/TFI9auY51+RaZJTrQ2UUy84c+pgYG4BJmUWWy1ceqaq2yjcmJhntu/8Tusy+/a1107qKaTfOBQdD3yKk0q2qJgoEwp1G13WQpdqlnwMm9XudSa7bnVdE3XuelVZfKbMFf7P/ez6D/kiXxAo6GtECNohQtAwo8CzqCg2N8BnFxHqmztbY3NFjzACES2HF+qGL+VLPdZLSQE3/cwQ238cbuw/vt9XywfssFttoD0nh8h1njdD/lkbfRRLevOklX2pnlpZDT4232Ja2dY3dX80JShREDGpheYzXv+iDAvFToiylXep3GrHl3PMcmAY7vzL3rbwFzBXtcLVE0uJq7CTq6mGqxsCNq6IJH4W2cSBubzcu8QAcgYSoHaOApiwWGYby6U=
*/