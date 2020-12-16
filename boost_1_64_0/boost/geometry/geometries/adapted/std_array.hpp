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
uo8361A2iT78G6XTayzg7IzsutIXWYz//WHpdAwGIqdV/fU77H1f3USsw2ovZy/uSeW+31Hv4XHWaLptwgS5jR/d+KjoW7iH12texQa/Dcgc5oyLnHlVWVSWz+1k0fxIeaTuY79WeTrjs7JzwHUu0k7Ht1O7cN9zxYf1P4sYVHiVmd6/zxf3wzR+6l/fUy9JDaufap9qxgwzRc/yOe/zc1K+2X2e62p9db/7y0gLf/810Hr/FUizlVoKTva28Fw3RvrUbRd0x7Ov4z3MC4H0N7t8nOusnOUznMhJvVJfluGMDtTvQFxZUMenH04y5StOEa+jfa3MeUv5+sxtu41y2M0Vu3bGLkXGx8PT0JFbuEhiLM0kwecZ3pda91LwsxH3+5AGy09U62aPi9u4zuskbNfZeHNd/WhOl/A8yLHWJ1R65kEuZe8Vb9xHzgfsTD6MJs/bc82brTS1kGSJ+WbMk7ocOX9SKoP5swM/iV3c+fNt5pHdB6/vGp5Hz3PdjAh5VMLfdj5Vu+OvfqLUzp1PGY58mkP4OVz3xZB82o35jK7h+bcP8+yuR86/TEf+xeB+MuLMv6+Th9WuPET3yMOJ3QI+7QDbIud1IM5eeVhSlXtxUWW5L0Jdy3akYUNXwuxmpyGhWfec0LJ3xjO+e3g8t5O3FYeJJ4XtFU/1Ext4L0YcdyOB8pGoBto4ZruC8f/abdzZptdpGuLVRwvN63qvNJRVzY2Qz+o++oj97OHiUqc3mET1kYDMJi4bvOJSxTf4Ap7zTFxYfLnQvO9UPzFhcW1n7BLD+p9iv7E7YjpSXOnQa2uddvYTnSL0E6v1g1drXzDNt5DWxshppero3mwh6Y3y2f5iA2tDHemNNnat1S6Y3hy/sZP6tRLLDOJ1u1W/jvK7V7pHPqS78kF1zYez7PO85EUEfohLO+iHf8Lz9kA+FLLoMlcyo7KGHCguKi0tz13MvhHzljI4u6imqMp7na36TzN7jbwt+j5OVoxz7DGg8w907POeuPk9Y6/KiOOJyip5Zgu8pyavDvWkf0+y7i2LGclG9dCwg3MqNOw+4u8irqX2rMUsX1hS5BxLdxA3J6vu992CLn2ClpvtJ9ex50J7OFTc9fI51mqad0Qni12mlGWKb7bUh8+JbwNyOfXtaM8ttM4QjJYweQePA+e57406cfxcpJOOYa+wnqmrg2VZmb/EuxT5eeUdZan+jzd5eYboAw6Xl+pn7GHzriOcIO7S7faAP4+81LH1WLHLONw5hK6xMP7NHJdU1/N4ML5pkr9223DH0dlOio/X9/7Eo7VFbSf1gbwtZw5Srk4+Chwm6Wg1ZUVVVfnzPc8fVf/tzPPpPaK/5RtJXUm0+uBUroe0QdoiSUgykoK0Q9ojDdSjW5HbOhz5DD17r7xlNcG98mbWhO/DllETvuda75rwPdc6Bc3MnhyJNeH7sPmM2YmiH6h278O21+ijRH/H6CNF32X0EaLvMPpwdMrb0Uac5ba6r9ljwfAU613x4kjlVpZfa5eYLiD2KDf1n93svQorFgfze97i8PzJW+zOn9nozvyZge7Mn6nozvyZhO7Mn/HozvyJD8mfqZo/pVpZhum98ARkvPVeN2L+sItMNV9SywvII80o7zzSMALfgmaJ3RJzVmc7qPbmWbcjdblTanPqsKu8zXPuLNHlGq49JDb117PpdIz4B01j0pLDpnFJeaV7f4E07Yd6ir+9vvH8eyXyTPBbjYaZEpbmNEmzbf8L30TuYd/hTdgGPee5Haa3i12COcu/J/nSAl5Nuy5PDvDzILl/HPlM1ubklXVPWSLXpm9PdefdSn0ZWa7nr0HJu+zaiHlXWSRZ564Tx2veFYk=
*/