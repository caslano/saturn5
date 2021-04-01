// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017.
// Modifications copyright (c) 2015-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_BOX_HPP

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/expand/indexed.hpp>

#include <boost/geometry/strategies/expand.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace expand
{

struct cartesian_box
{
    template <typename BoxOut, typename BoxIn>
    static void apply(BoxOut & box_out, BoxIn const& box_in)
    {
        geometry::detail::expand::expand_indexed
            <
                0, dimension<BoxIn>::value
            >::apply(box_out, box_in);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<box_tag, cartesian_tag, CalculationType>
{
    typedef cartesian_box type;
};


} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::expand

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_BOX_HPP

/* expand_box.hpp
43+7eDBIvn+KnZDpepfJ3VKe4oPS2j3J209j3mig8Z5qPZyxIjhkwJHWTHV7ZNPt9PRAMTyguAvcA+dxwvRYekSUDCHGYdeYGB72wgElgvIeHgXqI+wssfPNfneHYiMpw1YaC3vKVj8m3opzHeGRyoRvcTPzp74H8vKrScofk3ZvfS9CTRr7A6lsq22QToLreOIdsqv4OPfRp5avNOvKM+ZkUtjX9DBuwW4EYZH0z2csRKZLT/QUjtatKUVUuSbLfNfJ3vAva1cPWZ+aWjmOPd3lA3inzeBkYKBH4KIiGfIalTPo0Xb9wKnt7eNJ9yvVEX4d0sHAxkBBv/anzynZhMaLxuxMzwZvpqL+MKwm00FXM8KhB9jF5EpUW+GFkg0LvDeNS6jGIHctetTR4prE5P3Dc1/NNIUBzMsglpL7VOOGoYG3QGnLLJc7iLCjK6LybsFK9zdFJ4DNVHRR2jODE/TTUgqU6efPMwUiZ1zMEn9p46WnJS2m0WFu8OO5Ci4j8HVChfoyL4AuEh3ETr6gdeZsdewwF+l7BP9zGkxYmi4qYeoknfCpwp2h6A==
*/