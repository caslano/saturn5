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
m70Mn74gUzxNi/gYbhWFLdYjKtEOlwPnIzbyz1T4Jpfs7enoFYaHEE5g2Gi5/8FRiln2kd8cV61gAsMTfNXC0sm+wuGQSEKxEKRk+7Hdp8E4BawCf4gJibZjQWFVLTYujR1kLKnYXhPPiPg1jGw5+su2uWFKeHtnDGmkt/6EbDHS7/uWHOm7IAIeP3Kf5KL9BStL+1GO+dDfZokTQAhJGx6W5kNPtC7uTUuAJ0koFykoi3PkfJnXR1Y20k9uhMdMEytjC4y387WPfN2493/eZMzX+rP3649Cjm7Sw9PwSCUr9vv1WRKhYedXn47Ov9a2HXuZIffoih8l92gcXxmUHhQc2J4EUAsA7Y9/ts07pTxXh1LxhxTsIVZ5UAoG8eZpEoMYRJ+n01MwiMaDZOn+MCW1dOGFSaZTqM/g9UwxQhbWw+dapP7MRRW/Lq7sHg06IjrCAjq0NmjGE1ZgWRP7LKBh0prXYZ/cFzB3RzLpD2aUpo51Rk7NfN56Q0kgJ3KPeBxzsMJSfMVIw6KDirFYo0JoqTvUy1c8ZzFD03xR7xDEMKW/yj8kvCd/5lC2zofpyU7802B0YrXdiXf1kt5hI9ewmTq7uIuMOSrA7fEOyWNrPZonhfFYfYahOziF95+kOSQh/SNh/i7KI6lVd5XymYdjB8ojEwDTilRL0lUoLWK0p7PamaSCJFqtcSF2wk1DWTLbiS1Lmz44Scj7idWeLUu75YcHljYQq6NYBkpB+/OVTLb6Wmn23638kx4Gez0ypmrS3gRz6Ydc4q8JG1kj4QzsWaADiE5dJ5WL9SOZcJltf9nJ+eu2poffJ9sXGZtqZ2+19OybM9VGiMedaSPEJ2MPEjrJLwaiV6yF/bntuJ7C80ZrGBqdFu/YgoXokqmnyCl3LqfcDDnlynBA9VqBLA3zE4Z5429lYsOT5D6vCY9YsyQzYlJumbkP9NBq4mkA3heXgSsTV8Jbu41ISPBb5eacUjw84ZaMt3XKOd0AQBrSL9gbaDmFAXtQGLBlSD/KAu4awDPgrlV+o+45Yjm7VwlbIbP7CCzrCUIrvjwvOIm6wx9whgL5vjjb8f5zGOlch9pO6Yk5D+vNyI/ah3KYjzpIExWenmFrp61QHpevLHKjCZwjX6An9s/tGQRxkwcwQ0NFVfhemsOMvgc6cD21gFCQxDpmlDFZ4e9qtazD1+13o3zM+OGsA/3rswqLrhQr1kmx6gJ+syjDdrIfJ6VyRYHasmMi/LcuhFcivFxOxEDxfXT+FTxeqMOoKiWXh0UnqypZM3ugNqcgAYsyFFmWq6kerSUAgpMdVKAm9XEOsnCfnLx+CUs5oj6J8F5Np3Bxjlib2Quv9tSQsoIoLU80zKoAbS9fDb4uQGKv+aTPvGIATDAu9N8JMviqhKB/L2Ixz0J8uDHzrvBrmfo6oGat8JAQ/XbdAH4Q7oAO28VIhbGRb8xmVyRa4hUyYLb0fOEvvlu0h5jmf+I0b8c0b8AlXML8+AqSU6y+U3iUeoo6sEz3mGi3EjZ5M1IiQeb3Pr2BevPT5gzRHhnxpfsSPMWttbZzIwWKB+AixVMiRWlOfBKZtS1pxrhGY9xqfcd7cNKbwJ8KQxSRdQqOx/Dm6ZkjuBgzrlQ8rw+eiLL4dTlxjkRJKvlMoxb+6I0J4IuZQJAN2teM3wdQzPVvokoTWaUd+1JG0U4R/iFHUU+Eq7kV9HDG6e+3p+Ou70w0om/CHWnG/EsADvk5PEiSsPJ8ofLdw3M5u0OlwI03smF/xFWIJxzuvbHqU+OP6nLurTyIeONoj9mRSgPTQeHB//ae/tay3S78BidSDAng0EnMX9+ovyDGrV+Zym0ZJNeqwzO5VqU=
*/