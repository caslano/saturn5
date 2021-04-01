// Boost.Geometry

// Copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_AREAL_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/iterators/segment_iterator.hpp>

#include <boost/geometry/algorithms/detail/envelope/range.hpp>
#include <boost/geometry/algorithms/detail/envelope/linear.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{

struct envelope_polygon
{
    template <typename Polygon, typename Box, typename Strategy>
    static inline void apply(Polygon const& polygon, Box& mbr, Strategy const& strategy)
    {
        typename ring_return_type<Polygon const>::type ext_ring
            = exterior_ring(polygon);

        if (geometry::is_empty(ext_ring))
        {
            // if the exterior ring is empty, consider the interior rings
            envelope_multi_range
                <
                    envelope_range
                >::apply(interior_rings(polygon), mbr, strategy);
        }
        else
        {
            // otherwise, consider only the exterior ring
            envelope_range::apply(ext_ring, mbr, strategy);
        }
    }
};


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Ring>
struct envelope<Ring, ring_tag>
    : detail::envelope::envelope_range
{};

template <typename Polygon>
struct envelope<Polygon, polygon_tag>
    : detail::envelope::envelope_polygon
{};

template <typename MultiPolygon>
struct envelope<MultiPolygon, multi_polygon_tag>
    : detail::envelope::envelope_multi_range
        <
            detail::envelope::envelope_polygon
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_AREAL_HPP

/* areal.hpp
KaDgmJDqc3PeUW9YeKX1aphnC24RBfHi/k7+MYQicPiRrOPB+ZOGH7Tpam7uRklZEUg1SX08CwTXYBkedTkYf08lBEbh5JJ06/pyFyF3BGmvPV/RdC1UjkUJmfhXtJHnty7QW5GePdsL3laCIH1FV75WgVuXU/WVJNEdW7UvghHBOnH+LklsRDcCUdqqYjiIMdPwqYFM9qZ3KFI/zmklZu6ZZ6zr/bV+W9S3iGc643p4mQi92v70rKikT56f3SwCdzAK0BOqGZ+PwOzFeXpWtk/N1+XUbvSRJYzsMLuRQajgebAdkB2hevhzfRZMWZ0PNhiuj8iTEPfPZoDmIUbQRW7VGZsO6QiwQLUDR3k5l9XQoSELdIeECn7D0Z7GknY5+4c1zK0bIMzM3Rg3szxBL/sM8Q7d1EOoQbw4ZMiiRzgtZt+u+p+uP3E747G2TliZEAd7i04AwlEsmCdYquvqySI5ZfRajZVu4ee1hTM2kTpBNVenww/zZdnJQCmn5Fi98Nq5ZZEOnZcjYvms85jqIGyA/Qq8TF0MfhGyq8JRJShQPW0H1e3g2D4MxQ==
*/