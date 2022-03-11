// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SEGMENT_IDENTIFIER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SEGMENT_IDENTIFIER_HPP


#if defined(BOOST_GEOMETRY_DEBUG_OVERLAY)
#  define BOOST_GEOMETRY_DEBUG_SEGMENT_IDENTIFIER
#endif

#if defined(BOOST_GEOMETRY_DEBUG_SEGMENT_IDENTIFIER)
#include <iostream>
#endif


#include <boost/geometry/algorithms/detail/signed_size_type.hpp>
#include <boost/geometry/algorithms/detail/ring_identifier.hpp>


namespace boost { namespace geometry
{



// Internal struct to uniquely identify a segment
// on a linestring,ring
// or polygon (needs ring_index)
// or multi-geometry (needs multi_index)
struct segment_identifier
{
    inline segment_identifier()
        : source_index(-1)
        , multi_index(-1)
        , ring_index(-1)
        , segment_index(-1)
        , piece_index(-1)
    {}

    inline segment_identifier(signed_size_type src,
                              signed_size_type mul,
                              signed_size_type rin,
                              signed_size_type seg)
        : source_index(src)
        , multi_index(mul)
        , ring_index(rin)
        , segment_index(seg)
        , piece_index(-1)
    {}

    inline bool operator<(segment_identifier const& other) const
    {
        return source_index != other.source_index ? source_index < other.source_index
            : multi_index !=other.multi_index ? multi_index < other.multi_index
            : ring_index != other.ring_index ? ring_index < other.ring_index
            : piece_index != other.piece_index ? piece_index < other.piece_index
            : segment_index < other.segment_index
            ;
    }

    inline bool operator==(segment_identifier const& other) const
    {
        return source_index == other.source_index
            && segment_index == other.segment_index
            && ring_index == other.ring_index
            && piece_index == other.piece_index
            && multi_index == other.multi_index
            ;
    }

#if defined(BOOST_GEOMETRY_DEBUG_SEGMENT_IDENTIFIER)
    friend std::ostream& operator<<(std::ostream &os, segment_identifier const& seg_id)
    {
        os
            << "s:" << seg_id.source_index
            << ", v:" << seg_id.segment_index // v:vertex because s is used for source
            ;
        if (seg_id.ring_index >= 0) os << ", r:" << seg_id.ring_index;
        if (seg_id.multi_index >= 0) os << ", m:" << seg_id.multi_index;
        if (seg_id.piece_index >= 0) os << ", p:" << seg_id.piece_index;
        return os;
    }
#endif

    signed_size_type source_index;
    signed_size_type multi_index;
    signed_size_type ring_index;
    signed_size_type segment_index;

    // For buffer - todo: move this to buffer-only
    signed_size_type piece_index;
};

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

// Create a ring identifier from a segment identifier
inline ring_identifier ring_id_by_seg_id(segment_identifier const& seg_id)
{
    return ring_identifier(seg_id.source_index, seg_id.multi_index, seg_id.ring_index);
}

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SEGMENT_IDENTIFIER_HPP

/* segment_identifier.hpp
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
*/