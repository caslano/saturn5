// Boost.Geometry

// Copyright (c) 2015-2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_RESULT_INVERSE_HPP
#define BOOST_GEOMETRY_FORMULAS_RESULT_INVERSE_HPP


namespace boost { namespace geometry { namespace formula
{

template <typename T>
struct result_inverse
{
    result_inverse()
        : distance(0)
        , azimuth(0)
        , reverse_azimuth(0)
        , reduced_length(0)
        , geodesic_scale(1)
    {}

    T distance;
    T azimuth;
    T reverse_azimuth;
    T reduced_length;
    T geodesic_scale;
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_RESULT_INVERSE_HPP

/* result_inverse.hpp
Y8rF/tI0oW1cRuHnhPxrqxpnQSK/pJUXM1bRBtB+yajQBQ295MvFsTprawJrArvLKOfAuLaDFn/QT+XlfOVPacISDy3S9FolLjLArNf8W/ZPfbPDy8JD9obo8hkmoyIoXPzdb7PN0q6kGiz3jYRyXcx67OOqoF3o5diYpVz4ElW3SczFPqPP1amgD3zrTpeGbP7dOe+pzOwVm+/9t7sVCoV5kEkXjlyrbjiRc0dZu9rX0K5+f3kzOTUerVLz0TBz2WP6b67bjNHphPXnyNE/O09lQs+iXBNbAzcZIc37SMPv0ooZb+S4PvNQdYZLK4u9+B0rslVzJiIyd43mebElMAqKGtKmGi4wML/fOpw37ahob9XM5RkuFt1YcyfmYFFofzP7a0ScfpdW+5RpgHpWKe2IoqLViXms6zct20umKLOrYtXO9nVapsZ72FAZ/9kHkiIDJ1eqwwTDtsDylMp0MTYS8hea0UpvCS5Mr0kozOwP5lYjsZayJdZtrz9E7TzoYyecVmk/D4+aJIntLKDwGz3SMdzVKX1u06mkNx/sitrndDmrf+zywRqQjqoknVQfZoXqYYWe5x8YBFoj4InXMbWl5pop1zKoly2+oYevqp7BWr7ljUiqg9j2tZuPMpN9mtygUau7fwx6qmNpxf84dDBsuKNGcccpGX27DrHHaZX+eynuZJMWavluP5pr143SAg0XwiuoIhl/5r0t
*/