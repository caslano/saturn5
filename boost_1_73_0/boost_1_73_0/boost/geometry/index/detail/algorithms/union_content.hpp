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
qDxeqp9xAUvpFZZrxOrFLGY+NfqQmFHeVfyHuX8kBhq/2oRD2DLRAI/RpxA3BoOt5nl6xipOOlKdVTMUp0/dzfOLC86joO6HwjMDEpe9N1kHnTSQXmdWB8A6RE1+KjM2CYqwc1SWpLWRN1xvXpXaoB4VMB6qX5VujeSrHcwwMAZ58+ntlpEgAJYcVaU1j3Sj6J6JLNHaoC889oaP50MNChkJfGY0zuWAS78oE3bk1nvBXr8oWfP13mTBC6tGc3cczz6mDJyFUd3gNRZPBnX9hq9BMmdXMRTzOcuDKIa4N+HurA8rh+gFEWpCiVjuorVM05mOJoSJLp3n9cKooVUhnesFdd4jrHN1YGdLMFozawz7QTpi3BONmvMV886c3ujK4cg+qFB/yJG3LZ/AGlxrIwqVO4hYTMUMQfiLmSohNLxwPS48HcSXBqj7Qaio1EHFrRv1fa5EPMnP2r+6rSu+/r1CHGMxwYcjEu5laBd+FQ0iqH0ieL13jKPbxftEOjbOBlN1LShTl5HQAN2Us7o9gpHf3VP8ph7hc8SI/M8g2draapF6I5H3Uzoi5cYsnafXf/94cpgOcbA9ms9A1sLnUAGYji978ojgw+e2Qm6Nxas37w9fY3Ke5xYcnfUElg9jpPMLHcFqItx8xS9F
*/