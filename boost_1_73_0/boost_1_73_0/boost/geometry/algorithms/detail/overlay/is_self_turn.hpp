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
zq+X0AEyOrEv7DM2zXAXrx/P7bE/hCUeHPYv+2M4xpJOveEF9Ye+9uXSd6DGHtvMjVDDD78JVgdp8NgZG7+9sTscMDX0jj07t2jgnPXdM2fQc5h3qBnG7NPw0s95mmR7rs8BHV6OWcBQy4SYgaMJWI5OCWcdtmgrHA+BuLC14NN6irhI9rb2dKEMUW0yCrh+poJQpaMgC+lKPknRou1JloRyJsV0m7fOZBoKugoisTAitn6U0STMwKgpb1KhsmVrvs0bs2gqZnRuXzk3LpJ2MxgPR3q9XPY/+Tcj27Mvbs7Xgo7SVbq3DJJg0Zq/3/pRROjEGhdkaXnuoMaGVpf425PRN/hsb2QbS6psQbIM9pixwlXxinduIhVrp545u0xkpGbGW2gBKbLStU9OPP/fZH463cpWbYfoTWVr3OlWdmh/K0/OaZwsMCGCiNzRwxsKptNEpCnPJ8wfzJkQbxTKe0yZ3NDAahQjwEMykiil36ep2iErSClAkqNUNXTdxUoc8AO94smXYqhQqgIMljRfVcG9YJ4sSuVdhGk1mQfJSx4+bJCMbtgcglgZLTOl68EI0IT0sozdG7K03rokepkmk2b+CBOblMo/xI3SH42tP7fI7KnF8jdeimfW9v7bt63K33bj+hBkOV8oosMt
*/