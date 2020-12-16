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

#ifndef BOOST_GEOMETRY_PROJECTIONS_MBTFPQ_HPP
#define BOOST_GEOMETRY_PROJECTIONS_MBTFPQ_HPP

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
    namespace detail { namespace mbtfpq
    {

            static const int n_iter = 20;
            static const double epsilon = 1e-7;
            static const double one_plus_tol = 1.000001;
            static const double C = 1.70710678118654752440;
            static const double RC = 0.58578643762690495119;
            static const double FYC = 1.87475828462269495505;
            static const double RYC = 0.53340209679417701685;
            static const double FXC = 0.31245971410378249250;
            static const double RXC = 3.20041258076506210122;

            template <typename T, typename Parameters>
            struct base_mbtfpq_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    T th1, c;
                    int i;

                    c = C * sin(lp_lat);
                    for (i = n_iter; i; --i) {
                        lp_lat -= th1 = (sin(.5*lp_lat) + sin(lp_lat) - c) /
                            (.5*cos(.5*lp_lat)  + cos(lp_lat));
                        if (fabs(th1) < epsilon) break;
                    }
                    xy_x = FXC * lp_lon * (1.0 + 2. * cos(lp_lat)/cos(0.5 * lp_lat));
                    xy_y = FYC * sin(0.5 * lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T pi = detail::pi<T>();
                    static const T half_pi = detail::half_pi<T>();

                    T t;

                    lp_lat = RYC * xy_y;
                    if (fabs(lp_lat) > 1.) {
                        if (fabs(lp_lat) > one_plus_tol) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        } else if (lp_lat < 0.) {
                            t = -1.; lp_lat = -pi;
                        } else {
                            t = 1.; lp_lat = pi;
                        }
                    } else
                        lp_lat = 2. * asin(t = lp_lat);
                    lp_lon = RXC * xy_x / (1. + 2. * cos(lp_lat)/cos(0.5 * lp_lat));
                    lp_lat = RC * (t + sin(lp_lat));
                    if (fabs(lp_lat) > 1.)
                        if (fabs(lp_lat) > one_plus_tol) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        } else
                            lp_lat = lp_lat < 0. ? -half_pi : half_pi;
                    else
                        lp_lat = asin(lp_lat);
                }

                static inline std::string get_name()
                {
                    return "mbtfpq_spheroid";
                }

            };

            // McBryde-Thomas Flat-Polar Quartic
            template <typename Parameters>
            inline void setup_mbtfpq(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::mbtfpq
    #endif // doxygen

    /*!
        \brief McBryde-Thomas Flat-Polar Quartic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Example
        \image html ex_mbtfpq.gif
    */
    template <typename T, typename Parameters>
    struct mbtfpq_spheroid : public detail::mbtfpq::base_mbtfpq_spheroid<T, Parameters>
    {
        template <typename Params>
        inline mbtfpq_spheroid(Params const& , Parameters & par)
        {
            detail::mbtfpq::setup_mbtfpq(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_mbtfpq, mbtfpq_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(mbtfpq_entry, mbtfpq_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(mbtfpq_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(mbtfpq, mbtfpq_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_MBTFPQ_HPP


/* mbtfpq.hpp
Q20GznZ/4W9/O5T7Cw92oddXpb+6S+wYfwNKQcBeeSuRsOxItJj2I45/x9gOE/sRfZ2s/3mN3A6b7VT3PzdSgxwevxHa6WXQOo3dhs2QsjHJwFXUF7DnYC5fNZKs/FCVbzncXqLjSKVzugWmD/GZvMW2+/FULZ3RZdjeTBFui9OEJg8y2NCsCQMyb7+ZSByIuk4Sv8atBDGXVIB8MYnckoY9WMr0XR9Qptm4RD95ORNJkqahT0BWSQj6/aSHBJkij7xNiH0dSEgtaALrJYDV08zCl2Su95O4qhk/t95f8mZ2wBlBcxAaNeIgAlyRccSV3Ezw220mUEvXAF3LqsHKmx+nU9QoAFETzEM6Yfw2XtbiUnwXT4oNvxIbXAkkKvzsNMQSpewxCYhfjmlJR63M8tnXX5JM2Pl+h7KOwb1emaYgN2AGAd4mqq9IaQ2IW3dgShMIY0/DLlpJthbHbGWbDquanOn2u075O8XKX9DEX/AA+BNnrwfBX/JIdVfMNFKFfXz+X/sGCTN/XNhCXfEm+6n9LT0a7iXARQMN9lABUFlO9ghfckrzqH8Qc0n3ElLTdQOMhqK20FqYCzzzLTDjqC0T2auQVgazvfUvASI6e3nrK53s9Hrry8G5DJw4X/CunCd8GeCDaetM0fWrpYG8wHgoJOLnVA4CaDCfzwcQeoIB9cMZmIAOYqoBPEtYMtAId4nwT4WmsaumHwXWVRdo1At3iYCMGhlrQN2uTGHCZAs9XydtuiZbVfIAVikkWoXX2pfmMnmMdjNgINyJ8N5EnfroIgS6FFAj4EXxE4kGZIAEwUhHAifouEpsBB+EjezYD5kyRTkhHqDEyHN0fLCRQl48VxUh+t1f3nl1T79k1akX3qVWnKqorVSe4ChU3O10wONEXEX05lWq9tGqzrSP5CAQ6lT7KKTP2WCzKdzIM4HMy9WU9Tk1Zf0aKGyL58Ohd0smrwAm6YS9TEDKouBRw2ux/tkjxsnqLUz+Z5fRyaqV/D/Wa/C8ARDnaHsfEWeeSh/n4Vc7EvKQ8UMITcq2cRbLBB4CFH0ASLUyxlMB1zND7tiHTlOhulscrBc+xqDb0Ibpbt1Bh52Dk1AluTkmVsg8RC7YROkDOeST7RzweaXPpKE1yJKDVU1KWTxHBZg0zAaZUBHCNH76a0C11q+6GxFMCpDFCPKcvI0knVet5XSFtaHEKoyMIiqey0k8DUmgX9z7AJ8kBEYSeDF5zsNmLmjxpP/05URCwVprAUafsAOMVPAwmb0dDxtEYTEFuOb8U9TISGw9v+XWc9mlNo2z6ZfqEJlNTJo5QoTNkAqnNx9cKAP/D7Wl5Hp75l94LFVGE82rhRXu9y52Qxff6CZTdr+CBuC+7K5MR9Q9H/6Fa1hk18up7Hr1yGo/Hxj+8S1KX78qAep+7m/9NjMd+wis/w0xrfq1+evT1K+dy1E5lv6r9PSBh3Iksc7xKYXzH8n43egzrSP737uYCMj4JjK4UNrKL9xTA51PbmjSCTf1pxnfddMGz6kPaerSu4pKo0FmJpT9gGVPKBo0kdgtXtpc72CTvawBa0DyAXKzBVIAkFUWiB8ga8yQUKH+0k7gHuBr0c9EUd7jPMy3aCT9eOtRAR+doGCBP67wqfijhcvwxxM+J/YjgeAPL8WfYHjWMvhB5sNno4uMGs2JLwFx+fulLC4r4zXg275E+q4C3w7lqwDfAwrzbAyrk75SjKd8J4Fvm/IFwHetinc4+J5QYTkY7zThi3JxgbOKjAW2oQsnMfcC1HvjA/AvwmGq+MqWDno7+dmgC99OXgc/9HYyUGsnfkkU8d0lgIVNsHgEANPqTIAFALjEjHEOADabAVMBsME=
*/