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
UJ4BsMLCgoqUjWIuwSKEXerfslieIaDYK8J+Dx/Nfj4CFiWs9PDBD1iXFHO2zDzJnggWI6z/ipnbmC+wSGEZXau+43kE85bx/Du4KM+j0YZxaTutby/eJ0x+3qS3J7cyr2Emwm7OTN3NswpmLWzyl8n2XAeYo7BnQ5r9ZA7CYoXd+LmwE/sQmIewtJrFzrEOwuTce57r+jf7ZJiDsM6XQ3px7mNQi+T6lWvWljUSFiqsfmih
*/