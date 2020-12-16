// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2013-2017.
// Modifications copyright (c) 2013-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTS_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTS_IMPLEMENTATION_HPP


#include <deque>

#include <boost/geometry/algorithms/detail/intersects/interface.hpp>
#include <boost/geometry/algorithms/detail/disjoint/implementation.hpp>

#include <boost/geometry/algorithms/detail/overlay/self_turn_points.hpp>
#include <boost/geometry/policies/disjoint_interrupt_policy.hpp>
#include <boost/geometry/policies/robustness/no_rescale_policy.hpp>

#include <boost/geometry/strategies/relate.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace intersects
{

template <typename Geometry>
struct self_intersects
{
    static bool apply(Geometry const& geometry)
    {
        concepts::check<Geometry const>();

        typedef typename geometry::point_type<Geometry>::type point_type;
        typedef typename strategy::relate::services::default_strategy
                <
                    Geometry, Geometry
                >::type strategy_type;

        typedef detail::overlay::turn_info<point_type> turn_info;

        std::deque<turn_info> turns;

        typedef detail::overlay::get_turn_info
            <
                detail::overlay::assign_null_policy
            > turn_policy;

        strategy_type strategy;

        detail::disjoint::disjoint_interrupt_policy policy;
    // TODO: skip_adjacent should be set to false
        detail::self_get_turn_points::get_turns
            <
                false, turn_policy
            >::apply(geometry, strategy, detail::no_rescale_policy(), turns, policy, 0, true);
        return policy.has_intersections;
    }
};

}} // namespace detail::intersects
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTS_IMPLEMENTATION_HPP

/* implementation.hpp
pM/jhcCTq2/RCV4wj4doq7xuMgeMwrDvdz9kxKN0/LlqliMmEyPNgZ4J+RXL4TNahLUQ2yddDNnPITusg2Uvs7L7C9krbdjlIuzrraxb8N6khH27TCPnWmtt4oIyPjpQPnQLU9z2H6eWzztOofMtw33b6VofMVc5YhljvN+Tw75LhHW3L3XpmLx9ic+HSw481DJu9ImMkU+Q71QX4fh4Asc7t0Tg9fJMbS/78y9HWKvOJJ/xpnM5gZp0bie6p4nx8L7ljyBerHRzlmkB1uMfD3G7ACv85Bqe/HNgBzbl+7b76RQvabxCz8+EuL+f2d83HOLhQqyI57qQZxdi2cY3Ei6LAWWvp8ELsZhL6PbihVih61dCTrgYK9eEwTO1PllZaIRnI662WKOAmAxiLe/vTAaOtpO0GhR5UL+vl5j5nhL6fxVYYw/pdfrZw/2j/mgHl/ktEQeWkPcap3E+2sF+xpiDox2MfyfC6eiG6Ud+BOyYFXR352va7UeQb/SESj/yFLUfuZ3aZLJNjeLguvIzYPIMnbTxHSkMh3Z82fwyhU2jf8/CkGZmuAbC+Xt+LVbEhE62z88vkXKbhQandyeFoxPJdLbax/kbwtyl+V6+dLGVV3tx1RDkYl4HOdUYAE7+bqsDZL3TQuffnsJyKKbyOY9cFuD2yvh/L+Tmltu0ng3WM5CDG8Tzh1NYLu3+Z8hR/uWkBtj+02F/lRg1Jo/9HZgdXnqoeapYbxNsncPknDrxUSSJcjn/i/qUvoGBwQHTs9hw7NdJ4eEdX/hvTYi7jtH7Z1J4+i6og1M4d3zc7x2S4oQdH89x7mt41cTQ8r5qyLTDpeE8HKUQ3Bso43SlJ+OETIk01KWh6NJQdWm/L9L3CV72kJb7BGE/3ifYfrr6Gzjvlul6Gxy6htqFMYKTLX4gyfBBQefGwBlZQXO7S+9Bn7xQLyv7FD+g9smvX8J9cgNvs5QEdvyasI8E7uvwiTEWnDs7yeLwblHEdveyv6csxif2E0XUQeIQHJ61PNbUJSuVvqQ1kIMf1U3ItErGfisbrrHH0CL5QnznO8mVSL2NHoqwiK8KNVG5ZqfLqbsueiI8HNfXRXjoP94Q4Tw3yNaB5wa6DmbqyvjmCOe5wyPW0EtPLzT1yH6X9FnZN4Ws38rqQjZoZb1CdpaVPVzItlnZ4UI2YmVPFrJzrGylkJ1rZV8Ssl1WdqmQPcHKlgnZE61sp5CVrGxCyHZb2XlCtsfKPmlkOfcY14qN2eSXufwt8mPcovoXa6YN9Y/iAbG+0aH+kUH8LZjXdi+O8OAbaTYKH74Bec4qi/cPjowNDfi2tpTjD3C5p/jCNSEm5/4NiY2O9Y2dPerjZt1jjvSBzylxmDRc+gseH9nmVGe9Ayw4C7k/CBfaY5+zx47hwZHBx+j2YDywx0VrQsxE7PebOgzA0PDpdodWFC/j4r29p6bCpu8aeqbAzx4cHdPjZlzG/axU2HTcz/E4qs6W88YGR/X6x3hY/y6Owof2fr7EB/rG+rhv4/gljuilfpdE4cN1kkesErhevyUelOcL1oSYLM8XS2zH8OigrjfjKb1fEoUP+/2XMX7Ojq2DA7LOcBoKR9x/8HIljvQ89NWOMzo4cs5Q/+C2Hf1KO405sp2+RolD2up1Hh86YxiteGRQr0OMh3Xo0ih8uN97wyqPD5+xbdBYVMlDzJF5eP2aGJd5eBPwUm+lAI7oS7muvJVx1x/6sO9gTPZlHd5/xrjtkzje9zqM+xUf7wc8xn2DzPOVHuf2LfEPMy7aJ9vkasa5fYl+5eNpXOT5k4xxHZdvlzHO9TOl/3XMkXXLp3ED46JusP5fZFyWqw9/I/BKbymzTL8=
*/