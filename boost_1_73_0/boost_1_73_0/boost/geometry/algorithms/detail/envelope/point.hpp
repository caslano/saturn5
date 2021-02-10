// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_POINT_HPP

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/envelope_point.hpp>
#include <boost/geometry/strategies/spherical/envelope_point.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{


struct envelope_point
{
    template <typename Point, typename Box, typename Strategy>
    static inline void apply(Point const& point, Box& mbr, Strategy const& )
    {
        Strategy::apply(point, mbr);
    }
};


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Point>
struct envelope<Point, point_tag>
    : detail::envelope::envelope_point
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_POINT_HPP

/* point.hpp
TC8oSH78LAd7qSZnnICoeLWtWpPNpaWRnpCaELtIseiUGE3El/D2zt3ewGeV814ulh0I8yGVDPy6xe9eTTM+SwCxoVtptUe7+a6TusnhstE2lafHKw+4n4Y8KnoL3cobGyk3is2jD8u1ideEa8OHC2adcx7+NQVfcJRxTd2Qw2aG2ewxr+GTqH0GhABinl/zVH6oqB017cmypGk1NdgspL1t1km0vJubPi63zO3tBuC84UdoAC8EoSFMpecBHt378GOwRvGYhf6xTxjtnS81sBM8NZPAN+Mqu9Du8M0uPwvI3Vm9Ea0OnkQRX49WbhfDdDFV8YaU0i1SVcjA3mwiCBe+1n5NXPb8bkNgbrGquLcyoJ+XlB/Az+j4tDG/WsCNkNP+6/fnaO+PJo1Dc/oI6fmcebRl/ZmtdKdG/ave8HRwdV5V6rXMfyLTfkCtSlGp+SblnyGaH0LxxK8UDua5M9O8+q/RSOX/AlBLAwQKAAAACAAtZ0pSrM5a5hcGAACYDQAAHQAJAGN1cmwtbWFzdGVyL2xpYi9odHRwX2NodW5rcy5oVVQFAAG2SCRgrVfvc9pGEP3OX7FNPvhHFIjdTiaJ004phpgJBg/gSdymoxHSga6R7hjdyZg2+d/79k7CSuzEX4JtQKfbfbtv
*/