// Boost.Geometry Index
//
// R-tree node elements access
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_ELEMENTS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_ELEMENTS_HPP

#include <boost/container/vector.hpp>
#include <boost/geometry/algorithms/detail/expand_by_epsilon.hpp>
#include <boost/geometry/index/detail/varray.hpp>
#include <boost/geometry/index/detail/rtree/node/pairs.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// element's indexable type

template <typename Element, typename Translator>
struct element_indexable_type
{
    typedef typename indexable_type<Translator>::type type;
};

template <typename First, typename Pointer, typename Translator>
struct element_indexable_type<
    rtree::ptr_pair<First, Pointer>,
    Translator
>
{
    typedef First type;
};

// is leaf element

template <typename Element>
struct is_leaf_element
{
    static const bool value = true;
};

template <typename First, typename Pointer>
struct is_leaf_element< rtree::ptr_pair<First, Pointer> >
{
    static const bool value = false;
};

// element's indexable getter

template <typename Element, typename Translator>
typename result_type<Translator>::type
element_indexable(Element const& el, Translator const& tr)
{
    return tr(el);
}

template <typename First, typename Pointer, typename Translator>
First const&
element_indexable(rtree::ptr_pair<First, Pointer> const& el, Translator const& /*tr*/)
{
    return el.first;
}

// nodes elements

template <typename Node>
struct elements_type
{
    typedef typename Node::elements_type type;
};

template <typename Node>
inline typename elements_type<Node>::type &
elements(Node & n)
{
    return n.elements;
}

template <typename Node>
inline typename elements_type<Node>::type const&
elements(Node const& n)
{
    return n.elements;
}

// elements derived type

template <typename Elements, typename NewValue>
struct container_from_elements_type
{
    typedef boost::container::vector<NewValue> type;
};

template <typename OldValue, size_t N, typename NewValue>
struct container_from_elements_type<detail::varray<OldValue, N>, NewValue>
{
    typedef detail::varray<NewValue, N> type;
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_ELEMENTS_HPP

/* node_elements.hpp
p+A38M/wiF5v38L34FEYHD/Xql4ecBk/39P+Yw9sBPfCtvAj2BF+DLvBT2AvuA/2gQfhCPgpPA9+Bi+E+2E+/ByWwy/g1fDvcAk8AFc64fX+RdcQw4Yu9y8jPU69nQ3rwHNgumM34bM1fIZL+AEafiBMhoNgXcdu+ve1Gn6sS/8+CrkkmKfhxmv6E2FDmA9bwAmwOyyAo+FEjb/Q0vWmcJrGHw8v1viXIlcfLoMN4E2wCVwOm8PV8FS4AvaAN8PBcCUcCW+BuXC10Yeu4YQj3O5nLac8scg3g3HwDBiv4bNso/3naRo+ALtq+DWqz9/DDHi7xrMWtoN3hPbDx7nuH9Xr8XGYDLfANvAp2A4+DTvBZ2B3dR+g7kPVXdNhjV70ceVF7ce2w3pqz1D7BXAHHK/2q9W+UO03ql3T4QKKPq48p+k8D+upPUPtF8BtcLzaZ6t9gdoXq13bI2u3orfHIm2Pl8O6cBpMh1fAhrAMtoDlsDucDkerv85XdG0Ufi7zlVu5L7G5BibD22E9uBbWh3fDDHgnbArvggVwHZyk/pPVvUTdy9Vdz7HUtTXaH0WcY3m36nE9bAbvhe3hfbArvB9mwQe1XA/BcXAjzIOb4GT4R3gFfATepPbb4APwTsdu8nNI8/O6S37aIVcbngobwUzNTyfYA3aF82E3uBT2gCvV/U51f1DdH4Hd4fNq3672V9Su9e+sswCTXeo/BbkAbA6bwBbwTLWPga20vbWGl8CWsMCxm3MZl2r8aZi9Eecy0mcYuY3VkCvE7FK5U136t3JtT9NhAF4Ba8ArYTKcAVPhNbAOnAkbwdmwDZwDO6q/aT/6Lvd9l/q6Vtvn9bAxXACbwltgZ7gIZsHfwAK4GE6GN8Jb4FJ4G1wGN6v8VrgS7tR43oY3QR1feXer7cdlfL1Yr5tL4KkwF/aAefBSmA9L4US4CBbBZbAEroSl8A44Cf4BTtZ8TYF/UrknVO4FeCncrnbyh/L1XSD8m+avJizX/JGm6H8xbAmXwPbwt3AovAkOhzfD8+AyOBUuh8/CFfAF9X9V3d9S9z2Ou/Y7+t4IDnfpdyZJVrHDODgVpsNSmAmvhF3hDNgdlsHecB48HV4LB8Lr4SB4HRym9sPwMcxWTX+oztPt9rZB01+l86k1sDm8A7aBd8J2cLPGe5fqYx08F65XvdwPx8J74UXwPngJfBCWwofgM2r/K3wYvqfxfqH+3cnTRtgP2vYBat/vZ17xjSfqGaa5+DFwm7NOl+K2ARNtv/wDxzm7dHfI+aV1BtOPXfXrn2NaPCv6WaZDZ1fdd3/tLzjT9IfZ5lxT1zNNd2MKrz7x2abbB1T/fNPsOcQHM+ms9ww4+bNOn8QcwySeTRyYMdU497TCngDApf9lZ6Bao4lrbuVZAmvm/jrnofZ1ORN1W8i5qInnh589MDvK+aixF1AH8369c1KbYLpixlwbfl7qhpM4M/XYgKjnpp7UmalrQs5NXUX72IrZh/EzSWyBOQtTjlmF2YrZg/kB04LJY1/MxZjZmDWYJzF7MD9g2jCpHIyZgFmIWY/ZjtmH8X/HW23MYEwxZjFmA2Yn5hAm9hjxY4ZiijFLMY9g3sZY3xMWk/X9/89k+P/f///+//f/v////f/v/3//e3//8f3/2Uzs19j/v7uVyNo95x7WZ00ocU7os/NWzude+YhNKyiTb2tySux0p7EwUj4XJtyf7W9p+puzAWR7s5zyvPHFBWpBrhlyLyB3SOIPkXM+tZL1cY2Q2Yym9hsZO91KiXb4T0dun/Gvksmckqn5BZam9yLpZZ7umq8pefmOzHY77+OC8U0ouqygrNykqPHssGXc45k8Q2VeQmavu0w=
*/