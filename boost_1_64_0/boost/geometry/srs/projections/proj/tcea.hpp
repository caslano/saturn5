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

#ifndef BOOST_GEOMETRY_PROJECTIONS_TCEA_HPP
#define BOOST_GEOMETRY_PROJECTIONS_TCEA_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace tcea
    {
            template <typename T, typename Parameters>
            struct base_tcea_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = cos(lp_lat) * sin(lp_lon) / par.k0;
                    xy_y = par.k0 * (atan2(tan(lp_lat), cos(lp_lon)) - par.phi0);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    T t;

                    xy_y = xy_y / par.k0 + par.phi0;
                    xy_x *= par.k0;
                    t = sqrt(1. - xy_x * xy_x);
                    lp_lat = asin(t * sin(xy_y));
                    lp_lon = atan2(xy_x, t * cos(xy_y));
                }

                static inline std::string get_name()
                {
                    return "tcea_spheroid";
                }

            };

            // Transverse Cylindrical Equal Area
            template <typename Parameters>
            inline void setup_tcea(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::tcea
    #endif // doxygen
    
    /*!
        \brief Transverse Cylindrical Equal Area projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Example
        \image html ex_tcea.gif
    */
    template <typename T, typename Parameters>
    struct tcea_spheroid : public detail::tcea::base_tcea_spheroid<T, Parameters>
    {
        template <typename Params>
        inline tcea_spheroid(Params const& , Parameters & par)
        {
            detail::tcea::setup_tcea(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_tcea, tcea_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(tcea_entry, tcea_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(tcea_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(tcea, tcea_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_TCEA_HPP


/* tcea.hpp
5AcZyXRCUmBW85ZTgPyz4JOOKvkafyEp2RSptn2zhgbgKB3mSQyzN8GcaMK8HGEmuHE/FD3YqR74Nuh7NTwOCvmQ9Ei2MWliKWAsGyoQi9vE4kMsK5DSQx2qvhCqnp92XEy1rgrTDWYEKbM7l8FPIvDvmbW/5mQLHiFVjbZqjsMhSBHnP4TyTzfzX3yyfQgy0Dj9YDrOuxaKLz9qysXpx+pfdn6//P69P0d7L7XUhSuUKn+BaWaqeWGtVFNVx+r1CKloJkk/R8I6myYFFXESR3SX6goq4nCKYLuwuxCuSw66sjgadPfPVixzhRp0n59IW8QPPHgqc5IQpoXOPo19mWK96BMXvY9QwJUxz2oGHiTgOSbw2wF4w0SPPBBeXB5h/sWfJVfjyxR1xHt4FffmBKViIKbCc0WWIhVylJ2riHMtE7nsk+4hItc0FZJg55rGuS4WubJZda44iZc9XNRsx6LewkU9axYW1WMW9eE8KOpUSyoxRE6ldeERsY1xBwNJJSBTTCAXIZA0i3U6AroCQWZoN0F0Ims5Q9x2nQNZKQjxTXeUgfeA0uMIMvBrmNx4Wl85Uf0A4zjvOgeqHzsBcCAbFwRnM8xAswQ/wsBSnAi+AIH1Nyw2E7Sdp1jsg9FGOx1Yi2+Md3mp/9eR6ZerYJoy8KVLnQXR/2civhvdZv8/HvCtk4ZVNvZwSY35W08m8kfHkr+RwZ1O4NqY5N8P4MK0daozZlfcbJGSF0U5ayZ46ISX46OFsJ3yLaEGQJYI+cbcaBarPHSyFNDeiz62DCd8maG9MAbF3QWoWlYY+GXK/EE/R/5fSvz/OvMqF3dvMdAEAzu7xObTS4xB1sAd69urlbrXStWx8oLEp2fwdkRuGZQqao9/sXc04FEVx3vvLskRAhcBIfwIAQJGQAw/ahC0l3rqYaOcghoVNYrVVLFEuUD8QRITNDGgCKhoK6JFi9WqrRYitTYRK6DWomjFVitapZdeVVSsGMDr/Ozu2717gUOpba3H98h7+zMz+ze7OzM7e+3ODoB+zEBXEtCrLAPoZycQ0IFCLxYOrAratPIG/lh6pab1EICNYbCTAU8iwEeZgJcx4PW2NDv01u2wA/NuoP37RPM6h25ooM+99pBJNOaOTUXmy2T9VzWPOQPZKEDG+T/kSjolxeiX48UQbNtEiqUnllqoxwybDgYv5JG04WQynjpdKbaRO0Ay8HZr5XokDQiB0y8IU/qhyWgzEKEydLqSoM51Kd8BXD7brXynHC/H90Au3+UKbW5Y8yVonkm4eGZH3awv47ptNi0HTFzvHUcYAsKIqyy2BSZOmi34s/Vy+DTPV9AcRfr+jRBChqwzgee44x7MuPsQ7tFmp/kB414sbbnduaQf3XupeJNLxk+0HUdH4L7u+D3AsYjbusP5iQGHue23ltx7vt/rh9XE+rSTc/ddTj3wCD6zqbrAAOYbvapU97vPOf9/LHWBF6g34+x1/mzob0eTa2aG48zqwxnOH6IIZ5EJpz/DqVdweiMc9BSkXb4N2Yoy+PxTlKyCiJOe9F3hCNGxCoJw+sVHGxEZ3HM2MobXZlFpA0QlD+yvS9fR8X7k9VmqUSrVRqFLJe0gvoc7CCyCitg+w9lzLNQj+s5w9hzL9YinZ3S05ziRW2fUTNXK9zvn/0uodQ4SxrqVsaurBJPhz6mXqcV6hBfrT4Ztx/tei+a2FC0v5FUQ7dTaYkIsFCDLVEimA7WMoV6keD9DVdrsoNcRWK/waCqKl6NiB6NCHp2evInJFVCDBFU/ToJQec47FfMvp7oQECtUyLnTkzc4T53AEMMEUZOURQTEsJigzXXq2dwED19Oy2yzCXZ/h5rgTng=
*/