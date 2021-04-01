// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_VALIDITY_PHASE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_VALIDITY_PHASE_HPP

#ifdef GEOMETRY_TEST_DEBUG
#include <iostream>
#endif

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry
{

namespace detail { namespace is_valid
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct debug_validity_phase
{
    static inline void apply(int)
    {
    }
};

#ifdef BOOST_GEOMETRY_TEST_DEBUG
template <typename Polygon>
struct debug_validity_phase<Polygon, polygon_tag>
{
    static inline void apply(int phase)
    {
        switch (phase)
        {
        case 1:
            std::cout << "checking exterior ring..." << std::endl;
            break;
        case 2:
            std::cout << "checking interior rings..." << std::endl;
            break;
        case 3:
            std::cout << "computing and analyzing turns..." << std::endl;
            break;
        case 4:
            std::cout << "checking if interior rings are inside "
                      << "the exterior ring..." << std::endl;
            break;
        case 5:
            std::cout << "checking connectivity of interior..." << std::endl;
            break;
        }
    }
};
#endif

}} // namespace detail::is_valid

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_VALIDITY_PHASE_HPP

/* debug_validity_phase.hpp
Rt1iXJv8Mkv3JOtrqT7yhwt7s1Ny5Mwhiz18rvButpbNN8bwDl4nalzRaH0pXEpQLv1RtwiUMCAJqm1rrI0Nf+N58XeG1/GLyARc6b1g+Dwufly5G0APqV5wICBGIgMc+3tUazM2ZCYohp+XjFq6UO7uZtFrJgl6QhrXbFIPJ2+gZd5QOKFCqB17ekrw2egyGsUlSQHZJ4QJcxq6TY91w3SBrDOKzUY2voumLi4SyHspKo09yXrk50xfjIeJsq56HJnLNdbXHgQNx0OiXW328Ls6zMKrBGzastl48o9bh3eGJ0k7JTkXcyvLbdlpekIgUBRK5MYvscpMy6T47wnhStC1UbnKS5TWsubpZXZdDw1qpdNHn0ADWLtlmnkGRZCzrCWoblLb8oioDtNfIHFp4zWqVcDkisar6A0PXXvUbRF2/CENgbweTY/lSmBr/a3oiuEcLSoIr5KA4IfLC+oA02btmpIRXijMwswOx9NF+E8YR0QlzTWhdoJCODBxsEYjIP3gf+4q0zkhYU+9Kwc5WuCvN3HLGaukIWdl4VCDlKOGA3ZXRit2Ln5KUA==
*/