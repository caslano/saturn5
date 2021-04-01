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
IphZaemkYan8SbR7p/rm5ieLkK0q7r2ny79Aqtp6MoWRh0g35c1S0yrN983rlvAM4ZZTvslmLF8+5c/i15XuJNsjF7s1kUAJEcGPmhT/6kecwbxGGZqKVFmY1kWofGrnOtiaiiu3wdkwT+ZgFfustTVj7DV9/9rm9dD5GqoeIXwSFC/6j5qhJopD5C+iwJ6sevYkA13CeN+VGnTfsOWY/W0Yi2IPHuGAhZepok0xvA+wrP+iRWE/PwQUXuOhOBmYBOrZAPfMfcWyP9kWQ28AivoCtcC0M8Gd5Lsb6L7oc02QX09dLLZnFqXHmRq8spPfA9QYtdInhrnQA1Q6GhcH1q+ChDhUjPyC0CaADiWCFYzT18rkCMIg9S2GFOjMMyOZ8uxTUHN+rKHVK9X5OypPviGbxU07bY3AZfQD0pDFsif1QRIPm1wciuQbM6phodSh0CWsF1ZxwGxHigLybaqZg8u/2wx7TkmTJbSCYex2uC298KGT+3gxQG3P1s5cEqsBY05B4ImSbTXFI8VMpFcDoaUQCkmvXS4vgHOk+O4QGEbC5DmqevzMrl8v8Q==
*/