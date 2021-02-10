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
DBrQRwup1bEkweZOHRGVYNo14BWnFkpmm9mCcgJhKltG64YrrUr5tIzDsdwqV+GXMziFbziRy5/NWdeePX5mD7+aQ+YOkT1DZTjysJ2+7nvT/mRaKmHT0cIvZuYNC+lb/fEnnO0kwlGr/fjJ02cn/3l+2v2996p//vrN4L9vLy6Ho6v/jSfTd+8/fPz0mc0wweaLpfjrOlzJKP47UTq9WW9uvx518ghkSilVFlx7pK5idPs2f3ACcMweDIjdEFKlcSjdIMiESDZl8vC6joQtzUwZvtEUEuqVpjEjjadJDnqW4thPsgG3wCBJ1BenmoRRQGkk2hpXIHTD9DSHUC4q17xTOzKm7M+qAf2MXTEYZ0r/lFyp4LsOPtAroTzJF4yyBc6g5Y4j9HQeRuucjH4U9Fs/MobCueRrfIW44W5Xg8m1iCHkzGQqbjeY1DHzuUkmUzIowaJeq5LxJAzJQl4ZTCZX3V6/gjR/tP6sVuGfUlZujx4R1fdMwxuEK+Q2GGIh61QPTN5mGjBdrQA4O4PycdmJ2XW63dmXbVvAHvuj8gErDlJ+aeWkaOIHjktcgEWEVYUw4LpBu86SxbSMrHgBFzg+zqbsGhc9GQFWOi6dmTPOHcTJSQfIwoxeZDG1RkGWQjY+e2CpmPuChdhY
*/