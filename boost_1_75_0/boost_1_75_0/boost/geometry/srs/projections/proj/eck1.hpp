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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ECK1_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ECK1_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace eck1
    {

            static const double FC = .92131773192356127802;
            static const double RP = .31830988618379067154;

            template <typename T, typename Parameters>
            struct base_eck1_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = FC * lp_lon * (1. - RP * fabs(lp_lat));
                    xy_y = FC * lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = xy_y / FC;
                    lp_lon = xy_x / (FC * (1. - RP * fabs(lp_lat)));
                }

                static inline std::string get_name()
                {
                    return "eck1_spheroid";
                }

            };

            // Eckert I
            template <typename Parameters>
            inline void setup_eck1(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::eck1
    #endif // doxygen

    /*!
        \brief Eckert I projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_eck1.gif
    */
    template <typename T, typename Parameters>
    struct eck1_spheroid : public detail::eck1::base_eck1_spheroid<T, Parameters>
    {
        template <typename Params>
        inline eck1_spheroid(Params const& , Parameters & par)
        {
            detail::eck1::setup_eck1(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_eck1, eck1_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(eck1_entry, eck1_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(eck1_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(eck1, eck1_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_ECK1_HPP


/* eck1.hpp
rQHeplcwXW65GfqRDeDvEQo54Z21IY2vs12vnogskGQ6AXh9SwVHWlBI4yXLTyGeaFIgQq+K4EzGDBdS/RqkgQ8/WUgDH/clDsdvyU0Cgo/lMiHDkaGMJ+dFcEF/hotgZTCeNJzIAyqpP2KeiJd9jt4/OCH/IvGhFQb4sHUEH2RHVG8/zbbxXxB7vriS2JpFfrhF13tu3XBBhG+CkdHPvBFmXGoVbnzRTihBn42+jvtWOkh9w0dAjE9oPPI2ABe7nhj/Yqe3I11ca7+zbyHx6OTVSSo4qbW+EU5ue3iDTeMpI/e9QPsjY1B96Uolp7+nZ5pDtrf59reLapeEGK/LSxKfddsC+5a1RH7TrlPP8yO0zQnT1eJZV4uaU+yxeMbVZ311y7A4Cc0GExVGDtTd/YwQPEn8aSZaql8KuYWCZ05Ieo+Bdl4w+AjlBeBJ2QGiU45LQ7VQcbci/ksnvRsMkQ+FqtJK49HehcUF5Q+yUFlUcuAfpteEIpnnJTt6Da9B0Y2zkrN3s3izr2YHYfPls4LO4pf8zjiUsiFqOK+/zjpzRZkS8XbH3mIfZ0v+DNwgfPAGDETkPFApy5/Ij1eES44VFVTYv9buDbkJgj+7GZ1FTOhalkhVv393obnvtu8xu8Fpta/gTHCpHacZoBeaBmhNISx7OcvlTHKZPQNisFu+FN0SAQqEnNJ9nzR/wGLAWpiLvMUR8V2J/Pjq
*/