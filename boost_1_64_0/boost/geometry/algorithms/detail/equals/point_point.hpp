// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_POINT_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_POINT_POINT_HPP


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace equals
{

/*!
    \brief Internal utility function to detect of points are disjoint
    \note To avoid circular references
 */
template <typename Point1, typename Point2, typename Strategy>
inline bool equals_point_point(Point1 const& point1, Point2 const& point2,
                               Strategy const& )
{
    return Strategy::apply(point1, point2);
}

}} // namespace detail::equals
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_POINT_POINT_HPP

/* point_point.hpp
F/t9DByG9I8aIMMt9+Ho1Z10jz3CnI/2+BLgD9g2+lorW2JkzbVRHJnW5o4vmaWNP4v2EO2Q9jgK+QQDiC/EtqpY0bZdF6eG+bAiH4MWI91sbeG706kd9cu9DWSrOA3G1DSGCXNpNDavMjqlUUXp9w5XdTqa9m0UiPIWy6l2cF9WkxhqdjP3b1AeS+VaXbP7K2Zp84E6peef+OQOqLH9HJSmtqeqc9a0e6qQsN1T1dA3aEoLWY3SWjlLOze+Irds8JYLHYCHuuV3z4NPRml0Xxnla3MpPtt1jDoeTlC+jl2xEu+rFpa0y/X5VsoLjSUVft5A9l2ngJNsrtTSJt6gn9/msRx/b+lR6+7rKY/WLcZ99ctIbr7gjUOlPB6qGFReKpXld8ZDpU1sBDNFeBmxC9Nh7ZMebIDp5NkOxAeM93LvFsppv7aQyYSbs692hulVrDuR9pvTMtKQ4++OIhkdz6OzAZ7/NsLM+OH5p6Uy+kxP3n+x34exQH9nCHnt5KGWedKWkMcni9gu7/IcKJhOCnjs3YwNIy9jUs9nEobPocx/j5dxOq2BbvLH5fdZPFu2c1gelO08L88v2wXMicr2VsbIKvI+KItxuRn7AGOUXmx/jOtszw+RbKyc2IQydRgYztfXy4NNjfEmaa2vr6tt+hJKxwTCNJznN5eynCqh6I8+whhVLBxsIhWyTS9jjtiVyXF8NMRlQ/acj2U4sh9w6Vweclyj9/m4IsBZz/Nzwod9AfM+nsPjsVqPD9kJ5rufEDgaA9/HJORJjk4/HXLasjq9OsB1nX4m4Og6vU5yFJ1+VuKRTqPwuTr9fMSLdKrGh+z4NexNwL7+fLoT41dNtZNaznr1Xer4fKsZO5Ii5oYum64d83uTAP3TitFbk3bBJ/uSTzMW3WN0TQYzkyIZ9krG7RvryjuUdrCT4d7PmHuFEmlGGJkAaHPjobYX8Hx1zvflaI2P85lN2a8+OLC0rW1JfKeHar8zebxqW9S+pNC2bFGLgrUvWrK80N6+JB9buozekIT8Ses7edCuy35mZS8Usl9Y2QFG1mj5kqL5yXnL9VK1fL+htSuC8RpbrisB+HFV+kggzzhJQj8F8MhRMS+MV3NU8P0TxAkcFTIPR0qc57W8npe4LZr0VwATDouMvwKYdFiwv4Kx2D/CGO9RDfTlnRXeV8HyyDdyAGMuqbhswCgp6CXUbWZSxOVb4fDKkA0LLON/AB7dZ7mcMZqMAJO2qg6XClm9sa0YZ901tu/O1Wn9ncsbs30E+xJ6O9aR74jfm5uVweWDfw777bwUK/R2r4p08EeBmbkJMOHzYKwibP+QCINx26fzsJAnmbgesRhsNCrlfyV5tGftUZILp2hUVvarCLs97nwnUlctMS51JfPzJOOmHChbFM77SwLfC+wJ5wt/PycfSpSPGNfz8W/GOR8czuej0bufXJ0z3o+4zn1b9X08RTZQHAQNfqO1aernMO+dNe05TCTuHCAN+3hsmsizkub3VT/Ij/PLiQkjzxe3x8CFuJ0jRM4LPOcZOZz2Ju2kf2d5QO0b7qf8R3NLxsM80VynwW9oNj/6nWk/VddROx9A+UE3LdaLYJE8WOT7b/AWQ0uH24v7mueSPOq3diF54ABw2K4SQ2FluN0khoWytN3uDosXyz78Hp7Di2X/TZoxF873ETMJC/rLvVjm+a2hDnPHvH08HpdxNmNRGfdlLLeM+zGHy5ixoVzrOGx/xlycUZ2w4yzPCUguFv4Ik6nXtPBvrr6a9ON+7nF1vngQ5YEX/iJ/LxAYVULW5QsJ0xb/fNcLc+Ti38dxMOPR4t9/N8pwsvdQvDjCSY+54en9iFzcdRAujwsyuMs=
*/