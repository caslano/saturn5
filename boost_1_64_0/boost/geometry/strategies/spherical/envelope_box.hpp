// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2019.
// Modifications copyright (c) 2015-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_BOX_HPP


#include <boost/geometry/strategies/spherical/expand_box.hpp>

#include <boost/geometry/strategies/envelope.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace envelope
{


struct spherical_box
    : geometry::detail::envelope::envelope_box_on_spheroid
{
    typedef spherical_tag cs_tag;

    typedef strategy::expand::spherical_box box_expand_strategy_type;

    static inline box_expand_strategy_type get_box_expand_strategy()
    {
        return box_expand_strategy_type();
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<box_tag, spherical_equatorial_tag, CalculationType>
{
    typedef strategy::envelope::spherical_box type;
};

template <typename CalculationType>
struct default_strategy<box_tag, spherical_polar_tag, CalculationType>
{
    typedef strategy::envelope::spherical_box type;
};

template <typename CalculationType>
struct default_strategy<box_tag, geographic_tag, CalculationType>
{
    typedef strategy::envelope::spherical_box type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_BOX_HPP

/* envelope_box.hpp
ooNahOZaAF2ExGvlpbPyetXctojtr7OLMVLgAv7BMlR2gBhX9/rCzfrEv79m4ygLDqQnoN6Q/XJsehBKwNm8ZEC+qaWshX/yA93vfEwAgucYp3nLQKNZ4rxGRg8oq2W1TLWuohuNb680ewnpawVBz7spRYGzvBJO0EKzS7PczaOnd2F3oHOSjBN1vRB+OjjTtMSOgrx/PunYb4M6H2ryiuLx26sIHkqja/yZJb0xsYXSGGVFU2P3PzB4KaM1laCQ7dQIUmLrWZOAUOepsiVL0UWVRw5IJpcF9s9W2iTyRa8HLHD6N9hKKHx+SdIkLV2vnuB3HyDOB+U9Ca7m8LuUjlu6iYN9kLERkuIeFMUlPAzOx+6CTyvWM9apx0ADWIHUmKLzUodB9JvWlLJpimbFMIu09clbjpf8vI0i+UeXUItpJxwdnmbf3xE8KJJbKrlMpdDLHpLnT5XgZ4aRrNIpX6abSJ66zA4TqDA1RVn89mG1xlcg4GfJEorkd4Wi7LsQa/4WzfIEuPfDumNaoIrBHdTUlUGGEv05b13tKWvSDDoqrBPCsjGiLAzkiw==
*/