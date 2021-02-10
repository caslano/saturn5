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
ngWglKMiSimBJKfta5PksFHrJQxECMuO4mGGJGMowJ9WSawI9XHnHw2DOM5TfA1VKL2AUI3xqeaPCp17D364kGw8irh5F+tUwua6VMO8WClvI4gKaRvqnAH14VSmLbHy422BvP5mDpbY6+NGG/O1KQXGLVIfHB0eIrlfV8Yv2UERP94MhhorYipLIawJOmuY+FE6kcl+TymtorJR3tkkkOE4ze9fCPBYnOWrWvEILaadYlONgSnfsG6A8NNj8frzZ9HMX7c6ov/2VPzl9ddH4s+drzvfFAW7DMzI5XCnB2M0yRCHX+eIrZQUxh+b47eIqfMBWzpHD1omyeJ4MsmayrxvYM2hDgY0SkzQ0lueR4eAD8qQ+GkFdym5mgHskbyATeWUNqwEmQbacrQxblZNda6+u09RycYlXvp/Tn4uJ5cmg8OsyuFp1HL45vy8imE2g6PVS99QgKjRKq5s5SkIHjzuCKh6ZVRZ4e5VbqGptEZAQwqVPQJculOhQLtgAZ9TYiNtmf4BklZKSPsD5O01JeSmgCEnph/K8jrqvBgLzOxfuWAv89TtNQVdcFEM3WX64Cll3pLlL8dW8ip28EqfTGe4YDNpJU5afUyJChNSxEQE3tV9lepddEweoR042mMrRj9V9fV75hvvmENT
*/