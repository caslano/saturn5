// Boost.Geometry

// Copyright (c) 2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_UNIT_SPHEROID_HPP
#define BOOST_GEOMETRY_FORMULAS_UNIT_SPHEROID_HPP

#include <boost/geometry/core/radius.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Spheroid>
inline ResultType unit_spheroid_b(Spheroid const& spheroid)
{
    return ResultType(get_radius<2>(spheroid))
         / ResultType(get_radius<0>(spheroid));
}

template <typename ResultSpheroid, typename Spheroid>
inline ResultSpheroid unit_spheroid(Spheroid const& spheroid)
{
    typedef typename radius_type<ResultSpheroid>::type radius_t;
    return ResultSpheroid(radius_t(1),
                          unit_spheroid_b<radius_t>(spheroid));
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_UNIT_SPHEROID_HPP

/* unit_spheroid.hpp
Fh6EyX3YlBvqLY68iMhN3IjgkncxxNsLEAzCfYInsjCKptDDiVsfW/xQk2ALSuzXr6nKItr8roZrb63Uw8svXSSv+4HNVZFbGWbsi+B3b8etYIxIxcXA1Y0tkC88JTcsFz1FUhvSWBMsvgWd5p7pb96DqVy8n2AJmPJi54i6/nft+v/XLssa/572N6sNG+mEuKKhNpCH+qvC6RDuuAW9GeiDNJkFHL9D2E+bib8aKzaYxj4Mj/ocwH7kIfGUIsdJx86SFqaAz3+GcLg/O5qXX+f4ERSRMG79uwIAmD4ZJGqeyO6AjrAfBzrQQw86toM1sJEGku/uDk+Tv92b2+CP4YboRQAYyTSYSMqy+WdNtV0z9ykjYEjdpDyYB/5fSRZsPN/OaaAdLmIX1WwFaKo8DWAubWvZpoPg/KOpvp0TmmKbjR+IlFzSUxuXZ4BA6tviEulXLTASRBrHWQeTbOpOUZNht4D0vnRNaLEY/dqzyMM1zkjGMMDilocxDu1a/OwK199iQsJ/NOnoJZ5L3TtKmM2CdUprYjYsFvNUBa811JBuu+nD5pbf7ZXnDw==
*/