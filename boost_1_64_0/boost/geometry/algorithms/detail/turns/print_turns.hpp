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
hpgnDFRlzALJXXxo8pEQ7WndqxCxLg0NNQ8MwAtdl4Vj7GorbAciSDkAjmrBGHibNeFH5h02MjcJE0dyPS5DF54SeR8hUGLc5ZnPrP8ZX1bKNVtonahMaq484diQKzosZlRFWtHTbA7W0WE7jjO6oRCzdEPOuvlQp83r69eSjuISCOL6VBdmEBXMycIPw2QG+oBZ1ZaihBMOAnGZDgqSH+r8OB+DI8j8//Ll2un4DF5WhE6NJQfk+O3rVqrSj8Abr09kHNn5V29AUEy2t6go8Mns6wq4NQyfXdxtTOdE0y/umEuizD52Pv0wjALmSV492i2pWyVkIJufhu4R+HjU1t7TOBUxiTOCNJWNY8xXfKI6mPWl87JvW7d99kx2nmlmGjGwo5HtiKV56eKRz95gKWLAe0PdG/mBcbe62H27W5sF2Om4F7Pxo5VYSfXsFL60cJ0Dk1zl7Tjh3Fbeuuc92xwyk4ArsbdUN6R4pLXG1Qo4Nj+0hr+VtKTLBJmUCb3EjRDqAuwfv3jAhd0VbAW7T3LFpeJ01EUFfvM2v2j8H20DFWcCPFp5udaD8Q==
*/