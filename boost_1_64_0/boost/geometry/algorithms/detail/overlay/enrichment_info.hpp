// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ENRICHMENT_INFO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ENRICHMENT_INFO_HPP

#include <boost/geometry/algorithms/detail/signed_size_type.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


/*!
\brief Keeps info to enrich intersection info (per source)
\details Class to keep information necessary for traversal phase (a phase
    of the overlay process). The information is gathered during the
    enrichment phase
 */
template<typename Point>
struct enrichment_info
{
    inline enrichment_info()
        : travels_to_vertex_index(-1)
        , travels_to_ip_index(-1)
        , next_ip_index(-1)
        , startable(true)
        , prefer_start(true)
        , count_left(0)
        , count_right(0)
        , rank(-1)
        , zone(-1)
        , region_id(-1)
        , isolated(false)
    {}

    inline signed_size_type get_next_turn_index() const
    {
        return next_ip_index == -1 ? travels_to_ip_index : next_ip_index;
    }

    // vertex to which is free travel after this IP,
    // so from "segment_index+1" to "travels_to_vertex_index", without IP-s,
    // can be -1
    signed_size_type travels_to_vertex_index;

    // same but now IP index, so "next IP index" but not on THIS segment
    signed_size_type travels_to_ip_index;

    // index of next IP on this segment, -1 if there is no one
    signed_size_type next_ip_index;

    bool startable; // Can be used to start in traverse
    bool prefer_start; // Is preferred as starting point (if true)

    // Counts if polygons left/right of this operation
    std::size_t count_left;
    std::size_t count_right;
    signed_size_type rank; // in cluster
    signed_size_type zone; // open zone, in cluster
    signed_size_type region_id;
    bool isolated;
};


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ENRICHMENT_INFO_HPP

/* enrichment_info.hpp
CCGApgBJ6EWpFrA8b4gFLBDwwb7/n7lbEng+1Fe/x/2yc+fMnDlz5syZM/0ma9Bcg9lgMETg5/cbDEUG+WQYzuIxGgyNWhU3MixrsPmSIqNr8yV9R44alzBm7P13jR12b8LwYffdd39uwh13Jox135cw6r4Ex819Eu69f8Sd7Rs2jEnUSazqsG+xv8+y2sDvaNJltcfwHp3y7vGTeD/WCG8Brzj+V/F++/iP4r3k+E94Ozq8i3Cmfbe2bW/CS47vEeHLjp8S75618r1cwL1HDR/JfAJFyM40GEbMshi6dE66JRB22NA6IdbUKMZgizQYZphE2J9bwbEJb57RoPsRFaWniQomjpbCFNFDjXqi4KsuHPIO7RllWNTZYKgdHm14noEl0YaFgmi0YUR6mMy3RRuGxhkMcz+LNKT+QtVsQ/zz4QHZ0Ybapn8fv33unRNz8Z7QKFIwJMoeURcnAWy2HztiWO4wg8EyyogA4NyNdzO8w54M/LWXaIYjdOaiIIPwnhZVH6+k/RiJOLGLLKvBgdeeqNPpjdLxesuyGPrifWH06XjJycNz7jIYLmAlLUE8q2/MGfDGjhs7HH4h4xLEW/Aeeya8O0ffD8RdTYTsUVa8HzwNr4vhf/TZxKe6W+sIQ3Xj8WZD9dfdDYbqY61MhurvZ8BZs8JoqB65Hc7SNIDfvgm8lZ3hS1wEPL8Hzoa/IvZPjyIioQK+/ZfCGbQUYIP34Hz9GJyv+iDsxf5I9uYgOCOvBDj8VqQd3AG+dmPhrP0zIob0AgcxIxAxn5kb3oFzwflwoiLh2O9BxMOt4fvjLUjx2CVw3lwCcEFfRPS5GL6biFz9AKj0XY9YqwLwdfJ37Tyw8fxVwLuV4BNvI2JYf9LbDfArMvnOWjgnSa+wHL6lblC5YRhQ0hQ4L09FhPVeIN+9Dk7zWQC3FcPZaITzBDN/ezKSjX4AsQMeR9otJQAffR/Ooq2U30SE3VQM8DwnwBEfw3nkEYAPMY8C5jYmjfSi4OQUIOzRn+DkkUDFhQi74xhS+J6EbxFrYWcbpJiTD7CqK5xccvBnluP1LcBrs4X8TQW4uBpUoobCKX0O4Bt5iFhhBMo7LPnUBDgTuyBi3s/wDW4Poq89B5THWb/WR+HEXIWIzNnwZTdFRBJT/IX82UnqDZaj4gI4ZQ+ByppI6gtRPENYvw74zrsVeMuWwecfDKf4L8jj3T9TzpT4fsYuvxwRl3wO5w2KONqPtN8/i4grmUflQ0hRngnkTy4AuJKUx6wA2MqCiEGVCCs4n+W9iPqyAQR2xcFnPILY6wl2HA6w9SPwNWwGX+0hhq0BgfdGw+e9BGF9XaRHNRu0EeTbtIPzfAQI1NwOlBZ7Ad7LyrvtA4Atqe0vMo+GTkQMHAwnJRbgJ5RG2kdwXt4D59O3ENapCr7Iy8ygx2Qbf4DvOmbZOA/JrmhOfX4JYTseg3NRH4CpzGgca+vbhqzfdXC+mG7S29ugkfBFUgZDH0WK2ELgdWOdD2Pbuu0zhN1F5NZFiNicCtByHsClr8N59m7g7aXCfXAXnPvZ1A6VIuLOeDhzn0CKVSPhrKdubF+NtFdkUq/eQliHTgjL+h7OnpVIVk4q7Tez/f4EZyZ1cgjD9nWG83YZwIxB8CW9CQKv3A5fr03Au+0yRFzGcoztAcfnRuwHqxHWpwK+Rgks7wHgJTLFcw8CPHQH2HA/hbC8e+CoFOzyJ5EispT2hUQntAReEz/5o74smI8I81+oz2tpD140Iw/apu9ep71ibl8eI71hiF21k/r8JfXlezhPv4bYFeTlsx/hnCQHExcDpXweqHybTn15C46D/H03CbHFJPBTO9YHbcR+NrWjH7M=
*/