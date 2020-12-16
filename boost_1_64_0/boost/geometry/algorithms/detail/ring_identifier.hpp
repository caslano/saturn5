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
ll2DQP5bPfQYXt/3fRHSe4ew5YVsS7zhJGx+CdMh/aBD/YQwyg/roP2U3uBX5ZRsC9nOZtsZ7+Jr/BXVSkbJ0Hvar1J5rdu/a6qDc3Y/Er7zQ3O3lsrH60BPcPkONIVtPqg5DR2fzkzC1l8EvZR1c3VQ1k7QXhxCe4ui/QpobxNvVt0pdUK824judvpJne5A3G0i7pUhcb9KdHepuF9D3Fsi6L+u6O/h/ACNSsd94Lc9gt/9it83QX+d0P2GkLjfIrpvq7jfQdxrImR9V9E/CPqbI/g/pOi/j7DB6/lZA/ui8q2HlW0uVvgfET6Ql2ZcpPzrUUmDuu9KRfOTEJpbFM3jShddh/48hMd2xeMXisbk0Q2K5pchfK5RNE+H8LlZ0TwjaG6g72fF3BKFLc1zqk3HHd2oU/C+uUj3BdUov/KuvOrsfOFvgCM6Wxe8IHAGJtcN/+Bwpr7m/vmfVP/8z9XQR9wV+CLBphF+H9Sf8t1O/avQc6gk8SWh04DaH/uybw/gBkLuXXuF+xLM3/xAr3mWeK9VR903SW8atdMAoI0atLTfp1cw7MN5o9rJSFE7trv5flqZr1u2rL7OHTFaHYbgtvLv1cE9D/+w+ebevvLvJ35LjP9G5qmz4T1c3Ic6Gt/Y70LyMO7s9oJ3Fadw/qfavmWc3Jgw9z9nYeV4G8QA7TkjglV4HQMpB+K97u8IneNS5xCV/bkhbqc8fhMk0Da/i7ruDdG/uCbG/QtrTwpbnODF77dIHyqawmXKytH39g+fwj4m3yQxNqA0u7+yv7LXFIQFf+hAssPHWyMR57/V3G7bsPEB+abD30X5HDUluB77QZYLHiJdhs916k2HmMJfo95YGO3rDTzBmYb+Wr339XlAPtEA73jsL3j8dYxIu3gPp5xoauV9IeIOi3/G7DnwTA98cbH1MTOt/Abvjxk7RfoXbSVSryMzBHNVofMJecSz5xVg894IfZfb+yXc7SISFvO6LAhhM6+FMOZkcQeE3HvzmQPN3CzeqsU868EirTt3MweBMZPVsYTHV/IOAbleP8KrIN7YO8T7SZG3ZHfzU++XTEHdDbysuyc6HM1liPv+lL/GKSznlSYjTLz03hrmKfUZr9bap7KvGXz43QcfnYLxHmhgF3HXAebopvCakqJDP1/MI89UcsPG67ORNgNHWt2b81iP0+e8jEnmTgk/Z3goweUdsyNFPo0vcfGkXQ6nMHwhnL+WQb4wn9OEOJIv0rSAwjn1Vm1vvZ9/oNF6LvTx4Kfxiyg8P3zekd4+tJv5yfH7+Ml7BeW2cDH8sCrwXmAnvRXZzWcwlhDNSPeGIZ8hXSrKXqwAmcH9sq3pTWgvbXnM3oHrLYKcZSzHnqHotLda0QmeVseZW/pQDO+d4zda1PxyehPWcpBu11bXY71hxZR89sT7z1eR1oNdmXnzZtq3t+UduY2Uf1dNCJaBT/g+n60HYp8/IFs/rALc+gB8ezXBZJ1zNIVD+1zvw072nXzItHfKTOG2l+soA5P12vEoexXinZjNEW1Bhe1HpVu7M56488mEcQYeNOWo4y2NbAsA++QUe89Q79q+LJ94sQlbItsOjjD7o4XfTC9efNTCRao9kxBKfzWlcW/Uaaiz9F/0qWU7sbd3EtcnJm4+cejN/nziqPaog+KEt9W7T5vJ27VT1H3dWF8+Lnd+JdvlHV0m7NbGOC/K8TY439dVbMKGKLvHu0vkRUXxqmUtM+i1e6XzEGjk3un845t0r0e6UW7Y/nNy3Ine29fBqzYBCHj2gmetrEvE2mJftr4U97kZRtl9zClhk/I85fZB7sHDnNx+y6PN1p+zY+5OQb9veGyMZYq1dlq7tjzT3Nc=
*/