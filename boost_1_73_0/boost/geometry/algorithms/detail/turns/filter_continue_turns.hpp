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
XdXaJg5IT2asl0XBR10eC9dsUfDmWl32U8hGSOO8Gdu7fc/9lGQ7iqvJJv20D3Y6LBvk3hgd2cGWad7gYM51XzaIJagOVsN4v3vfRnarkph2GjrB92ONxxJm89vlKraM1AYHc53/ukGsTXWwOsayOmW0Q0lZFO9Np7595oPvpyzhSG67IsT1sebHoTPx8uP4kfsD+n09/vZ6yyjoiPiOdP0h3+oCHAusVoNLn9eAXxvEAtMr
*/