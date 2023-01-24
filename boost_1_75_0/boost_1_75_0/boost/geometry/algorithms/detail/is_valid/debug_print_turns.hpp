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
ItPzQoe4TA7R80qCQMahDKrnlXIommC7jaj/nhIOil3SJTrVV1I9L3+882+DnmndIe38Gzx94N48pMkjn+Xn35op9V5jXTboNVr/OaWAu99lgAlhTxIEUbUeIYW0O144FJFDHOx7yGBFfM1+J5owtvYivgDjoUzaKXcp2XKp4rUUKvPkharXmqtqcJPklhvp22x5e9SbsPS60GDf7gjYN6A5VJvbI6dKBfz+qhgdoYrH+d3Zmi0rincdh7XhGKwNTw7Bu7oh/ssJRP4RPJueyEB/AVfN2ofd3jrIRNR2RG4tpCeC/JgQ76PzOcEoZWMSY1Q56d2fAtO85KpFArdsnmC8zZOrE6WJYXboaDRiz1gq/HgzgX1tEgrYiXw46kSe3RMqzKYXVZmEVyjs/3wEOw0IyobEj2jFKdBTP4I/H8U4I5+NknILi34DDeIpCh4FUDqr8iUAQmXV4BORA/5i8xfQy0kTeTDN/OYBQL0n8WC9efevneilIB8Sq8zreiHytINJGM/GUlBOw0qJ5YASksvUo9agbbe917HC1esOeirSe72nfWtwjq/JnDk36yrsD2TPzanNfhfnPJ+7K+DPW53/TkF34fSC24tqC9bleQJFuRPNXk96WeqrpZumZ5dNxuUFFV2zaivuwbMScGXhrNUVE7Gjx53p8NmCVh+Mt3yxVChBy8UiZsebqOARjSGPmu7xebPUbCXHnuvJ
*/