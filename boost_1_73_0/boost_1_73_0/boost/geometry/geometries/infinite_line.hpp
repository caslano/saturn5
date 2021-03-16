// Boost.Geometry

// Copyright (c) 2018-2019 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_INFINITE_LINE_HPP
#define BOOST_GEOMETRY_GEOMETRIES_INFINITE_LINE_HPP


namespace boost { namespace geometry
{

namespace model
{

//--------------------------------------------------------------------------
// Structure containing an infinite line.
// It is written using "General Form", a*x + b*y + c == 0
// Might be conceptized later. Therefore operations are implemented outside
// the structure itself.
template <typename Type = double>
struct infinite_line
{
    infinite_line()
        : a(0)
        , b(0)
        , c(0)
        , normalized(false)
    {}

    // Horizontal: a == 0, for example y-3=0, y==3
    // Vertical: b == 0, for example x-2=0, x==2
    // Through origin: c == 0
    Type a;
    Type b;
    Type c;
    bool normalized;
};


} // namespace model


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_GEOMETRIES_INFINITE_LINE_HPP

/* infinite_line.hpp
ccnbHx0dDzP7OWqvKw0eu2xJ+7T+Pe1nrP0o+Bpj/0ftb914aK85GLpz/Verlz00/r5cxmYOwPZhg1ttL19wtPPciVuuXbvq/m8YW0ntq4u3PPNM1yjf/q2XPnpg6kU1jO2l9l09vR/dt3mRdM6n3c3fbnKDfw3OJTs+lPcfk8/f/H31HQUPLPbe9gJ4NbU/XGf/+vicmtd++9HB5wP9Ai+Bfqj9+LvPFNy6bv0NjX875g9dNPEAYx9S+9xvp0w=
*/