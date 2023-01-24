// Boost.Geometry Index
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_IS_BOUNDING_GEOMETRY_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_IS_BOUNDING_GEOMETRY_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

template
<
    typename Geometry,
    typename Tag = typename geometry::tag<Geometry>::type
>
struct is_bounding_geometry
{
    static const bool value = false;
};

template <typename Box>
struct is_bounding_geometry<Box, box_tag>
{
    static const bool value = true;
};

}}}} // namespave boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_IS_BOUNDING_GEOMETRY_HPP

/* is_bounding_geometry.hpp
P5lisFDXBRyYUVqoa1of5cwkpesjFupg4UBPYX9xVUDqF2K5TQ4MfK7m8cXeG9cIcxbnkvp4dA30bWQjvo/KkungTLo58Vwe5wlRhHqb+HvZfpzqClGqm9H+Ro6Mxvlsmp10FXdfDqLKF65UpZqn2naUzk40FqGyQV8Nz/zSTu4EmY08mJONS1SRcdEwNb0yHQVOPRfhLhqBr0qJNiZGx0xPPkvhcTkvnc1g1lGQlsQJyCHdKUWAdEF16zW+zHeBxHNEEWWwDcfBCs5KKQYOWL8olxP8MgadVl6ag9K2pmBfBNqpcb4JL4o+KLMzBDC9m7Ay9ORV6rVToQDOGAKCOEOf7OBxM8iZPjebQc6dfvdPxdw7p8JrerSBuEVvfPj3hEcI8gOmFaHKz0sGTK0jR8G0M+uhBuzGU107zyUnD12F/M9cmZQLM/fQx9dn+ipe55WyNS6YRanzdvp6wH9T1WKYgtogBy2lfmRRsI4T/u65+Ix2zP0m08zOOUG/Q4l15kyiybQXo60gUfWfqJ41nHiLUKqunw11WvW71US0ucWgZ7vAuVkjdIhWCHd4QNS8+I8DoUDri4ZbYQ1HD1sdL5zEG8p31vujxNWZhtuqqCCTl2X4LF+K+p9d44tTUaKi+O75lUHhKPwHQfATGH/cyRuS/o7zEmKD+og31GbRfcFis3+hlNpAatzG3gl6smVOP8BhvUYEXAR5NXOK
*/