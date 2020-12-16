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
5Epk+h/w8sHogzfRXRDqj/DP9/ig0WvRP9B5v7XIKnQdMZT8RBHnr4jZz2XP+bHviJHhlyL8+Ep03MpSYhn6H43v0Pgj3zbD/75hFjRch686E/mKYwsWYBf3I8d3Nefzp6P7P8O2IVdeKTa9Ffqhpz69Eh4hz1B+JnoS3jhlNHn2BlCoOxhddRF8fs1s8s9DyOFdS0xIrm/ZWMb1W3T/v8mBwi9XYa9ug09fyiVPRkx13DrG2pe9iUXkeb7O9KYdhm3rJHeOPDeUkZNtg38+x46jv7Lhr4POwgfCjpb/hO9B3FLQhA4kv7Mw3/O6yPt8gw3ZiN+887fkSg/K9IaOo90afCF8i8wa+KcLmszCx4WOQ5CFljnw9RPoOg96wdvv/4LOwBd76IgsfHtyLgdjs34DTc/Bp/4E+Z6GHR8N7x7A/utEcjDY4qPg3R13hGaHkDsYCZ/io/+hi3n9gl+OjTwB328U7Rz2Ljxzmkdek/gP29qJr//WVcQ8K+F58ngF+FeX1CFfZzCGteiKP+EfoxPvGge/7YJ9AndSCWt/GvR7nXmSl3t1f+wduZy2PGLff6F3boQG37I+nzOfR1lDcqAr6ffwJ+HvI4hPyQENfQwegyZNf4GmO2OHf0S/nIO+ZY3zx6HLPyZv6kFb9gM/gvevDJPXxLfrfBa/9l5s/c3gQ/PpR8C3xGS5lzCeV4lxf0Rvr4Jft2ZPeSDm7B18Z2Tma+Z1DXiXYU+nYn+HfYevTNzyDu2MuhW5JH/z2dHs/VFvMf0uvox88Wv4Nvgnz08nd89aHvMM61yOr4RumHk4dvkP6Fv84RjjCj8FDYvJn53mMTb2hvaAlkexfvD8AvZQX0We717JeHbDHp5KvpH8z0PERbc+Qg4TPTn4Lnwyxv3LC+Q78BuHvkCO/+UMr6oc3YiNnR6FRsj2n8Os2zro/jFznIKNe4ixY1dOa4AWHeCspu8VzGUs3xojr15zCTHvtug19PncQ+g/DE+SDx3dqfbZkBvWZOxw5vgJ5djg55GT/tilH6DVzuj9B+Hj8ejBi8kl1dPX4bT13iX4GcxlWQdw+DQbuWu7B9uELzqC9T6TWP3j3zEXaPJvfILYQeRucpAH+jiItb56Hvuy69TZEsbPeHPeRwZvwP/Dn6s5CX5bjF9D3nUu8ziPvEkZMfzqx8B5Dn6Ef3JLyY1fB2/MJW9IDufTxfjXn8Ef+E9vkc/dvhRawpfnXYhPFCPGPh4fGls5BtnpuIh1XcrcbycO+pj1JmcfYmynfYP+P5P2toXe+BXT8pAdbMjnrMlI9OH+A7HHUzj/MIn4LYt9BnzIfacjo/0zvcX/wh/DFs3sYt22Rt77wRczoc+vsc3o9UuVrKI/Nh6PLiWvdGge8SPrsMt9yBS8cxE5gg0DOV+BPL2GLR5YBp0j+AvYmD6vEIsRk65GXhuwBV34+t9MJXZegw7FTzgF/X0EPt2ecz14k3M/xD39sTejaXNv7M2+jKEM/770Z2z1Vei44fiPyMDp/yL/OQc7xu8nMcbXiT/6rsSXRZ+PnpbpHYvcV8CH4fOh+9vopAOh3wvEGzHO01zImK9mXvjTXzL38/l9W2LFjhfgS3yvo2Zkep+q/DB6/ucMZGcA/vbbxBXI5pWd3A2fjw3B9v70BHHzSORmKvmSm5kDenfGFtjLCnxC2lk1ibJa9mivx66/mslZIXz4WeQ6FyLnA7Ch2LTOVdhRZG7v98jh/oq81tboruPwqYGF8B23wiYfgW8yizxhGXb3vuewOZWsxxnwdZRc7jbsDVwEzbGxt/2FHHMhub2H0SHo5+pR8CB672/oin8ia0884rFPif6CdzPRU7nnYrPwVW4=
*/