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
9nxzDPdfU+cPSfl2Ufm8A6Z/PWT9VKzctyHs64zmGub8vDVpXXl2wByFRez6wXczYTBfYQVGVX/C2gqT8SzTakpBxgzmLezJ9Y8HmUswOb/SA9Is2QvDrIW9q5dYks9VMLn/HhWdG8d4wiyEPc1OMuJZrFxz3d2qzPkjMJmfCzY4/oc5qIybUTepAfc7TK5tx05vO7LngzkIi4ubmMhzbJ7hNbt2rc764gqT8+vbbxDjEgaT
*/