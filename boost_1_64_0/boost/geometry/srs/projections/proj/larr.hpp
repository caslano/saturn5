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

#ifndef BOOST_GEOMETRY_PROJECTIONS_LARR_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LARR_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace larr
    {

            template <typename T, typename Parameters>
            struct base_larr_spheroid
            {
                // FORWARD(s_forward)  sphere
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T sixth = detail::sixth<T>();

                    xy_x = 0.5 * lp_lon * (1. + sqrt(cos(lp_lat)));
                    xy_y = lp_lat / (cos(0.5 * lp_lat) * cos(sixth * lp_lon));
                }

                static inline std::string get_name()
                {
                    return "larr_spheroid";
                }

            };

            // Larrivee
            template <typename Parameters>
            inline void setup_larr(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::larr
    #endif // doxygen

    /*!
        \brief Larrivee projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_larr.gif
    */
    template <typename T, typename Parameters>
    struct larr_spheroid : public detail::larr::base_larr_spheroid<T, Parameters>
    {
        template <typename Params>
        inline larr_spheroid(Params const& , Parameters & par)
        {
            detail::larr::setup_larr(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_larr, larr_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(larr_entry, larr_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(larr_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(larr, larr_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LARR_HPP


/* larr.hpp
ekECxgdI34zAQy8CmOXghjwtYWeosEUcVmTm1Wq01UQwXCHlGF7c9i4aQ5lNEUFfP16Cdni6D7oiO+itKuj13O+h56J2UCF+cfZbstg1ZzoM46sE7fQuU3akIBxmRO1MDOPEZz+JGYFaTKCBx1vGVF6QAs5JmU7ZKmDfzKBlMfpgisIo85lthRZrWyGqthWiyV1orBLVNTPN0ptmp7nHi4i23iSgprlzKTfNjf+NTdM2IV+3SOShps+UKelxx6lmJc1J1iilktvrk6Y5rTS5veY4XqOcKPP463Hg45gvi10inqAYuP0y/s39bDOYPqD1aS51UwYe+fzrck6P/QqqeqvuN7TwQlcfEtbiw0xoUeGqrVuBPMIkVcMqqZ6GUhMNR4kPUP568p+WKcLiBOXPtyhV680UoeYL3N3092UxwzmGvKly96qCV7W7VzW86ozc6rcQA9Vfni2xddr1xvbOhchRP/zgHxPIOmDDEdO1nur189vJZZTK36Q8nAsIxlZR3rjtLakdfb/g0OHHIJvrzeKQ71dsqnBnvRKsV8KrjOLl9YyJ9kGISoN2mQ4Vr38dxMd7QqKOcnN2cW6pfxb/XpuHWQmxuQZPzYVOD3qRR0PdyEjtCFdq9OsyUKCbQHGwnppA1eEQaS5f/aNpLlZ1OK+MqgPqd90e1O/P2o/n+xkyGifX2WQ04tE6PCEtW0Zz38KmEDlx7kxQWndAlCHTzsKQAuhli1/WddrGz+HhUx5Emywsa+INrQGqbpHmZU36HHxL/Qr7zkhvDrp7Xo9VXsbJNhbrMLRfCohzAWXLpsLL/g3n85nyM/cvdJE3FVPVRrJnZh5OBCe3GfLZ9KxEz9X0sPkliX6zNNjNqtEWtFAHpVBrugiVEd37tRzGiu1cHa7n9Bdy+msz+b3i6O4oSKjFEirxYVThdkl/Vhb9/TX9XvG3T1b4ddE9Cf9CDYcvbTkyh7vrRTvN0r6pzg+EG7vPsHKX9ry0Rg+kAdW7FYqER5+agfgvrhmD/5NrpqSmqyZfH/Wa8T6WlypgsB7/Q6R2McgBavIz1UBvKnQ2v9n7DT9fYLYW6zxmxWoNI54oLdT202DFMOy6w8tPLRAn5U4rMmZFx4Z7RplP4w107a1Xq4mW+WBDf7x0QWfabZFhDbUfp9OyBZFL2THb5rULXjITMxxnG7+YpD3VLaoFJaFFQzJghSUhyKpf0Q2ZcOO9tgxbVkxDaq1cap4G4wNNVnqaAeOataxuisGqYKxcdU/rFJYqwFMC3KWnu1Cdk0UVMEW1yGBVOqgW8V2JeEqAi0PWTZBM0wTMOWAB8hB40SyPQvEos+pEIyAN2yMo9mFxmju1R/SlMg3tUUJV8Q6Be4Zy58NdHcf3+HYwiaDDTUQNLRsBognRcDCmtGZnkAIZ0PZVanLV8i0SHmYXsUo1ryqaoxH1hu0BIB3Bm1414yTuijxTp8ahgsG/a8ONMQpJrKyg9QyZdZBDysM/FCN48C73hFfcYPYFzQWo+CiLR2ds9qEQTHw/OZ/iA7kjQc7i71g4qfYQqxn5HX60/m1RDosoiZB9wEW5cBEBFyxAkvwzKrgFD2l4Kph8AT7ETd3/wd5Hb372/d+v2sbPElQF+xYuuv6hM6jrb4r5gPvX3WmHd2nLaBkf5vyZkZoI6fMlzm1g57HimBw+VpzMAVZvQAB4raNw7x0BkIN4RIin32biLYT022InEuCFBJ84PQu+g8apMOCStPJLOjN4P0DIbxDy7YR+RXEmD5ME6XJBepWQvlwchMduPx026UGRkBNfOk9HNuFiFdkWGgqAPU3ITAMZHaSd+B5kItxS324/SH2qvsP3KTbO/0k/OW9zDuI=
*/