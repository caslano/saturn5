// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2018, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_COMPLEMENT_GRAPH_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_COMPLEMENT_GRAPH_HPP

#ifdef BOOST_GEOMETRY_TEST_DEBUG
#include <iostream>
#endif

#include <boost/geometry/algorithms/detail/is_valid/complement_graph.hpp>

namespace boost { namespace geometry
{

namespace detail { namespace is_valid
{


#ifdef BOOST_GEOMETRY_TEST_DEBUG
template <typename OutputStream, typename TurnPoint, typename CSTag>
inline void
debug_print_complement_graph(OutputStream& os,
                             complement_graph<TurnPoint, CSTag> const& graph)
{
    typedef typename complement_graph<TurnPoint>::vertex_handle vertex_handle;

    os << "num rings: " << graph.m_num_rings << std::endl;
    os << "vertex ids: {";
    for (vertex_handle it = graph.m_vertices.begin();
         it != graph.m_vertices.end(); ++it)
    {
        os << " " << it->id();
    }
    os << " }" << std::endl;        

    for (vertex_handle it = graph.m_vertices.begin();
         it != graph.m_vertices.end(); ++it)
    {
        os << "neighbors of " << it->id() << ": {";
        for (typename complement_graph
                 <
                     TurnPoint
                 >::neighbor_container::const_iterator
                 nit = graph.m_neighbors[it->id()].begin();
             nit != graph.m_neighbors[it->id()].end(); ++nit)
        {
            os << " " << (*nit)->id();
        }
        os << "}" << std::endl;        
    }
}
#else
template <typename OutputStream, typename TurnPoint, typename CSTag>
inline void debug_print_complement_graph(OutputStream&,
                                         complement_graph<TurnPoint, CSTag> const&)
{
}
#endif


}} // namespace detail::is_valid

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_COMPLEMENT_GRAPH_HPP

/* debug_complement_graph.hpp
3Brhj/BwnBczcecA52vlEJruUnIx76zwJOHskWoq+wLDwSjo7VeUK7OoFkOwGCjLXGxOsCRy3LxfBBzbyKH/Jf/CMetfqZwQQ+fK20ewb5zbJqeuPOmdWPudLc94Y/+/imuxs5CmeiBoPMxnKtmpdDQjydr3OcCVEs0tfEM9wz171dSRGb4y7uG6XIyW9y8uqcdtU06c+oZHRJ4a3lV0R4n098FTJK77DuulUnw4PW/zdpnIoWl6++5FfV45n69EXHvPUj1urG1fTXP7Mt+seS4YL3ZKDe/R9XioRXqLoS4PhjexexwfK3N1l5P0+XiJZ4dL9M1XiDz0TLwv/kSRN1OazZPe7VlbkeveaynnTy0w0bjvkrqcdH4G7glf2LaBi7ZNb4PU5xXKrF49bT5eOhNmlQ4X5jq2+4y6PHqGztjus2Sub7sL8l2bPCLzPJt8Tl2eUqfLfa7MJftl3OfJXBpa8XdHZC7Z+oJxYv/KpL1Uqt/oJr23Fl6k2v0AD+njgAeN06T5YhHHzjDvc/we/CPCMLhi3/ZSbO+8u0TzZXA2Zdrz8HLk+dnGBtjyXlmPpzpdLN1XI0+sntyeXleXV5vhfuHqOjx+X9eCecR7u+hNkno87A5Y3a4+GXjVCiqM6fx0lHtrfG+GeLG0sSx4GzZHY0xdnBfnK6UG17mz0v6M1nOl835vgbyYjpa/R4N4b/V4xUyoL0WanxdAhMSz6+Aej/Yj2bXpGMecK+Ljw2s4hzrPNo5r4zhluy6HZ3m1cL5M2vNj4nqnE5e8l+fdnKNqs6BLmQcZE3jvYTx/bwfp/L0Oj+eN+qjbOzmnBF1bGTN7M0z9u0HHbcrItyWaR3yfyKXxa5/+vrV1+MI5bMv9QJwL3xmPej6uGy3Z2Ye6aN+UUUF1nPaVfYR8BUVXqjS+Fq8Kzau7yXOl9fAbMf98w6i7IM64n5C5tCDOuJ+al1ud4/22T/tcWhRnNvoZmefd1/FZgRfmqd/0eQkX0vuixBPS+7LDgzEIXgVm0/uqjHvvmHxd5mnlEu+b9XlVvqb+bc7TjSxSiXMT5yDo3dPxXYcDGo993/fjON5d7n3fD2We9303e7wq7Qfg75z4PHFPwC1d4r5oVAjj/Vzm4SJ9o3tSKlL7+YhzhTG0u9c39PeK/rKL4/X3gP6a8bhvbth/hOXpgpf3vNj2/wbSHEiMpHp74P6W1NCeZHq8swNUmy3lnPblVpGXD+K82zweTdZz3u0ejxTX8PeqHZj+3iX6XvHOEbAJWLGK7pKF8A3d7TUH52fFu8oC0T5+738rdBywDsu6wM4fb//+CJyhPb2pTelkKrUPHobuGehLp6BD2tOPjySy+ac/UxtvQZOXv3JsqlotpwPnjf87GI7ZpO9o6o5hapsDw48FnCofJsz7Fcd1k30b2J73Zlg83bszjKe7TKh/8bneE3TYeHonajnXwfJ4GDRHq18T5700jvmkfNzbyimPGIb21Jr82XuWIAwc/073pXqG8HzAHkjRfXv2VJGDd6At9+PRO5fTzjed6uEQAT97rPFEr5sNnsbpEgdiWe7FwbMghacscPs4Q+No5yosYfflGITjvuT+DOtKw4Pao2mIHN9Mglho7XgeHsRIb2lyXiwfD+JYLP9H1iNGH8/mhDGco/vl8XCu5gGnsC7ult0ajQ/PY0NnSxzMvxhPbRwmgQQbOFvikA3wOLgepPCiLs5BnDrYmD6tD8dwnvZ6joEviIdti+MQ1mAbGIbhqO5u5BiEWWn8xHocD8xXd3/VQhy57vJ4ZJ1RHHLdPRnDz1t3b8c4/LrrxcGzIIWX6+5SDC/W3T9iWLHuNrNwXZS1JLyf4dTdP7fU50E=
*/