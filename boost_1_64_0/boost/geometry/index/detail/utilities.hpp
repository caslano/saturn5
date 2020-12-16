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
J6p45WcG7Al4VbnZKXrzuVGUOWfeUe/W1eMbEG0ueFHYSOO0u5iwiHrB4eGxRniXqfAKaA/+vSuvEi/C855rnOGlzIilCnNAYLr1mYO/V+63egaL+ynafbQ6m+sc6mG4nEdhqCWUYTcqandUMqoXqieqN6oLStwQ/2nqWS/H8l89ex8QJXuXd6vnP8B32+xa7IMLbTp4sqxdLy5Gz5r0KnJmuYOsLrfLHt0ONjWQfR4EGgE7wPeIc9IUaQemjE5bVJwl7foc7L0eilG3a9P9SE+M7EXNUvrDlPwDrDlIMvd82ereJPyOUm4/DbBbrOvlpcpug+jNcOM8CZRLqMd+/iCKOEyjX7blvd6PeY4KI9Rr5HdSLfo+0kveqfRa8m65nBn+1yC+88KX4IU8d/PUqnmXW5Bb6pp34r6ryqNyke3pSnYyUNGyQtzR7mMkHXuV/s6gQu8NfEdqKuZez9nTDfNhnKHawNvTG6rCXSd7OKkH/Iiakm3skVpYytZs/37fV1SYDf1n4Cv9Fbp95s5A77C/eDpul00z7L7yKr12G24rV3VWjIrjGyIrmHNWfg+w7eM2bxTu18eIrEjLyy0pLdHxO6Di00SfS3NY6VcFTfJe48kjD6KknkxTz27HKV2h6pyom4yxgnJ7Q1ATHZ+FRlvUcZqj4jBK18t/Kf0PDnF8iDjiRpu97b0Ad8Rb1TuPHvP5z4a9S7nbhT/02t/r3hDMmgSmt8RfFs8qN/X0PqI96PFJGOh1GH+iHm9RYXytwjCK1C+DHzPckKcXmnmt86aD5I1ZJyS+8uwZ0335F6XDJW6qzvj3NY9Xbsrd6p06H3FzA74bhbE+z7gDKbh/eGgTT+DYRMnYBHEXFy7uGpQ/FN5oSHj9lfNtbs0wU0y3wStbhYfWc3WXg7tPDXdhK0PCg5v4xxXiLkrcrdfPXjnNLaztZliNVv42PLiZLazB6Jug/wI3/0SZfcER/r4x0mf2E3r+hkpZ3LjLLTnXXOVvqJzpWb3cKg+UW2K2DiJXMDPlSv+mk1WYrA+Ptsq27XI+fyYqFDUXdTl+k333mZmRUyd9YGUbq5j1r59yP9szlf9F3kkYDTy2Plz65EnKfhRrnRroPnm1+LH04dKHjlZ2Ez0Dxf1Uv/ta9cPTCGOEcp/qGYKfavYgO5yTQngBe8Higuu+B6eue8Sc9+Ccvr1d+Q0M88p/nN9mY/rWRr8Ke9Ub8909O933UjnvgXLbM1X3PW4zGxrmkfXXhu/a1GzlNXfsO+s3D3a+w30PmvNeMPe9cs57stz3cDnv1XLfy+a8h8t9j57z3i73PWvOew/d93Y5761z36PnvCfObY+Y+x7A7zCX9zgla3fB1qhP9d++sb46w5e/ZX0m8xb+9ZmpVdZn/l7WH+6FzeGLMF70pv/N4r+rg//l4v8i2BZeDDuI3vR/SPwnOvjfJf6fh1FwN4wRPf4Z+co7OYzxuVd/R4v/1gHukmvh7igqVdzxzkp8fPH6QNxdibskeBXsCa+GveFv4EB4PZwHN8BF8Ab4KLwJ/hluhF/Ap+B38BmYIPfjt4W3wo7wTjgA3gUHwbvhULgFjoXbYBl8AFbAB+Hv4EPwbjF/BO6Ez8OH4YfwUXgMbofJpO9xvT5Z3jHkXSVVr0/2r7ONgB1ha9gZjoRd4VzYDWbCLrAIdodXwR7wMZgs6e0t69b6wETYF3aAZ0s87jXH4TLuJx74IX+g8esn9WcQ7AoHw/5wCBwo+tGiT4VDYSkcDtfCEfAWWALvhaXwITgaPgnHwDfhOPiFmHtk/W4InAAj4EQYJfrmom8FJ8E2om8v+l5wFhwHZ8NpcA68AM6Fl8B5cA1Mg9fDC+A=
*/