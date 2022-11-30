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
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
*/