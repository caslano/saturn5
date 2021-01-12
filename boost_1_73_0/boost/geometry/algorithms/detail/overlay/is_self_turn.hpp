// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2017 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_IS_SELF_TURN_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_IS_SELF_TURN_HPP

#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template <overlay_type OverlayType>
struct is_self_turn_check
{
    template <typename Turn>
    static inline bool apply(Turn const& turn)
    {
        return turn.operations[0].seg_id.source_index
                == turn.operations[1].seg_id.source_index;
    }
};

template <>
struct is_self_turn_check<overlay_buffer>
{
    template <typename Turn>
    static inline bool apply(Turn const& /*turn*/)
    {
        return false;
    }
};

template <>
struct is_self_turn_check<overlay_dissolve>
{
    template <typename Turn>
    static inline bool apply(Turn const& /*turn*/)
    {
        return false;
    }
};

template <overlay_type OverlayType, typename Turn>
bool is_self_turn(Turn const& turn)
{
    return is_self_turn_check<OverlayType>::apply(turn);
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_IS_SELF_TURN_HPP

/* is_self_turn.hpp
+7uP0xUjQxtPjelXTj5wQPdaGsJ88EHjMFtgSUCYI8fGYrbhuOsx6q4hBrdH9E5MfN7y0AEGt0iEcJn20YShPYToRx43pMtvzJ4c0tFIDu3lqKz3nPKY62u72zcccpvL3W97MmIcC7jW3tzd8TT1dEbDrZa/g3jGgDZaEv6ZfzlDdFR0cNrmOaRhu1m6eB+hZ5GGR+11N9Q7O98ddp91+DxiVrdXN6k8Fy9gGjoffuXKqFsZ
*/