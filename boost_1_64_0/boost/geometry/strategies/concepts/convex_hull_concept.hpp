// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_CONVEX_HULL_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_CONVEX_HULL_CONCEPT_HPP


#include <vector>

#include <boost/concept_check.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
    \brief Checks strategy for convex_hull
    \ingroup convex_hull
*/
template <typename Strategy>
class ConvexHullStrategy
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    // 1) must define state_type
    typedef typename Strategy::state_type state_type;

    // 2) must define point_type
    typedef typename Strategy::point_type point_type;

    // 3) must define geometry_type
    typedef typename Strategy::geometry_type geometry_type;

    struct check_methods
    {
        static void apply()
        {
            Strategy const* str = 0;

            state_type* st = 0;
            geometry_type* sp = 0;
            std::vector<point_type> *v = 0;

            // 4) must implement a method apply, iterating over a range
            str->apply(*sp, *st);

            // 5) must implement a method result, with an output iterator
            str->result(*st, std::back_inserter(*v), true, true);
        }
    };

public :
    BOOST_CONCEPT_USAGE(ConvexHullStrategy)
    {
        check_methods::apply();
    }
#endif
};


}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_STRATEGIES_CONCEPTS_CONVEX_HULL_CONCEPT_HPP

/* convex_hull_concept.hpp
H0vxNO7BESzDM1mWF7Ic/8J9eA8r8Anuy7dYmR+wKr9gNW7hAYyVS+liiTZV2lrFy+Uo//45lMuB5mvBemzHBuzMhuzBRhzAxhzMpjyfh3IWW3IJD+cyHsEH2Yrv8Uh+zHb8J9uzVFF5YCUezdbswKN5PLvyBKawG8eyO89hDy5iT97IfnyC/fkST+R3HMAfOYglrPNw/pUpXM5UvsoRfJOj+BFH80uOYew392PZiOPYi+PZn5mcwomcwUm8g2dxFSdzI8/mx5zCLE5l1RJ+A8SuPI+nchpP43RexvN5Ay/kI7yIa3kxP+Il/CdnsaTtein34Ww24hwezsvYivNDfXCO9Fu38Lwp3Gc2L+LvoT5ULa0+cD+2ZW12Yh32YF0OYD0O5sE8k4fwStbnjWzApWzMB9mU5aRxGKuxBduxJU/g4ezDI3gyW/FcHslL2YZz2Z438Cgu49Fczw58jx35ETtxj2LWkXV5HFuwC09iV6byeJ7B7pzHHrydPbmWvfgSe/MH9mEl27Eva7Ifp7E/r+aJvJ0DuJYDuZ6n8kMO4t95Gssp/9PZgEPYhCPC8cyxPrTlirfxsp08C1bvwnYaHY5nY9mQ49iCaWzHdHbmBJ7KSZzGs3gxz+GNnMK7OZWv81y+y+n8hOezmDQv4J68kE05g+14EY/lTA7jLF7IP3ExL+VNvIx3cy4f5RV8hfO4ifN5gHW8ksfwL+zCBTyTV/NKXsNruJBLeR3v5iI+xL9xLZdyP+V2C5txGbvydg7hnRzJu3gh7+YcruDlfJDheVZO2zDfeRZ8nnVVGduBV7Mlr+VALuSdvI5ruYhv8nq+zcX8lTeE4+GNbMQlHMSbOIE38y/8G6/hrbyeyxm+XwntwfxNrM83JvPb4frzHZ7M93kuN3IeP+BCfsjF/Jg38RNu5eRioc1XaAtm+Zat3jH2WhKe397K6ryTTXkXj+UK9ue9PJX38Tzezwv5KJ/jY3yPj/MjPsVfuI7VJf4C6/BFHsP1PJkvcShf5nC+ylS+xpF8nWncwPl8k1fzHb7En/kP/kL3A07M9hsWZT+W4FCW5BjuwfNZmtewDG/gnlzKvbiOZfkS9+YP3If+XWRfHspK7M7KTGcVTmQ1Xs/9+AqrcxsPYBvHh1rsyNpM5YE8g014J5tyDQ/nVzyC29iaVUs6nrI527AX2zKD7Xg52/MKHs2beQzv57F8m524kV1ZsZTjJxvwBPZgN/ZlT45gL85jb97KPnyBfbmeJ/INnsRNHMhPeDLVP885ctq8OQeF42Aj/04Jx8F7wvX6fdyfK1mXD7I9VzGVj/JyruZ8Ps7r+QSXcQ3v55N8lU/xTT7NL7iWpaX5DMvxWdbic2zHdezI59mHL3A8X2QG13M6X+J1fJl/5Stcwlf5AF/ju3yd7/NNbuHb3LeYesv6fJfd+R578gMO5EcczE3M4Me8jZ/wcW7mj/yMFZTnF9yfX7Imt1C5e36Q087OuodyP8S/O4Vybx6OKy05jkdwIlvxXLbmRWzLy9mOV7E9H+JRXM2O/IrHsExRy+fh7Mx2PI5D2IWpPJ4X8ARew258hN35BHvyJfbimzyF58n7qfwrB/FvHMJ7OZyvMIWfcxRj++doHs0x7Mux7M9xnM7xXMI03swJXM4M3s+JfIyT+ATPYvh+Lt62DlOSfD93+F7KlUeyDtuwI9uyH9txNNvzTzyKi3k0V7EDX2JHdiuqXDmMx/JMduYkHkf58RumRLs5323JjzjUv2eE7TxXvqvwCtbiPNbnlWzBq9iDC3gRr+ZsXsMFvJZ/5XW8hYv4CK/nWi7mi/wr3+YSfsab+A2X8icuY+w8eRcP4N08iPewOVewLe8=
*/