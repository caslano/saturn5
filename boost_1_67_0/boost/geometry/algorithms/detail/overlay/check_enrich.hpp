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