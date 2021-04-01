// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_PRINT_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_PRINT_TURNS_HPP

#ifdef BOOST_GEOMETRY_TEST_DEBUG
#include <iostream>

#include <boost/geometry/io/dsv/write.hpp>
#include <boost/geometry/algorithms/detail/overlay/debug_turn_info.hpp>
#endif


namespace boost { namespace geometry
{

namespace detail { namespace is_valid
{

#ifdef BOOST_GEOMETRY_TEST_DEBUG
template <typename Turn>
inline void debug_print_turn(Turn const& turn)
{
    std::cout << " ["
              << geometry::method_char(turn.method)
              << ","
              << geometry::operation_char(turn.operations[0].operation)
              << "/"
              << geometry::operation_char(turn.operations[1].operation)
              << " {"
              << turn.operations[0].seg_id.multi_index
              << ", "
              << turn.operations[1].seg_id.multi_index
              << "} {"
              << turn.operations[0].seg_id.ring_index
              << ", "
              << turn.operations[1].seg_id.ring_index
              << "} {"
              << turn.operations[0].seg_id.segment_index
              << ", "
              << turn.operations[1].seg_id.segment_index
              << "} "
              << geometry::dsv(turn.point)
              << "]";
}

template <typename TurnIterator>
inline void debug_print_turns(TurnIterator first, TurnIterator beyond)
{
    std::cout << "turns:";
    for (TurnIterator tit = first; tit != beyond; ++tit)
    {
        debug_print_turn(*tit);
    }
    std::cout << std::endl << std::endl;
}
#else
template <typename Turn>
inline void debug_print_turn(Turn const&)
{}

template <typename TurnIterator>
inline void debug_print_turns(TurnIterator, TurnIterator)
{}
#endif // BOOST_GEOMETRY_TEST_DEBUG

}} // namespace detail::is_valid

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_PRINT_TURNS_HPP

/* debug_print_turns.hpp
xb3XvTIoyAXtVrlzuegajP+7+8Qg0bIKyNBRunwOaQ2o7JTkCw5YL9FfxIzzAqtyFzMRl6iwMsvjKTG9cf6rdkaHTpB1j0Xc7XTVSUltQwZtfJOx2mUHn1c41rHdxxjKQzLzEH64fNRL1M/F6wnsDukjEMZsxmKciXj3UlWdsJpI1OrJubhtlCNuSs1KkqTWKFeOjld1oYgQmsAFACiop2upVrEKxqATeuApU1Vbvxclpjd+5wf1/Az6Fdt4oIyYrSpJxD9xo6a+R8xAL/rxEPzt8nFefgS1jWRmHKSkLzZ0lY7ZJ2v4Uh4/JFGGSUfWsy9Hk8llf9s7hQf07qOkI9YjVFYKKM6MCmobgq4awjJ2eVFRFxt9KsHMiQzNotx9wkuJroOjezcuUVcCBlIcsvP6jccSm8KoHmxT/bpHeWXaYRCRgFcA0yHihmGMjbR5kwuk1vV9CaY8riTCGGMp1WgJcWaXG6HqHv8IX3km/1wmvD97cd30CUgJmsd3QrohO9cuTIOHsOTN8ze2nqiaKJmQLLLFrd0ysj9bba3YQgzkGP2OIeK9VABaBQ==
*/