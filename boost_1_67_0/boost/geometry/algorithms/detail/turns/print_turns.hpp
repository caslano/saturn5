// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_PRINT_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_PRINT_TURNS_HPP

#include <algorithm>
#include <iostream>

#include <boost/range.hpp>

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