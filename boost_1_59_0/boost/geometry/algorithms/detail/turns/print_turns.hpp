// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_PRINT_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_PRINT_TURNS_HPP

#include <algorithm>
#include <iostream>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/algorithms/detail/overlay/traversal_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/debug_turn_info.hpp>
#include <boost/geometry/io/wkt/write.hpp>
#include <boost/geometry/io/dsv/write.hpp>

namespace boost { namespace geometry
{

namespace detail { namespace turns
{

struct turn_printer
{
    turn_printer(std::ostream & os)
        : index(0)
        , out(os)
    {}

    template <typename Turn>
    void operator()(Turn const& turn)
    {
        out << index
            << ": " << geometry::method_char(turn.method);

        if ( turn.discarded )
            out << " (discarded)\n";
        else if ( turn.blocked() )
            out << " (blocked)\n";
        else
            out << '\n';

        double fraction[2];

        fraction[0] = turn.operations[0].fraction.numerator()
            / turn.operations[0].fraction.denominator();

        out << geometry::operation_char(turn.operations[0].operation)
            <<": seg: " << turn.operations[0].seg_id.source_index
            << ", m: " << turn.operations[0].seg_id.multi_index
            << ", r: " << turn.operations[0].seg_id.ring_index
            << ", s: " << turn.operations[0].seg_id.segment_index;
        out << ", fr: " << fraction[0];
        out << ", col?: " << turn.operations[0].is_collinear;
        out << ' ' << geometry::dsv(turn.point) << ' ';

        out << '\n';

        fraction[1] = turn.operations[1].fraction.numerator()
            / turn.operations[1].fraction.denominator();

        out << geometry::operation_char(turn.operations[1].operation)
            << ": seg: " << turn.operations[1].seg_id.source_index
            << ", m: " << turn.operations[1].seg_id.multi_index
            << ", r: " << turn.operations[1].seg_id.ring_index
            << ", s: " << turn.operations[1].seg_id.segment_index;
        out << ", fr: " << fraction[1];
        out << ", col?: " << turn.operations[1].is_collinear;
        out << ' ' << geometry::dsv(turn.point) << ' ';

        ++index;
        out << std::endl;
    }

    int index;
    std::ostream & out;
};

template <typename Geometry1, typename Geometry2, typename Turns>
static inline void print_turns(Geometry1 const& g1,
                               Geometry2 const& g2,
                               Turns const& turns)
{
    std::cout << geometry::wkt(g1) << std::endl;
    std::cout << geometry::wkt(g2) << std::endl;

    std::for_each(boost::begin(turns), boost::end(turns), turn_printer(std::cout));
}




}} // namespace detail::turns

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_PRINT_TURNS_HPP

/* print_turns.hpp
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
*/