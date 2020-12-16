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

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_AUTH_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_AUTH_HPP

#include <cassert>
#include <cmath>

#include <boost/geometry/core/assert.hpp>

namespace boost { namespace geometry { namespace projections {

namespace detail {

template <typename T>
struct apa
{
    static const std::size_t size = 3;

    T const& operator[](size_t i) const { return data[i]; }
    T & operator[](size_t i) { return data[i]; }

private:
    T data[3];
};

/* determine latitude from authalic latitude */
template <typename T>
inline detail::apa<T> pj_authset(T const& es)
{
    static const T P00 = .33333333333333333333;
    static const T P01 = .17222222222222222222;
    static const T P02 = .10257936507936507936;
    static const T P10 = .06388888888888888888;
    static const T P11 = .06640211640211640211;
    static const T P20 = .01641501294219154443;

    T t = 0;
    detail::apa<T> apa;

    {
        apa[0] = es * P00;
        t = es * es;
        apa[0] += t * P01;
        apa[1] = t * P10;
        t *= es;
        apa[0] += t * P02;
        apa[1] += t * P11;
        apa[2] = t * P20;
    }

    return apa;
}

template <typename T>
inline T pj_authlat(T const& beta, detail::apa<T> const& apa)
{
    T const t = beta + beta;

    return(beta + apa[0] * sin(t) + apa[1] * sin(t + t) + apa[2] * sin(t + t + t));
}

} // namespace detail
}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_AUTH_HPP

/* pj_auth.hpp
qABhzudJlc8Wlc9TnM/TMKZtBhk9AzJ6VsnouUL6lIyeZ3ovMO7YwPzlxL5e6Kuy7dyFzpZYF19EXRyibJPS7DnZ+ZqfhIOoby+H8pXa8/iD5aHfJBO7kFf+yz7rVZs+KX3Wa1hO4rm2o75f8Y1R6X3/DrO/M3X6BtTpm1Cnf1R1+lYhfapO/8R1+ufCId/piiX7Y31xKUggTnh5G3h5R62j/0rhaMhe/7vMw3uM/62ArDmLoL/Y/iRxIfb/MP/5m12PWJ98LX5Kf1wvlnd3Xbic9zr8uUwF6Ww/+zOeyvOZ93H/Y5hyCNdftSzE1aB/jgbtlH6LHD9S7Xwr1+GHhby3zPL7R+EgPiO2o/+3PpmBF/Nb/GsoXj5jXj5hXv7FvHwu4ya2RSPuyrhzYYN9Rcyf7Eg78oqgHQ1zPhequ8Nsg4bnjCIpm/ktZc6k31jmkUXczxoeKT6riH17QPoHQWY7q/S7cPqHWGa7cvrdFB7RD/TnuzPeHpDPk5BPDsX7bT+XfmPbz6MwfYG2n8/0CoqGHH/18CtRKL8ixX+x4r+E8yt1eEOtFVWlqXjoc8qgrvYEGXxByeCLFKYveH7HPO3FuLMHnz9iB2y5CoUwX+OAry8BX3srvsYX0af42of5qigKG9OWdQfOB9z7PjLWTsC2M4xx85xIwAcx9YXu25foaD+/O/H51lcJFi6ryqoq2mBtqa5pqmqsbWimnVbJeiBE+pv9Qafpt8jtAKVTk1hOE7ntHchyOkjwMsw8UH7/QvVXh3D6yZx+Cqf/GqR/Ro2b04qk/HKn7VBOdxiky1G8zuC8tnA7n8lpKlNpSEeG9WZkyqVSTV1z41FWnOmAUq/VRBv74Cpb5s5kT09qHKyxcf1ROjnoXh518f7caHbR8OZGk9PMjQ636VN53ex8rsX4fE3evZgD+lrsVdc2NdNarLauOTD1UdG+/g7RXu35BKWpObymEYSmIKyDc0Fe4CO1f2lrb/eJrW4P08QfYcvl9uV6++Liu3NeoN25Xb/Gmtl+CTAicCb0oZq317Ge1BcNshYBOYWISNrVAqWTjapPbuK8mh2e3AnBu8qLQF/L4PeeivZRTHsxt62jmfbXIc1FsuZhnbF5dfd20Qmhv1d1rE3f6nr7qN/fx2XOftww9TLdnL3Fpk96/jsoSwL1JuNMVVcfVbAvXBXNdZjGdm7wfS8jhzaWidh6UridvpGR4L2cDpZhFPrHIugfl6o66OI6KOY66Ob0xxcNPTcczv6uyb8H8l8G41qvGtf6KNynxrUY83NC0WB+IX3PebQf5R8o+0yFg9LvJw5jz8Xwk1ByTKp2spz5XgH1sADksEqlP5HTN3I9nMTpT4a2cADI7lQlu29SmL7gHRKmsUb6BdyzhHMZjstW650I+xqexP3ut7HfHWJ9gnqK50nr+Cz0O8zb6VC+N1xbV+9C2a0SWZOvtW3R+HjjMyJuk2dim9zBOUUmyPe7Sr7riuhT8v0el2E9444Xvv3+oyWw/6l9N29Anoexjx06/93O/sfwey7oA/gSx6MVz8SfZ2XdHQsQMnww/+cj/9t5ZgNnqHL2jf3Y91m2F0L7OQfsQS+meJyDmrnnJU7XZA6qbawuJfh0NedVvIevIGAGjGek+sz5Cub5yjR9Nel+oIxXMf7VRXA2Dm1mVMg5/w84zbWcZltgzDKdW293B+592DjZ7yD7JFunYuNxJNGJuHTy/oKxTy42cfDWwkWEV+51TOpmnI0UrvC6J/l5TafwRArHOdxJ4SleXPDPoPBMgi/n8DUUnuMtF/h1FG4geD+kX+z1C9zIYwnst5g2tDsJ/Xqox65h7rfuDO38h6qd31hEn2rnN7E=
*/