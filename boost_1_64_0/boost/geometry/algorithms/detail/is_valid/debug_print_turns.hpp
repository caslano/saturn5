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
jDa+EONb0BdMI29BXzDDebHvynOM9MG/y/cF9C2+/VM42RdQ2Lq+4H4Yfl5fcKzEwfxL8ci+gOLxfYEfB9eDFF7UxXLE6/qC42I4T3sFYaIvOB5x0Rc8FTHRFzyZYRCmgTNT0Yk14Z2eD4j91E7sS/j3dDL9bPI5Ob4v95wlHu6cr21d6uHOm85dXvzuGd/N5BcZh/CtgKOuON7IPGa9O4E/Ifazz++m/inWZDrHQd/L8YJzP9B2L7y7TtTL8b2Jkd2Dfd757oTA4XfO7OI4DP1xzms6z+8+2s05UKLcbr97CmGYOOXvwRDOnU8dx01KjLNX4JirewxngHHsSzh671qzpMsC9asHWdj4PP5DGCa8ZkJn4B2em75JZ1cnceL7HS5c4s7pmbsKDb6v28VRx4SPx8PTnfD07Rxn+0dHY3EbHSzR+LXNeu/MOOqSy+DRKCW3+jrYjXK0ELNdBbdvuPO1yKNpX3o38mGx/hL/zgsII5vn+zcsTt/D0+3rxHflIW2zSkvlQ5gpHsRoHlXM0zj5DDFPOcJ5nqwuJwAHPajns3J8jWuy23ufM0XHMqh+FAQergkRZxo5PAu4tEW2Lt4xXgij6eA8v4dvxo+L/IWcFmaHzQ2UBA7oINpCOVELso3Np+CEvX8e63bB51JdoMMuKVUdLF7ujuNuG3VkiYeLbRThbht1kRe/20aFZMOMQ3hNxFM2/UNkb2L4wyKeaqRfoGf7423c34V+AemDJjiTYKBuO3Zxtz/vDUqnM2yn+Di1Y3I6wHHK9RI/DbRbMTzs/UoMD/SoloLP2zhxQA4Z9iKex1g7fikLZ64kxz10UtrufXCX8bBRjgm7nGP6GniDPcbBoHbxt3Tgv5kwaDPvEWUzQYnPCz2ObAzDs7BXEMZ1adN9ItoX4TxdwsSwT0c8MjDMFK2RdUd7/rKwWdCfMTftXctiuGxtvV3zn4H+CN6z792THtxJQYS3SOweDzeMeFGKif95HlfOEl9vfMFCYcCncv6L5uXT2yUrmY5kTdL68ZUYZz11WN5LiCd+lknzZSLPvevnFTJHGTCd9wfOHBC4oSyXMDvfj+cTXw3YmatgfQZ47ceSXY7cxwkzh/dbYpirdJjnRWFQ9lote0YsnrFYPPE316ZjOO4XJvyhcRw0zfEgjmOVj/L0esjT6Cp8n3VDQ2cv9ayxN847Z53Ufr5B+xU7AIZP5P7qjTEcvB2WjYy18jH8mwUcN5RwX+lyCswu3uKGj9RnsLe7mLPH9loPo3QN58Wb/PvWYaxdBRdq0/jdyvicNeXtAatic8lsrv3hpyMWD/OXNjv36GHvYn7YgAa7Dv2omI/1qxCT8nHodMTiYa7H+MR83ICYkw8+TtCayo4zG3q/qaMI4updQ/di1HurZodosx+iMc5D5HE24dI4+8NeeLcd/gjD4+PfjzIMkwV9C+nyMenHeBhIisf38dicMM/npwijvFI+zT06YtjPUDmysO44sIIDvkb6inXe6RmicmL5+5wdR0PiqCxe7wmL9ZE+z8Nh2dB7DBrDciH5i3Q/Pu6jv6T58f1ddu+FxemE3CLu3In2Wy2Jfwt8hn17Tccb9/lfM/KQ0uPf8Q1W5qgTX57u2XeAY98mDHXG9PUdsgOKj+RifN+zGMVH4dw9SLT/iLA58zaTORDCxsE/wP5Acqgnl4PjMuHOzEyheJj6Ftw+VTx3wj4z/thxUvQjP7J2lhgeUUqQ/QjhMT9ysxfena/7CeB0x3glD3su7OYfkYN7dA3F6vwWzcFbs7GZNdjPHczdl/sLbvtu+nj/jsTjeQCalwdw8IWcnwfCMA/L4/USk8eTE6AjD8dkESZbpPpH57Ntvfs=
*/