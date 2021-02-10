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
bNKd0TsuShT+vV5eb/5pK2dksVWbwiW4HPyHIqyQHWfcoB6b01uZX3S6oU8SpiG2oYqyOVKUoySkJPUO2VXZUnmrbTjVHhFu3E6hkYbwGn+Nqga/pC5dg5AyVwqBV7yU3MBTuhFW4CDkzFVSbhp1q7Dx5bwsqPwEuuFOy/JqESSZWgGJVqBbIjU4Qmilbm+OJV3F+TlRSCM4ARERi1kWgpRXUElXpsCl83wRw27IdYT94Fh7R6jF2jt6EK56BckMJZwW/BMMtHQLgRG0LJzsXasdDfVuQce2/LG1HRk1ThzetvI4bS7MKP6ObB2tMXEre23r0LLg4b9LCXojqSnDlwK3A2wGac5ymrXZ8hRCrUp6UlQjzKuLOuuiSmyxsjvY2mneUSlzLufdoooTJdzKOuehidHZEf0B6yjenhWVLfcVxdvPMhwBf9Vi5UsGsc2aI3TPzTf3h8gqtPzcZaBCfGGPcYJVwqV2DH/Fp8RlrjOQAdA1di5AqIMOOB0PD4z+diE/U1RiudbtB+ga7Z78cvj6Rzd/S1wIvLZ4YPjvzrJG1hAY7fYSOhcQlR916x5/Uz0mysL5V4BBdlX6qKy4LredXuAyW8Y2mYBp95W3wub2aN5ThR6X6ga5o4GtaSlverCX7KQBp4fY3d93
*/