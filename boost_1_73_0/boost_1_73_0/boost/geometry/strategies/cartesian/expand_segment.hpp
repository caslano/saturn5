// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_SEGMENT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_SEGMENT_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/expand/indexed.hpp>

#include <boost/geometry/strategies/expand.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace expand
{

class cartesian_segment
{
public:
    template <typename Box, typename Segment>
    static void apply(Box & box, Segment const& segment)
    {
        geometry::detail::expand::expand_indexed
            <
                0, dimension<Segment>::value
            >::apply(box, segment);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<segment_tag, cartesian_tag, CalculationType>
{
    typedef cartesian_segment type;
};


} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::expand

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_SEGMENT_HPP

/* expand_segment.hpp
+6PHsn4usHYPs3bLWJ+ut+zzfy3ws8P8rMj/IMvi4gbix52ifyYZ/RjZV3zlL5OKW+zqBFW7hdIen5h/qh1Xs35cLQ4wwqfQ51DYcb4eOh77ku5bVmK1YPkxjpqTDux9TFNd84QuqKba3Vq4K88Ecg8IG7Dvh8rMCjHSRxLrwk1UPMNZIDnWTHaXrJs1IIgotcz/8OCmZzZsez+/QudweEANr16CmkoN0phSGa9PMxxG2cRZJ0Jrsz/ioPGFsMsidRK675u1bOPl9/+dVVHtbYrbxP3Jzauw59XQhAMbZXETNDbSoetiJm+I0fwmlHzcDROY3dJ1iaWhNhC4FZBspIx0qyA9V21o8Zcd7nQfOS7TBDVvtw2ZfHKd2DhY2DSR0mgPRED4Y6NJcd+5hRWOC9f5s9C6rjzF+/v77oVhc4tcTEEKLANVUxaUs+1ubkB+iNoLE3fHNmeZ28fxncXKtfyqWyLdJGua/+8y4/EuS88vRh86heomGM+MjlzaIRfu9Lm0jdo2pj/Qjt5SBfwfUEsDBAoAAAAIAC1nSlJ+Wm7wnAMAAEQIAAAbAAkAY3VybC1tYXN0ZXIvbGliL3N0cnRvb2ZmdC5oVVQFAAG2SCRgrVZtb9s2EP7uX3FIPvgFmtWlRbFuxTAjaRaj
*/