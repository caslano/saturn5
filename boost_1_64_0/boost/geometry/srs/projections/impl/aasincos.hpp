// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.
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

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_AASINCOS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_AASINCOS_HPP


#include <cmath>

#include <boost/geometry/srs/projections/exception.hpp>
#include <boost/geometry/srs/projections/impl/pj_strerrno.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry { namespace projections
{

namespace detail
{

namespace aasincos
{
    template <typename T>
    inline T ONE_TOL() { return 1.00000000000001; }
    //template <typename T>
    //inline T TOL() { return 0.000000001; }
    template <typename T>
    inline T ATOL() { return 1e-50; }
}

template <typename T>
inline T aasin(T const& v)
{
    T av = 0;

    if ((av = geometry::math::abs(v)) >= 1.0)
    {
        if (av > aasincos::ONE_TOL<T>())
        {
            BOOST_THROW_EXCEPTION( projection_exception(error_acos_asin_arg_too_large) );
        }
        return (v < 0.0 ? -geometry::math::half_pi<T>() : geometry::math::half_pi<T>());
    }

    return asin(v);
}

template <typename T>
inline T aacos(T const& v)
{
    T av = 0;

    if ((av = geometry::math::abs(v)) >= 1.0)
    {
        if (av > aasincos::ONE_TOL<T>())
        {
            BOOST_THROW_EXCEPTION( projection_exception(error_acos_asin_arg_too_large) );
        }
        return (v < 0.0 ? geometry::math::pi<T>() : 0.0);
    }

    return acos(v);
}

template <typename T>
inline T asqrt(T const& v)
{
    return ((v <= 0) ? 0 : sqrt(v));
}

template <typename T>
inline T aatan2(T const& n, T const& d)
{
    return ((geometry::math::abs(n) < aasincos::ATOL<T>()
        && geometry::math::abs(d) < aasincos::ATOL<T>()) ? 0.0 : atan2(n, d));
}


} // namespace detail


}}} // namespace boost::geometry::projections


#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_AASINCOS_HPP

/* aasincos.hpp
ht5WqfOYB44gOqv7WmuSzg5+CJ7XWYUEvqVkubTgedzdS8ryR4G/VcfssIwFHcGtSAUOlQ+JmB7l1kXw+YF4JcZ0kWjriDhocc8paJ/5ANHmERcmvlPtln2QaPeIjilapzWsPWLPFNDSQn/Nc73LU567CKaa59aIhAmmunwDdOt0Y+uV84/eiH8ct1/jWAyyEPH6TSN4zkQmbJwditUjCxazs2edm4Dtgvbb5aA7ouHUfBIXA+5oxD2JJIxuu6sj7ndB6Pll8hnHVyk6IzoH9Ne4OQkyV8Pkvxr4Yy5e9g0Tf0fgr41IvfXe/zopK17ynx1TPg6cGVN+DmhORLwx3HPB96TOH+nu8suRILvdFFFfMmC2PBVxjUi+/KMIvs/pjv95ygbQuJvhgzMGTsv8SxcnfMH1XqK5JSIPz1REhur5vZZbM2Jy3hpxCniPHtbEaR0FUir4v4m6DKzGWVGBQ/wI8eCciiGtgZ0aoyq2m7LHyhPe3JiYF0d9uwBcK3BmDJzOAKOyvd1YQyqf47gLNJ0Y0sqOJzZzN8jTHk1CdxwnoD2hPrkMz2lZb5Tho48ud3fw2hpFEp1TiX91Ut0As5zWXg5H/+RjdT94AIiBy7FTDD5k6IERAwsDm8aMdtS/X5cRn2VDV9V13gu4AxwHai7npAcHZy9U/KMwC+eVt6TxtNAjuSjWPxMNn6NwODp3jsKRaPgchaPR4ByF+8A2V6syxqLVEvj7AX9N1GdFC++lecm/jHATt9wm8LqWl8PvZNH28LluNp546DHseFTjMZYxXU9Ec6hRDQwUuE9ZOt/6ZHV8XOes3R+8b4zqhSdWm6rfXgj4KQ5n5+w3U7+08R2OMTvB5qBfEm4sXsAogbQIS+NuYTiR4a11uDWayBRycoDXoorW4uOSVTe7jG59T15unapDHPfbpSzHNdZRbgOtubZCz1gdFsrMrg8A7Egdz1eiyRDNInV9IMocrSu6q15dx4MBa4vpr9gUEo5zMEUDBxvz2v3KCKGLlXhQF/itj2Gxq2i78bw1JtaskJXx64xV8u+uwCi8g30uoDfGcjFwG5Dvq2NzYrjUFATg6+2dzZWz4p1sn9zb7D2T61PnJrvwW5S6RK35dzP6j7MzvUsN+gFF/4mYpB9U9EOM/pHA1Cv6YQ3XvOrl/YhxprO3GZdxprNP8b4Mv41zbNxb9B7QXeQ+K8HPrR8Kmihgen3QoeI3D2PtEKNzZM/hsWvT7YHxSCPCa4B1u7ze8tmvUPwRSxIZHDXijyIXl97fEbm8NsEo3sYSEFmuaLuAS6Wp7HoBw9LAVuPFqPBZFtPcBl0bYZtHMNsM6XeG4izTnIECcrL0+V4mn58qFzQtA3G/jRv+daDZG19JKB8YY/41wPwzZdDbin5Q+ee4op/QZz4R/k6Pu5iwdOyvUcf+KB/Hm5O5shIvjmeNHM9WhkPK9STHrWE4tC6NvW2cXwJwvVayxJoTY6bFY6VYxxmw+7jlUgDytkY5CaP6N7v1wOpFb67P1kr9G737V10UX2hk7zp1ivIS5I5Vd4DPpPm4FiIXmOdidRq5WYeN2NQSPHf49sMsxSX0kz53zLHxLz/nGTn2geSk9Ey8Hsl4Ffk41Cxl3KpkLiuZ1+B5tcojzri2Gcem25mEgNS+hwkm53xd9skyp5aQnjk0Qjgi1Ph1cj+M2RAhLySaPIrtX5o0nOU+XOXulcUZBY0BlbEmYowzMle8iKUBwS4w3gPIQvZ2CbP0PgzvDyTcpCPmm50RMXCMiYlRj1y0Zuqt4CyddzHkyugckr1GjXHgvV/A5c6beB8QMPQiOU5KZTUupXF6HQcT6bWGA36TLl6eB5hnNgXSv2w=
*/