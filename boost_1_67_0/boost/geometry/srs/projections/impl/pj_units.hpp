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