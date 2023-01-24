// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle


#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_FILTER_CONTINUE_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_FILTER_CONTINUE_TURNS_HPP

#include <algorithm>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>

namespace boost { namespace geometry
{

namespace detail { namespace turns
{


template <typename Turns, bool Enable>
struct filter_continue_turns
{
    static inline void apply(Turns&) {}
};


template <typename Turns>
class filter_continue_turns<Turns, true>
{
private:
    class IsContinueTurn
    {
    private:
        template <typename Operation>
        inline bool is_continue_or_opposite(Operation const& operation) const
        {
            return operation == detail::overlay::operation_continue
                || operation == detail::overlay::operation_opposite;
        }

    public:
        template <typename Turn>
        bool operator()(Turn const& turn) const
        {
            if ( turn.method != detail::overlay::method_collinear
                 && turn.method != detail::overlay::method_equal )
            {
                return false;
            }

            return is_continue_or_opposite(turn.operations[0].operation)
                && is_continue_or_opposite(turn.operations[1].operation);
        }
    };


public:
    static inline void apply(Turns& turns)
    {
        turns.erase( std::remove_if(turns.begin(), turns.end(),
                                    IsContinueTurn()),
                     turns.end()
                     );
    }
};


}} // namespace detail::turns

}} // namespect boost::geometry



#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_FILTER_CONTINUE_TURNS_HPP

/* filter_continue_turns.hpp
uuX3GQea2XocGFfXXDb0OKuwwGLLu6n5RdfS2U0UjbpS1z2UI1mSRckSKUsLKeIBXp3QBhvtv7XuLD2Bt2e7Mt35tEN4ae5WzXLyVQnldyapGMdy1hjM8TDO7xUhWrSlYkNzzuUom+X84zpFxuvqM8x9+BBzhAgaF1nNvNnAVOrGNBQ02kLu6loAwFfrvm1z/8mhcHm0bnPBWxz6ZaN0e344wNwoD4cvdEiloyzvWr0bmQEHxjGLTGxwhLxasOfgI7CPLkxI9vwGUtnaVO59FwXvCoZQzC4MYyKHmKuZxIPWb1vgKk4YFoELxu3mG5jsDe8Y81wUx4rVV4e4IdzXAjlmnAms11vpDk7pNPH0LUe79j52zteqm6oxK8izk0ouq6dvSryvBnkWGKU0WXoWFHXCbBLYjWO+6GfDB+ZjYtqXQVs2HeGgLb92GxBwl4RNma3tKFubsZxrmWv5aU3W300Mc0/etoF0NCGn80qD4giQCRJflSelZUTwljfxNQ85XYgpCQdTZqJP3uKU+VgKWb6cgmXbdBfBmPmCvnfdnQRoypBRoVuXWkMlfq0D3h4Eh8bBiINPXvJqwOKn4RNUMR0d6vj2V1Cct1KdZR8ma+hty8p56Y6L4qB5wVvPLsHdVnqVVrRYpLrUBuaPaM2QHi0KTfjsFzuAXFa7B/jpim02rpYqBbaaLd11kfhYMYxLwlRIwnfpyZ9R8y1j
*/