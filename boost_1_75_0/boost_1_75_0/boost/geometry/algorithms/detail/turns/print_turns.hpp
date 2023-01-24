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
Gxf3Lh+/zW5fiU2GB1smwwqaF1foXGrJu2diwt9cYjBxtcAjxikYR7rfngnwtPd6egfA2N6fFpoAltWj5DjoTq1OdWqVTteDQUuH/dkzGmHwk06xHA2syXKbYOYvv/51cb9Z+ID4wfHxDIJu7yUKA/r5IegHFLviUhPW0s/cWnt8X/ow2DXP3rNwYKVPKtpy9Lu1NTtiqpigtmNcHtTu47TRIcM03XgmUB4Hv9MZyLFMJAx3wwZFtUkc3+9Ko2eIQbxu9ycvpXZt3uEWglNOSs6+YPdelktbpcC3M61jILd+yN4C5Sd/Hq1qtAA9Vt2bcD3xEDnZ9IRjBqSKVoTSyQgyKm/LeqRCskGgc1WngxjHW3fn2Honxi6Yt46mUT597mnZ9huv+dQlcEN5agj5lAElduecvDUGajMPZGFeeiTLqRQimfpB+4z/J8bWP+sfiQSWky4trTYBGaYia157KyWdRM8Vn7LffJW3qqsoHbo9rmrvJS51pLFEyKbGUKZ+FLWSYrJ5GBzJU2++Hl0w9R5k87jiGZmTt46WG3cHE/gMvlf0g/OsoR/UGn+OkUuDvAE6dzBCQeioixuMIL5a3193c6RaR3Jqtb1gj7ZKjVpORSpWseRVXSVYcWQhhQ8TchxDtPb+gV8JZ4moSo25JkZHZSXF+/qhUixParRRKpLOj/ElThRPL9VQJMZI7qDA73cT17jHn3BwP2EO
*/