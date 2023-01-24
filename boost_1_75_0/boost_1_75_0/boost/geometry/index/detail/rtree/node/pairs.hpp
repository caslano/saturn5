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
oegbZYAYQplhi6TGY7lMator6iRw3kh7RZyAv+qJ0DnqaGmursFBRHzXrnmYb6XB6ZqqdqvYieFeRnuqNgqPLIbPmvqtMsModHnZ7KYEU50g9+Wo32aE/cLPUaCgFf7VmhmeJ/kJdu3GUlm4ZaOO+NUJ5u/SzLdfxtGBjzfl8TmwVLqUrcLc0pcneMT24mnZXI9uRmnwlieZBTFnKGFEvyr9og1jagZ6ZK5MMTz43Jh+ESKAHO1I24r8XFIU2g8e3BM307pm0vQ6U4JVPkEzBB2Fw7AtFD4QWca3ymDXD+/z+sqMtEE4vwyRVNEOe/aw9NcpGyQJ6iv287/BDmP7XZIr5nxVAv9RrIvM2NJ3zmqmUM49VFoERL7GT+2JdGAO6c2idN/8bKMK4qLAxjQIq+ow0A9rvmxyfuUIh2N5hPsZ/DEIc8pu9sQQ7aEM2SXB+yxf0HBU/M0/wRLONcKUdwJqfS0vsgnQ/sn2PRjVFWMOA409pDEkLQ2lNCrecqqBdjGYu/T8R9of0TiIEtNStTEebufeiHiUuR/4phdsITd1kGCWmYQpINh8iTZ2Aqq0HWo6iZqRM6/5zheAq8zPukLDH3Awd9IAklaKKAJ72wxp8GCARfDWSA6wEcJveVep/pwIGjl3BpYs5LuxshCz6iV2m5b8WHBaCCiLbHBaHB0ddR8w3srIzLAfwesoWO5c8ubHi8NZLNNMLLuk
*/