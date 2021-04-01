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
F979me2mzUztVYOdJa0famsdJ0JPFUvlO6dT9UipZU+7M0UvZeCsL3VY7wJLnVSkN1wiBaxTO0EEdOuioLQja5VOo0wsG6lEnx2KHGZV9DYE1HF3xJ9zU8K6pR3bFjkoXz6h6ydhqO03krVEw9s+CwRMOqRe4LWHXoScrUSBWqoNQ7JLoAz4WBcoham4dUhmUMDy3GU64mOtBerx2ZEnrDpTzclTFz3YgtF/h4vm64YDDrLN3zNLUMmXSRea6Jfn+yG7uEyNz5W29VgTlh3FE3LkVW7+z1mrwRRPOS9Mgobj5o7vHECKKHlPFYf6gOhs3OjBP0proeOHsWVlhCTce4LHOnhZ2y5fSGBqkzNxeRUVDmsA67ClwcSTbhkWgzsP1yhjHTvokms3zM8dDjcXXRuNE7eFi8g8pB4I8upvBXw6Jda0gH0OFnkn4hAvSJQWSmIx6+VjrWieA/6e36uhTahx6i2+aXN9DLIwMcLlh0qPMSnB/x8h56LvFnT+I9gSJIMv1cbeo3PAcyEA5/GWfGJcjXXcSFyYkgH5qBPFpe04JQ3NzTfd+USGdw==
*/