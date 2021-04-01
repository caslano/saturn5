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
mEtewONp/kicuQnkNxnSp7R5QIOnpJdBMJKHYuvlkRtnhxAE+xjAVtO4NFZpNrAlX4KYMP2VoB4/fHWs6n655IdKVYSDCU1VZK8CaEIa+Px07h/wR+cr8BWpbL7Ap6bWadD5H2+JzWH9FQolb1bBZ9pFDm0G1qhjenUlgGqHsiCaR/x0hoMDSvYt9xW0BfXYjvxufo2uremSv06UVlj4wRWnc7naChouYvvRfMq5FrXj7d+IXOGUC/MgKStzMgNp+wpUr7MNAiJkRZGaSosp2niXbET8LFMfVqSiiKjpXIF/DQLpHO4YQJ9fUVmCQAdowBGNrLCmHRDU4jotmXKEjRaFu5e0AZkb24KAJjU9tjNvPV+gZtmCcTg9qOIbPo+IVtA/QplJyih0RNNFgm0Ikfut26engd++ioWr41Mg6HaR92wwXzGqdxDSqB1W5cblawaqcMLkWatrO4+vwqle+t4fo4q0o9hZcKVtACKTEqdzTul+vV2lgzsR7/nIMXcYBJ6BTBfRmomqD0FzS1cZxhm8Y/9MaYQukfdctxKAw+3LsAf3kqWcQ0KjHw==
*/