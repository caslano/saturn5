// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_LINEAR_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/envelope/range.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/envelope.hpp>
#include <boost/geometry/strategies/spherical/envelope.hpp>
#include <boost/geometry/strategies/geographic/envelope.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Linestring>
struct envelope<Linestring, linestring_tag>
    : detail::envelope::envelope_range
{};


template <typename MultiLinestring>
struct envelope<MultiLinestring, multi_linestring_tag>
    : detail::envelope::envelope_multi_range
        <
            detail::envelope::envelope_range
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_LINEAR_HPP

/* linear.hpp
9PQUVB+yIgiq7ngWqYs/PbqdHupJcj5fi3upPr0zzfelKGfb6JY6vPVoY8/jH7kyA+/3hdIex7FniV8z5igH9nZbpCbHA8KiVhU+uaaWJT/6fBe29+C8Q83eeKf58C4h2xiQDWY6K+L/t0FTc07g8ICWvPAUDJ5C6EULFE84uH3kSkNYbGlVgrhkOzyWLmmLtUf3iwpdO/NWg2wsoOA3YIoUVU9CgTYll7uchTPGCGMGk6lclrgNFx97cJr5JXLsy7mHnX+j8V2GzdxAuDWg6TvYDnAmJL8CwBjNnfnRYcdZeoG31MGYcF/Oik/722IUzaejLGsyN3q0S2OiS3Ke6YR/QhdA1ZvctYiDG2q2xGXc+IGrwH/QpD46Hc882TbKwX6CAEA9SspVEilLB4x3+/k6IPe4lajg/hIwnsMijno1YzJw5Cn4hCbo8b7+/kZ+mNqyifb3JdWtlOqWrs+Ucq2FsllOr3WxbG/bvWzHEpqoDbleeK1N9IeV2bmK4XVEbZC1fInQtVuWPkMhiPLwn3Ixb0/h7zqOAQ5InDBUNjNWRdJ6BnRdZSOseQ==
*/