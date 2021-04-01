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
3/fyjFJoJJosh92Jw9HEMSCnMe4G3EzgdWfc6BA27frUo+3QDjUz69ZjQbWAzWwS+W2oaWsMJhCyaXm/yTT1g5F+dwW2moD0wLd2qPyArpX+RkdOwO6kP2sFRvqdOZ8z3Iw7P+MZ4Eg1zct39lsG+XOpKp1CWGia6VrwD7XMQ9ZaBrxbqdZEiM/nroWho1Xi6L7z73XG/hfNIEEtRgkIz//I91TSDBaQLjveAVJ1sg/xK92M0UXbpCZ2STVcmeKDFAh1FBIRRuRfq8p/2yVGEALAAVCZsGgWqZHG+chmKua/aXDWQN9b8xIkPng1C0oE9zTitO1oW0HivAPqWXI2Uu7GLbpEmAVNhH9sIpTXrKIC89X57UKv/gUXBuXX4Nw5dfwB4Q7aGDQRjPSceghLxZCxOubPMGEIL4QzfrUSWWpwRqubkS9zdgpKlHzVTY9u8knqRLLVNu+INW7jEspm881pnakyEaJJelCu0Hz4cRsWT7Kz/6ner2aJ4+G9myPXIQz9OgZ/g3FD4KXQYyCRT1KT+yfUunh0x9MorvftKF7VN7+OzSleAN8s/Q==
*/