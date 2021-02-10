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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PJ_TSFN_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PJ_TSFN_HPP

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry { namespace projections {
namespace detail {

    /* determine small t */
    template <typename T>
    inline T pj_tsfn(T const& phi, T sinphi, T const& e)
    {
        sinphi *= e;
        return (tan (.5 * (geometry::math::half_pi<T>() - phi)) /
           math::pow((T(1) - sinphi) / (T(1) + sinphi), T(0.5) * e));
    }

} // namespace detail
}}} // namespace boost::geometry::projections
#endif

/* pj_tsfn.hpp
SfJDVZL88LNWPdDE230yzX6jI8226Ti4W8dZ2h5mXNuTZipmbLc6lQM4d844IDBxp54u40ARiN3R587Xh9GP77xqQJ41hiOMZKIiCdIfTwT9Ua6Mdsu87PfQDTHls3c5PJe96Yu/41TiW3VsEUNY14A7s0H5XTobuID+QV6YpQl810pTrAwpiRTdvsZD1eMGFctflkO3AecqczY6pZPa3g6zKpf/Vbf9k8UibXJCgPKdleSuVryXxnAw2JPYWvnugyUDtZT5NjsCs/PtPTagcQozNZopzCoihbT8feBU4OJAabAbcIXn4mYwt7hlgxSwvVtFrq5I37xutHO0W7pL595291ahhb+VXJvt84vRiRT3kW+75+j//O5Z7iDM7nJxGFT0bv34wXhLuarYafvBePf9DzoFh16hrHuHYs0AXfSJLPBa1SPVMuHka9FilXxt8eSCO6GuZhnEHETG66mTN0rnWyn6D3aAI5xysZmN4ReRig0+VxKSZdVoJBG0ADJEVjojFc2CXuTvLCqj7FiTuetNy7ozgSRTuTo1kj2dimGcJWt+YNR4VecPHwpJLDaYviDar9kVEpffqJczQPOQ9DjY2e0KE+mTb7OY7cJstKQ2ppBptaQoCUvMzd7xyrd6UchEvrR0/4tlfjFP
*/