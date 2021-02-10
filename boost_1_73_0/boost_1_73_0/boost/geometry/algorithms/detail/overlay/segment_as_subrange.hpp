// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2019-2019 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SEGMENT_AS_SUBRANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SEGMENT_AS_SUBRANGE_HPP


#include <cstddef>
#include <map>

#include <boost/geometry/core/access.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Segment>
struct segment_as_subrange
{
    segment_as_subrange(Segment const& s)
        : m_segment(s)
    {
        geometry::set<0>(m_p1, geometry::get<0, 0>(m_segment));
        geometry::set<1>(m_p1, geometry::get<0, 1>(m_segment));
        geometry::set<0>(m_p2, geometry::get<1, 0>(m_segment));
        geometry::set<1>(m_p2, geometry::get<1, 1>(m_segment));
    }

    typedef typename geometry::point_type<Segment>::type point_type;

    point_type const& at(std::size_t index) const
    {
        return index == 0 ? m_p1 : m_p2;
    }

    static inline bool is_last_segment()
    {
        return true;
    }

    point_type m_p1, m_p2;

    Segment const& m_segment;
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SEGMENT_AS_SUBRANGE_HPP

/* segment_as_subrange.hpp
KZWG2sCKovBchJPCHtIWWBzLE/gwlJSxdN5YrayX2uZ6/SqQ6uhZssooEqI6UFCqqcwBKnqhTB1c3/xZ4ljTusDvtuaUbwqtKBk0owXGiyZW3Eob4H4cj6a3Me6j+TyaxEtMfyCaLD3Zr/HkhlovScxA7EojLIkbyHVZSJEeNT9uhY1GS6qkqFKBpu8es8JVZS9vNhpSOQy8i2aHY6XTqk0u3y1lHZKcG3QDbLRM0e1880RZPYWiu+FpvLzyRvNZdDganWSvuCl56DV6+XWjJQqZ4TCw0naNul/048FsPGOjDo0qnLLpUIWo1tY/9ne04b5SBaeOgS52EtjavktKWR74FT1lLyPxzf12wT7428FbxzPqaEFZvDNLvfA/UEsDBAoAAAAIAC1nSlLYh8uNjBwAAHheAAAWAAkAY3VybC1tYXN0ZXIvbGliL2tyYjUuY1VUBQABtkgkYL087XbTSLL/8xSN9xBscEwIsLtDgL2Oo4DPJHbWH8OwDEdXkduOFlnyleSEzMBr3Re4L3arqr8l2fHM7r05HGO3uqurqqvrq6v19DF7Nx53L/tPv2RXL1m+Xq3SrGDzNGNnk0t2wOI0zXl8x66CnM9YmrA0njHo+6IT7rHH8I/10tVdFi2uC9YMW+zZDz+8bOPn
*/