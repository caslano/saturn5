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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PJ_QSFN_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PJ_QSFN_HPP


namespace boost { namespace geometry { namespace projections
{
    
namespace detail {

/* determine small q */
template <typename T>
inline T pj_qsfn(T const& sinphi, T const& e, T const& one_es)
{
    static const T EPSILON = 1.0e-7;

    if (e >= EPSILON)
    {
        T con = e * sinphi;
        return (one_es * (sinphi / (1. - con * con) -
           (.5 / e) * log ((1. - con) / (1. + con))));
    } else
        return (sinphi + sinphi);
}


static const int MAX_C = 9;

template <typename T>
struct AUTHALIC
{
    T C[MAX_C], CP[MAX_C], CQ[MAX_C];
};

/**
 * @brief determine authalic latitude
 * @param[in] phi geographic latitude
 * @param[in] a initialized structure pointer
 * @return authalic latitude
 */
template <typename T>
inline T proj_qsfn(T const& phi, AUTHALIC<T> const& a)
{
    T s, s2, sum;
    int i = MAX_C;

    s = sin(phi);
    s2 = s * s;
    sum = a.CQ[MAX_C - 1];
    while (--i) sum = a.CQ[i] + s2 * sum;
    return(s * sum);
}

} // namespace detail

}}} // namespace boost::geometry::projections

#endif

/* pj_qsfn.hpp
f0758NYT40JqwfdKfZsdVo89DVY299SlfPfybiH1k9msI9bCC+Bq+GSwsoh5Ryv0j8CP8OSEiZR5NOPwZEi9XxBSF/yE+9DyPbUP9Zy5Blr8Sak/TAmpO6h/N/jvkVN4rwTe/byTe3M+9NRZ9HHCaWF1+A6eOuIPSt1bz9/duct9dUjtMtlT55yq1Mq7sZPPCKta6HPlb3mHFXpHjuTdJ/joN7Q5QtzQhWFVcTl9q/NUKzz41Okh1XoftvfPuVOh3VPP/AmcXM264UqletwUUg+E6depIfULMDXuBDDWqNTu4HdXMJr3S2g4XKmmX4K1lrC674Ow2qXIU09P9NTevw+p8kPCaha/J/VR6h7m6M/2ZV9QnHP8I3jXEr57mLTdaPsVtOMj+jW4Dy+BHc+dIgWeWrk3cuJMMNTG+gK8W3wQvvG9eMGnkX1g8Ny4n4XVzXvx5sP+YD7KXtfckCo7M6zueIV711aT/gxjCS+eC3buYuwuuYE9xx956rB7kBW1lEn6nm+H1NAy+P0RTz0+mDZfDi+C2abfhdQH94fUQ+PA7jmUA3avfdFTVbeE1JQbQ+qGWfBHsVLLDgqrR+jLKVeAo6e5j/8M/n8cVr+E3/o9gw+F/9kfhtVLe4fUVzmc53wYOi9izBmjUfDmLXtBC3jgm6uQcciUYb08VaPA9Beeuh963z4Butzoqf7Up+4LqePB5dfI5U7oOuk7pUorkXEfQ9eF7Bucq9SfeofV1OuUqt+PuclmYbXZW9yTeomntn6J9sJnbzN2HzIGR3QgMxdQxlruUxtI0R1KPfkUe/UG8coR8q0liz59H1bHVzAmO4bVNz3BbqanTkI2nYXc/dt4+gXP/+5c5OT9YPEFzsmsRD78NKQuP4/Xke5BH2wBRj5BRm+N3gC3PZ8Hx3+Cz7fgDPCwsHqT+p4tCqurPgITD3pq4ifI5KlKXXE96U+E1W/RH8OmMG7Qfcpb8MN7YfUiGN5mNmd7rw2bsV10F7KC32/3Ro8M4PzxK0rNQFeE4a2sg0LqlHuh5SpP7XeXp0qnoFtuUuramUptNZ8XCTfz1F9/plT7SGTpNGRpIXxXjVzJh360/+09PPX8i2F1NXLpUPC24AF4ZTwyckve03sppJY/zjrKWbzJQfyd/WkT/LJ2DphELtbWIHdK4PlPwmoMeF1aQfpLyJl67qcZxbrMgpB6/Dn0w0F8v9BTU49hXI9jhy7YiH7gKQ9+GYy83QFZ8xfw83N07bw1yOmrwNZl3BXRzJmLM5E5kzgnvRyZsQk6Dl1z/dbcYfI7T62+GD1PXSeT5/i6kFpBWacjdzrO81Q2fPrqtnwLL49B1maQp0+ZUu/vwuxxN0+dfQTyiXG66E18YReDY34PQaa9dgO0fp4yDmF9h74/uh864GPexjgObx6y/4BDuZ/ibfDzIa+Ho4Mey4W/GdeHJnnqC/Txdjej77ZG5uVwrw/68CRk/Crwdjc8+LMF3Pnex1NrdkB+IKsy0d3nTGBtpzykjn4jbOgR+iUyrc1Ts9EVJ/6OMUdHtW3PeHFuN44M/6AmpHanrNffx++s75d/Bfox3l9fxb3GE7lrmPH4tldYNV7kqc3QowMuoIyHKQvev41xX35RWK26CXlwAzwJdnd5CDtjDTrpZE/dB/a2fJYz9H+ER9FLf7qZtzaeDqn+T3gqk7afkOOpLe9A7t1JWZ8zvkXomxHs9t0irM6jD9OR5wXvIs/B5+x4SD3zF/idcnap9tQSaHZKq1Kjj0d+DkHXlSMrxyFHwE7eOeizQdhkJ4fUqdB33lQwvRScfhFWh/4K2fslPL9zSB01X+9HgH+2Qjdj41z8LTJqj5Ca1pf7nvc=
*/