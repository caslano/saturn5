// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_NORMALIZE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_NORMALIZE_HPP


// For backward compatibility
#include <boost/geometry/strategies/normalize.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename GeometryIn, typename GeometryOut, typename Strategy>
inline void normalize(GeometryIn const& geometry_in, GeometryOut& geometry_out, Strategy const& )
{
    Strategy::apply(geometry_in, geometry_out);
}

template <typename GeometryOut, typename GeometryIn, typename Strategy>
inline GeometryOut return_normalized(GeometryIn const& geometry_in, Strategy const& strategy)
{
    GeometryOut geometry_out;
    detail::normalize(geometry_in, geometry_out, strategy);
    return geometry_out;
}


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_NORMALIZE_HPP

/* normalize.hpp
TYhY8U7vA/pU9qxhPDjtaUhtIp2Ww0qRFtfL1YAcIyvhlyp9PL5AIlIdKXMnPDFvkcftLvIXBmYEi8LlgQX+hHuycT+aDJtMka4TOAKSgJtGNKI7uh6Ggy/rd3buCcC5x+uM/w31Y3bmbwARwmH0HUhCZ5cMJse3CMYn24MjLEklThVMcxaToHZsZ6q7QTjZ73Vt8OXDMkeeJ8sFnuBbeomxxb3C02S4gW9diL2ztRhwMoukiLYGxzkQLuNbPWbcBM3nNUPkdusD2QyvZGN6LxDPQjoHSegEhGCM6V1OWlVjQ/xTYtzAcVKHq6R8PB61EvM93WADyq6whQ2YBZlvu8LMfqu/K1kwgwG8J91z3YECmITmS4kDWA2PW/5PkHlQlHuvy1nhV4n7OVZunEP+mdiCtF3ifZH7mnOdOwKPM7ufU0B8Aak3bOHupJ/+nSYXICxsujObCLHYrmnE+sboIGq+FB3iIovktcp8daNWrW82inGOsZzKbYEvPYBnoIkiuphhxFBKm6lJUGTSpngmZP6L8Dk/lzjXjjck+QuC/wYNaTtT+FKeKfbAoy8x/geIbyBlpYdp/A9LPDoiqcEXRzebCjcL88NjGUeu4AbUfNxT7A23p0d6smZNS6AVMvsWvkUqpRVyXNmsrtGGYMUtJ6Sl+ovEfc3zAHFP07lj53gRB9PQJkq6u8Iz350Cc212um0NvBcyK9N5ezyQ
*/