// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2019 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_LINE_LINE_INTERSECTION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_LINE_LINE_INTERSECTION_HPP


#include <boost/geometry/arithmetic/infinite_line_functions.hpp>
#include <boost/geometry/algorithms/detail/make/make.hpp>
#include <boost/geometry/strategies/buffer.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{

// TODO: it might once be changed this to proper strategy
struct line_line_intersection
{
    template <typename Point>
    static inline strategy::buffer::join_selector
    apply(Point const& pi, Point const& pj,
          Point const& qi, Point const& qj,
          Point& ip)
    {
        typedef typename coordinate_type<Point>::type ct;
        typedef model::infinite_line<ct> line_type;

        line_type const p = detail::make::make_infinite_line<ct>(pi, pj);
        line_type const q = detail::make::make_infinite_line<ct>(qi, qj);

        if (arithmetic::intersection_point(p, q, ip))
        {
            return strategy::buffer::join_convex;
        }

        // The lines do not intersect.
        // Distinguish between continuing lines (having a similar direction)
        // and spikes (having the opposite direction).
        return arithmetic::similar_direction(p, q)
            ? strategy::buffer::join_continue
            : strategy::buffer::join_spike
            ;
    }
};


}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_LINE_LINE_INTERSECTION_HPP

/* line_line_intersection.hpp
MpUEywQDFG7Q8B+BnhhkYJ+sTeV8NbhQeitEfX41pQjK2EAujKfAcRPeZrcsm6HF4GgGC79CKW2AXC70wVIxRRcccEAI3/wBADXqjS/0hkuuL/BHw4n+hBflzQ2Ot1+lzPpj+fj60tH/YkYkdWVraX/dQipwR3MMMGO5L91SCV3G6RKFldNAtnUk5lKQCDWe3wFEfTT7RJZfTB/+qGZ234aRFzFCVE0FcvEX9FjAmbbndpxc98IxgwexHrno4tLsG8FrZXjqqdjWXS/NUmgQm03iTVvS7pUqklrq6wOuKriTGoeq5VLnsS02DeN9BfH8W6mzMraSroCZtVbeyEwy6PRw9FfdRapa/SSwH3KDAHBFKGEYQyJijKFCEAATvl7JpwTNXjNLRd4fReAOawFfcnTpP1pTidM4aiv9qKC6fOTILkpsSOWubBxXPnz2t73cS1LhRVdFfD8kP9IPopHGVsOXnKcc8LGsvY3P94QT0OsKhid+M2Vzo8dpf3EiILXRQcuFZLipv+HWpG7LUrdaVGOPokeJbDqfpBn57BGVQ6QSVdgBuf90SEGDPg==
*/