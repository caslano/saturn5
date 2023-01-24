// Boost.Geometry Index
//
// boxes union/sum area/volume
//
// Copyright (c) 2008 Federico J. Fernandez.
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_UNION_CONTENT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_UNION_CONTENT_HPP

#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/index/detail/algorithms/content.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

/**
 * \brief Compute the area of the union of b1 and b2
 */
template <typename Box, typename Geometry>
inline typename default_content_result<Box>::type union_content(Box const& b, Geometry const& g)
{
    Box expanded_box(b);
    geometry::expand(expanded_box, g);
    return detail::content(expanded_box);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_UNION_CONTENT_HPP

/* union_content.hpp
eI9VBkFOrc5Kihceeu+2aFJKepAPfGHKuY8rvf5745F8y6i7w2/fzW0HZBFb3cFVXz3TPwTEOmsn94iQRJnJgLPFvMcTHeaumETlNKrfaKbFBMpxp7yJ899bmNxZ/itLHFSHX8yjE7ouwnPBDF3dyfolMRt0hzTde3uNaMC1sYv/Q//cqSkYFl1jct2S0n9cr76y2tEJ3rzgjoLHt9xxYBpOLcUWLRsuVkp/J15qfubJoRWBtwT4f0iVXdIpaS0nGWIzasvN9BJTJLAtWjDxxX+u1DUlxjk+MTBFpJqGTDJL74Gpt7rM36twkywVvKkkkS2IXQLT+aTyJCYqsOEvet4pI32a8mzgJetUI5gPSgfgFnWuq+UkXx8eFZNPEfOr9cJqxFYgDoqZFPYvLBf+AvYiOI2PeY3q0z3DXbuQ+IgiC9O665MC3GtnpPHaKz8flxERyQGOYv7PniT81hjJdR08yN41/vXf3J3y+/yWCC/9K3y9HPEV3seZyO2113xQoFfsH53PwdiahBWXF+l2HCJkVUBNL1oIHpWIVE+z856EZo8NZ/h4+Kmex4kvbVdMSJGvtGzr7lyRamMb38CVdPhm2duHpHq8x4r8Tv++TuGXueWbw9Gp/u/k2ZKSqUx54iJjXREWjwQ6cFIKDenupg7D3C8n/vPiiAC5R9qBxyvf/Km7PNW3nUzrbR4PwgLAIRyI49bwi7STyux1
*/