// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CHECK_ENRICH_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CHECK_ENRICH_HPP

#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
#include <iostream>
#endif // BOOST_GEOMETRY_DEBUG_ENRICH

#include <cstddef>
#include <vector>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template<typename Turn>
struct meta_turn
{
    int index;
    Turn const* turn;
    bool handled[2];

    inline meta_turn(int i, Turn const& t)
        : index(i), turn(&t)
    {
        handled[0] = false;
        handled[1] = false;
    }
};


template <typename MetaTurn>
inline void display(MetaTurn const& meta_turn, const char* reason = "")
{
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
    std::cout << meta_turn.index
        << "\tMethods: " << method_char(meta_turn.turn->method)
        << " operations: "  << operation_char(meta_turn.turn->operations[0].operation)
                << operation_char(meta_turn.turn->operations[1].operation)
        << " travels to " << meta_turn.turn->operations[0].enriched.travels_to_ip_index
        << " and " << meta_turn.turn->operations[1].enriched.travels_to_ip_index
        //<< " -> " << op_index
        << " " << reason
        << std::endl;
#endif
}


template <typename MetaTurns, typename MetaTurn>
inline void check_detailed(MetaTurns& meta_turns, MetaTurn const& meta_turn,
            int op_index, int cycle, int start, operation_type for_operation,
            bool& error)
{
    display(meta_turn);
    int const ip_index = meta_turn.turn->operations[op_index].enriched.travels_to_ip_index;
    if (ip_index >= 0)
    {
        bool found = false;

        if (ip_index == start)
        {
            display(meta_turns[ip_index], " FINISH");
            return;
        }

        // check on continuing, or on same-operation-on-same-geometry
        if (! meta_turns[ip_index].handled[op_index]
            && (meta_turns[ip_index].turn->operations[op_index].operation == operation_continue
                || meta_turns[ip_index].turn->operations[op_index].operation == for_operation)
            )
        {
            meta_turns[ip_index].handled[op_index] = true;
            check_detailed(meta_turns, meta_turns[ip_index], op_index, cycle, start, for_operation, error);
            found = true;
        }
        // check on other geometry
        if (! found)
        {
            int const other_index = 1 - op_index;
            if (! meta_turns[ip_index].handled[other_index]
                && meta_turns[ip_index].turn->operations[other_index].operation == for_operation)
            {
                meta_turns[ip_index].handled[other_index] = true;
                check_detailed(meta_turns, meta_turns[ip_index], other_index, cycle, start, for_operation, error);
                found = true;
            }
        }

        if (! found)
        {
            display(meta_turns[ip_index], " STOP");
            error = true;
#ifndef BOOST_GEOMETRY_DEBUG_ENRICH
            //std::cout << " STOP";
#endif
        }
    }
}


template <typename TurnPoints>
inline bool check_graph(TurnPoints& turn_points, operation_type for_operation)
{
    typedef typename boost::range_value<TurnPoints>::type turn_point_type;

    bool error = false;
    int index = 0;

    std::vector<meta_turn<turn_point_type> > meta_turns;
    for (typename boost::range_iterator<TurnPoints const>::type
            it = boost::begin(turn_points);
         it != boost::end(turn_points);
         ++it, ++index)
    {
        meta_turns.push_back(meta_turn<turn_point_type>(index, *it));
    }

    int cycle = 0;
    for (typename boost::range_iterator<std::vector<meta_turn<turn_point_type> > > ::type
            it = boost::begin(meta_turns);
         it != boost::end(meta_turns);
         ++it)
    {
        if (! (it->turn->blocked() || it->turn->discarded))
        {
            for (int i = 0 ; i < 2; i++)
            {
                if (! it->handled[i]
                    && it->turn->operations[i].operation == for_operation)
                {
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
                    std::cout << "CYCLE " << cycle << std::endl;
#endif
                    it->handled[i] = true;
                    check_detailed(meta_turns, *it, i, cycle++, it->index, for_operation, error);
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
                    std::cout <<" END CYCLE " << it->index << std::endl;
#endif
                }
            }
        }
    }
    return error;
}



}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CHECK_ENRICH_HPP

/* check_enrich.hpp
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
*/