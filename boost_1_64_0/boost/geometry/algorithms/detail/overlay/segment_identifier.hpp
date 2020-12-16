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
btQdQvupm078JGAWgBi5Fh/F8rwGEwwP75cy3W6f2Gh/rld4zGsjh97Y0WN/qc5rf3TTok7hMQ+NPMF+52qF1xV9BdoekTdHDgkM0HNkaZEji8wR/zdQA3hkv3g8U4t4JhmP/xtcjOeMx7MmxeMX4/F/wwmIp8cxSl9jUrn16PQaWWC/83NwYlCGKpRhtT34Ib4AssFkkftMe9lmk6RXrPay5+FaenBIoJOLbUnEEXNh7m5OMzajJOkgewskbGIa58jP888rmvsZCDTMVx7RHRbgvWItyF1btOeGSsXPpQ6O8NjceSNPtZcxuzFoEEr26TOQL38kTNxlNQdecAs0i9yNuznY8PMXiiaBdqKhIIHuFHxRVYW9vMLMFnYFv4BcwELuacUrWA8y3uMECnOjPpkBHOybiPOeAawOTnnN0lYjKlFsbXgGYcwE8+OSip0St1f0OCDG9MBkMIQkd193/3rZhQJZMn+ohFjOGy5EO7hFPc0dgmkmM62S7WCyrbLLpUjWXybbKu0vjsliMWlqFolO7r+V3TNwUpskn6HdZAq/GJPNGkGK0zAXZ/dvZj8O9GmdAhXXsIaJmpHoWmzlRbWMEtzV15/raqzq6x8kqoN1u9z9q+RooFfgxFhqACKA8iPMaBXDEXlXtr8fomVDfGDtTnf/apWOHnURGryW38FzYajcLRY5Yj0lMkSMGcCDKLYhFhsL9qwj3UIFijrai4x0jn0zDngXqq/QsyJpBmCF8wb/lnn8O7auenJ6NWzG98oPdK3bLIs8uOqyM3FwNVzz4SZmWRcY6QlYsu3R6WUrMh8xoJzGGoKAGm+MRfhAz+sY8BVCmSSKDoeu98guMw4yXv+z7Pi5scXZ/pKzQ1AbhnX/xp7sfw6pjH7pgKZQKZkoEXmR5p8sMUM5Ky08xMhUhmJn/E3lmtZyNmo/683zDPCIClcLDbU2z/5cWhnM0iZmzpEFnK3USF/Uyf7cOCOKU1YV+HDpeTAlnKjFRAqCwCB59CALp6Zdsdon1JTsE5yiFQesTr45hdOfE7M0Kck1AMQv2UtTWOJm2WrrCcHAgootUviJzHMGL1Ot4iSxCK88aeK0UNTQULxLbORGW5v2cTTaMBERVN7K5sHZoohd4pPZ7QMQlijmew15+Bar9Xz9FxLl/0NPYr+gcxmGSf7393V5dSM3BOIg1Gdc4q9FtBBbmF9sg/anMOTPGGmfPGNkkXDi/ASdPzzW6KpcyeNdyoj3NO8wG7D1M2lPdI+bYqO9hch2dZbIg+CVHybL//bguGtogBftHVCqj6TTie78OTZ/J/J55npGRt1hQ4zR84Fn7iEM0wp58E89Vu5P3fnz/mK49cYiYS8SfbxiP2T4eJNAsVes4j0FM7zh8x1FEkC0BCwjW8HMkYHz3CxTHhmtud6CmgAE57aDByhPgSxFYOP5hAluxe3D/jaZ/+kLneIpWBN4uCjUpyhkj66nRrI99D0p640suSq3mOUJ4mfblJW3R7rxjbLFTzuLQesmzJS7Lv12R5Mu/3OTvkPMeGWcldn9/F0UoNb6B3zhUWef/dBAqelVSapOQ+9RirYvl+gi5LDao1/Ys43vBUXc8dR0lLxTmHzuqN9W9fuOkk5VREq4DJOgmhTrZVd4XavYFaVeDTeq92AzLKzTx/NE/yk1jw69UH6p0wMxaiy+MN1dIKxnwcVpsYQ72oXoT5fCfwo8ZkTvfpwo5mqQnrASxwYU+fytssNatc+7StHU+OX3ZyFKw9/lQTDJJkQGHLDUavld7BJv8DsPUh0C4IlrGM8wBfLAXbF2GiZaH9p5gaL2eAyBTukTm4pAiMzDmsb+CUMPRm94Krqm1wHNB4s=
*/