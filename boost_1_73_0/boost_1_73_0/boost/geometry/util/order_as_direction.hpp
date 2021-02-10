// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_ORDER_AS_DIRECTION_HPP
#define BOOST_GEOMETRY_UTIL_ORDER_AS_DIRECTION_HPP

#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/views/reversible_view.hpp>

namespace boost { namespace geometry
{


template<order_selector Order>
struct order_as_direction
{};


template<>
struct order_as_direction<clockwise>
{
    static const iterate_direction value = iterate_forward;
};


template<>
struct order_as_direction<counterclockwise>
{
    static const iterate_direction value = iterate_reverse;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_ORDER_AS_DIRECTION_HPP

/* order_as_direction.hpp
dfzp036RvGyrpFTxdF+6Gl6nhSrySXkbLxIFv0/TUZIVyVjFhRonxWiRXsIfaabK60RN0mmijs/Of+31X7fV7XU6usZO7vKlKq7z5XSsruObRC2SUZLecB/zeFGqfALNofNxWpTQ4bJM82wfxk5UmSxmBfaBw8fTIlfxTZxO40sYKC7VdVnOixcHB6PlYgqzPxjno+JgpJe/f13OzEp+hUnM4juVz0tV5mpZJG2FNdtqlo/TCf4XNgQ+zpeX07S4btvZwFDZ+CBfqCKZTrEvaJcmBU87UQPZnjZWU3OYcVrif4o8K3Co2+t85lWEfcReJstFBgPBPkClcQ7b3FbLbJwsqDKtXA8he0ob3Hg0dr5jlWcwGbXdGajeYFtdxkVatNUvveGbs3dD9Uvn4qLTH/6qzl6pTv9X7OzPvf4JHH0Kgy1U8mm+SAoYfKHS2XyaJmMZ89v9HGxt/S7NRtPlOFHbeHpRkZTL+f71NhZMxslEven83I363WEP/ol6/eiNbfHHLClT+OcgzfavX279LsngBMN2Jz+FTcaXDbU7F+ediMZxW8SLeXyAwzSPEfVehYMcpJOG+r3zN6fnnfOe16I3v57O43na0Gbw6yDqnR0PT71GxV1xkOajcrqi1XnnovO20gquWzxzWulm
*/