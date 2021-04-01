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
5RMTvxSEi9cuk2b0verXePjiGLIRZr2GriXkE71dSCdzVALovJVFcmVOZKpbyLhFY64G3SdyPx4+ngkkA4GDXDR2xJeAJ5ihg31W4UJ6m4y5QEIZPpsU905D9wJnAYaSsbZBewVQeuPiyjdGsJvmhjN+KGGr/f0dORIX4P5iewE7mgXlKQDO6UMw4pq/6+MacN1xTlnXYKUy2EmVDWD15Hg3Zs5OgzPZvmfo149pomFq7Bt00Q8oK6/NUg/FCNekUxFzFLc0qQvN6u8mKxsPLANWfiXzH/i1aGxqVYoW4pkdwzJUU/BoFmtvT+wdiucFgSPxOlJOnyg1oYDT4U02AstgYGw7qzsAUmrFw+uqnXMKlwraC1J6XSpJTRzy4cMGoFVqvjlnB9rfVacts7po2Juz5M7W6PZz8h71GJngMec0Wplj2qhm4osIENHmSVKS12VKnpqM5O7wyZ2QLeqHC2wcRWQx6T55atIUlssLHaFUaLlXMjSPUf1WqcJocWYY4fRDQAfbZcsR7Y2ZDKPGOdRsmi2/v9sXghpq0b7nrGYb/WGUG8kvYzyhrg==
*/