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
px2rgl37vbiUiTgf8CvyUe41b6Vv4hsSgN89HeXb2iTwVliC007kw3d74Bl6xoqeg7aTl/2es4Km1z+PQ/l+fFLSwiPMGrRZOI8ffdm36GPEwy0YyQL6eAn8um25gr5hdY+IqPCK5fXD6rXc94oaoruDB6boKxdmQ39NNtD0+H0Wvpnxpq1YY2WyELrnfK2V0CEfPcc3qHCsaeI8Y+1s6Ien/urqS4qDCD746dm+nh/w8tAiD/CXWTkLfZe/YuHXDjPfnodROP0c010lvoaPCjqz1sgXkXFjnJ0U8f7x6a4yMEWb4BEowWfwMrxB9MG4KAPwNXPRn+v+Q+DpBfTMOPq776UvFTRRyagP5ISYbGz/I73CxFnNgrmw1Vfs5rqfLzR0hhF0wHnN7XmY377xhFiPxT4yfCSvTWsFHec3kdOiwP/vnwUfp9JaM85wXpwH+W96gy7DNHGO8wB8KX/1v+g0MaBBv1ACvdMxDRissQN3eA7a9BdfbEXXoD04wO+dB/yf8juZYx5R8GLt6AuTm0ORKEYbcFe5X7o7Fzgpt5/XzdnNog7iJsp+lOuqX23H2obsgMDjbOdk4/Z1TcyrHooJ3n18zmitWccU5+rY0ADeBbxYf5i5oTMwwpwnMd5xVrV3LvRn/nr27VbLJ2KhAFPPZjWjZc7H/oVVHRs2dHe2d6xrb+rouqezq6Opvk3+6rqHmdWctwo2jO+H
*/