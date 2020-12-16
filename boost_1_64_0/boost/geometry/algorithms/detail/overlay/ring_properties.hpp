// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_RING_PROPERTIES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_RING_PROPERTIES_HPP


#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/within.hpp>
#include <boost/geometry/algorithms/detail/point_on_border.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template <typename Point, typename AreaType>
struct ring_properties
{
    typedef Point point_type;
    typedef AreaType area_type;

    bool valid;

    // Filled by "select_rings"
    Point point;
    area_type area;

    // Filled by "update_ring_selection"
    bool reversed;

    // Filled/used by "assign_rings"
    bool discarded;
    ring_identifier parent;
    area_type parent_area;
    std::vector<ring_identifier> children;

    inline ring_properties()
        : valid(false)
        , area(area_type())
        , reversed(false)
        , discarded(false)
        , parent_area(-1)
    {}

    template <typename RingOrBox, typename AreaStrategy>
    inline ring_properties(RingOrBox const& ring_or_box, AreaStrategy const& strategy)
        : reversed(false)
        , discarded(false)
        , parent_area(-1)
    {
        this->area = geometry::area(ring_or_box, strategy);
        valid = geometry::point_on_border(this->point, ring_or_box);
    }

    inline area_type get_area() const
    {
        return reversed ? -area : area;
    }
};

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_RING_PROPERTIES_HPP

/* ring_properties.hpp
mpTr//2yPVlznRHvBcRTYrjeAcoOnvTWDure/Nfw0k+PRFOVJxvGYsDmq0nmlyga5q37YvwS3f7Q941qn7D3HEUcX43v8B2jo1FsBs+z34nlR6kbyPMn7S+IhauT0tV5FfKyIlMqSo+IczB7hj0m7WeIJoWhELGB6jAhnCqWOLRP0ogso/sCq7raYbnSlNBOGyFF2Ge4Ks9SoG86qHgxg3NjZ/1jAZL8Sv2ANg/xVj4WO+NBOtLJP8ptceEkdySxA7SMh66UOP05xFeVK9l/WQq0draeLLcqKY2rcqTKy+4DKi/3D4/l5fmzdQ6tnglmrBaxYloVDzTcgPqD5x/gyYgDW+U2l7l9B/ASGf0a58Nf95Fds01/fHp5TF78RbMU1J45H/LiVbKlrVPnH0UyXKDjpbD/p+CxDRR5GjyLm8cUUAB//xWAH8r4CK+ab0b+t4181oZ7kzTdPKIBu6O3Udj0g2p/1Cnac8AmEvCBHqVXQsX7i+gK0h4dJmc1hJFcnX5/dCAm+hft2bixRezwQiMSmJkgMlvFflXG7iBj16nYXfXY8agjVNTfJ0V9sE1Uk4zaQUzOKn2HCVGl3/OI8irJglngkKcI5+hHzvst6HoTpdm7X8Qv4Jo/TDJkx1EQyQgNWrxJT/XBm9cQnlreiKnm5HVmNvvZ7P7gi0Qc8OsAv0g6HFvXwjekhMv+OVJj7X/0/c9PFROtsqMatmfjVFb2s/fOMBtS2/9SKTRDrlnNcTS2tmO4LHWOhSYxh6t9d8h6+Vz0/VfxiVljnic4agq+Df6LXZXvG9XUSLOqr3wemw/nnxnnNVPyiHNfrcHIkB9KkBldkR4TEeRGbFouIsPryBygmC6DAU5NNJPw2T4dymPXz9v3qNIewQY/ZK2YkzyAU+93n2QK7ne5oNNyjTxscEE/BG+P9s53FAviVMkKZQSPvhOmGUBshtcggoAvlpVJ60NwKDNCf4Y3jRi1+/TIU9DVP95b4AjgMGQMZAtACI9xUCnUpr6dmT68Yx4OeOCYwugJTcmUrzEOT+2YzJSqpeoBaP94ICF8ROb9TBMyOU/Z1LfLAQ9HzCMTHpleYQB8h3zBR9c69YZihESq+e/u2Hx6LVks2D9cjgZfeGZc/+ZzWOUV1SkaRd//6+nZpU8blmL//5NE+Ounp5D/Twp/JkX4X5LCH04R/mBS+ANntA2/JSl8GUrVpvxJ4eemgD8qKdydIv3JSeHvDklR/h8n1c/QFOVPCq8akqL8SeH1Z6Qof1L4ghbpfQI9xuQStiE2UV3zZed9uv6LgkI+7X5Q0JPZqyaoCYTnmZptiBT2bgYfMqul/tpnp5kN+Tl+GyS8dy75uOVZ5bXqcAcM16r4R/uZdjRJkEnxXCWdWymnsGeWqcNqJe74fqFocIGb7k/D/7RAmutFNfG/KBkjsQ2pT6T7RJfC8vf9tiIaNKyKpIED4kWnDpWpiKQwXzepKZNmLlGGhXJlFk/JHTm50jZp5c4XGjnAjdIVz1/mFTVF5TvsZTciIYED6CWQacV/DExH+e6STgVXj7SXT0ZwJMAJhyRG+YQe9rIR8OKcozwy7WX9CQLnZB3d5Vdn2ct6yM8oP7+fbS+zys9GfBYsGmAvb0QZG2v6+ruICSP6r2+s7msve096Zce9kKgeXi4elc3kyZa9nBxbb0G1/zxvQVXA4hOcjDATKaawB9PJBHo4Yh6Z8MAc5nL4Qh7MY3WeWqecS2qdNin+foMCbwlcJMGXXa7A28soWPH1UDT0VLDNgcsUbKsC6XcDAeAiZRswbRBx+s3dwvuiwN/nnBuaYmt4UdoypesPcMkuM02heMRAFOgFFJc6TjQ6EmSfPRQ=
*/