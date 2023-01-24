// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017, Oracle and/or its affiliates.
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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PJ_MSFN_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PJ_MSFN_HPP


namespace boost { namespace geometry { namespace projections {

namespace detail {


/* determine constant small m */
template <typename T>
inline T pj_msfn(T const& sinphi, T const& cosphi, T const& es)
{
    return (cosphi / sqrt (1. - es * sinphi * sinphi));
}


} // namespace detail
}}} // namespace boost::geometry::projections

#endif

/* pj_msfn.hpp
4AFCkrWb3Z2d3Zlv5tycP/Cced7vlfBvMI05CPdsxZkK5/qNxnW5tvSC98LQPID6fkYX+kUqj1Yyj+T8Kz+q5Q3eXc96HX33i+AL1nvBgKvwC/1WwvNI5sM51HP0ZmXLZzJwmwsXlUsKeKB0TgnFoxEdo67iE+zi+dMzJE7IV7q9g0Mu3uufN+h0gSHC+3RvLmtdiC+h13ZParevUDo0Tz4vwdWyHwbNIYLBm40l9EGEijQdv2MOFjMvs6ZiDown7u8IhLoX/jaIXodUyrgORobbBYn3K6LSnHO7xfkDUeOTSTmLCyDpozfRHFYiJf0MahsIETtj2UHmJEH4bBy2OW/IyYgHrPi5Q42whTH7RBKZmlqx0ukz06mSHRzFz/RCOLBEW8PFyVS1E6uIeVxfX57Uslm7EZ51PpF3mK0KZ2l375ysxJVvLVIziiIHq2i5/J51MyGAsNxxFGHUetpafEcN/w7gZ8kVKnqVEf736vaNu5yM2VAgu8Yeii8WZGFVeF87J6227uM6ISSBtKXInaUquTTlCa3lUBBFQatMdgIC/4JCK0BBpo2ncjFQov3BZKjyyU6ViOHc+331LwAEh3PzQGj+id9Grj8gZxflKuiAdVXq45CJgcJnQOIy3ePCwVPXpTU2NcEbahs2dHAWlvTop5GWBtULyIveFrtri2nhzWqvJRGNxef2wB4k9bNxiw/PkNR/vytsZLs/
*/