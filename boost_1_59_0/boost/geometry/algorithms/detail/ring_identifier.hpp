// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RING_IDENTIFIER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RING_IDENTIFIER_HPP


#if defined(BOOST_GEOMETRY_DEBUG_IDENTIFIER)
#include <iostream>
#endif


#include <boost/geometry/algorithms/detail/signed_size_type.hpp>


namespace boost { namespace geometry
{


// Ring Identifier. It is currently: source,multi,ring
struct ring_identifier
{

    inline ring_identifier()
        : source_index(-1)
        , multi_index(-1)
        , ring_index(-1)
    {}

    inline ring_identifier(signed_size_type src,
                           signed_size_type mul,
                           signed_size_type rin)
        : source_index(src)
        , multi_index(mul)
        , ring_index(rin)
    {}

    inline bool operator<(ring_identifier const& other) const
    {
        return source_index != other.source_index ? source_index < other.source_index
            : multi_index !=other.multi_index ? multi_index < other.multi_index
            : ring_index < other.ring_index
            ;
    }

    inline bool operator==(ring_identifier const& other) const
    {
        return source_index == other.source_index
            && ring_index == other.ring_index
            && multi_index == other.multi_index
            ;
    }

    inline bool operator!=(ring_identifier const& other) const
    {
        return ! operator==(other);
    }

#if defined(BOOST_GEOMETRY_DEBUG_IDENTIFIER)
    friend std::ostream& operator<<(std::ostream &os, ring_identifier const& ring_id)
    {
        os << "(s:" << ring_id.source_index;
        if (ring_id.ring_index >= 0) os << ", r:" << ring_id.ring_index;
        if (ring_id.multi_index >= 0) os << ", m:" << ring_id.multi_index;
        os << ")";
        return os;
    }
#endif


    signed_size_type source_index;
    signed_size_type multi_index;
    signed_size_type ring_index;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RING_IDENTIFIER_HPP

/* ring_identifier.hpp
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
*/