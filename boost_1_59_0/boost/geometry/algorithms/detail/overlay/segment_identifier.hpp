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
// It is always used for clockwise indication (even if the original is anticlockwise)
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