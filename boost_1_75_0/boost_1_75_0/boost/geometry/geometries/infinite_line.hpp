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
sj9XZpnH254OJyxrnOm+IBFJZ3GAR0yOxvRoMMxcxmEyWytk8dNRPGiO0RZHNPIwLcV9eH2cODRrX4+uZIb/UNGYx5vq9dsIwZY887mlHxWtp5HICtrj7Lfi1XVj5QfGFZyl0h02z8sZ9bAuXJNP2i7WCGXamTKv7bVOgkeoxHfuJuswb3+Zz4DvKMASd/6IrzNVXZ+vU5h7GAdV6+76nw2NNxz1ETI0qFRVxG43rBne3v6WNXuV5KzfWxHeskZNL3ym0/BTtjAngs6kgv/3vhmm1GjsoOOC3pTVXDbjo83+L4y+zTRVhjsmG1deZuo89T2wisqxLMvbsYIveBzl2bDp631gkXe2FGtdwIAaf1Y60XTwSMP3j7f2kVXxqyKxrD76S5TkV/ugQXvcfHO49PKoiYvvF/FNb6WmNlV/2FzJ7/hhGK5kAjLg9s9JtiPDtC7icWmmHdS5uidncEe1pUTUkR9ujnGeD5T7BHWr6FdZG0k1CWopT3WKFLNQkYeXPAJOVgau7v7p+bgMDw6e/KMY4JeU+SYD40bVUv8LtuNOM+/s60g45kCygZvab9TknOowa2gwvklYEN6Sm4xUaAoN9RtvAIr7O8+NNKMyHJXmBJVShWubqwtw60/OqkjSPB+XeC4k/PYxALHtmTyCq86k4oRdz4t/wTdsUjluT9j6ER9RwgtogXKBaDBWti56Dpi+vU+9PWQBt9av
*/