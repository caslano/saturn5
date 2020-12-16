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

#ifndef BOOST_GEOMETRY_PROJECTIONS_GINS8_HPP
#define BOOST_GEOMETRY_PROJECTIONS_GINS8_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace gins8
    {

            static const double Cl = 0.000952426;
            static const double Cp = 0.162388;
            //static const double C12 = 0.08333333333333333;

            template <typename T>
            inline T C12() { return 0.083333333333333333333333333333333333; }

            template <typename T, typename Parameters>
            struct base_gins8_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T C12 = gins8::C12<T>();

                    T t = lp_lat * lp_lat;

                    xy_y = lp_lat * (1. + t * C12);
                    xy_x = lp_lon * (1. - Cp * t);
                    t = lp_lon * lp_lon;
                    xy_x *= (0.87 - Cl * t * t);
                }

                static inline std::string get_name()
                {
                    return "gins8_spheroid";
                }

            };

            // Ginsburg VIII (TsNIIGAiK)
            template <typename Parameters>
            inline void setup_gins8(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::gins8
    #endif // doxygen

    /*!
        \brief Ginsburg VIII (TsNIIGAiK) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
         - no inverse
        \par Example
        \image html ex_gins8.gif
    */
    template <typename T, typename Parameters>
    struct gins8_spheroid : public detail::gins8::base_gins8_spheroid<T, Parameters>
    {
        template <typename Params>
        inline gins8_spheroid(Params const& , Parameters & par)
        {
            detail::gins8::setup_gins8(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_gins8, gins8_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(gins8_entry, gins8_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(gins8_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(gins8, gins8_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_GINS8_HPP


/* gins8.hpp
POqNGu1neqL8vDvArz6zl11h4b0TcZbhUd7RiPFRR+MG6mhkqI7GP8aJ3QbeznhTPZyXrUXAABbNYmGX8LBv7qWwt5jDrlVhv9V42Iia2oYQm6nzsWWao004i8SxTTdyO3U+ou3OLimhMN1RSfGm0D3wnXkDgnTnqZ6NrTz6LnIobK2nkbglQTix++5m/tdBQ19hLvJlzrAOMAaDNb/LJXlSX4KNkHehuv7BCQ1I4hqQFzWTlaKfl2KUV5Vid1WK+8bIUtyn5gFLK6kxEeoTZeH9VA8FvtUceLUKvNowpuRT/6ZzDBJiZeaN5bY6oiHarsZK0MnKSKcLKkhJFMzaKYrRKYrRKVaro2hEW3NyNvREHl5K+iC830OqvStgM36ec38BRJ1jFznu5MU1fA/l+M2U439QOd7nBpnjTkJQf0WcAd+zlbc+meICKN5nY3VFn9xw+ppx01RL21YWOtXwjqZHcjmq1U9sBHQbG6GLO+l+JtAMduJgMJeu8muSbrRZur+Mpl/ugssQ9iEWtvAsCpvHw874OkTKxiCs7yYfo7uO0w1ldBPMdL2I7mKRyAS2Q0sUbzoH2ud8dZRPjBdRw/vQT8LDxGGNqrxFYAZQLDN/p6FsYFUuYhd5PaBWarrTTv5yAt5xkI1R08gklu60ID/bkVNsbsxTdNWMrrA3ZeKrPBPtX6mCulBl4g/X8zNebKJEu0BWXu9Ki+EIxnKoq6g24lx7HdVA9vBVOze0iM+zsZva6FAGHVB9QRxQ7c3hrx3QhdrGhZq+O4RQoxsRqjXesiX0sZaEtQrpVPQ98J2ZRbfrcInGNzCZxdAdoN49nLbC9jIFfFRfUU7JIEYkvM/qe9ZLG1tJZIfKytXfMal7kNReLvXmL0NI/ezIkFL7xrJWZ7vi59/PirC5Arx9kG9jYDF8x2O4gcUwyhzDgNAxiA1VRb+D4ob5hOza9L1P129+wdpynjN0C0x3a+EfmOZwjJtjOhIok4OSOcjOfXcfMORhe95Std+lSukilYdR14l5PJ6Bep+HmQwe/iwe/vO/qzLQw782QoXvpsL7VI9s+gKzHWf80jm/exi/m8z8CkeEkGeRFlrRubVq/73fz9S9n3uohE0HTG/upLqnqAsQnVzXZVT0wPxd6FtK8mWL+xx2hsivv10bLN/v0ucJuF/pI0yXbTL4n95n9vf4Vvj18cJb9/LxQu5dcuRuxj8n8C9VhMbPE/iMP4fGTxR4y72h8ZcJ/NkLQuPPE/gXdfn09FR8bU7fn74w+727gtL72T2c3/N3h47vrwJ/y32h8Y8JvKWR9M4U+CsbSe91Ar+6LDS+j8CPnxsa307gz7k/NP7IPI5/pJHy+kzg08tD5OdH/wjQn28D8tdr9scG6FfVN2b/eI/Z/9Ne+E+2/Aj/VQD/z83+j/4eIN+egPi/CAj/JfMH73+cK+6768h3C2Thh/PEbOtVYtAaxv4nySSJMzl8EDsokln/4irzDgo1x5ci9x6xprbeswfbgxlcWCunjfsMt1+nhN1RD5TvPTeTL2AvZGkm34l1t4K4uay+pnIfZKI+jcOvBD43QHYnyd4HsqOHEM9wbM8AuhIbQlG24JRxDBd4RVrUiV5jFs5+ph13i6Lpyotm9AFZvuOGhVO+bJnk/rv1TRks21ozJzuOL2b/87xsQ4RstQRe47mRzFNGTZh+G62eetdkxoFtr1Bb0jx78Jvn6vbcWb11EihHorhEzW6Sg5dbOvMSEQviu8DXRNe9Tt5b0cFjCKVawWF+y7WUwP2PFYb5qOg7Qs8hc61tVyGK7mxedE/uR61KJMyyIaJW6dWisfnQHeVqQiAl6La2VOZlxRSp3BBN6j4=
*/