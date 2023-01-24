// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_DEBUG_TURN_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_DEBUG_TURN_HPP

#ifdef BOOST_GEOMETRY_DEBUG_TURNS
#include <iostream>
#include <string>

#include <boost/algorithm/string/predicate.hpp>

#include <boost/geometry/io/wkt/write.hpp>
#include <boost/geometry/algorithms/detail/overlay/debug_turn_info.hpp>
#endif // BOOST_GEOMETRY_DEBUG_TURNS


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace turns
{


#ifdef BOOST_GEOMETRY_DEBUG_TURNS
template <typename Turn, typename Operation>
inline void debug_turn(Turn const& turn, Operation op,
                       std::string const& header)
{
    std::cout << header
        << " at " << op.seg_id
        << " meth: " << method_char(turn.method)
        << " op: " << operation_char(op.operation)
        << " of: " << operation_char(turn.operations[0].operation)
        << operation_char(turn.operations[1].operation)
        << " " << geometry::wkt(turn.point)
        << std::endl;

    if (boost::contains(header, "Finished"))
    {
        std::cout << std::endl;
    }
}
#else
template <typename Turn, typename Operation>
inline void debug_turn(Turn const& , Operation, const char*)
{
}
#endif // BOOST_GEOMETRY_DEBUG_TURNS


}} // namespace detail::turns
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost:geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_DEBUG_TURN_HPP

/* debug_turn.hpp
C9N+oyUhMnuqielvlwsT36zQ4H0U9if+ww3v9SvAoyOrkDg1onPIBPl3H2is69NzqegI0JgYObxOa0yoAiB1yuh1CVicxysZB14+nDfZX2beUtj/4diVE7EbYKiFMJ0UpKmDlGEYhtLzg9oz1GHMp1ojG/eolKxP+fbyeFCx74gyKou6nzg4x4944oLGsgx2lNJOqYyG4+7VPPPiyCKnKqFkZu2r/qxPaS2o2W0HdhxqcaRPBX3itGQHOKSyHS3ZfxIM0o6yHLuUkGqp35uH43QVKrr8WU8VKgKcgpj2Y4s8UWcCM8Pucvu+PdY0A28fzOC2+Xy0Dw/m+fBN0ZbTQnvVZq51ZrQDE0K3fpqxu1WnWlXLTNrjrqV3AKxbbalo8ozQScY3M3braoC4KtNhj+NJ71iTipaUiqZyY5JXKjHbcalOdaz2KxpY8UmH/EZkjx0zGzhsN7h0WsnC9wDufLS0Yofio/aNzcyOy1j2iACn2m9KXf663nvdKx/+fWZIboC3tEt715KUsmrNmoJ+xjkoGA/+JFDRD/zc2DNrEekexUTK+p9g5RXii5D3QtcdX7ErqJ3uepg/UUMKVNS+xf1mnw9AvD70nlELHLX3vPSGa0f9GcJ6R9EroDAMfdmTDTUr5eeBmf5RQ7i8QMVBMXZJE5A8k8ngOMnS+q85R7Vfm73YGeXA0UbVKU09J2NQHNaxyhYXyiwrYiYh
*/