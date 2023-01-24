// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DEFAULT_DISTANCE_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_DEFAULT_DISTANCE_RESULT_HPP

#include <boost/geometry/strategies/distance_result.hpp>


namespace boost { namespace geometry
{

/*!
\brief Meta-function defining return type of distance function
\ingroup distance
\note The strategy defines the return-type (so this situation is different
    from length, where distance is sqr/sqrt, but length always squared)
 */
template <typename Geometry1, typename Geometry2 = Geometry1>
struct default_distance_result
    : distance_result<Geometry1, Geometry2, void>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_DEFAULT_DISTANCE_RESULT_HPP

/* default_distance_result.hpp
/+gK7MLuIrsZM9FOCvjI9QfYvm6R3U42eTrzri5QGfEBFOO0qnXlW/dm23PwsR96f+XIm4+ED9pv0azWEAf4IC7WL4CG4QqryxfANWOZ1YMerlmqNQWZVYwg1lngBldEJ9GK4iHnlMahxDu5Q+opJm/SkfHk9XfrdN4EgPC0RwKlVeYguUP1Cyut2zhfpdUe/qDmzgto8COOR3nbJ9NJo9jf23JLU/p4TOvu7lTrODfGB6rsLnInE/XpfDK7ADHhUX2FKLh5fwx+Yo4V9xDkNrEzq44c0+oTNGWe6T3nENg3A1xTqMOT121N8d3aQazy2zsv8SNJgZcUAqb+3STHz+uYWtrEiz6xPCCJWR5SW/u6fy+MC1IG3EdZca27HXuvu3V/c7pezKYZvH085ordszGAJHu6snnlIOMXmGz7pjf51m1AXQ8eK5S8zBxWC6pZAuXmAjXBDYTDpHU59Sfiy8qG7p5/eC3zs3s83+tY8g9nnouFqUjdeXiftOvUVom6RBJZpubNN3ZgJiinM9WUoAq9dp6hcR1Lp8qh6gWl5E+fQkTTcX7BbhR7z9eeL4l2T4so+z9mIyu/s6zPYqgRaYceR6hXUlM0atjSpHIPJK87ZFcNX9WmVEy7R56f87pynw1ux63a3HLU+NEq9CmI7nPDqYEUF479ZxsmD/g94bNt+5g3aQxzVaEtOUOsemx3TD5fBRuSyhuqaEzD
*/