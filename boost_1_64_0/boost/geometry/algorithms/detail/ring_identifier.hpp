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
ko7hec1zSs142Z5nMZdY0NF4xHBY1f+r6w8bIFgs4VoyQIe3dJaKY/Zo6/+8G8F/XVSY0zTOqstko6AGmGjHqHHKupt2Uw0ROuTXqtljvfi9M0FdXK/+YH05Fh6uTXzyT1QWO29GGLn24wuO2mySRvI3cXLw6AH2TqXS0CMqVSbJ8VMCfoDTW9GefiRVEddY0MClPPgAxFH+qSAQdFEGwlEbdADk61PQFhC4E8NQYmU1AO8FkDHOfLTUvlBn10feWtdHdRmzktNov0r/nRx7RcflJLFQxsXk7TbPl36oGErIKgqbisq7pgFMede3df5+Q7ifg/CJ10SnH+/tGl7+20zkM4m5klXkCIc4HFfreJHeKcqwwNUhKPe36KxclG6E/l21Xd7QYL+blgGCE0FFhrozBV3fdTCCpMamL9FPS7lDjr+lyXKxwJSk1YhubRJiXv59KgYjnsPFLs2g99xVolmxTc0eY8WOy6FPc7Sfz2WxNEudapOIAsPE/fb6QMYfOTJgD06rqDswa/PjleJAkssg96pX/eoMB1Z/I8+F+sz5U0qJlhMVG7yI5A==
*/