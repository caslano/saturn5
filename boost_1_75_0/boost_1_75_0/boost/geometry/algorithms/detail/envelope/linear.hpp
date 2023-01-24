// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_LINEAR_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/envelope/range.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/envelope.hpp>
#include <boost/geometry/strategies/spherical/envelope.hpp>
#include <boost/geometry/strategies/geographic/envelope.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Linestring>
struct envelope<Linestring, linestring_tag>
    : detail::envelope::envelope_range
{};


template <typename MultiLinestring>
struct envelope<MultiLinestring, multi_linestring_tag>
    : detail::envelope::envelope_multi_range
        <
            detail::envelope::envelope_range
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_LINEAR_HPP

/* linear.hpp
MeAmQWQ3hG4IWUyH3c13Po1u2JFwx8SGyCNPnYFqzqbuI9Ix0x3yBiT3QKRkT+9n7GGseLddlFXtT/CNjIwg+UHB0Avww10dpa00oPLSbB70THDmJ3i7sMsEtUzhliG8D6FJypc7bGpYe1wJynXOuGuhs1QudE/0xbyL/HPt3qkZ+cFgRpm3TK6RlqIGaIIGBj4ra/4cEIhAKDLGRQjGha/PuKj5FpcN74LIUQhvQ8iQdEQkJqUaPG7ArDTdOLsbOmyF3mGpyNRkYGTtxi9iem+8jQlNDEPtNTtGPv/xbxlibhHUSsqIih5hnZgvTZYblYdhfL+LtS7HOufnriL3ZFfM4dRi8hLxgE153nveV+Sf7ItBh1+FVnGQUaJspQKh26v4CWaNookmjGkr/1Ue5vzXDIjMgbAsnFgn+PxN58aWsJULWyC4umGJmE0n7XbClJAhxefhXngkXeFMK2bhIbghnmF4JL2efcf87PhJAfQRefZNE3aJNf/KGJ5/D0TCEIrGJPLfYsp/dIx1neuwaS/AstMGuY+Q3JOJncpTB/vKUy1j+Hp/L0Qeh3AKgiuxmPbGn9dx6enGBxtQR/AlLGDNcQheRA7nsTGJUbDdGAXU6fD0rFV2LORJecpxtRZ7aajCTgh+R5Vao01Vt+ON6ka4+z6EGv5ELX4bQgYNVTRkw9OV8PSj8PQ2uHMQQg1/oha3wb2QVqXmUcz+
*/