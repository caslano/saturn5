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
qZc/4W6Ew+HbSz1179OOOrQH9HjGURcQo2skWvXKaE9dfz98UeeoY3Io/zVHvUxE64AFnvrtMY4qTnPVeeT7/VaeOqMvbTnEUdu+5KjkMzzV8BdXrWD879/ZUeV3UgaH3Uo+cNVtPzsqYytk5nBXvbwZXoefMqDrojGeem53Rz1znKMevcpT3Rmr2nhX5S1UCvZVNe85auODrjqnjggsPH/4Do46Ow963xfS+MdPHJVS5KlTurrq/kdctfIE+Lufo4aPZ6w3Oariz44aFu+pAmRgHOXfeLqrVjEW7zBuT0LjO56Gnx6Bj95gDWsGPE2lb3T11OQXPFXHRpILaXfFqZ4qhfc/pe6p3yt1NOWn9nPVCdfR18cd9Rbl5FwMXaYxThtYu/8JWo131GvfO+q+5Y7acKajdtvbU1f2dtSmElfNegkZe85VQ19y1ePQcqcb4KOhjhq0o6dOPxQZ7O+o869h/Irh3+c99e77rnr7UvjrA0dtR39vTXXVFfwesp2rypCVrDsd1dMFdjs8luao3sj6ya+46q7urvrqelelnQRvH+GqAbNcdSZteehcVy27w1P+HpXrn3LUhRcSix3iqMr5jurfzVGL4pWqfcdT1x7hqNdrPXXMmcjXrq5aDo+9kYGO7QU/NCDzUz31t5toz2P0F7q8Xu6qG39yVJd9KJN8J1yGTlyObn7KUyW7eOrzicgnz3LmumogusAj7wOkbt08tTULdO/czo4uZOf4nrRlCu/fL0c3XOGpoed56qWzPJUwxlXjN3jqV5nI5CpP1SN/8c8R953L/Rr0cRK65oop0OpyT12yHfPSi57a6jXW7uZ6qvhxdAK6qXq6q24B9+rdPbUZ/v7GddSzT8KvjPtJg+EZ0lmk80jX7At/3eipb9CPV6DLzgf22DpPHfitoyadCO/DvwVPu+qa5zz1Jbw97Sb4bxnR35PoF3+/9ainVr/rqtXT4bW16OhdPZW0Gbk70lHZDnMLdBic5KnfzHJU4mWe2pYxabjJUzMp8/OvXfWHTz21/T7UsbOrfncve2t7oDuRzREX0ed7XLVka2j5BrSE1lOSXVU621HHHc38gh5aRt7r73bVvdu6agfHVa/8zlGfHe+oB+Md5ZwGb69FryK3r74Nb9a66ink8so3HfVlDTyx2lXbZrrqtHnQLo69U7cxVtsodSDj+MoFjjp1gKd+faOrTj4cnYE+uqGBMuYwvvTpe+Q37yJPLWY8c5gXFr7K3Ii+yvjeU5+xqNl3BWN8tqOOHeaqR893VWZ/ZHcaskk/PtlEDH6Oo5KI939e56m/0qcDj/TUVWXINgR7+EpHPTfeUxdcD61/A1/dCX0fhUfZZJW+0lNvX8JcejP7hIa6akEfT61nnPMTkFH60AvcZX2QNWRy+RjG9BzavBYZZp45ta+jHtsPHc+80ftgVz32LDRETvesoi50xVsrmGt2gB+Xk/c4T307iHlxCLYEaRnp5smeqmJeWE+/L/+jp14cg10zh/auha83Mk5fuGrOC6768a/Mf0XUuY+nHkOXPvE58nCsq07ZAdqgD88ZgryQziZdQLqEdBHpHdIDpJdIPYZCQ1I+aQkpi3QCaR1pPek80qWkk/Xf55AeJL1Leoq03VjsKvjk9iR4Cb11F7x/xiJX7V7NPTiM03m/ov7r0MmzXTUSflle4qixPV11VjFrKWOZ6+5An73sqBMGMUff5anfYb9MoczEt2jP7x31/q8dVcrcetnxjPmZ2AqP0HZgL1zuqvmHYDew+PJxuaOmQJ+h9cz1vejLtczZa9Hbf2NueAt92x8eucBTt72EfG501J6U/8njrjoe3X0n8/zhyPh1y1x1Uj/05Kk=
*/