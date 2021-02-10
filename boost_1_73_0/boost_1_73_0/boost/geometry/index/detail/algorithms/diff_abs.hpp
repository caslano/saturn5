// Boost.Geometry Index
//
// Abs of difference
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_DIFF_ABS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_DIFF_ABS_HPP

namespace boost { namespace geometry { namespace index { namespace detail {

template <typename T>
inline T diff_abs_dispatch(T const& v1, T const& v2, boost::mpl::bool_<true> const& /*is_integral*/)
{
    return v1 < v2 ? v2 - v1 : v1 - v2;
}

template <typename T>
inline T diff_abs_dispatch(T const& v1, T const& v2, boost::mpl::bool_<false> const& /*is_integral*/)
{
    return ::fabs(v1 - v2);
}

template <typename T>
inline T diff_abs(T const& v1, T const& v2)
{
    typedef boost::mpl::bool_<
        boost::is_integral<T>::value
    > is_integral;
    return diff_abs_dispatch(v1, v2, is_integral());
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_DIFF_ABS_HPP

/* diff_abs.hpp
OznZIk4mcpgmPp8dMUN88Wm/qEwm5pfMJhl69oS8zXKFQuXBZ5V7wLrxOq5dZNh/EFj227QWqQ8aEpZPsrillL0OFs0nufkymWK2HU7NTi7jIeqjIIA44esdctph8+Uh1/pv4JTgKKjmriKCecPe9s0oDEkHK0E0A64J6HaxdoWhuI439+OKzCkro2y3SV63gsOIg3ZWpE6V5s/Xaf325IeT4aELFVXi6aFtMXXSb1yQmX0L8Zgv7c0CgEzhq+dtX7VVIuCjiTMGP28vzLCy1sIakvk+JV3g64jqTj2QgQFePMXcFvjh4UESHtiutKYXZxP1rSPVRkB7zkosJdQhysKWAk87fI7RYyYHVeTZzIiwYj/9M9QiTAKWTDNH4WlTIfUKhwXw3iT1VLGYOVUwVU9QycNO42/uIRZi9Hbq0Qh5tExUi6C2R5TfbBxNjrQIXP+xEVTTWhGBrg0VnAGpeWQ+eZHECvhlebgZrtet2BgsRBU6N5zRFo9YC4i4FGrUjZbfJRsEaixjafODVr7j3HxkoeB0QwXy9cBHeTARKOFB07gn9ZhEAaPVo124InjZVpw5jpgkcwpBldlgyudK2fFau8aW9HbEn9ID78paOAY5HslcIADNWYb2j9a5u3ZBrxEcrMgms161CVcm
*/