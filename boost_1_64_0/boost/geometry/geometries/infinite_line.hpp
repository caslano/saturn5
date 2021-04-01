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
z+HZ8g0Xg73txwnXYM4nvDA7wOWTednzdT7nUbe19oOHHyuTgNDv8mBCrUNhqFuUHBc1eIigTkuSog9IsQNHa6/pEwomqLaNQiJX+jCj6Tcgr6sVMKUs+IEeivAzKatejlwviCFciEtXEA3zZfZavw0lhkWxUSiGwA5h0kr+tfq0KeizOP9CXOgyc2/9co4OHtay0Pl39FHwmWmCsGJbf3HyixUPiKzWmsf3aOhbKD66vfXESAp+jrm1XSCp8Iweak2XeoMdRzOq4F+Zv/xPn6ktYyOjmzeb6WPAPtJ4qTjREzhBKwyRk4sZmr9X5YUWS/frO0EiOQyNJm7xwso2ggdzEYHKIbrZHyCHGdJonRurJS83n9XQiTnJD/UupRZ/06AgzdV3eCmhoFiUF3udlC/7VIJI7Bl8Bi5HyiP9jqaQ6czJM6WOGg6uUIT94HsanbEcb2O11Iqpq11NbUBfJDEJE53YUYzQpQHN/cOl70gNjChD+JKwnFMndOqpi8V1U2I7vQTGSG24SzIBpVJ7kRd1jQKLABEygYzZvmE+P0ZtJvYaQsP9fvMSPw==
*/