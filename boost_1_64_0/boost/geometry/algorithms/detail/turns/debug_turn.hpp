// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_DEBUG_TURN_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_DEBUG_TURN_HPP

#ifdef BOOST_GEOMETRY_DEBUG_TURNS
#include <iostream>
#include <string>

#include <boost/algorithm/string/predicate.hpp>

#include <boost/geometry/io/wkt/write.hpp>
#include <boost/geometry/algorithms/detail/overlay/debug_turn_info.hpp>
#endif // BOOST_GEOMETRY_DEBUG_TURNS


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace turns
{


#ifdef BOOST_GEOMETRY_DEBUG_TURNS
template <typename Turn, typename Operation>
inline void debug_turn(Turn const& turn, Operation op,
                       std::string const& header)
{
    std::cout << header
        << " at " << op.seg_id
        << " meth: " << method_char(turn.method)
        << " op: " << operation_char(op.operation)
        << " of: " << operation_char(turn.operations[0].operation)
        << operation_char(turn.operations[1].operation)
        << " " << geometry::wkt(turn.point)
        << std::endl;

    if (boost::contains(header, "Finished"))
    {
        std::cout << std::endl;
    }
}
#else
template <typename Turn, typename Operation>
inline void debug_turn(Turn const& , Operation, const char*)
{
}
#endif // BOOST_GEOMETRY_DEBUG_TURNS


}} // namespace detail::turns
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost:geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_TURNS_DEBUG_TURN_HPP

/* debug_turn.hpp
5sqVSlzEO/+1tuygz18o8cNm1ivzDBXRo+3zZZ2Gp630ldqv6tceFPZJcbeG3rWclN56sX7Yryly/eOqpJUDN8g/XhUnT0rRjI5VnWJ3vVfKSMuVwvEAJOfdRTtqoSc5OsFET9mrOhbmNi60I6acw63pnHuehC8AOlrx8epMg+0K7dRDme7eraYEzPn3gj8DPj2p6x3Chvj8E+F0tHP8b+V8d56tg7iy0bHyH/In5dENxe0mtX69Zvf4fGB0NQC8WmBY1TEfCcR4D5DNO0a2B9e6fHdT/iT/GiKaHyGd26pTrDlMXrDxMBSgErX1uwUTLJdih+tvoLeJNjwnY5v8avhVPSIy2AwiMRvmrQyMrXPy9bn86d6qnyJkXY3I5pZrytiZBiSEnEuFOPJBIjuVbtl3Y0mXIxB6Y6gL+OUFihSIBQasy+aqPkH4NP7VnD1I+xGNRNAz2EXwpqmygJoA2oVqrApFiobj2bBKK8GNKtiYFyyEUi++5vde2Ob8o7QO+wgQgBX9aD/3bJD0gx4HHPedm0M3lUlauLEYw1txI7XLhOgDFoBc99q/Mg==
*/