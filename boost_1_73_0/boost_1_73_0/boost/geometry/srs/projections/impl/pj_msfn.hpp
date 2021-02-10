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
/DiL76V966j1jeLYWSxjERgHHY5GneEOpTthWrQFaIvk8u92rNqJ9Vsi2igssw8eViAfrFPAcOaUKWANWmlnCHZ8WmNg/8RVTXGne4nTwBRUnqKDRaFOTUQz70GZHxskerTU3uIiP3/OnfOU8bo9a2B+7n0q7L1EL3/bm8wxGXbhGP3GYNRudJoXDdDDdCMxIADHKLac2YzFK+gGY9AAhsORZZ6d9QYjPWSgGt1hBiwrioOwEDtWybbZ2C3X7A7rm3gZPtUqJzNsv9apMfaw4sp4W62TbiQdB3EqbsRH5VlKKbauifXJPpt6sx5VVUGpahXeUebl7PMKgJ2ke5cvLJMA+OPN1KGCh4pVkIYBFf4mCN14vqBHmEyiwC2iIgUGT/ae0k9l59/oFE86W9cXcIN/Ngdq0E+myecfdjjO3eUdCzBZ+WjXwFUDHOtrDWrKna7Pd7rtzf6blDZcU5o0i/yo2YcN3jI7jZxHVb7Qu9J4TY13o2vfJO8lkuELxLJ4srT8ALaL/bg3W1T7vNsboDrVHQGlLIzaFf4GCsvc+HBOTfZnAeO1r6xet5OjZzfgeda5zHRAevlqqR4n6JXv4cGjWARFjlcWplhAQj6GRZUW9mbPAw0AfhYmw2Vxk7ks/Cf0ERZnpuosrFmt
*/