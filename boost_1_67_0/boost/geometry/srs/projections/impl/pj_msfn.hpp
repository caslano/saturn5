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
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
*/