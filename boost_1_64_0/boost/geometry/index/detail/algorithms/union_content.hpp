// Boost.Geometry Index
//
// boxes union/sum area/volume
//
// Copyright (c) 2008 Federico J. Fernandez.
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_UNION_CONTENT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_UNION_CONTENT_HPP

#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/index/detail/algorithms/content.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

/**
 * \brief Compute the area of the union of b1 and b2
 */
template <typename Box, typename Geometry>
inline typename default_content_result<Box>::type union_content(Box const& b, Geometry const& g)
{
    Box expanded_box(b);
    geometry::expand(expanded_box, g);
    return detail::content(expanded_box);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_UNION_CONTENT_HPP

/* union_content.hpp
XM3vYczHN3GjTK8Aj+BufBf34Xv4Ir6Pb+Ex/AhP4M/4OQYwz99gd/wW++BpHIjfGfPlYk4/DktxJv6IuXgGF8p4fV78wr5/qbucZ3pI/1LP8u1AX9if18Jryv2CnNc6lduvMr6w36+ekv3qaVT3j7JfPS/7VZHsV6T18Wm3TO9Xi+PTaJlODEbgZOyDU6T/bSoa83QDjscbcR7G4x2YgKsxEQ9gEr6MM/AtGf6Nmdb1Uvqlfb9bK2l3bS39bm2QcqrP3PGVKse+r8qp43eI9Lst8TTr5U6MxOXSj/Y+DseVOAbvxokyfBreh0m4GmfK8Fn4IOaptLmca3GdpPPxIdwi6R24Affiw/isDN+Pj+Kb+BgexU34MW7Gk7gFv5b8P+BG/Kekf8YC9DCer0cf3I5+Lub4+rgTQ/EJbIm7sT3uwW64F3tJ/n5YiCPxKYyR4ZPwWZwh6Qx8Hm+X9F34Iq7C/fg4HsBt+BI+I/lewIP4kqQP4Wv4Db6O52W4C+vsELqjka6Bb2GopJtLug2+g5EyfKCkh+JRHC3Dx0s6VtL6Oucb+36qVGmnv0n6edKln2qWHK9LVGOiXO/J8VDdp0j5HtIv1AtbY28cgX1wFMbhJIzEBOyLS7Ef3inj78eh+AgOw2dwOP4DR+AJyfc1jsE/cCxWM9rfsDpej3VwIrbCSRiBU7AHTsWBeAOqdzqN+UOmq+tp92n7fpQEqadEqafpstwp5cofOW1/XnxEzov5cl58FANVWh+fOCib5Yssjk+veZuf9waG4t+wDx7GvvgxDse3cSy+gzPxXVyIH+A6/BDXS/7HJf0EHsc9arg5P8Y2WCrzkyXHGeNz6shxppn0I7XBa7ATjsCHcSx2wcnYE2/CXpiO/TEPB/mY638wPoBRuBWH4F4cgUdwNH6OY/ErjMGfcBz+gePR21j/WB8nYHOciJ1xEo7ByZiKUzAL43Ap3oB3S/oeSa+R9KOYiNswCV/EFHwNZ+CbOBM/xfX4PW7As0g9qP08zcfcv9PRB7PQH7OxAc7GhjgHW2MOdsB52BHzMB0X4XxcjKtwCa7HZbgHV+ALuBLfwlX4d7wHS/Fe/BXvw98k7XAz0w3QyNcJ12JPNOY/ElfjCGyLM7Ad3mSO18+7RP5obieJFs+75Es71qNYDx/D7rgJe+I26Q8uwCGSHiHpMbgFp8jwWDOt22eL5XO7W7TP/uJlfu6v2BDPo3q2trrZvvIb6XBJR6i03DcwHd+fzOmmuprTbW1sdy7SnyrHgVexvqSD8HXsgn/DSHwbh+MRnIDvYAq+hyvx7/ggvo/5eAy34j/wKTyOB/AT/BuW4Hv4KX6CJ/Er/BJ/wq/Rx7jew0A8jR3xOzne/YBT8Z+YgWcwF8/i/fgz7sIyfA1/xY/wAn6Hv+M5/AMvoAv9Sl7UjxvWQQ8MRS/sgT44EGvjaPTDJPRH3Q7MBNW/EnFUvj/7VtqVTqMnfof++D2q/70t7e8/Ykf8CTthKXaRtO5PPGffnrNW1uc66ad+SI7HeUZIubVSriZmq1LoZm5Xs7E93oxROFfOe/MwBufjZMzFWFyAmXgr3izpXEkvxBxcjHkyH/lE5M/mfByR+fDD1TIfi8nXDG/HrrgER+MyOe/eidPwLkzE5TgDV2A2rsS5eDcuwlW4Au/BNXgvbsT7cCfej3txqWynD+j+EqLMnM9GFvtjjqzPuVgD52FtnC/r9VYMwAXYUNK6XazMfv09K+vvOVl/z5e7D14l5SZb3Ae/U9v8/HcxGI9iLzyGg/AjHIEf41g8juMkrdt/frE/3zeW832onO+bYKCk9f3UL/btdqXS/vZPrIU/or6f+sW+PnrLfVgfrIY=
*/