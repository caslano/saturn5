// Boost.Geometry Index
//
// n-dimensional Indexable validity check
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_IS_VALID_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_IS_VALID_HPP

#include <cstddef>
#include <boost/geometry/core/access.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

namespace dispatch {

template <typename Box,
          std::size_t Dimension = geometry::dimension<Box>::value>
struct is_valid_box
{
    static inline bool apply(Box const& b)
    {
        return is_valid_box<Box, Dimension - 1>::apply(b) &&
            ( get<min_corner, Dimension - 1>(b) <= get<max_corner, Dimension - 1>(b) );
    }
};

template <typename Box>
struct is_valid_box<Box, 1>
{
    static inline bool apply(Box const& b)
    {
        return get<min_corner, 0>(b) <= get<max_corner, 0>(b);
    }
};

template <typename Indexable,
          typename Tag = typename geometry::tag<Indexable>::type>
struct is_valid
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_INDEXABLE,
        (is_valid));
};

template <typename Indexable>
struct is_valid<Indexable, point_tag>
{
    static inline bool apply(Indexable const&)
    {
        return true;
    }
};

template <typename Indexable>
struct is_valid<Indexable, box_tag>
{
    static inline bool apply(Indexable const& b)
    {
        return dispatch::is_valid_box<Indexable>::apply(b);
    }
};

template <typename Indexable>
struct is_valid<Indexable, segment_tag>
{
    static inline bool apply(Indexable const&)
    {
        return true;
    }
};

} // namespace dispatch

template <typename Indexable>
inline bool is_valid(Indexable const& b)
{
    // CONSIDER: detection of NaNs
    // e.g. by comparison of b with copy of b

    return dispatch::is_valid<Indexable>::apply(b);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_DETAIL_INDEX_ALGORITHMS_IS_VALID_HPP

/* is_valid.hpp
tJVf/UqW89lXh54O6ofZdqDiP39Mgosd/SyEAeF5C2ekyB61pObUPftQnnwmr138PEBpUSDF9AgaVbWEuZKL9dlOTyJfzY5gNiGz/q5AT7Oc1dQAMiS9dmTuIvLJzg2xGpF/F1KD+Fe8pyO5X7lU/oe4/iVH2SafxpY2yjb9uW5+a46xP1j7Zc3V4TCm+lbO7LP/SltnjF930Pm/1EptDdh/akGcdIiLOui9CxHK9slNFHdizlAoFtaMLc+ynvtPAf7cp3k79ah8d202buTSlunkUKY63mIH+T7MTkFVn4Dl2wz87BOOxcPQFvmg3bxV0sNlrxqhtGjj/e8QsDS9tXoEZTH9kKPAbHi6Py1+b8FepkfBu3kFKM6huB65+6iJCpXXXa1JdUbcq0f40btSjiEtZOPXWxoC+lUp1KNrWsm6d9azoMxra8IZG3QqrzpPPs/kTkebn7qrJfHXB96zVHQuq68d6WsLdyviDXWRHm8vs+TFD49p+08wJlzjeit41nk89H2SkbiGTpUdDg+Lh8Dvgr0pJ5TL3/cmgeHzwTMHTG29fHu1XJtKrcPqEqWLQ/RIpK/E9yC0H88nkT6EeyoXRLlGqFaC7bGUAlkXDqbkbQtwOITvbsPn9Tr8HUH/1hJ/rrxSehnn00k746XCPy4bt3/GFxbjw/iQHu5ZoL4L2j/B+YTMkSVP1pYS4D2mcpmG8INOSHtdrNMN
*/