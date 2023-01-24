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

// Purpose:  Stub projection for geocentric.  The transformation isn't
//           really done here since this code is 2D.  The real transformation
//           is handled by pj_transform.c.
// Author:   Frank Warmerdam, warmerdam@pobox.com
// Copyright (c) 2002, Frank Warmerdam

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_GEOCENT_HPP
#define BOOST_GEOMETRY_PROJECTIONS_GEOCENT_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace geocent
    {

            template <typename T, typename Parameters>
            struct base_geocent_other
            {
                // FORWARD(forward)
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                        xy_x = lp_lon;
                        xy_y = lp_lat;
                }

                // INVERSE(inverse)
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                        lp_lat = xy_y;
                        lp_lon = xy_x;
                }

                static inline std::string get_name()
                {
                    return "geocent_other";
                }

            };

            // Geocentric
            template <typename Parameters>
            inline void setup_geocent(Parameters& par)
            {
                par.is_geocent = true;
                par.x0 = 0.0;
                par.y0 = 0.0;
            }

    }} // namespace detail::geocent
    #endif // doxygen

    /*!
        \brief Geocentric projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Example
        \image html ex_geocent.gif
    */
    template <typename T, typename Parameters>
    struct geocent_other : public detail::geocent::base_geocent_other<T, Parameters>
    {
        template <typename Params>
        inline geocent_other(Params const& , Parameters & par)
        {
            detail::geocent::setup_geocent(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_geocent, geocent_other)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(geocent_entry, geocent_other)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(geocent_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(geocent, geocent_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_GEOCENT_HPP


/* geocent.hpp
HcVmeelL22QjS8d3PvSJiyJF211Ut9dtbHVqjDNBUZnjZWgAh0TI01ykpm66oJaYq7L6wojj3q71p2cvBqz6M+s69lBou+bE9971qvmqF+Pi7dmsM9geYyby6mUvIukYpjuO+4lfe2MLctI0uCdhVQP0V/IZOBIb3W7YoX4vyZ8SlTMsEDe2S49pDtVT8+3w7sSXdQ20KH5xtaUAtuySTDMCHemOZzXINBItea7ToqeeKSsumRp195Mft0+uX5UYCTilADWMoj33udcKXI38PTCEkjvmGhTMJn/GK7Zg8+2pdcN7gLMOOTtugZdSjbDI7eeb6vMpZkh1+7TVU5UN187NEerOoEYhMdN9ghnRs9PPmmMivYuzbyXgTwGDYnEeu3JDr4fppAjFR4auqs5GCOq6U7T3g7hn/AUnTRXjpbBLPAufuR94JYK36KGkE4wL4KWfQ6+ZBy88ko0lzJdyV4MSBBMYXNi9ch8DiM0Rwjg4HemWu3mvNl0IidigX0s3xAwXc4ErLnFEGOeWe5zR5MWLp88QkusSut/TMZMzNXh+1Vm9UmMrzwySAyXXg4xkC4YMz3GYd6vdv0XukTXCXNg0p/OgcaSkLk9+sRsrx/3k+5EYjO/pylp2Fku92Bnjv61AxvamYNmkNqxJCIfxBrfR9SrfkTVFuiT0sdA2Z9FdVVBVzBu01K6TzoytILVvcUXCfdP3LuSv7hOM
*/