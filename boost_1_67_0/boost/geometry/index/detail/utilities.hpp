// Boost.Geometry Index
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/swap.hpp>
//#include <boost/type_traits/is_empty.hpp>

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_UTILITIES_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_UTILITIES_HPP

namespace boost { namespace geometry { namespace index { namespace detail {

template<class T>
static inline void assign_cond(T & l, T const& r, boost::mpl::bool_<true> const&)
{
    l = r;
}

template<class T>
static inline void assign_cond(T &, T const&, boost::mpl::bool_<false> const&) {}

template<class T>
static inline void move_cond(T & l, T & r, boost::mpl::bool_<true> const&)
{
    l = ::boost::move(r);
}

template<class T>
static inline void move_cond(T &, T &, boost::mpl::bool_<false> const&) {}

template <typename T> inline
void swap_cond(T & l, T & r, boost::mpl::bool_<true> const&)
{
    ::boost::swap(l, r);
}

template <typename T> inline
void swap_cond(T &, T &, boost::mpl::bool_<false> const&) {}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_UTILITIES_HPP

/* utilities.hpp
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
*/