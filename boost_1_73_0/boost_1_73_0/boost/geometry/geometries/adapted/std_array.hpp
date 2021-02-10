// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010 Alfredo Correa
// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2016 Norbert Wenzel

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_STD_ARRAY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_STD_ARRAY_HPP


#include <boost/config.hpp>


#ifndef BOOST_NO_CXX11_HDR_ARRAY


#define BOOST_GEOMETRY_ADAPTED_STD_ARRAY_TAG_DEFINED


#include <cstddef>

#include <boost/type_traits/is_arithmetic.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <array>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


// Create class and specialization to indicate the tag
// for normal cases and the case that the type of the std-array is arithmetic
template <bool>
struct std_array_tag
{
    typedef geometry_not_recognized_tag type;
};


template <>
struct std_array_tag<true>
{
    typedef point_tag type;
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


// Assign the point-tag, preventing arrays of points getting a point-tag
template <typename CoordinateType, std::size_t DimensionCount>
struct tag<std::array<CoordinateType, DimensionCount> >
    : detail::std_array_tag<boost::is_arithmetic<CoordinateType>::value> {};


template <typename CoordinateType, std::size_t DimensionCount>
struct coordinate_type<std::array<CoordinateType, DimensionCount> >
{
    typedef CoordinateType type;
};


template <typename CoordinateType, std::size_t DimensionCount>
struct dimension<std::array<CoordinateType, DimensionCount> >: boost::mpl::int_<DimensionCount> {};


template <typename CoordinateType, std::size_t DimensionCount, std::size_t Dimension>
struct access<std::array<CoordinateType, DimensionCount>, Dimension>
{
    static inline CoordinateType get(std::array<CoordinateType, DimensionCount> const& a)
    {
        return a[Dimension];
    }

    static inline void set(std::array<CoordinateType, DimensionCount>& a,
        CoordinateType const& value)
    {
        a[Dimension] = value;
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#define BOOST_GEOMETRY_REGISTER_STD_ARRAY_CS(CoordinateSystem) \
    namespace boost { namespace geometry { namespace traits { \
    template <class T, std::size_t N> \
    struct coordinate_system<std::array<T, N> > \
    { \
        typedef CoordinateSystem type; \
    }; \
    }}}


#else


#warning "This file requires compiler and library support for the ISO C++ 2011 standard."


#endif // BOOST_NO_CXX11_HDR_ARRAY


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_STD_ARRAY_HPP


/* std_array.hpp
Y+sOLh2HPdlmzbYjOuKoobex0XnoiCjs/xCqDLwS8FZCGriDAiR++xOw/r6beuBWoGcAth6cGuAPdbxHtz/w6i2HOLkrtQDaPJj4iHsSaP3c+BL8bJJCbIAy54E7x74CFCF850c/Hh1/OgK+thq69Kx/ivsLXXDSPzV+gcTav+xqVAS5n7mi3ePz94e9XJtC4aeD3f4HJMseusmg9OLQDXBbgRO6x1JwgPswMS7SILTgkiXSEwZffRrAbmQcuJcJ9tBTP+zunw2Oep8kO+TkqfzspLvTk+Xtt2/Nqg/Hn84O9o9kVVtXHfb2+szo9VxXdQ/7zKx6YQE87RtVLw2AQBGz13d2laimqld2Facjr/peV510dwdHB4cK4A+66vwIZ9XblVWvddXxTr97aKDRNsjxoffZmljboMf5yQnYQKPOIAjnq1H3ooFcrq3XcD9UW+dbjhpyeoSMs/qR1hX9XlI/2n4wpY3BJ4dN2xT2IWPf7n9y2tux8P2O+qs9y/yefGDR81Wu5xKjow60Rv+eYKwNwWKAo2w23Ts87vZ7RtMfeFMP6bPWKzTdN5q+ZtT0kpru00qB5QEqMYM9x407AA0/vObLQK0fUh8dKIJFxtcL/iDXl4jLVaIi9fGp+KJ2Tgw4dgF/CDHqp0jT
*/