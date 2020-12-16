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

#ifndef BOOST_GEOMETRY_PROJECTIONS_COLLG_HPP
#define BOOST_GEOMETRY_PROJECTIONS_COLLG_HPP

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
    namespace detail { namespace collg
    {

            static const double FXC = 1.12837916709551257390;
            static const double FYC = 1.77245385090551602729;
            static const double one_plus_eps = 1.0000001;

            template <typename T, typename Parameters>
            struct base_collg_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    if ((xy_y = 1. - sin(lp_lat)) <= 0.)
                        xy_y = 0.;
                    else
                        xy_y = sqrt(xy_y);
                    xy_x = FXC * lp_lon * xy_y;
                    xy_y = FYC * (1. - xy_y);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static T const half_pi = detail::half_pi<T>();

                    lp_lat = xy_y / FYC - 1.;
                    if (fabs(lp_lat = 1. - lp_lat * lp_lat) < 1.)
                        lp_lat = asin(lp_lat);
                    else if (fabs(lp_lat) > one_plus_eps) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    } else {
                        lp_lat = lp_lat < 0. ? -half_pi : half_pi;
                    }

                    if ((lp_lon = 1. - sin(lp_lat)) <= 0.)
                        lp_lon = 0.;
                    else
                        lp_lon = xy_x / (FXC * sqrt(lp_lon));
                }

                static inline std::string get_name()
                {
                    return "collg_spheroid";
                }

            };

            // Collignon
            template <typename Parameters>
            inline void setup_collg(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace collg
    #endif // doxygen

    /*!
        \brief Collignon projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_collg.gif
    */
    template <typename T, typename Parameters>
    struct collg_spheroid : public detail::collg::base_collg_spheroid<T, Parameters>
    {
        template <typename Params>
        inline collg_spheroid(Params const& , Parameters & par)
        {
            detail::collg::setup_collg(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_collg, collg_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(collg_entry, collg_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(collg_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(collg, collg_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_COLLG_HPP


/* collg.hpp
wffUxPD59Cnx+jt8PiU+KfxOnBp8T0uaFnwnT56iv6fq7yb49LC+6eTPyCwtLS7iyHLppOX8lRpiTEmixZWkWrLMySCtoVuMPG9XX+5vlWKNoQwTh6BVPTkSkhOnTA6/kxPD78nJ4fe0qUHMoMuA7v7aK73+gvQl6SvS16RvSN+SviN9T/qB9CMpGxr9xHdYzPQpwXcSEhB8T5sWfE9Onh58T0kIv6fHT9bf4Jc3FtWV0gxfSS7RMatPKPFT0mekzaSfB8izw6NH+Gt5c/LmhsZ9qu+GynjCmIjn4fymDM4OPo6Iavs4+qUyyvZfJ2g/aEfyvAGBtiEBs3xaYBH+KzDbjwRm+2TAbF9Lw6Z03Ocpr9cd0PEyQcfuAyUd7f5N1LCd6V9f1sB7KWARfQZm9xmY3ecYbCJ5UylvkShvVw2rEjBJG2A2bYDZtAHWQT/Upw3HV0q0y1ZS2+jfG1Wr1+kljQZKGhk+SQ74pMK/C3AlWqaoWL+QtCnOkcLzBvrT2IU4pm5npobtoGKwHA1LELC9NexiJwYr1bBRbgxWo2FHiLy/1rDX/bxbQAsd16ovWFbJBlzUCS4ffRF+6z/lmG6Zu/tf5rf+J3y2f4H39UtdLtXkp3Tcr4pwiwqqS2ujXYZsDNWYW7EFjkeLKlbWd9gpkc8hSBvP6ktMzcjPT2bso5Er2yqpTHfpv8MB7Sie8SJ9+d/ql/qs/4QLGjHOW8Almf8C99TySlXMj/lXO6i/QLzblWH2m7XlA7fvysr+tu7V/v+4sqK/7Xu1/weerNBrHXBq/+9cWRmXiHRr/++cWeGnt+bWgpYb+rL5Of8P/qzvI+G39vD3YA4M/dYxfI8l7UAaR9qRtBNpZ9J40i6kCaQDoNVEvltzif95n3Z2RTXdWdLC1xitfY1JfLdc29u15fqhgf1W4z0p8KQvB8z224DZfhuwCL8NmL2uCsz25YDZvpyASV8OmL1eCsxeLwVmr4MKvCN0fwf0AhbhGwKz1zKB2f4isC32pcO9wi196dmRfuKxgZ9YV1RRX2aiCk2bi0eYmIPYg1xeHz4WZ/dOHRG9R9nGO6G/wLMqk3smTh/ROl76ahU7Yw9eSVFtA2Bxn2/4vtNxETj+OzorahrrDVLEmn98BB8Cs/nQwP4E3rPw0mUKWARvxkfwJjDbBwdm++DAInzw+AgfPD7CB4+P8MHjbR9c5L0cWI+evEdiN2C27Ii8VwLbHbwBBibkScCu1nQ5SNRx3QgjYwZ2o4b1FLCbNKyXgN0CrJJ6vxN13KHrWCPqkPIJzNZHBvY38p5DeX0cMUYaNlDA7gf2ALAegqZS58Xbsi3yPqjbd5bfZqEHv6e8oQIm5T1+C2IiTb9LOaNOqmKjZBAWaS73lUZnS7l/jHboPIWUHASX/Ctx5Z6tjWGs0X8sUcMprbCUGX9L8IsafHwp509YbdDn0powDd7TreDpFpg+PW/qD0JdHJti7yI5xHlx2caiEi7LRC1oMja/u/eFGN4yDkb52ke10c/iMuyUMlmtr3/lGQ48kMJM81iNk8/sNgcvTQn33M5oC8/s9qLpHAYjoMRdBDW1vl9WL/YXvkx7g1y+L1hY1lY/ipaB06wbopzXZDmCpptMOShtNpnVN6epqe9NgxduVVtT7e96D0qMvHf1LTGenLauqfZPRetIplH4FVXBOfLxgk5Wnxqrrf5E4IITRf3NLccwn75X4DpTZ2JH66zjJx1sdmbQ9M3G5XxIhIxK+RwQ8byuaJU5R3Ex8LTKyvnAlbkTt+VYc2y8zOeV4CoehlTJcnHTfAcpM99fv5BwXTCP88IxRv4kHcyEHY6rXppoMc8mRMyzCRHzLDB7TjU=
*/