// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Geometry Library by Barend Gehrels (Geodan, Amsterdam)

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_UNITS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_UNITS_HPP

#include <boost/geometry/srs/projections/impl/projects.hpp>

namespace boost { namespace geometry { namespace projections {
namespace detail {

// Originally defined in projects.h
struct pj_units_type
{
    std::string id;       /* units keyword */
    std::string to_meter; /* multiply by value to get meters */
    double numerator;
    double denominator;
    std::string name;     /* comments */
};

/* Field 2 that contains the multiplier to convert named units to meters
** may be expressed by either a simple floating point constant or a
** numerator/denomenator values (e.g. 1/1000) */

static const pj_units_type pj_units[] =
{
    { "km",     "1000.",    1000.0, 1.0, "Kilometer" },
    { "m",      "1.",       1.0,    1.0, "Meter" },
    { "dm",     "1/10",     1.0, 10.0, "Decimeter" },
    { "cm",     "1/100",    1.0, 100.0, "Centimeter" },
    { "mm",     "1/1000",   1.0, 1000.0, "Millimeter" },
    { "kmi",    "1852.",   1852.0, 1.0,     "International Nautical Mile" },
    { "in",     "0.0254",   0.0254, 1.0, "International Inch" },
    { "ft",     "0.3048",   0.3048, 1.0, "International Foot" },
    { "yd",     "0.9144",   0.9144, 1.0, "International Yard" },
    { "mi",     "1609.344", 1609.344, 1.0, "International Statute Mile" },
    { "fath",   "1.8288",   1.8288, 1.0, "International Fathom" },
    { "ch",     "20.1168",  20.1168, 1.0, "International Chain" },
    { "link",   "0.201168", 0.201168, 1.0, "International Link" },
    { "us-in",  "1./39.37", 1.0, 39.37, "U.S. Surveyor's Inch" },
    { "us-ft",  "0.304800609601219", 0.304800609601219, 1.0, "U.S. Surveyor's Foot" },
    { "us-yd",  "0.914401828803658", 0.914401828803658, 1.0, "U.S. Surveyor's Yard" },
    { "us-ch",  "20.11684023368047", 20.11684023368047, 1.0, "U.S. Surveyor's Chain" },
    { "us-mi",  "1609.347218694437", 1609.347218694437, 1.0, "U.S. Surveyor's Statute Mile" },
    { "ind-yd", "0.91439523",        0.91439523, 1.0, "Indian Yard" },
    { "ind-ft", "0.30479841",        0.30479841, 1.0, "Indian Foot" },
    { "ind-ch", "20.11669506",       20.11669506, 1.0, "Indian Chain" }
};

} // detail
}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_UNITS_HPP

/* pj_units.hpp
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
*/