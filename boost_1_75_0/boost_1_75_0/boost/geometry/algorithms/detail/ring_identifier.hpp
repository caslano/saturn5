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
+gNdh1s4/umAcDLOeMYAS8b5o4teVNbVFyc2QDw3DIixA/j7RnR6bjdZiStN+a4Kz/dMYnDUDRDrCV0bHoDMLwbwtWGZVUbl6YtUpy61kQMoTkw80wGob1UA9Y33R33TfEgXbdAKjz1H59SLQLRDktULP++BSgv9hXQFhEt04/w0VC03oTfl+yTGg2Qy/yanPwAJwhrbCy6FQapfGkufnkYv8+hlcaED3XcNzW6DC1mqUduJbuTqU4Km/geI+ZBWBMMm9mYT6/dFQeeC+CLRzuHN5AVmbFNAYqnX5INBm4z6BGT+EORt+KJVHJNR38RaK66CQVzFVDgO/CObzouEhH4iE4ggpMKQpWPmnDzTMUdCzuIPubRnyBSpgkTxWApYyfaQbuxSZofCFv7IvZD5WYiv4Q9YhTLLrL0O/JGBDvyRbvwyTobClq3Kq5D5S4iPy4tW2cxW5ZhL/gHGB1G+wHdMJf8P2/a7/pC5I8zLGhh27gdZWN4BxdTiW9suVYdte+FcyDwY5n11b9jZ9dPFXjjQthfewj7nSNj2zacg80dRzzNh5ze/6pLnYrzPiYeSOj6bepsYB9lARCCV3BY2MVi5qpjbGuTf5hwH2bL+pnTMRWI4C0tlVPMmlf6zdy24TdR/GRDrIO223sXHXAN71xbrXeykmqZq70rrM+Bdo9mLypNjLqvLmHvrNtH2HwBBcsLIB0k1x3Xn7ZZj
*/