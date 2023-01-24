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
tbdWeyNrcM+FzY1q+JpNLx9vt2Etp9W5aqyoKAXFdTxKRY7dxqEa49fntffMX7YFf9ke/KUp+Mvz3I93mPNIux31CysjHhKdD6bGhfLh4VGhZQ+l5BlI6QoGrk4XR1HZucqO2LbiaagYHhbXWtwclXtk8bOSvbWXM2qG+iyq+Uc5NcKyaIc7M+vr+oyW0nLWEeuzezdHbM50KS0/XxYJHDfzqD+Vo434WS7XSOJmtFwjiZ+9BvZEal7pvvtkBt7nvm1fKy0Jt9KSaystqbnSkpW291x/NiQtm7RfarV1I+rj82Lnk8Rq94ltiU9sT3yiyXrifk8/bExwn3GxxX1me4pnmpxn1nn6o6Dm/rot9tftsb82xf76vKGV+eZC/orXKs/77r1tnnvbPfeaHHxdAdoprZxiXJH6tg2+xVNVPN3HU1USPbcugBwlS3dI2He9wgtv2mnUS7myrGtjexZEwpbWp6xQSiN77y6U0knl0vr0Sgm41CWoISds/16xLpNWV3i1JKwptfWsI9fx426P3MSEUlt/KrU+4GsJ19LS6wT+GuJ7kATppB4kQ6vBIydL1VP97biytnRd1d+STw7HyVLT86DknKmp1GgyL/SLrf+oX2y9Z7XWjprB1VobvrvbvXd1PWKtVq8N77Va7eHfXHxYq7Vk/7bagJeE4moDVvLuCq0NXYdogm/29QGP8unieKF85TknmuZD6Iu+
*/