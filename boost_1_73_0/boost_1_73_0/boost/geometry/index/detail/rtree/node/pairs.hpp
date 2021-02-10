// Boost.Geometry Index
//
// Pairs intended to be used internally in nodes.
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_PAIRS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_PAIRS_HPP

#include <boost/move/move.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

template <typename First, typename Pointer>
class ptr_pair
{
public:
    typedef First first_type;
    typedef Pointer second_type;
    ptr_pair(First const& f, Pointer s) : first(f), second(s) {}
    //ptr_pair(ptr_pair const& p) : first(p.first), second(p.second) {}
    //ptr_pair & operator=(ptr_pair const& p) { first = p.first; second = p.second; return *this; }

    first_type first;
    second_type second;
};

template <typename First, typename Pointer> inline
ptr_pair<First, Pointer>
make_ptr_pair(First const& f, Pointer s)
{
    return ptr_pair<First, Pointer>(f, s);
}

// TODO: It this will be used, rename it to unique_ptr_pair and possibly use unique_ptr.

template <typename First, typename Pointer>
class exclusive_ptr_pair
{
    BOOST_MOVABLE_BUT_NOT_COPYABLE(exclusive_ptr_pair)
public:
    typedef First first_type;
    typedef Pointer second_type;
    exclusive_ptr_pair(First const& f, Pointer s) : first(f), second(s) {}

    // INFO - members aren't really moved!
    exclusive_ptr_pair(BOOST_RV_REF(exclusive_ptr_pair) p) : first(p.first), second(p.second) { p.second = 0; }
    exclusive_ptr_pair & operator=(BOOST_RV_REF(exclusive_ptr_pair) p) { first = p.first; second = p.second; p.second = 0; return *this; }

    first_type first;
    second_type second;
};

template <typename First, typename Pointer> inline
exclusive_ptr_pair<First, Pointer>
make_exclusive_ptr_pair(First const& f, Pointer s)
{
    return exclusive_ptr_pair<First, Pointer>(f, s);
}

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_PAIRS_HPP

/* pairs.hpp
9GQXMIfzRDsPh5XX1nSBrcirMnfsg+Fl5izJG6kzOQeQ9JR6X7g/er24KjOw7yU2dr14vf1u6vO7nVyBRC5XZAtP3lLlVId4ZYdym+gFXxEQfFlU80y7tLNhAyiT9GxJTmUZ+4KdVq6mrWjWhKfDy6gAY+354qxxDLVMbb61EHFkL4uqNABCHLAosQhzhyqIqQyLw87XEE1MQ4B3Hs2Gb0LWgAy96s9oNHtFc+m069DnUXQ6uYzoc3867Y+jK5qcUH98xc4+jcbHOHoNsJLUbVEqB/CSdF5kWiUN5s/79PagfgaGAL31qwLhXAAv0/NSlqvXS50gnSoTcyogS0p7g28Smq8orzKvuzGM4eTG6oQGOH1RFYn0ytn4q/ItBKKCqsMLJd2KDvBStj/cW49N6lLtWNkhr3OFtFgIT7nOMt2h2kDo5BE3Is6ULF8OKxJrdmPfIdEDsHqPgrltg4WY0EG4bFlI72WcitgaY1QI5i7UvScLTmPEfuCGDeiAH7bAEvVCMFjNrc3ucS8ydSuW0iB3W7B3nl60Pae80EbEMsvmMv66M6IB7UZmldqC1u4Za/4NC+5bsUVGhlcQRxOH3dtDdtMIuymNBDBqAYLBYo7vtgNk7VttknGsCg8l638VV0OZK5jVaoAa+Vjq
*/